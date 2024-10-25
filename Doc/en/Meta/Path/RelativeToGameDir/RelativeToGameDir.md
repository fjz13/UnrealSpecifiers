# RelativeToGameDir

- **Function Description:** If the result of the system directory selection dialog is a subdirectory of the Project, it is converted to a relative path; otherwise, an absolute path is returned.
- **Usage Location:** UPROPERTY
- **Engine Module:** Path Property
- **Metadata Type:** bool
- **Restriction Type:** FFilePath
- **Commonly Used:** ★★★

If the result of the system directory selection dialog is a subdirectory of the Project, it is converted to a relative path; otherwise, an absolute path is returned.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath)
	FFilePath MyFilePath_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (LongPackageName))
	FFilePath MyFilePath_LongPackageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (RelativeToGameDir))
	FFilePath MyFilePath_RelativeToGameDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (FilePathFilter = "umap"))
	FFilePath MyFilePath_FilePathFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (FilePathFilter = "My Config Files|*.ini"))
	FFilePath MyFilePath_FilePathFilter_INI;
```

## Test Results:

- The FFilePath dialog box that pops up is the default file selection dialog of the Windows system.
- MyFilePath_Default, pops up the default system file selection dialog, allowing selection of any file from any path.
- MyFilePath_LongPackageName, restricts the selection to assets under Content; otherwise, an error message will appear. The resulting path will be converted to a long package name format like /Game/ObjectPath.
- MyFilePath_RelativeToGameDir, if the selection result is a subfile of the Project directory (the directory where the uproject file is located), the returned path will be relative; otherwise, an absolute path is returned directly.
- MyFilePath_FilePathFilter, allows selection of files with a specified extension from any directory. The example in the code is umap, which restricts selection to level files only.
- MyFilePath_FilePathFilter_INI, demonstrates the selection of only INI files. The FilePathFilter allows us to write our own filtering method using the format "Description | *.extension," following the same rules as the Windows file selection dialog, and multiple extensions can be specified simultaneously.

![Untitled](Untitled.png)

## Principle:

The processing logic for FilePathFilter, bLongPackageName, and bRelativeToGameDir can be seen in the code below.

- The FileTypeFilter sets the extension in SFilePathPicker
- bLongPackageName triggers the conversion of the path using TryConvertFilenameToLongPackageName.
- bRelativeToGameDir triggers the transformation into a relative path using AbsolutePickedPath.RightChop(AbsoluteProjectDir.Len());.

```cpp
USTRUCT(BlueprintType)
struct FFilePath
{
	GENERATED_BODY()

	/**
	* The path to the file.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath)
	FString FilePath;
};

void FFilePathStructCustomization::CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils )
{
	const FString& MetaData = StructPropertyHandle->GetMetaData(TEXT("FilePathFilter"));
	bLongPackageName = StructPropertyHandle->HasMetaData(TEXT("LongPackageName"));
	bRelativeToGameDir = StructPropertyHandle->HasMetaData(TEXT("RelativeToGameDir"));

	if (MetaData.IsEmpty())
	{
		FileTypeFilter = TEXT("All files (*.*)|*.*");
	}
	else
	{
		if (MetaData.Contains(TEXT("|"))) // If MetaData follows the Description|ExtensionList format, use it as is
		{
			FileTypeFilter = MetaData;
		}
		else
		{
			FileTypeFilter = FString::Printf(TEXT("%s files (*.%s)|*.%s"), *MetaData, *MetaData, *MetaData);
		}
	}
}

void FFilePathStructCustomization::HandleFilePathPickerPathPicked( const FString& PickedPath )
{
	FString FinalPath = PickedPath;
	if (bLongPackageName)
	{
		FString LongPackageName;
		FString StringFailureReason;
		if (FPackageName::TryConvertFilenameToLongPackageName(PickedPath, LongPackageName, &StringFailureReason) == false)
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(StringFailureReason));
		}
		FinalPath = LongPackageName;
	}
	else if (bRelativeToGameDir && !PickedPath.IsEmpty())
	{
		//A filepath under the project directory will be made relative to the project directory
		//Otherwise, the absolute path will be returned unless it doesn't exist, the current path will
		//be kept. This can happen if it's already relative to project dir (tabbing when selected)

		const FString ProjectDir = FPaths::ProjectDir();
		const FString AbsoluteProjectDir = FPaths::ConvertRelativePathToFull(ProjectDir);
		const FString AbsolutePickedPath = FPaths::ConvertRelativePathToFull(PickedPath);

		//Verify if absolute path to file exists. If it was already relative to content directory
		//the absolute will be to binaries and will possibly be garbage
		if (FPaths::FileExists(AbsolutePickedPath))
		{
			//If file is part of the project dir, chop the project dir part
			//Otherwise, use the absolute path
			if (AbsolutePickedPath.StartsWith(AbsoluteProjectDir))
			{
				FinalPath = AbsolutePickedPath.RightChop(AbsoluteProjectDir.Len());
			}
			else
			{
				FinalPath = AbsolutePickedPath;
			}
		}
		else
		{
			//If absolute file doesn't exist, it might already be relative to project dir
			//If not, then it might be a manual entry, so keep it untouched either way
			FinalPath = PickedPath;
		}
	}

	PathStringProperty->SetValue(FinalPath);
	FEditorDirectories::Get().SetLastDirectory(ELastDirectory::GENERIC_OPEN, FPaths::GetPath(PickedPath));
}
```
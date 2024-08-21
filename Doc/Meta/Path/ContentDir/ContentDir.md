# ContentDir

- **功能描述：** 使用UE的风格来选择Content以及子目录。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** bool
- **限制类型：** FDirectoryPath
- **关联项：** [RelativePath](../RelativePath.md), [RelativeToGameContentDir](../RelativeToGameContentDir.md)
- **常用程度：** ★★★

使用UE的风格来选择Content以及子目录。

默认情况下，选择一个目录，会弹出windows默认的选择目录对话框，因为FDirectoryPath 你确实可以用来选择到windows系统里任意的目录（可能你的项目就是这么需求的）。但如果你确实就是想要选择一个UE Content下目录，这个时候你指定ContentDir，UE就可以为你弹出一个专门的UE选择目录对话框，更加的便利也避免出错。

在使用FDirectoryPath的时候，ContentDir和LongPackageName是等价的。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Path :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath)
	FDirectoryPath MyDirectory_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (ContentDir))
	FDirectoryPath MyDirectory_ContentDir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (LongPackageName))
	FDirectoryPath MyDirectory_LongPackageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (RelativeToGameContentDir))
	FDirectoryPath MyDirectory_RelativeToGameContentDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (RelativePath))
	FDirectoryPath MyDirectory_RelativePath;
};

```

## 测试结果：

- 默认的MyDirectory_Default会打开系统对话框，可以选择任何目录。
- MyDirectory_ContentDir和MyDirectory_LongPackageName，会如图所示弹出UE风格的对话框来选择目录。
- MyDirectory_RelativeToGameContentDir和MyDirectory_RelativePath都会弹出系统对话框，不同的是MyDirectory_RelativeToGameContentDir最终的目录会限制在Content目录下（如果选择别的目录，会弹出错误警告），结果是个相对路径。MyDirectory_RelativePath的结果也是个相对路径，但是可以选择任意目录。

![Untitled](Untitled.png)

## 原理：

FDirectoryPath的编辑有FDirectoryPathStructCustomization来定制化。根据其代码可见，如果有ContentDir或LongPackageName，则则是个ContentDir，则会采用OnPickContent来选择目录。内部再用ContentBrowserModule.Get().CreatePathPicker(PathPickerConfig)来创建专门的目录选择菜单。

否则走到OnPickDirectory分支，会采用DesktopPlatform->OpenDirectoryDialog来打开系统的对话框。

从源码也可以看出：

bRelativeToGameContentDir会导致Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);， 把Conent路径的左边部分切掉。

bUseRelativePath会触发Directory = IFileManager::Get().ConvertToRelativePath(*Directory);，把路径转换成相对路径。

```cpp
/** Structure for directory paths that are displayed in the editor with a picker UI. */
USTRUCT(BlueprintType)
struct FDirectoryPath
{
	GENERATED_BODY()

	/**
	* The path to the directory.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Path)
	FString Path;
};

RegisterCustomPropertyTypeLayout("DirectoryPath", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDirectoryPathStructCustomization::MakeInstance));
RegisterCustomPropertyTypeLayout("FilePath", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FFilePathStructCustomization::MakeInstance));
	
void FDirectoryPathStructCustomization::CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils )
{
	TSharedPtr<IPropertyHandle> PathProperty = StructPropertyHandle->GetChildHandle("Path");

	const bool bRelativeToGameContentDir = StructPropertyHandle->HasMetaData( TEXT("RelativeToGameContentDir") );
	const bool bUseRelativePath = StructPropertyHandle->HasMetaData( TEXT("RelativePath") );
	const bool bContentDir = StructPropertyHandle->HasMetaData( TEXT("ContentDir") ) || StructPropertyHandle->HasMetaData(TEXT("LongPackageName"));
	
	AbsoluteGameContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	
	if(bContentDir)
	{
		PickerWidget = SAssignNew(PickerButton, SButton)
		.ButtonStyle( FAppStyle::Get(), "HoverHintOnly" )
		.ToolTipText( LOCTEXT( "FolderComboToolTipText", "Choose a content directory") )
		.OnClicked( this, &FDirectoryPathStructCustomization::OnPickContent, PathProperty.ToSharedRef() )
		.ContentPadding(2.0f)
		.ForegroundColor( FSlateColor::UseForeground() )
		.IsFocusable(false)
		.IsEnabled(this, &FDirectoryPathStructCustomization::IsBrowseEnabled, StructPropertyHandle)
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("PropertyWindow.Button_Ellipsis"))
			.ColorAndOpacity(FSlateColor::UseForeground())
		];
	
	}
	else
	{
		PickerWidget = SAssignNew(BrowseButton, SButton)
		.ButtonStyle( FAppStyle::Get(), "HoverHintOnly" )
		.ToolTipText( LOCTEXT( "FolderButtonToolTipText", "Choose a directory from this computer") )
		.OnClicked( this, &FDirectoryPathStructCustomization::OnPickDirectory, PathProperty.ToSharedRef(), bRelativeToGameContentDir, bUseRelativePath )
		.ContentPadding( 2.0f )
		.ForegroundColor( FSlateColor::UseForeground() )
		.IsFocusable( false )
		.IsEnabled( this, &FDirectoryPathStructCustomization::IsBrowseEnabled, StructPropertyHandle )
		[
			SNew( SImage )
			.Image( FAppStyle::GetBrush("PropertyWindow.Button_Ellipsis") )
			.ColorAndOpacity( FSlateColor::UseForeground() )
		];
	}
}

FReply FDirectoryPathStructCustomization::OnPickContent(TSharedRef<IPropertyHandle> PropertyHandle) 
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FPathPickerConfig PathPickerConfig;
	PropertyHandle->GetValue(PathPickerConfig.DefaultPath);
	PathPickerConfig.bAllowContextMenu = false;
	PathPickerConfig.OnPathSelected = FOnPathSelected::CreateSP(this, &FDirectoryPathStructCustomization::OnPathPicked, PropertyHandle);

	FMenuBuilder MenuBuilder(true, NULL);
	MenuBuilder.AddWidget(SNew(SBox)
		.WidthOverride(300.0f)
		.HeightOverride(300.0f)
		[
			ContentBrowserModule.Get().CreatePathPicker(PathPickerConfig)
		], FText());

	PickerMenu = FSlateApplication::Get().PushMenu(PickerButton.ToSharedRef(),
		FWidgetPath(),
		MenuBuilder.MakeWidget(),
		FSlateApplication::Get().GetCursorPos(),
		FPopupTransitionEffect(FPopupTransitionEffect::ContextMenu)
		);

	return FReply::Handled();
}

FReply FDirectoryPathStructCustomization::OnPickDirectory(TSharedRef<IPropertyHandle> PropertyHandle, const bool bRelativeToGameContentDir, const bool bUseRelativePath) const
{
	FString Directory;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{

		TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(BrowseButton.ToSharedRef());
		void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

		FString StartDirectory = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);
		if (bRelativeToGameContentDir && !IsValidPath(StartDirectory, bRelativeToGameContentDir))
		{
			StartDirectory = AbsoluteGameContentDir;
		}

		// Loop until; a) the user cancels (OpenDirectoryDialog returns false), or, b) the chosen path is valid (IsValidPath returns true)
		for (;;)
		{
			if (DesktopPlatform->OpenDirectoryDialog(ParentWindowHandle, LOCTEXT("FolderDialogTitle", "Choose a directory").ToString(), StartDirectory, Directory))
			{
				FText FailureReason;
				if (IsValidPath(Directory, bRelativeToGameContentDir, &FailureReason))
				{
					FEditorDirectories::Get().SetLastDirectory(ELastDirectory::GENERIC_IMPORT, Directory);

					if (bRelativeToGameContentDir)
					{
						Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);
					}
					else if (bUseRelativePath)
					{
						Directory = IFileManager::Get().ConvertToRelativePath(*Directory);
					}

					PropertyHandle->SetValue(Directory);
				}
				else
				{
					StartDirectory = Directory;
					FMessageDialog::Open(EAppMsgType::Ok, FailureReason);
					continue;
				}
			}
			break;
		}
	}

	return FReply::Handled();
}

```

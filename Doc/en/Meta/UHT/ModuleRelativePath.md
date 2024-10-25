# ModuleRelativePath

- **Function Description:** Records the header file path for type definitions, representing the relative path within the module.
- **Usage Location:** Any
- **Engine Module:** UHT
- **Metadata Type:** string="abc"
- **Commonality Level:** 0

Records the header file path for the current metadata type definition, which is the relative path within the module.

Generally not managed by developers, but the engine editor uses it to locate where a type is defined in a .h file, allowing the corresponding header file to be opened in Visual Studio when the type is double-clicked. The specific logic can be found in FSourceCodeNavigation.

The difference from IncludePath is that ModuleRelativePath is present on various type information, while IncludePath is used only for UCLASS. Additionally, the value of ModuleRelativePath can begin with "Classes/Public/Internal/Private", and we typically recommend organizing .h and .cpp files into these four directories. The value of IncludeFilePath, however, will exclude this prefix.

## Test Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Template :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	int32 MyFunc(FString str){return 0;}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;
};
```

## Metadata type information printout:

It can be observed that ModuleRelativePath is present on classes, properties, and functions.

IncludePath is only present on UCLASS.

```cpp
[class MyProperty_Template	Class->Struct->Field->Object	/Script/Insider.MyProperty_Template]
(BlueprintType = true, IncludePath = Property/MyProperty_Template.h, ModuleRelativePath = Property/MyProperty_Template.h)
	ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
	Outer:	Package /Script/Insider
	ClassHierarchy:	MyProperty_Template:Object
	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
	Size:	56
	Within:	Object
	ClassConfigName:	Engine
{
	(Category = MyProperty_Template, ModuleRelativePath = Property/MyProperty_Template.h)
	48-[4] int32 MyProperty;
		PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
		ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient
		Outer:	Class /Script/Insider.MyProperty_Template
		Path:	IntProperty /Script/Insider.MyProperty_Template:MyProperty
	[func MyFunc	Function->Struct->Field->Object	/Script/Insider.MyProperty_Template:MyFunc]
	(ModuleRelativePath = Property/MyProperty_Template.h)
		ObjectFlags:	RF_Public | RF_Transient
		Outer:	Class /Script/Insider.MyProperty_Template
		FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
		NumParms:	2
		ParmsSize:	20
		ReturnValueOffset:	16
		RPCId:	0
		RPCResponseId:	0
		public int32 MyFunc(FString str)final;
	{
		0-[16] FString str;
			PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
			ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient
			Outer:	Function /Script/Insider.MyProperty_Template:MyFunc
			Path:	StrProperty /Script/Insider.MyProperty_Template:MyFunc:str
		16-[4] int32 ReturnValue;
			PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReturnParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
			ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient
			Outer:	Function /Script/Insider.MyProperty_Template:MyFunc
			Path:	IntProperty /Script/Insider.MyProperty_Template:MyFunc:ReturnValue
	};
};

```

## Principle:

During UHT analysis, the type is automatically annotated with the header file path information.

As seen in the source code logic, the value of ModuleRelativePath can begin with "Classes/Public/Internal/Private", and we generally suggest organizing .h and .cpp files into these four folders. The value of IncludeFilePath, on the other hand, will not include this prefix.

```cpp

public enum UhtHeaderFileType
{

	/// <summary>
	/// Classes folder
	/// </summary>
	Classes,

	/// <summary>
	/// Public folder
	/// </summary>
	Public,

	/// <summary>
	/// Internal folder
	/// </summary>
	Internal,

	/// <summary>
	/// Private folder
	/// </summary>
	Private,
}

public static void AddModuleRelativePathToMetaData(UhtMetaData metaData, UhtHeaderFile headerFile)
{
	metaData.Add(UhtNames.ModuleRelativePath, headerFile.ModuleRelativeFilePath);
}

//Analyze file path
private void StepPrepareHeaders(UhtPackage package, IEnumerable<string> headerFiles, UhtHeaderFileType headerFileType)
{
	string typeDirectory = headerFileType.ToString() + '/';

	headerFile.ModuleRelativeFilePath = normalizedFullFilePath[stripLength..];
	if (normalizedFullFilePath[stripLength..].StartsWith(typeDirectory, true, null))
	{
					stripLength += typeDirectory.Length;
	}
	headerFile.IncludeFilePath = normalizedFullFilePath[stripLength..];
}

```
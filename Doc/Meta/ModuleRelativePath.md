# ModuleRelativePath

Description: 记录类型定义的的头文件路径，为其处于模块的内部相对路径。
Usage: Any
Feature: UHT
Group: UHT
Type: string="abc"
Status: Done

记录当前元类型定义的的头文件路径，为相对模块的相对路径。

对于开发者来说一般不用管，但是引擎编辑器会用它来定位某个类型是在哪个.h里定义的，从而在你双击类型的时候，可以为你在VS里打开相应的头文件。具体的逻辑可以去FSourceCodeNavigation里查看。

和IncludePath的区别是，ModuleRelativePath 在各种类型信息上都有，而IncludePath只用于UCLASS上。另外ModuleRelativePath 的值可以包含“Classes/Public/Internal/Private”这4个以开头，我们一般也确实会建议把.h.cpp划分到这4个文件夹里。而IncludeFilePath 的值就会去掉这个头。

测试代码：

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

其元类型信息打印：

可以发现ModuleRelativePath 在类，属性和函数上都有该信息。

而IncludePath只有在UCLASS上才有。

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

原理：

在UHT分析的时候，自动的为类型加上头文件的路径信息。

从源码逻辑可以看出，ModuleRelativePath 的值可以包含“Classes/Public/Internal/Private”这4个以开头，我们一般也确实会建议把.h.cpp划分到这4个文件夹里。而IncludeFilePath 的值就会去掉这个头。

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

//分析文件路径
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
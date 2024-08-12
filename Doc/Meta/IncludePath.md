# IncludePath

Description: 记录UClass的引用路径
Usage: UCLASS
Feature: UHT
Group: UHT
Type: string="abc"
LimitedType: UCLASS上的信息
Status: Done

记录UClass的引用路径。

开发者一般也不用管这个值。

有一个作用是在UHT生成.gen.cpp的时候，在头文件部分方便引用到该类的头文件。

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

其类型信息：

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

同样也是在UHT中分析后添加的。具体的逻辑值请见ModuleRelativePath中的原理代码部分。

```cpp
protected override void UhtClass::ResolveSuper(UhtResolvePhase resolvePhase)
{
	switch (ClassType)
	{
				case UhtClassType.Class:
					{
							MetaData.Add(UhtNames.IncludePath, HeaderFile.IncludeFilePath);
					}
	}
}

```
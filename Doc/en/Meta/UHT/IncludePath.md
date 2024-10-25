# Include Path

- **Function Description:** Records the reference path for a UClass
- **Usage Location:** UCLASS
- **Engine Module:** UHT
- **Metadata Type:** string="abc"
- **Restriction Type:** Information related to UCLASS
- **Commonality:** 0

Records the reference path for a UClass.

Developers typically do not need to concern themselves with this value.

One of its uses is to facilitate the inclusion of the class header file during the generation of .gen.cpp by UHT in the header file section.

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

## Its Type Information:

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

The value is also added after analysis in UHT. For the specific logic, refer to the principle code section within ModuleRelativePath.

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
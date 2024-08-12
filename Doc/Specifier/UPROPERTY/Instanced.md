# Instanced

Type: bool
Feature: Behavior
LimitedType: UObject*
Description: 为对象属性创建一个实例，并作为子对象。
和类DefaultToInstanced配合。用在对象引用属性上。
在本对象创建的时候，会创建一个对象copy赋值给该对象引用属性，用做子对象。
隐含了EditInline and Export.
EPropertyFlags: CPF_PersistentInstance (../../Flags/EPropertyFlags/CPF_PersistentInstance.md), CPF_ExportObject (../../Flags/EPropertyFlags/CPF_ExportObject.md), CPF_InstancedReference (../../Flags/EPropertyFlags/CPF_InstancedReference.md)
MetaOperation: =true
Meta: EditInline (../../Meta/Meta/EditInline.md)
Status: Done

在Object*属性上设置值的时候，如果不标Instanced，则只能为其设置一个对象引用。而如果想在编辑器里为其真正的创建一个对象实例并赋予给这个属性，则需要加上Instanced标记。但光有Instanced还不够，这个Class还需要加上EditInlineNew，才能让该类出现在可新创建类实例的列表里。

但是仍然要注意，在C++里手动设置对象给这个属性的话还是都可以的。也要注意和UCLASS(DefaultToInstanced)区分，DefaultToInstanced是表明这个类的所有属性都默认的加上Instanced的意思，避免了对该类的所有属性每次都要手动设置。

```cpp
UCLASS(Blueprintable, BlueprintType,editinlinenew)
class INSIDER_API UMyProperty_InstancedObject :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyValue = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Instanced :public UObject
{
public:
	GENERATED_BODY()
		UMyProperty_Instanced(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_InstancedReference | CPF_NoDestructor | CPF_PersistentInstance | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = Behavior)
		UMyProperty_InstancedObject* ObjectInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UMyProperty_InstancedObject* Object;
};
```

蓝图中测试：

![Untitled](Instanced/Untitled.png)
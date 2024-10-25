# Instanced

- **Function Description:** Specifies that editing assignments to the properties of this object should create a new instance as a child object, rather than searching for an existing object reference.
- **Metadata Type:** bool
- **Engine Module:** Instance
- **Restriction Type:** UObject*
- **Functionality Mechanism:** Include [CPF_PersistentInstance](../../../../Flags/EPropertyFlags/CPF_PersistentInstance.md), [CPF_ExportObject](../../../../Flags/EPropertyFlags/CPF_ExportObject.md), [CPF_InstancedReference](../../../../Flags/EPropertyFlags/CPF_InstancedReference.md) in PropertyFlags, and [EditInline](../../../../Meta/DetailsPanel/EditInline/EditInline.md) in Meta
- **Commonly Used:** ★★★

Specifies that editing assignments to the properties of this object should create a new instance as a child object, rather than searching for an existing object reference.

- The effect of Instanced on a single attribute and DefaultToInstanced on UCLASS are somewhat similar, with the difference being that the former applies only to individual attributes, while the latter applies to all attributes of the class type.
- Often used in conjunction with EditInlineNew, allowing new instances to be created and edited for object properties within the details panel.
- Instanced implies EditInline and Export capabilities.

When setting a value for an Object* attribute, if not marked with Instanced, only an object reference can be assigned. To create an actual object instance in the editor and assign it to the attribute, the Instanced marker must be added. However, Instanced alone is insufficient; the class also needs to include EditInlineNew to appear in the list of classes that can create new instances.

Of course, manually setting an object to this attribute in C++ is still possible. It is important to distinguish this from UCLASS(DefaultToInstanced), which indicates that all attributes of this class are Instanced by default, thus avoiding the need to manually set each attribute every time.

## Sample Code:

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

## Example Effect:

It is evident that the editing dialog boxes for ObjectInstanced and Object are different.

![Untitled](Untitled.png)
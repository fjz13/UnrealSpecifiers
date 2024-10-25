# Export

- **Function description:** Determines that when exporting an Asset, the object of this class should export its internal attribute values rather than the object's path.
- **Metadata type:** bool
- **Engine module:** Serialization
- **Restriction type:** Object property, or an array of Objects
- **Mechanism of action:** Include [CPF_ExportObject](../../../../Flags/EPropertyFlags/CPF_ExportObject.md) in PropertyFlags
- **Frequency of use:** ★

When exporting an Asset, it is determined that the object of this class should export its internal attribute values rather than the object's path.

- When an Object is copied (e.g., during copy/paste operations), the Object assigned to this property should be exported as a complete sub-Object block (as seen in the examples below, this actually means also exporting the values of the internal attributes), rather than just exporting the Object reference itself.
- Applies exclusively to Object properties (or arrays of Objects), as it is used for object exports.
- Effectively, it's the difference between shallow and deep copying. Without the Export mark, it's a shallow copy, only outputting the object path. With the Export mark, it's a deep copy, also outputting the object's internal attributes.

## Sample Code:

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ExportObject :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyValue = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Export :public UDataAsset
{
public:
public:
	GENERATED_BODY()
		UMyProperty_Export(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Export, Category = Behavior)
		UMyProperty_ExportObject* ObjectExport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UMyProperty_ExportObject* ObjectWithoutExport;
};
```

Configured Object Value:

![Untitled](Untitled.png)

Primarily used during export operations to determine how to export the content of an Object* attribute. NoExport will only output the object reference path, while Export will output the internal attribute values of the object.

![Untitled](Untitled%201.png)

Exported Text:

```jsx
Begin Object Class=/Script/Insider.MyProperty_Export Name="MyPropertyExportAsset" ExportPath=/Script/Insider.MyProperty_Export'"/Game/Property/MyPropertyExportAsset.MyPropertyExportAsset"'
   Begin Object Class=/Script/Insider.MyProperty_ExportObject Name="EO1" ExportPath=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO1.EO1"'
      "MyValue"=456
   End Object
   "ObjectExport"=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO1.EO1"'
   "ObjectWithoutExport"=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO2.EO2"'
End Object
```

You can see that objects with ObjectExport also export field values, whereas objects with ObjectWithoutExport only export paths.

## Principle:

In the source code, the function in question must be noted: for the Export tag to take effect in ExportProperties, the export tag cannot be applied to the sub-objects of the main object, or it will follow the ExportInnerObjects call route. In the example above, both ObjectExport and ObjectWithoutExport point to another external object, thus DataAsset is used to generate the assets.

```cpp
void ExportProperties()
{
	FObjectPropertyBase* ExportObjectProp = (Property->PropertyFlags & CPF_ExportObject) != 0 ? CastField<FObjectPropertyBase>(Property) : NULL;
}
```
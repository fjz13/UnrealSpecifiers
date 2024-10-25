# CustomFieldNotify

- **Function description:** Prevent UHT from generating the FieldNotify-related code for this class.

- **Engine module:** UHT
- **Metadata type:** bool
- **Action mechanism:** Add [HasCustomFieldNotify](../../../Flags/EClassFlags/HasCustomFieldNotify.md) to ClassFlags
- **Usage frequency:** 0

Prevent UHT from generating FieldNotify-related code for this class.

Used only in the source code for UWidget, for instance, the bIsEnabled field in this class is marked with FieldNotify. Normally, UHT would generate code for it. However, if the class wishes to manually write the UHT code, CustomFieldNotify can be added to prevent UHT from generating the code. In UWidget's .cpp file, because it needs to use the UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR method, it must reject UHT generation.

If your class also requires manual implementation of UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR, you can use CustomFieldNotify.

## Source code example:

```cpp
//E:\P4V\Engine\Source\Runtime\UMG\Public\FieldNotification\FieldNotificationDeclaration.h
UCLASS(Abstract, BlueprintType, Blueprintable, CustomFieldNotify)
class UMG_API UWidget : public UVisual, public INotifyFieldValueChanged
{
	GENERATED_UCLASS_BODY()
public:
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_BEGIN(UMG_API)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(ToolTipText)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(Visibility)
		UE_FIELD_NOTIFICATION_DECLARE_FIELD(bIsEnabled)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_BEGIN(ToolTipText)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(Visibility)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(bIsEnabled)
		UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_END()
	UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_END();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter="GetIsEnabled", Setter="SetIsEnabled", BlueprintGetter="GetIsEnabled", BlueprintSetter="SetIsEnabled", Category="Behavior")
	uint8 bIsEnabled:1;

	//cpp
UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_ThreeFields(UWidget, ToolTipText, Visibility, bIsEnabled);

```

## Principle:

The condition for checking includes the presence of HasCustomFieldNotify.

```cpp
		protected static bool NeedFieldNotifyCodeGen(UhtClass classObj)
		{
			return
				!classObj.ClassExportFlags.HasAnyFlags(UhtClassExportFlags.HasCustomFieldNotify) &&
				classObj.ClassExportFlags.HasAnyFlags(UhtClassExportFlags.HasFieldNotify);
		}

```
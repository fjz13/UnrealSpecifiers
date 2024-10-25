# AlwaysAsPin

- **功能描述：** 在动画蓝图中使得动画节点的某个属性总是暴露出来成为引脚
- **使用位置：** UPROPERTY
- **引擎模块：** Pin
- **元数据类型：** bool
- **限制类型：** FAnimNode_Base
- **关联项：** [PinShownByDefault](../PinShownByDefault/PinShownByDefault.md)
- **常用程度：** ★★★

和PinShownByDefault的区别是前者会导致只能一直显示为引脚。而PinShownByDefault默认显示为引脚，当也之后也可以改变。

## 测试代码：

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct INSIDEREDITOR_API FAnimNode_MyTestPinShown : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest)
	int32 MyInt_NotShown = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (PinShownByDefault))
	int32 MyInt_PinShownByDefault = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (AlwaysAsPin))
	int32 MyInt_AlwaysAsPin = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (NeverAsPin))
	int32 MyInt_NeverAsPin = 123;
};
```

## 测试效果：

![PinShown](PinShown.gif)

## 原理：

根据源码的里的逻辑可见，bAlwaysShow 会导致bShowPin，和PinShownByDefault的区别是前者会导致只能一直显示为引脚。而PinShownByDefault默认显示为引脚，当也之后也可以改变。

```cpp
void FAnimBlueprintNodeOptionalPinManager::GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();

	// Determine if this is a pose or array of poses
	FArrayProperty* ArrayProp = CastField<FArrayProperty>(TestProperty);
	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp ? ArrayProp->Inner : TestProperty);
	const bool bIsPoseInput = (StructProp  && StructProp->Struct->IsChildOf(FPoseLinkBase::StaticStruct()));

	//@TODO: Error if they specified two or more of these flags
	const bool bAlwaysShow = TestProperty->HasMetaData(Schema->NAME_AlwaysAsPin) || bIsPoseInput;
	const bool bOptional_ShowByDefault = TestProperty->HasMetaData(Schema->NAME_PinShownByDefault);
	const bool bOptional_HideByDefault = TestProperty->HasMetaData(Schema->NAME_PinHiddenByDefault);
	const bool bNeverShow = TestProperty->HasMetaData(Schema->NAME_NeverAsPin);
	const bool bPropertyIsCustomized = TestProperty->HasMetaData(Schema->NAME_CustomizeProperty);
	const bool bCanTreatPropertyAsOptional = CanTreatPropertyAsOptional(TestProperty);

	Record.bCanToggleVisibility = bCanTreatPropertyAsOptional && (bOptional_ShowByDefault || bOptional_HideByDefault);
	Record.bShowPin = bAlwaysShow || bOptional_ShowByDefault;
	Record.bPropertyIsCustomized = bPropertyIsCustomized;
}
```
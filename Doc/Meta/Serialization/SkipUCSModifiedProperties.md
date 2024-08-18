# SkipUCSModifiedProperties

功能描述: 跳过序列化Component里某个属性
使用位置: UPROPERTY
Feature: Serialization
引擎模块: Serialization
元数据类型: bool
限制类型: ActorComponent下的属性
Status: OnlyInternal
常用程度: 0

原理：

只在ActorComponent.cpp里用到，感觉是用于跳过序列化某个属性。
也只在UPrimitiveComponent 里的BodyInstance用到。物理的表示信息是运行时生成的，确实不需要序列化。但其实标一个Transient也就可以了，只能说是混乱的用法了。

```cpp
UCLASS(abstract, HideCategories=(Mobility, VirtualTexture), ShowCategories=(PhysicsVolume), MinimalAPI)
class UPrimitiveComponent : public USceneComponent, public INavRelevantInterface, public IInterface_AsyncCompilation, public IPhysicsComponent
{
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Collision, meta=(ShowOnlyInnerProperties, SkipUCSModifiedProperties))
	FBodyInstance BodyInstance;
}

		class FComponentPropertySkipper : public FArchive
		{
		public:
			FComponentPropertySkipper()
				: FArchive()
			{
				this->SetIsSaving(true);

				// Include properties that would normally skip tagged serialization (e.g. bulk serialization of array properties).
				ArPortFlags |= PPF_ForceTaggedSerialization;
			}

			virtual bool ShouldSkipProperty(const FProperty* InProperty) const override
			{
				static const FName MD_SkipUCSModifiedProperties(TEXT("SkipUCSModifiedProperties"));
				return (InProperty->HasAnyPropertyFlags(CPF_Transient)
					|| !InProperty->HasAnyPropertyFlags(CPF_Edit | CPF_Interp)
					|| InProperty->IsA<FMulticastDelegateProperty>()
#if WITH_EDITOR
					|| InProperty->HasMetaData(MD_SkipUCSModifiedProperties)
#endif
					);
			}
		} PropertySkipper;
```
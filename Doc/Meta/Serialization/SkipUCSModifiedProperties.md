# SkipUCSModifiedProperties

- **功能描述：** 跳过序列化Component里某个属性
- **使用位置：** UPROPERTY
- **引擎模块：** Serialization
- **元数据类型：** bool
- **限制类型：** ActorComponent下的属性
- **常用程度：** 0

## 原理：

只在ActorComponent.cpp里用到，感觉是用于跳过序列化某个属性。
也只在UPrimitiveComponent 里的BodyInstance用到。物理的表示信息是运行时生成的，确实不需要序列化。但其实标一个Transient也就可以了，只能说是混乱的用法了。

SimpleConstructionScript指的是这个组件是在Actor的蓝图面板里添加进去的，而不是再蓝图通过AddComponent里动态添加的。

```cpp
UCLASS(abstract, HideCategories=(Mobility, VirtualTexture), ShowCategories=(PhysicsVolume), MinimalAPI)
class UPrimitiveComponent : public USceneComponent, public INavRelevantInterface, public IInterface_AsyncCompilation, public IPhysicsComponent
{
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Collision, meta=(ShowOnlyInnerProperties, SkipUCSModifiedProperties))
	FBodyInstance BodyInstance;
}

void UActorComponent::DetermineUCSModifiedProperties()
{
  	if (CreationMethod == EComponentCreationMethod::SimpleConstructionScript)
    {
   	 //TMap<UActorComponent*, TArray<FSimpleMemberReference>> AllUCSModifiedProperties;
    	//把组件里和CDO不一样的属性存到AllUCSModifiedProperties里
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
    
        }
    }
```

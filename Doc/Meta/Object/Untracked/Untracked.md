# Untracked

功能描述: 使得TSoftObjectPtr和FSoftObjectPath的软对象引用类型的属性，不跟踪记录资产的 。
使用位置: UPROPERTY
Feature: Behavior
引擎模块: Object Property
元数据类型: bool
限制类型: TSoftObjectPtr，FSoftObjectPath 
Status: Done
常用程度: 1

使得TSoftObjectPtr和FSoftObjectPath的软对象引用类型的属性，不跟踪记录资产的 。

一般默认情况，属性上的软对象引用也是会产生资产的引用依赖，虽然在Load本身的时候，不会像硬引用一样也去加载其他软引用对象。但是因为引用关系依然存在，因此在cook的时候，或者资产重定向的时候都会去检查这些软引用对象，确保其也会被cook进去，或者正常的处理。

而当你想在属性上记录“引用”一些资产，以便之后加载使用，但是又不想产生真正的资产引用依赖，这个时候就可以用untracked。源码中应用的不多，这是比较稀少的情况下。

和transient标记的区别是，transient属性在序列化的时候也不会序列化，因为其ctrl+S保存后重启编辑器会丢失值。transient属性既不产生资产引用关系也序列化保存值，Untracked属性会序列化保存值但不产生资产引用关系。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Soft :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> MyStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Untracked))
	TSoftObjectPtr<UStaticMesh> MyStaticMeshUntracked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath MySoftMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Untracked))
	FSoftObjectPath MySoftMeshUntracked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	TSoftObjectPtr<UStaticMesh> MyStaticMeshTransient;
};
```

蓝图效果：

在蓝图中建立一个UMyProperty_Soft DataAsset资产，然后设置其属性值。然后查看其引用的资源，会发现Untracked的属性，其设置的资产并没有出现在引用关系中。当然Transient的属性也不在引用关系中。

![Untitled](Untracked/Untitled.png)

原理：
Untracked元数据，会设置为ESoftObjectPathCollectType::NeverCollect的选项。继续搜索会发现带有NeverCollect的FSoftObjectPath，其上面的资产package 不会被算到资产引用里，从而不会带到upackage Import表里。源码中有多处地方带有这个NeverCollect 的类似判断。

```cpp
bool FSoftObjectPathThreadContext::GetSerializationOptions(FName& OutPackageName, FName& OutPropertyName, ESoftObjectPathCollectType& OutCollectType, ESoftObjectPathSerializeType& OutSerializeType, FArchive* Archive) const
{
#if WITH_EDITOR
		bEditorOnly = Archive->IsEditorOnlyPropertyOnTheStack();

		static FName UntrackedName = TEXT("Untracked");
		if (CurrentProperty && CurrentProperty->GetOwnerProperty()->HasMetaData(UntrackedName))
		{
			// Property has the Untracked metadata, so set to never collect references if it's higher than NeverCollect
			CurrentCollectType = FMath::Min(ESoftObjectPathCollectType::NeverCollect, CurrentCollectType);
		}
#endif
}

FArchive& FImportExportCollector::operator<<(FSoftObjectPath& Value)
{
	FName CurrentPackage;
	FName PropertyName;
	ESoftObjectPathCollectType CollectType;
	ESoftObjectPathSerializeType SerializeType;
	FSoftObjectPathThreadContext& ThreadContext = FSoftObjectPathThreadContext::Get();
	ThreadContext.GetSerializationOptions(CurrentPackage, PropertyName, CollectType, SerializeType, this);

	if (CollectType != ESoftObjectPathCollectType::NeverCollect && CollectType != ESoftObjectPathCollectType::NonPackage)
	{
		FName PackageName = Value.GetLongPackageFName();
		if (PackageName != RootPackageName && !PackageName.IsNone())
		{
			AddImport(Value, CollectType);
		}
	}
	return *this;
}
```
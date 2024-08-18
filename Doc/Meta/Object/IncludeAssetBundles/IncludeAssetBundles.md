# IncludeAssetBundles

功能描述: 用于UPrimaryDataAsset的子对象属性，指定应该继续递归到该子对象里去探测AssetBundle数据。
使用位置: UPROPERTY
Feature: Asset
引擎模块: Object Property
元数据类型: string="abc"
限制类型: UPrimaryDataAsset内部的ObjectPtr属性
Status: Done
Parent item: AssetBundles (AssetBundles.md)
常用程度: 2

用于UPrimaryDataAsset的子对象属性，指定应该继续递归到该子对象里去探测AssetBundle数据。

这样这些指对象内部的 FSoftObjectPtr 或 FSoftObjectPath 属性，其上面标明的AssetBundle的数据才会被解析添加到UPrimaryDataAsset的AssetBundleData里。

- 默认情况下，InitializeAssetBundlesFromMetadata_Recursive只会分析到UPrimaryDataAsset的本身这一层级的属性，比如下面的Icon和Mesh属性。
- 而如果再嵌套了一层，就是UPrimaryDataAsset下面拥有只对象，UMyProperty_Asset_ChildObject，而UMyProperty_Asset_ChildObject 里面又包含FSoftObjectPath ，希望它被属于AssetBundles 的一部分，在加载UPrimaryDataAsset的时候同时一并加载。这个时候就需要告诉引擎需要继续分析这个子对象。
- 注意到UMyProperty_Asset_ChildObject我都是用TObjectPtr，是个硬引用，该对象在UMyProperty_Asset_Item 被加载的时候也会自然被加载进来。因此无论如何，UMyProperty_Asset_ChildObject 都会被加载进来。但是UMyProperty_Asset_ChildObject 内部的ChildIcon是用TSoftObjectPtr，是软引用，因此必须依赖AssetBundle的机制才会被加载。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Asset_ChildObject :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "Client"))
	TSoftObjectPtr<UTexture2D> ChildIcon;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Asset_Item :public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "UI,Game"))
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "Game"))
	TSoftObjectPtr<UStaticMesh> Mesh;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyProperty_Asset_ChildObject> MyChildObject_NotIncludeAssetBundles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (IncludeAssetBundles))
	TObjectPtr<UMyProperty_Asset_ChildObject> MyChildObject_IncludeAssetBundles;
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
```

测试效果：

配置的数据图的下部分，分别配置了两张图片。但在LoadPrimaryAsset后，只有MyChildObject_IncludeAssetBundles内部的ChildIcon才被加载进来。

![IncludeAssetBundles.jpg](IncludeAssetBundles/IncludeAssetBundles.jpg)

如果分析UMyProperty_Asset_Item 的AssetBunbleData数据，会发现其Client只包含第二张Stone图片的路径。这是因为只有第二张图片才被分析到并包含进来。

```cpp
{
				BundleName = "Client";
				BundleAssets =
				{
					{
						AssetPath =
						{
							PackageName = "/Game/Asset/Image/T_Shop_Stone";
							AssetName = "T_Shop_Stone";
						};
						SubPathString = "";
					};
				},
				AssetPaths =
				{
					{
						PackageName = "/Game/Asset/Image/T_Shop_Stone";
						AssetName = "T_Shop_Stone";
					};
				},
			};
```

原理：

UPrimaryDataAsset下的属性如果是个Object属性，只当有IncludeAssetBundles的时候，才会进一步递归向下探测。

```cpp
void UAssetManager::InitializeAssetBundlesFromMetadata_Recursive(const UStruct* Struct, const void* StructValue, FAssetBundleData& AssetBundle, FName DebugName, TSet<const void*>& AllVisitedStructValues) const
{
	static FName AssetBundlesName = TEXT("AssetBundles");
	static FName IncludeAssetBundlesName = TEXT("IncludeAssetBundles");
	
	//根据当前对象的值，搜索拥有AssetBundles的属性的值，最后AddBundleAsset，BundleName就是设置的值，而FoundRef是引用的对象的资产路径
	else if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
	{
		if (ObjectProperty->PropertyFlags & CPF_InstancedReference || ObjectProperty->GetOwnerProperty()->HasMetaData(IncludeAssetBundlesName))
		{
			const UObject* Object = ObjectProperty->GetObjectPropertyValue(PropertyValue);
			if (Object != nullptr)
			{
				InitializeAssetBundlesFromMetadata_Recursive(Object->GetClass(), Object, AssetBundle, Object->GetFName(), AllVisitedStructValues);
			}
		}
	}
}
```
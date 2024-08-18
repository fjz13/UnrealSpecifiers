# AssetBundles

功能描述: 标明该属性其引用的资产属于哪一些AssetBundles。
使用位置: UPROPERTY
Feature: Asset
引擎模块: Object Property
元数据类型: strings="a，b，c"
限制类型: UPrimaryDataAsset内部的FSoftObjectPtr，FSoftObjectPath 
Status: Done
Sub-item: IncludeAssetBundles (IncludeAssetBundles.md)
常用程度: 3

用于UPrimaryDataAsset内部的 SoftObjectPtr 或 SoftObjectPath 属性，标明其引用的资产属于哪一些AssetBundles。

要理解这个的作用，需要先理解一些基本概念：

- PrimaryAsset指的是在游戏中可以进行手动载入/释放的东西。包括关卡文件（.umap）以及一些游戏相关的物件，例如角色或者背包里的物品。顾名思义，主要资产指的是游戏里的主要根部资产，其引用树下有一大堆其他资产。另一方面，我们往往会主动加载或释放这些主要资产，比如加载关卡，加载怪物角色，加载掉落道具。但我们一般不太会直接去加载材质贴图声音这种资产，因为它们绝大多数是被主要资产引用着。我们在加载主要资产的时候，就会自带的加载这些次要资产了。
- SecondaryAsset指的是其他的那些Assets了，例如贴图和声音等。这一类型的assets是根据PrimaryAsset来自动进行载入的。我们一般来说不太需要对次要资产进行管理，其会被主要资产根据引用关系来自动的加载。
- AssetBundle可以叫做资产包，其实就是一个Asset的列表，我们对每个资产包起个名字来区分，比如UI，Game，这样其实也是对一些资产进行标签分类。这里的Asset我们不区分是PrimaryAsset还是SecondaryAsset，因为这是从用途上进行区分的，而不是加载方式。AssetBundle的作用是当我们加载PrimaryAsset的时候，这个PrimaryAsset本身可能引用着另外一些SecondaryAsset资产，各自有不同的用途。我们就可以把这些SecondaryAsset资产划分到不同的AssetBundle里，这样我们在加载PrimaryAsset的时候，可以通过额外提供AssetBundleName来更加精细化的控制SecondaryAsset资产的加载。
- PrimaryAsset里的指定AssetBundle的Asset属性必须是软引用，否则是硬引用的话无论如何也会被加载进来。软引用的Asset在默认时候需要我们手动的进行加载，通过附加AssetBundle，就可以在加载PrimaryAsset的时候，附带的加载该软引用资产。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Asset_Item :public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(AssetBundles="UI,Game"))
		TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(AssetBundles="Game"))
		TSoftObjectPtr<UStaticMesh> Mesh;
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
```

测试效果：

- 首先我们在BP里定义了UMyProperty_Asset_Item 的资产，并相应的配置上了引用的对象。如图所示，有一个图标是给UI和Game用的，有一个Mesh是专门给Game用的。大概设想一下在一些界面我们只需要道具的图标就可以了。
- 然后在LoadPrimaryAsset的时候可以指定LoadBundles的名字，从而只加载特定的Bundle。如下图所示。
- 当指定Bundle为UI的时候，可以看见Mesh并没有加载进来。
- 当指定Bundle为Game的时候，可以看见Icon和Mesh都加载了进来。
- 要注意在编辑器下测试时候，如果之前已经加载了Mesh，因为还常驻在编辑器内存里。因此即使是使用名字UI，也仍然会发现Mesh可以被引用到。

![AssetBundles.jpg](AssetBundles/AssetBundles.jpg)

原理：

首先UPrimaryDataAsset里有一个AssetBundleData保存着当前引用的AssetBundle的信息，这个信息是在编辑器环境下PreSave的时候保存的，会在UAssetManager::InitializeAssetBundlesFromMetadata里进行meta的分析和映射。之后在UAssetManager的LoadPrimaryAsset时内部调用 ChangeBundleStateForPrimaryAssets，然后检查AssetBundle把其他额外要一并加载的Asset添加到PathsToLoad，从而最终完成一并加载的这个逻辑。

```cpp
void UAssetManager::InitializeAssetBundlesFromMetadata_Recursive(const UStruct* Struct, const void* StructValue, FAssetBundleData& AssetBundle, FName DebugName, TSet<const void*>& AllVisitedStructValues) const
{
	static FName AssetBundlesName = TEXT("AssetBundles");
	static FName IncludeAssetBundlesName = TEXT("IncludeAssetBundles");
	
	//根据当前对象的值，搜索拥有AssetBundles的属性的值，最后AddBundleAsset，BundleName就是设置的值，而FoundRef是引用的对象的资产路径
	TSet<FName> BundleSet;
	TArray<const FProperty*> PropertyChain;
	It.GetPropertyChain(PropertyChain);
	
	for (const FProperty* PropertyToSearch : PropertyChain)
	{
					if (PropertyToSearch->HasMetaData(AssetBundlesName))
					{
						TSet<FName> LocalBundleSet;
						TArray<FString> BundleList;
						const FString& BundleString = PropertyToSearch->GetMetaData(AssetBundlesName);
						BundleString.ParseIntoArrayWS(BundleList, TEXT(","));
	
						for (const FString& BundleNameString : BundleList)
						{
							LocalBundleSet.Add(FName(*BundleNameString));
						}
	
						// If Set is empty, initialize. Otherwise intersect
						if (BundleSet.Num() == 0)
						{
							BundleSet = LocalBundleSet;
						}
						else
						{
							BundleSet = BundleSet.Intersect(LocalBundleSet);
						}
		}
}

	for (const FName& BundleName : BundleSet)
	{
					AssetBundle.AddBundleAsset(BundleName, FoundRef.GetAssetPath());
	}
}

#if WITH_EDITORONLY_DATA
void UPrimaryDataAsset::UpdateAssetBundleData()
{
	// By default parse the metadata
	if (UAssetManager::IsInitialized())
	{
		AssetBundleData.Reset();
		UAssetManager::Get().InitializeAssetBundlesFromMetadata(this, AssetBundleData);
	}
}

void UPrimaryDataAsset::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
	Super::PreSave(ObjectSaveContext);

	UpdateAssetBundleData();

	if (UAssetManager::IsInitialized())
	{
		// Bundles may have changed, refresh
		UAssetManager::Get().RefreshAssetData(this);
	}
}
#endif

void UPrimaryDataAsset::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITORONLY_DATA
	FAssetBundleData OldData = AssetBundleData;
	
	UpdateAssetBundleData();

	if (UAssetManager::IsInitialized() && OldData != AssetBundleData)
	{
		// Bundles changed, refresh
		UAssetManager::Get().RefreshAssetData(this);
	}
#endif
}

//加载asset的时候，如果有FAssetBundleEntry，则一起加到PathsToLoad里
TSharedPtr<FStreamableHandle> UAssetManager::ChangeBundleStateForPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToChange, const TArray<FName>& AddBundles, const TArray<FName>& RemoveBundles, bool bRemoveAllBundles, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	if (!AssetPath.IsNull())
		{
			// Dynamic types can have no base asset path
			PathsToLoad.Add(AssetPath);
		}
		
		for (const FName& BundleName : NewBundleState)
		{
			FAssetBundleEntry Entry = GetAssetBundleEntry(PrimaryAssetId, BundleName);
		
			if (Entry.IsValid())
			{
				for (const FTopLevelAssetPath & Path : Entry.AssetPaths)
				{
					PathsToLoad.AddUnique(FSoftObjectPath(Path));
				}
			}
			else
			{
				UE_LOG(LogAssetManager, Verbose, TEXT("ChangeBundleStateForPrimaryAssets: No assets for bundle %s::%s"), *PrimaryAssetId.ToString(), *BundleName.ToString());
			}
		}
}
```

参考文档：[https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine?application_version=5.4](https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine?application_version=5.4)
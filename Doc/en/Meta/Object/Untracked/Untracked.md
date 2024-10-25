# Untracked

- **Function Description:** Allows properties of the soft object reference types TSoftObjectPtr and FSoftObjectPath to not be tracked and recorded for asset dependencies.
- **Usage Location:** UPROPERTY
- **Engine Module:** Object Property
- **Metadata Type:** bool
- **Restricted Types:** TSoftObjectPtr, FSoftObjectPath
- **Commonality:** ★

Properties of the soft object reference types TSoftObjectPtr and FSoftObjectPath will not track asset dependencies.

By default, soft object references on properties will also create asset dependency references, although during the loading process, they do not load other soft reference objects as hard references do. However, since the reference relationship still exists, these soft reference objects are checked during cooking or asset redirection to ensure they are also cooked or handled properly.

If you want to record "references" to some assets on properties for later use without creating actual asset dependency references, you can use untracked. This is not commonly used in the source code and is a relatively rare scenario.

The difference from the transient tag is that transient properties are not serialized during serialization and their values are lost after saving with ctrl+S and restarting the editor. Transient properties do not create asset dependency relationships nor are they serialized to save values. Untracked properties are serialized to save values but do not create asset dependency relationships.

## Test Code:

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

## Blueprint Effect:

In the Blueprint, create a UMyProperty_Soft DataAsset and set its property values. When checking the referenced resources, you will find that the Untracked property does not include the set assets in the dependency relationship. Of course, transient properties are also not included in the dependency relationship.

![Untitled](Untitled.png)

## Principle:

Untracked metadata is set to the ESoftObjectPathCollectType::NeverCollect option. Further searching will reveal that FSoftObjectPath with NeverCollect does not include the asset package in the dependency calculation, thus not adding it to the upackage Import table. There are multiple instances in the source code with similar judgments using NeverCollect.

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
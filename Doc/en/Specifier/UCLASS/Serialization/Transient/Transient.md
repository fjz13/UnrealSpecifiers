# Transient

- **Function description:** Indicates that all instances of this class will be skipped during serialization.

- **Engine module:** Serialization
- **Metadata type:** bool
- **Mechanism of action:** Add [CLASS_Transient](../../../../Flags/EClassFlags/CLASS_Transient.md) to ClassFlags
- **Associated items:** [NonTransient](../NonTransient.md)
- **Commonality:** ★★★

Indicates that all instances of this class are to be skipped during serialization.

- Objects of this class are never saved to disk. This specification is inherited by subclasses but can be overridden by the NonTransient specifier. It can also be overridden in the subclasses.
- It results in the corresponding Object having the RF_Transient flag set.
- Note: UPROPERTY(Transient) specifies that a particular property should not be serialized, whereas UCLASS(Transient) applies to all objects of the class.

## Sample code:

```cpp
UCLASS(Blueprintable, Transient)
class INSIDER_API UMyClass_Transient :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};

UCLASS(Blueprintable, NonTransient)
class INSIDER_API UMyClass_NonTransient :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Transient_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMyClass_Transient* MyTransientObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMyClass_NonTransient* MyNonTransientObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Normal=123;
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Transient)
		int32 MyInt_Transient =123;
};
```

The key to serializing object pointers is to use the SerializeItem method Slot << ObjectValue; in FObjectProperty

Testing with an Actor's Class Default is not feasible because:

Transient properties are serialized for (Blueprint) Class Default Objects but should not be serialized for any 'normal' instances of classes.

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_Transient_Test :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMyClass_Transient* MyTransientObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMyClass_NonTransient* MyNonTransientObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Normal=123;
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Transient)
		int32 MyInt_Transient =123;
};
```

Nor can it be tested with FObjectAndNameAsStringProxyArchive, as this archive internally looks up the name before serializing an object.

```cpp
FArchive& FObjectAndNameAsStringProxyArchive::operator<<(UObject*& Obj)
{
	if (IsLoading())
	{
		// load the path name to the object
		FString LoadedString;
		InnerArchive << LoadedString;
		// look up the object by fully qualified pathname
		Obj = FindObject<UObject>(nullptr, *LoadedString, false);
		// If we couldn't find it, and we want to load it, do that
		if(!Obj && bLoadIfFindFails)
		{
			Obj = LoadObject<UObject>(nullptr, *LoadedString);
		}
	}
	else
	{
		// save out the fully qualified object name
		FString SavedString(Obj->GetPathName());
		InnerArchive << SavedString;
	}
	return *this;
}
```

Therefore, testing is done using a Package:

```cpp

FString packageName = TEXT("/Game/MyTestPackage");
FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());
UPackage* package = CreatePackage(*packageName);
FSavePackageArgs saveArgs{};
saveArgs.Error = GError;

//ObjectFlags:	RF_NoFlags
UMyClass_Transient_Test* testObject = NewObject<UMyClass_Transient_Test>(package, TEXT("testObject"));
//ObjectFlags:	RF_Transient
testObject->MyTransientObject = NewObject<UMyClass_Transient>(testObject, TEXT("MyTransientObject"));
//ObjectFlags:	RF_NoFlags
testObject->MyNonTransientObject = NewObject<UMyClass_NonTransient>(testObject, TEXT("MyNonTransientObject"));

testObject->MyTransientObject->MyProperty = 456;
testObject->MyNonTransientObject->MyProperty = 456;
testObject->MyInt_Normal = 456;
testObject->MyInt_Transient = 456;

bool result = UPackage::SavePackage(package, testObject, *assetPath, saveArgs);
```

After saving, the Package should be reloaded:

```cpp
FString packageName = TEXT("/Game/MyTestPackage");
FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

UPackage* package = LoadPackage(nullptr, *assetPath, LOAD_None);
package->FullyLoad();

UMyClass_Transient_Test* newTestObject=LoadObject<UMyClass_Transient_Test>(package, TEXT("testObject"),*assetPath);
```

## Example effect:

It can be observed that MyTransientObject has not been serialized to disk and therefore will not be loaded.

![Untitled](Untitled.png)

## Principle:

During SavePackage, RF_Transient causes the object not to be included in the HarvestExport process and not to be placed in the SaveContext

```cpp
void FPackageHarvester::TryHarvestExport(UObject* InObject)
{
	// Those should have been already validated
	check(InObject && InObject->IsInPackage(SaveContext.GetPackage()));

	// Get the realm in which we should harvest this export
	EIllegalRefReason Reason = EIllegalRefReason::None;
	ESaveRealm HarvestContext = GetObjectHarvestingRealm(InObject, Reason);
	if (!SaveContext.GetHarvestedRealm(HarvestContext).IsExport(InObject))
	{
		SaveContext.MarkUnsaveable(InObject);
		bool bExcluded = false;
		if (!InObject->HasAnyFlags(RF_Transient))
		{
			bExcluded = ConditionallyExcludeObjectForTarget(SaveContext, InObject, HarvestContext);
		}
		if (!InObject->HasAnyFlags(RF_Transient) && !bExcluded)
		{
			// It passed filtering so mark as export
			HarvestExport(InObject, HarvestContext);
		}

		// If we have a illegal ref reason, record it
		if (Reason != EIllegalRefReason::None)
		{
			SaveContext.RecordIllegalReference(CurrentExportDependencies.CurrentExport, InObject, Reason);
		}
	}
}
```
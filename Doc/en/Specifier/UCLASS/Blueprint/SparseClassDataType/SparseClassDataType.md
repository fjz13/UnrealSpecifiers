# SparseClassDataType

- **Function description:** To store some repetitive and immutable data of the Actor in a common structure to reduce the amount of content used
- **Engine module:** Blueprint
- **Metadata type:** string="abc"
- **Mechanism of action:** Add [SparseClassDataTypes](../../../../Meta/Blueprint/SparseClassDataTypes.md) in Meta
- **Associated items:** [NoGetter](../../../../Meta/SparseDataType/NoGetter/NoGetter.md)
- **Commonly used:** ★★★

This is a point of refactoring and performance optimization. When using SparseClassDataType, it is divided into two scenarios: one is for existing Actors to leverage this feature for optimization, and the other is for newly created Actors to use this feature from the outset.

## Example usage:

Divided into two parts:

1. Existing Actor has redundant properties

In short, these are properties that do not change in Blueprint. In C++, if these properties are modified, they should also be retrieved using the Get function to transfer them to the SparseDataStruct.

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_SparseClassDataTypes :public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		int32 MyInt_EditDefaultOnly = 123;

	UPROPERTY(BlueprintReadOnly)
		int32 MyInt_BlueprintReadOnly = 1024;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FString MyString_EditDefault_ReadOnly = TEXT("MyName");

	UPROPERTY(EditAnywhere)
		float MyFloat_EditAnywhere = 555.f;

	UPROPERTY(BlueprintReadWrite)
		float MyFloat_BlueprintReadWrite = 666.f;
};
```

Change to the following code. Wrap the attributes with WITH_EDITORONLY_DATA to indicate that operations are only performed under editor , and runtime has been eliminated. Adding _DEPRECATED the suffix mark is also to further remind the original BP that the access needs to be removed. Overload MoveDataToSparseClassDataStruct to copy the value currently configured in BP Class Defaults to the new FMySparseClassData structure value.

```cpp
USTRUCT(BlueprintType)
struct FMySparseClassData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
        int32 MyInt_EditDefaultOnly = 123;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int32 MyInt_BlueprintReadOnly = 1024;

    // "GetByRef" means that Blueprint graphs access a const ref instead of a copy.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(GetByRef))
        FString MyString_EditDefault_ReadOnly = TEXT("MyName");
};

UCLASS(Blueprintable, BlueprintType,SparseClassDataTypes= MySparseClassData)
class INSIDER_API AMyActor_SparseClassDataTypes :public AActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	// ~ This function transfers existing data into FMySparseClassData.
	virtual void MoveDataToSparseClassDataStruct() const override;
#endif // WITH_EDITOR
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
		int32 MyInt_EditDefaultOnly_DEPRECATED = 123;

	UPROPERTY()
		int32 MyInt_BlueprintReadOnly_DEPRECATED = 1024;

	UPROPERTY()
		FString MyString_EditDefault_ReadOnly_DEPRECATED = TEXT("MyName");
#endif // WITH_EDITORONLY_DATA
public:
	UPROPERTY(EditAnywhere)
		float MyFloat_EditAnywhere = 555.f;

	UPROPERTY(BlueprintReadWrite)
		float MyFloat_BlueprintReadWrite = 666.f;
};

//cpp
#if WITH_EDITOR
void AMyActor_SparseClassDataTypes::MoveDataToSparseClassDataStruct() const
{
	// make sure we don't overwrite the sparse data if it has been saved already
	UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	if (BPClass == nullptr || BPClass->bIsSparseClassDataSerializable == true)
	{
		return;
	}

	Super::MoveDataToSparseClassDataStruct();

#if WITH_EDITORONLY_DATA
	// Unreal Header Tool (UHT) will create GetMySparseClassData automatically.
	FMySparseClassData* SparseClassData = GetMySparseClassData();

	// Modify these lines to include all Sparse Class Data properties.
	SparseClassData->MyInt_EditDefaultOnly = MyInt_EditDefaultOnly_DEPRECATED;
	SparseClassData->MyInt_BlueprintReadOnly = MyInt_BlueprintReadOnly_DEPRECATED;
	SparseClassData->MyString_EditDefault_ReadOnly = MyString_EditDefault_ReadOnly_DEPRECATED;
#endif // WITH_EDITORONLY_DATA

}
#endif // WITH_EDITOR
```

After the BP's PostLoad is executed, MoveDataToSparseClassDataStruct will be called automatically, so bIsSparseClassDataSerializable must be checked internally.

```cpp
void UBlueprintGeneratedClass::PostLoadDefaultObject(UObject* Object)
{
	FScopeLock SerializeAndPostLoadLock(&SerializeAndPostLoadCritical);

	Super::PostLoadDefaultObject(Object);

	if (Object == ClassDefaultObject)
	{
		// Rebuild the custom property list used in post-construct initialization logic. Note that PostLoad() may have altered some serialized properties.
		UpdateCustomPropertyListForPostConstruction();

		// Restore any property values from config file
		if (HasAnyClassFlags(CLASS_Config))
		{
			ClassDefaultObject->LoadConfig();
		}
	}

#if WITH_EDITOR
	Object->MoveDataToSparseClassDataStruct();

	if (Object->GetSparseClassDataStruct())
	{
		// now that any data has been moved into the sparse data structure we can safely serialize it
		bIsSparseClassDataSerializable = true;
	}

	ConformSparseClassData(Object);
#endif
}
```

Within UClass

```cpp
protected:
	/** This is where we store the data that is only changed per class instead of per instance */
	void* SparseClassData;

	/** The struct used to store sparse class data. */
	UScriptStruct* SparseClassDataStruct;

在构造UClass的时候，会SetSparseClassDataStruct来把结构传进去，因此就把结构关联起来。
UClass* Z_Construct_UClass_AMyActor_SparseClassDataTypes()
{
	if (!Z_Registration_Info_UClass_AMyActor_SparseClassDataTypes.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyActor_SparseClassDataTypes.OuterSingleton, Z_Construct_UClass_AMyActor_SparseClassDataTypes_Statics::ClassParams);
		Z_Registration_Info_UClass_AMyActor_SparseClassDataTypes.OuterSingleton->SetSparseClassDataStruct(AMyActor_SparseClassDataTypes::StaticGetMySparseClassDataScriptStruct());
	}
	return Z_Registration_Info_UClass_AMyActor_SparseClassDataTypes.OuterSingleton;
}
```

Note that at this time, you cannot use blueprint get for ReadOnly variables in BP, as _DEPRECATED is in use. One approach is to define additional Getter methods:

```cpp
UFUNCTION(BlueprintPure)
int32 GetMyMyInt_BlueprintReadOnly()const
{
	return GetMySparseClassData()->MyInt_BlueprintReadOnly;
}
```

2. Another approach is to simply remove the redundant properties in AMyActor_SparseClassDataTypes after MoveDataToSparseClassDataStruct (make sure to open the editor, and save after opening the subclass BP Blueprint) and use all values from FMySparseClassData. Thus, it becomes:

```cpp
USTRUCT(BlueprintType)
struct FMySparseClassData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
        int32 MyInt_EditDefaultOnly = 123;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int32 MyInt_BlueprintReadOnly = 1024;

    // "GetByRef" means that Blueprint graphs access a const ref instead of a copy.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(GetByRef))
        FString MyString_EditDefault_ReadOnly = TEXT("MyName");
};

UCLASS(Blueprintable, BlueprintType,SparseClassDataTypes= MySparseClassData)
class INSIDER_API AMyActor_SparseClassDataTypes :public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float MyFloat_EditAnywhere = 555.f;

	UPROPERTY(BlueprintReadWrite)
		float MyFloat_BlueprintReadWrite = 666.f;
};
```

This achieves the final effect, which is also applicable to new Actors that adopt redundant properties. Note that at this point, BlueprintReadOnly properties can still be accessed in BP, as the UHT and BP system have already added a layer of convenient access control for us.

## Example effect:

UHT will generate C++ access functions for us:

```cpp
#define FID_Hello_Source_Insider_Class_Trait_MyClass_SparseClassDataTypes_h_30_SPARSE_DATA \
FMySparseClassData* GetMySparseClassData(); \
FMySparseClassData* GetMySparseClassData() const; \
const FMySparseClassData* GetMySparseClassData(EGetSparseClassDataMethod GetMethod) const; \
static UScriptStruct* StaticGetMySparseClassDataScriptStruct(); \
int32 GetMyInt_EditDefaultOnly() \
{ \
	return GetMySparseClassData()->MyInt_EditDefaultOnly; \
} \
int32 GetMyInt_EditDefaultOnly() const \
{ \
	return GetMySparseClassData()->MyInt_EditDefaultOnly; \
} \
int32 GetMyInt_BlueprintReadOnly() \
{ \
	return GetMySparseClassData()->MyInt_BlueprintReadOnly; \
} \
int32 GetMyInt_BlueprintReadOnly() const \
{ \
	return GetMySparseClassData()->MyInt_BlueprintReadOnly; \
} \
const FString& GetMyString_EditDefault_ReadOnly() \
{ \
	return GetMySparseClassData()->MyString_EditDefault_ReadOnly; \
} \
const FString& GetMyString_EditDefault_ReadOnly() const \
{ \
	return GetMySparseClassData()->MyString_EditDefault_ReadOnly; \
}
```

Still accessible in BP:

![Untitled](Untitled.png)

Values can also be changed in Class Defaults:

![Untitled](Untitled%201.png)
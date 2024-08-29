#pragma once

#include "InsiderTypes.h"
#include "Subsystems/EngineSubsystem.h"
#include "InsiderSubsystem.generated.h"


UCLASS(Category = Insider)
class INSIDER_API UInsiderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	static UInsiderSubsystem& Get();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

#pragma region Package

#pragma endregion Package

#pragma region Trace
public:
	UFUNCTION(BlueprintCallable, Category = Insider, DisplayName = "PrintObject", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AdvancedDisplay = "2"))
	FString K2_PrintObject(const UObject* WorldContextObject, const UObject* object, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/Insider.EInsiderPrintFlags")) int32 flags = 4095, FString prefix = "", bool bCopyToClipboard = false, bool bPrintToScreen = false, bool bPrintToLog = false, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f);

	FString PrintObject(const UObject* object, EInsiderPrintFlags flags = EInsiderPrintFlags::All, FString prefix = "");

	FString PrintObjectHelper(const UObject* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::All, FString prefix = "");

	FString PrintPackage(const UPackage* package, EInsiderPrintFlags flags = EInsiderPrintFlags::All, FString prefix = "");


	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintMetaData(const UObject* obj, FString prefix = "", FString suffix = "\n");

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString SetMetaData(const UObject* obj, FName key, FString value);

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString RemoveMetaData(const UObject* obj, FName key);

	UFUNCTION(BlueprintPure, Category = Insider)
	bool HasMetaData(const UObject* obj);


	UFUNCTION(BlueprintCallable, Category = Insider)
	void SetPropertyMetaData(FName typeName, FName propertyName, FName key, FString value = "");

	UFUNCTION(BlueprintCallable, Category = Insider)
	void RemovePropertyMetaData(FName typeName, FName propertyName, FName key);

	UFUNCTION(BlueprintCallable, Category = Insider,meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext,AdvancedDisplay = "2"))
	void PrintStringEx(const UObject* WorldContextObject, FString value,bool bCopyToClipboard = true, bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f);

private:
	FString PrintProperty(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");
	FString PrintPropertyDeclaration(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");
	FString ExpandPropertyObjectValue(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");
	FString PrintPropertyValueInline(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");
	bool HasPropertySubObject(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");

	FString PrintFunctionParameter(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");

	FString PrintFunctionHeader(const UFunction* func, EInsiderPrintFlags flags = EInsiderPrintFlags::FunctionDefault, FString prefix = "");
	FString PrintEnum(const UEnum* enumClass, EInsiderPrintFlags flags = EInsiderPrintFlags::EnumDefault, FString prefix = "");

	FString PrintStruct(const UScriptStruct* structClass, const void* object, TSet<const UObject*>& allObjects,EInsiderPrintFlags flags = EInsiderPrintFlags::StructDefault, FString prefix = "");

	FString PrintStructHeader(const UScriptStruct* structClass, const void* object = nullptr, EInsiderPrintFlags flags = EInsiderPrintFlags::StructDefault, FString prefix = "");
	FString PrintClassHeader(const UClass* classObj, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
	FString PrintObjectHeader(const UObject* object, EInsiderPrintFlags flags = EInsiderPrintFlags::ObjectDefault, FString prefix = "");

	FString GetObjectTypeToken(const UObject* object);

	FString PrintPropertyHeader(const FProperty* prop, EInsiderPrintFlags flags = EInsiderPrintFlags::PropertyDefault, FString prefix = "");

	FString GetClassHierarchyString(const UStruct* classObj, bool includeSelf = true, bool includeChildren = true);
	FString PrintChildrenProperties(const UStruct* structObj, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "", bool sortProperties = true);

	FString PrintClassInterfaces(const UClass* classObj, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
	FString PrintClassFunctions(const UClass* classObj, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
	FString PrintClass(const UClass* classObj, const void* object = nullptr, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
public:
	TArray<const FProperty*> GetProperties(const UStruct* outer, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, bool sort = true);
	bool IsContainerProperty(const FProperty* property);
	FString GetPropertyCPPTypeString(const FProperty* property);



#pragma endregion Trace

#pragma region Store
public:
	UFUNCTION(BlueprintCallable, Category = Insider)
	UObject* K2_NewObject(UClass* objClass, FName objName);

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintAllPackages();
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintAllUClasses();
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintAllEnums();
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintAllStructs();

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintObjectsWithOuter(UObject* outer);
public:
	FString PrintAllObjectsWithRawObjectIterator();
	FString PrintAllObjectsFObjectIterator();
	FString PrintAllObjectsTObjectIterator();
	FString PrintAllMetaDataKeys();

#pragma endregion Store

#pragma region Reflection
public:
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintDerivedClasses(UClass* objClass, bool recursive = true);
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintSuperClasses(UClass* objClass);

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintInterfacesWithClass(UClass* objClass);

	UFUNCTION(BlueprintCallable, Category = Insider)
	FString PrintClassesWithInterface(UClass* interfaceClass);

	UFUNCTION(BlueprintCallable, Category = Insider, DisplayName = "PrintProperty")
	FString K2_PrintProperty(UObject* obj, FName propertyName);
	UFUNCTION(BlueprintCallable, Category = Insider)
	FString SetPropertyValue(UObject* obj, FName propertyName, FString valueStr);

private:
	void PrintDerivedClassesHelper(UClass* objClass, FString& str, int depth);
#pragma endregion Reflection

#pragma region Find
public:
	UObject* FindObjectWithName(FString objName, UObject* parent = nullptr);
	UObject* FindObjectWithNameSmart(FString objName, UObject* parent = nullptr);

	UScriptStruct* FindStructWithName(FName structName);

	FString FindAllStructsWithFlag(EStructFlags structFlags);
	FString FindAllClassesWithFlag(EClassFlags flags);
	FString FindAllClassesWithoutFlag(EClassFlags flags);

#pragma endregion Find


private:
	bool IsObjectIgnored(const UObject* obj);
	bool IsObjectCustomized(const UObject* obj);
	bool IsStructCustomized(const UScriptStruct* structClass,const void* object);
	bool IsStructPrintOnelineSupported(const UScriptStruct* structClass,const void* object);
	FString AddQuoteToStringIfSuitable(const FString& InString);



public:
	UFUNCTION(BlueprintCallable)
	void PrintFuncStatus(AActor* actor, FString funcName);

protected:
	FString PrintMetaDataMapInline(FString objName, const TMap<FName, FString>* keyValues, FString prefix = "", FString suffix = "\n");
	FString PrintMetaDataMapKeyValues(FString objName, const TMap<FName, FString>& keyValues, FString prefix = "");

	FString PrintMetaDataObjectCustomized(const UClass* classObj, const UObject* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
	FString PrintGuidCustomized(const UScriptStruct* structClass, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");
	FString PrintCoreStructsCustomized(const UScriptStruct* structClass, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags = EInsiderPrintFlags::ClassDefault, FString prefix = "");


	DECLARE_DELEGATE_RetVal_FiveParams(FString, FPrintObjectCustomizedDeleagate, const UClass*, const UObject*, TSet<const UObject*>&, EInsiderPrintFlags, FString);
	DECLARE_DELEGATE_RetVal_FiveParams(FString, FPrintStructCustomizedDeleagate, const UScriptStruct*, const void*, TSet<const UObject*>&, EInsiderPrintFlags, FString);

	TMap<const UClass*, FPrintObjectCustomizedDeleagate> PrintObjectCustomizedMap;
	TMap<const UScriptStruct*, FPrintStructCustomizedDeleagate> PrintStructCustomizedMap;
	TMap<const UScriptStruct*, bool> IsStructPrintOnelineSupportedMap;

public:
	UPROPERTY(BlueprintReadWrite)
	bool IgnoreCommentAndToolTip=false;
};

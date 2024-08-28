// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "UObject/SoftObjectPtr.h"
#include "InstancedStruct.h"
#include "MyProperty_Class.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyCommonInterfaceChild :public UObject, public IMyCommonInterface
{
	GENERATED_BODY()
};


UCLASS(BlueprintType, Abstract)
class INSIDER_API UMyCommonObjectChildAbstract :public UMyCommonObject
{
	GENERATED_BODY()
public:
};


UCLASS(BlueprintType, NotBlueprintable)
class INSIDER_API UMyCommonObjectChild_NotBlueprintable :public UMyCommonObject
{
	GENERATED_BODY()
public:
};


UCLASS(BlueprintType, NotBlueprintable, DisplayName = "This is MyCommonObjectChild")
class INSIDER_API UMyCommonObjectChild_HasDisplayName :public UMyCommonObject
{
	GENERATED_BODY()
public:
};

USTRUCT(BlueprintType, DisplayName = "This is MyCommonStructChild")
struct INSIDER_API FMyCommonStructChild_HasDisplayName :public FMyCommonStruct
{
	GENERATED_BODY()
};



UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActorChild_Placeable :public AMyActor
{
	GENERATED_BODY()
};


UCLASS(Blueprintable, BlueprintType, NotPlaceable)
class INSIDER_API AMyActorChild_NotPlaceable :public AMyActor
{
	GENERATED_BODY()
};


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Class :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoMustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|TSubclassOf", meta = (MustImplement = "/Script/Insider.MyCommonInterface"))
	TSubclassOf<UObject> MyClass_MustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|TSubclassOf", meta = (MustImplement = "/Script/UMG.UserListEntry"))
	TSubclassOf<UUserWidget> MyWidgetClass_MustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NoMustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|FSoftClassPath", meta = (MustImplement = "/Script/Insider.MyCommonInterface"))
	FSoftClassPath MySoftClass_MustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|FSoftClassPath", meta = (MustImplement = "/Script/UMG.UserListEntry"))
	FSoftClassPath MySoftWidgetClass_MustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|UClass*")
	UClass* MyClassPtr_NoMustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|UClass*", meta = (MustImplement = "/Script/Insider.MyCommonInterface"))
	UClass* MyClassPtr_MustImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MustImplementTest|UClass*", meta = (MustImplement = "/Script/UMG.UserListEntry"))
	UClass* MyWidgetClassPtr_MustImplement;

	UFUNCTION(BlueprintCallable, meta = (Category = "MustImplementTest|TSubclassOf"))
	static void SetMyClassMustImplement(UPARAM(meta = (MustImplement = "/Script/Insider.MyCommonInterface")) TSubclassOf<UObject> MNyClass) {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowAbstractTest")
	TSubclassOf<UMyCommonObject> MyClass_NotAllowAbstract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowAbstractTest", meta = (AllowAbstract))
	TSubclassOf<UMyCommonObject> MyClass_AllowAbstract;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest")
	TSubclassOf<UMyCommonObject> MyClass_NotBlueprintBaseOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueprintBaseOnlyTest", meta = (BlueprintBaseOnly))
	TSubclassOf<UMyCommonObject> MyClass_BlueprintBaseOnly;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlyPlaceableTest")
	TSubclassOf<AMyActor> MyActor_NotOnlyPlaceable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnlyPlaceableTest", meta = (OnlyPlaceable))
	TSubclassOf<AMyActor> MyActor_OnlyPlaceable;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NotMetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|TSubclassOf", meta = (MetaClass = "/Script/Insider.MyCommonObject"))
	TSubclassOf<UObject> MyClass_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NotMetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath", meta = (MetaClass = "/Script/Insider.MyCommonObject"))
	FSoftClassPath MySoftClass_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftClassPath", meta = (MetaClass = "/Script/Insider.MyCommonObject"))
	TSoftClassPtr<UObject> MySoftClassPtrT_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UClass*")
	UClass* MyClassPtr_NotMetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UClass*", meta = (MetaClass = "/Script/Insider.MyCommonObject"))
	UClass* MyClassPtr_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NotMetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath", meta = (MetaClass = "/Script/Insider.MyCustomAsset"))
	FSoftObjectPath MySoftObject_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|FSoftObjectPath", meta = (MetaClass = "/Script/Insider.MyCustomAsset"))
	TSoftObjectPtr<UObject> MySoftObjectPtrT_MetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NotMetaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaClassTest|UScriptStruct*", meta = (MetaClass = "/Script/Insider.MyCommonStruct"))
	UScriptStruct* MyStructPtr_MetaClass;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|TSubclassOf", meta = (HideViewOptions))
	TSubclassOf<UObject> MyClass_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UClass*")
	UClass* MyClassPtr_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UClass*", meta = (HideViewOptions))
	UClass* MyClassPtr_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FSoftClassPath", meta = (HideViewOptions))
	FSoftClassPath MySoftClass_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|UScriptStruct*", meta = (HideViewOptions))
	UScriptStruct* MyStructPtr_HideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FInstancedStruct")
	FInstancedStruct MyInstancedStruct_NotHideViewOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HideViewOptionsTest|FInstancedStruct", meta = (HideViewOptions))
	FInstancedStruct MyInstancedStruct_HideViewOptions;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|TSubclassOf", meta = (ShowTreeView))
	TSubclassOf<UObject> MyClass_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UClass*")
	UClass* MyClassPtr_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UClass*", meta = (ShowTreeView))
	UClass* MyClassPtr_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FSoftClassPath", meta = (ShowTreeView))
	FSoftClassPath MySoftClass_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UScriptStruct*", meta = (ShowTreeView))
	UScriptStruct* MyStructPtr_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FInstancedStruct")
	FInstancedStruct MyInstancedStruct_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FInstancedStruct", meta = (ShowTreeView))
	FInstancedStruct MyInstancedStruct_ShowTreeView;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|TSubclassOf", meta = ())
	TSubclassOf<UMyCommonObjectChild_HasDisplayName> MyClass_NotShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|TSubclassOf", meta = (ShowDisplayNames))
	TSubclassOf<UMyCommonObjectChild_HasDisplayName> MyClass_ShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UClass*", meta = (AllowedClasses = "/Script/Insider.MyCommonObjectChild_HasDisplayName"))
	UClass* MyClassPtr_NotShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UClass*", meta = (AllowedClasses = "/Script/Insider.MyCommonObjectChild_HasDisplayName", ShowDisplayNames))
	UClass* MyClassPtr_ShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|FSoftClassPath", meta = (MetaClass = "/Script/Insider.MyCommonObjectChild_HasDisplayName"))
	FSoftClassPath MySoftClass_NotShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|FSoftClassPath", meta = (MetaClass = "/Script/Insider.MyCommonObjectChild_HasDisplayName", ShowDisplayNames))
	FSoftClassPath MySoftClass_ShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UScriptStruct*", meta = (MetaStruct = "/Script/Insider.MyCommonStructChild_HasDisplayName"))
	UScriptStruct* MyStructPtr_NotShowDisplayNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowDisplayNamesTest|UScriptStruct*", meta = (MetaStruct = "/Script/Insider.MyCommonStructChild_HasDisplayName", ShowDisplayNames))
	UScriptStruct* MyStructPtr_ShowDisplayNames;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaStructTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NoMetaStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaStructTest|UScriptStruct*", meta = (MetaStruct = "/Script/Insider.MyCommonStruct"))
	UScriptStruct* MyStructPtr_MetaStruct;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|TSubclassOf", meta = (AllowedClasses = "/Script/Insider.MyCommonObject"))
	TSubclassOf<UObject> MyClass_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UClass*")
	UClass* MyClassPtr_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UClass*", meta = (AllowedClasses = "/Script/Insider.MyCommonObject"))
	UClass* MyClassPtr_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftClassPath", meta = (AllowedClasses = "/Script/Insider.MyCommonObject"))
	FSoftClassPath MySoftClass_AllowedClasses;

	//Not work
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UScriptStruct*")
	//UScriptStruct* MyStructPtr_NotAllowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UScriptStruct*", meta = (AllowedClasses = "MyCommonStruct"))
	//UScriptStruct* MyStructPtr_AllowedClasses;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UObject*")
	UObject* MyObject_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|UObject*", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	UObject* MyObject_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FSoftObjectPath", meta = (AllowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath MySoftObject_AllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FPrimaryAssetId")
	FPrimaryAssetId MyPrimaryAsset_NoAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AllowedClassesTest|FPrimaryAssetId", meta = (AllowedClasses = "/Script/Insider.MyPrimaryDataAsset"))
	FPrimaryAssetId MyPrimaryAsset_AllowedClasses;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|TSubclassOf", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	TSubclassOf<UObject> MyClass_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UClass*")
	UClass* MyClassPtr_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UClass*", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	UClass* MyClassPtr_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftClassPath", meta = (DisallowedClasses = "/Script/GameplayAbilities.AbilityAsync"))
	FSoftClassPath MySoftClass_DisallowedClasses;
public://Not work
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UObject*")
	UObject* MyObject_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|UObject*", meta = (DisallowedClasses = "/Script/Engine.Texture2D"))
	UObject* MyObject_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FSoftObjectPath", meta = (DisallowedClasses = "/Script/Engine.Texture2D"))
	FSoftObjectPath MySoftObject_DisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FPrimaryAssetId")
	FPrimaryAssetId MyPrimaryAsset_NoDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisallowedClassesTest|FPrimaryAssetId", meta = (DisallowedClasses = "/Script/Insider.MyPrimaryDataAsset"))
	FPrimaryAssetId MyPrimaryAsset_DisallowedClasses;

public:
	UFUNCTION()
	TArray<UClass*> MyGetAllowedClassesFunc();

	UFUNCTION()
	TArray<UClass*> MyGetDisallowedClassesFunc();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|TSubclassOf", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	TSubclassOf<UObject> MyClass_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*")
	UClass* MyClassPtr_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UClass*", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UClass* MyClassPtr_GetAllowedClasses;
	//not work
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftClassPath")
	//FSoftClassPath MySoftClass_NoGetAllowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftClassPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	//FSoftClassPath MySoftClass_GetAllowedClasses;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UObject*")
	UObject* MyObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|UObject*", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_GetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath")
	FSoftObjectPath MySoftObject_NoGetAllowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FSoftObjectPath", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_GetAllowedClasses;
	//not work
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FPrimaryAssetId")
	//FPrimaryAssetId MyPrimaryAsset_NoGetAllowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetAllowedClassesTest|FPrimaryAssetId", meta = (GetAllowedClasses = "MyGetAllowedClassesFunc"))
	//FPrimaryAssetId MyPrimaryAsset_GetAllowedClasses;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NoGetDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|TSubclassOf", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
	TSubclassOf<UObject> MyClass_GetDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UClass*")
	UClass* MyClassPtr_NoGetDisallowedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UClass*", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
	UClass* MyClassPtr_GetDisallowedClasses;

	//not worked
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|FSoftClassPath")
	//FSoftClassPath MySoftClass_NoGetDisallowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|FSoftClassPath", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
	//FSoftClassPath MySoftClass_GetDisallowedClasses;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UObject*")
	//UObject* MyObject_NoGetDisallowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|UObject*", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
	//UObject* MyObject_GetDisallowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|FSoftObjectPath")
	//FSoftObjectPath MySoftObject_NoGetDisallowedClasses;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GetDisallowedClassesTest|FSoftObjectPath", meta = (GetDisallowedClasses = "MyGetDisallowedClassesFunc"))
	//FSoftObjectPath MySoftObject_GetDisallowedClasses;

//public://not work
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|TSubclassOf", meta = (AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	TSubclassOf<UObject> MyClass_NoExactClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|TSubclassOf", meta = (ExactClass, AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	TSubclassOf<UObject> MyClass_ExactClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UClass*", meta = (AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	UClass* MyClassPtr_NoExactClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UClass*", meta = (ExactClass, AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	UClass* MyClassPtr_ExactClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftClassPath", meta = (AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	FSoftClassPath MySoftClass_NoExactClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftClassPath", meta = (ExactClass, AllowedClasses = "/Script/Insider.MyCommonObjectChild",GetAllowedClasses = "MyGetAllowedClassesFunc"))
//	FSoftClassPath MySoftClass_ExactClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UObject*", meta = (AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube", GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_NoExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|UObject*", meta = (ExactClass, AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube", GetAllowedClasses = "MyGetAllowedClassesFunc"))
	UObject* MyObject_ExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftObjectPath", meta = (AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube", GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_NoExactClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FSoftObjectPath", meta = (ExactClass, AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.TextureCube", GetAllowedClasses = "MyGetAllowedClassesFunc"))
	FSoftObjectPath MySoftObject_ExactClass;

	//not work
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FPrimaryAssetId", meta = (AllowedClasses = "/Script/Engine.MyPrimaryDataChildAsset",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	//FPrimaryAssetId MyPrimaryAsset_NoExactClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExactClassTest|FPrimaryAssetId", meta = (ExactClass, AllowedClasses = "/Script/Engine.MyPrimaryDataChildAsset",GetAllowedClasses = "MyGetAllowedClassesFunc"))
	//FPrimaryAssetId MyPrimaryAsset_ExactClass;


};


//For AllowedClasses and DisallowedClasses usage in ComponentReference, please refer to AMyProperty_ComponentReference
//////////////////////////////////////////////////////////////////////////
// Macro to simplify UE_LOG for debugging
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "CoreMinimal.h"
#include "Misc/AssetRegistryInterface.h"
#include "InsiderTypes.generated.h"

#define INSIDER_BEGIN namespace Insider{
#define INSIDER_END }

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EInsiderPrintFlags :uint32
{
	None = 0  UMETA(Hidden),
	Recursive = 1,
	Header = 2,
	Class = 4,
	Properties = 8,

	Functions = 16,
	Interfaces = 32,
	Parameters = 64,
	Declaration = 128,

	WithDetails = 256,
	WithMetaData = 512,
	WithSuper = 1024,
	WithHierarchy=2048,
	WithSubObjects=4096,
	DataOnly=8192,




	ObjectDefault = Header | Properties | WithDetails | Recursive UMETA(Hidden),
	PropertyDefault = Header | WithDetails | WithMetaData  UMETA(Hidden),
	FunctionDefault = Header | Properties | WithDetails | WithMetaData  UMETA(Hidden),
	EnumDefault = Header | Properties | WithDetails | WithMetaData  UMETA(Hidden),
	StructDefault = Header | Class | Properties | WithDetails | WithMetaData  UMETA(Hidden),
	ClassDefault = Header | Class | Properties | Functions | Interfaces | WithDetails | WithMetaData| WithHierarchy  UMETA(Hidden),
	PackageDefault = Header | Properties | WithMetaData | Recursive  UMETA(Hidden),
	All= Recursive| Header| Class| Properties| Functions| Interfaces| Declaration| WithDetails| WithMetaData| WithSuper| WithHierarchy  UMETA(Hidden),
};

ENUM_CLASS_FLAGS(EInsiderPrintFlags);


enum class EInsiderSerializationFlags :uint32
{
	None = 0,
	CheckDefaults = 1,
	UseBinary = 2,
	All= CheckDefaults| UseBinary,
};

ENUM_CLASS_FLAGS(EInsiderSerializationFlags);



#define INSIDER_ADD_CLASS_FLAGS(TClass,Flags) TClass::StaticClass()->ClassFlags|=Flags
#define INSIDER_REMOVE_CLASS_FLAGS(TClass,Flags) TClass::StaticClass()->ClassFlags&=~Flags


namespace Insider
{
	
	FString ObjectFlagsToString(EObjectFlags ObjectFlags);
	FString ClassFlagsToString(uint32 ClassFlags);
	FString PropertyFlagsToString(uint64 PropertyFlags);
	FString FunctionFlagsToString(EFunctionFlags functionFlags);

	FString CppFormToString(UEnum::ECppForm cppForm);
	FString StructFlagsToString(EStructFlags flags);
	FString EnumFlagsToString(EEnumFlags flags);
	FString PackageFlagsToString(EPackageFlags flags);
	FString CompressionFlagsToString(ECompressionFlags flags);


	FString NetModeToString(ENetMode netmode);

	FString DependencyPropertyToString(UE::AssetRegistry::EDependencyProperty flags);

}

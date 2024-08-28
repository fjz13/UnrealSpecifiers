#include "MyClass_SparseClassDataTypes.h"
#include "Engine/BlueprintGeneratedClass.h"


/*
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
	//SparseClassData->MyInt_EditDefaultOnly = MyInt_EditDefaultOnly_DEPRECATED;
	//SparseClassData->MyInt_BlueprintReadOnly = MyInt_BlueprintReadOnly_DEPRECATED;
	//SparseClassData->MyString_EditDefault_ReadOnly = MyString_EditDefault_ReadOnly_DEPRECATED;
#endif // WITH_EDITORONLY_DATA


}
//int32 AMyActor_SparseClassDataTypes::GetMyMyInt_BlueprintReadOnly() const
//{
//	return GetMySparseClassData()->MyInt_BlueprintReadOnly; 
//}
#endif // WITH_EDITOR

*/
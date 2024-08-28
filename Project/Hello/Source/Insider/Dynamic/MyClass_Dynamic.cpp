#include "MyClass_Dynamic.h"
#include "UObject/ConstructorHelpers.h"

#if WITH_EDITOR
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/Blueprint.h"

#endif

void UMyClass_Dynamic::MyFunc()
{
	++MyProperty;
}

void UMyClass_Dynamic::AddPropertyToMyClass()
{
	FString path = TEXT("/Game/Dynamic/BP_DynamicClass");

#if WITH_EDITOR

	UBlueprint* bp = ConstructorHelpersInternal::FindOrLoadObject<UBlueprint>(path, LOAD_None);

	FEdGraphPinType pinType;
	pinType.PinCategory=UEdGraphSchema_K2::PC_Float;

	FString defaultValue=TEXT("3.4f");
	FBlueprintEditorUtils::AddMemberVariable(bp, "TestProperty", pinType, defaultValue);

	FKismetEditorUtilities::CompileBlueprint(bp);
#endif

}



	//UClass* objClass= LoadObject<UBlueprint>(nullptr,*path);



	////UClass* objClass = GetClass();
	//FBlueprintEditorUtils::AddMemberVariable(UBlueprint * Blueprint, const FName & NewVarName, const FEdGraphPinType & NewVarType, const FString & DefaultValue/* = FString()*/)

	//const EObjectFlags newObjectFlags = RF_Public;
	//FProperty* NewProperty = NewObject<UIntProperty>(objClass, "TestProperty", newObjectFlags);
	//FProperty* IndexProperty = objClass->FindPropertyByName("Index");

	//NewProperty->SetFlags(RF_Public | RF_Transactional);
	//NewProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_Edit);
	//NewProperty->SetMetaData("DisplayName", TEXT("Test Property"));
	//NewProperty->SetMetaData("Category", TEXT("Test Category"));

	//objClass->AddCppProperty(NewProperty);
	//objClass->StaticLink(true);
	//objClass->Bind();
	//objClass->ConditionalRecompileClass(nullptr);

	//objClass->GetOutermost()->MarkPackageDirty();
//}

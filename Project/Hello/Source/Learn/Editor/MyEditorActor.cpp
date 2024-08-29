// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEditorActor.h"
#include "Log/LogTypes.h"

AMyEditorActor::AMyEditorActor()
{
	
}

#if WITH_EDITORONLY_DATA

void AMyEditorActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property==nullptr)
	{
		return;
	}

	FName propertyName = PropertyChangedEvent.Property->GetFName();
	FString str = propertyName.ToString();

	FFloatProperty* prop= (FFloatProperty*)PropertyChangedEvent.Property;
	float newValue = prop->GetPropertyValue_InContainer(this);
	UE_LOG(LogLearn, Warning, L"Modify:%s to %f", *str, newValue);
	FName widthName= GET_MEMBER_NAME_CHECKED(AMyEditorActor, Width);
	Area = Width*Height;
}
#endif

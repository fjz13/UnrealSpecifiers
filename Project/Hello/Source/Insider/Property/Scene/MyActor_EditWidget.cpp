// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor_EditWidget.h"

FString AMyActor_EditWidget::ValidateMyVector()
{
	if (MyVector_MakeEditWidget_Validate.Length()>100.f)
	{
		return TEXT("Exceed max length:100");
	}
	return TEXT("");
}

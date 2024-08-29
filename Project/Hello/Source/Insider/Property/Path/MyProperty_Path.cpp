// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Path.h"
#include <Utility/InsiderSubsystem.h>

void UMyProperty_Path::PrintValues()
{
	FString str=MyDirectory_Default.Path;
	UInsiderSubsystem::Get().PrintObject(this);
}

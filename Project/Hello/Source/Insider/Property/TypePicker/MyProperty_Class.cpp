// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Class.h"
#include "Asset/MyPrimaryDataAsset.h"
#include "Abilities/Async/AbilityAsync.h"
#include "Engine/TextureCube.h"

TArray<UClass*> UMyProperty_Class::MyGetAllowedClassesFunc()
{
	TArray<UClass*> classes;
	//classes.Add(UMyCommonObject::StaticClass());
	//classes.Add(UMyCommonObjectChild::StaticClass());

	//classes.Add(UTexture::StaticClass());
	//classes.Add(UTexture2D::StaticClass());
	classes.Add(UTextureLightProfile::StaticClass());
	classes.Add(UTextureCube::StaticClass());


	//classes.Add(UTextureCube::StaticClass());

	//classes.Add(UMyPrimaryDataAsset::StaticClass());
	//classes.Add(UMyPrimaryDataChildAsset::StaticClass());

	return classes;
}

TArray<UClass*> UMyProperty_Class::MyGetDisallowedClassesFunc()
{
	TArray<UClass*> classes;
	classes.Add(UAbilityAsync::StaticClass());
	classes.Add(UTexture::StaticClass());
	classes.Add(UTextureCube::StaticClass());

	return classes;
}


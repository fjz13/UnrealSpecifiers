// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyProperty_Thumbnail.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Thumbnail :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "false"))
	UObject* MyObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true"))
	UObject* MyObject_DisplayThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true", ThumbnailSize = "X=256 Y=256"))
	UObject* MyObject_DisplayThumbnail_Large;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true", ThumbnailSize = "X=16 Y=16"))
	UObject* MyObject_DisplayThumbnail_Small;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* MyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true"))
	AActor* MyActor_DisplayThumbnail;
};

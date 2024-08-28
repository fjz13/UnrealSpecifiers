// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_NoExport2.generated.h"

#if !CPP      //noexport struct
USTRUCT(noexport, BlueprintType)
struct FMyStruct_NoExport2
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Score;
};
#endif

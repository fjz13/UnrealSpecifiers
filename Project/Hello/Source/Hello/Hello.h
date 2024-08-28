// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FHelloModule :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;
};


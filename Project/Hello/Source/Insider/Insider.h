// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FInsiderModule :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;
private:
};
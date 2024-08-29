// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyMonster.h"
#include "MyAttributeSet.h"
#include "AbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMyMonster

AMyMonster::AMyMonster()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	AttributeSet_Hide = CreateDefaultSubobject<UMyAttributeSet_Hide>(TEXT("AttributeSet_Hide"));

}

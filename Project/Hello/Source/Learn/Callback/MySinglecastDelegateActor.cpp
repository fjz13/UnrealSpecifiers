// Fill out your copyright notice in the Description page of Project Settings.

#include "MySinglecastDelegateActor.h"
#include "LearnTypes.h"

AMySinglecastDelegateActor::AMySinglecastDelegateActor()
{
}

AMySinglecastDelegateActor::~AMySinglecastDelegateActor()
{
}

// Called when the game starts or when spawned
void AMySinglecastDelegateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMySinglecastDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMySinglecastDelegateActor::BindStatic()
{
	mDelegate.BindStatic(Func_One_Param_Static);
}

void AMySinglecastDelegateActor::BindStatic_WithPayload()
{
	mDelegate.BindStatic(Func_One_Param_Static2,20);
}

void AMySinglecastDelegateActor::BindLambda()
{
	mDelegate.BindLambda([](int val) 
	{
		FString str=FString::Printf(L"%s:%d", L"BindLambda", val);
		GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	});
}

void AMySinglecastDelegateActor::BindRaw()
{
	mDelegate.BindRaw(mCppObject, &LearnDelegateClass::PrintIntRaw);
}

void AMySinglecastDelegateActor::BindSP()
{
	mCppObjectPtr = MakeShareable(new LearnDelegateClass());
	TSharedRef<LearnDelegateClass> sharedRefObj= mCppObjectPtr.ToSharedRef();
	mDelegate.BindSP(sharedRefObj, &LearnDelegateClass::PrintIntSP);
}

void AMySinglecastDelegateActor::BindUFunction()
{
	mDelegate.BindUFunction(this, "Func_One_Param_UFUNCTION");
}


void AMySinglecastDelegateActor::Unbind()
{
	mDelegate.Unbind();
}

void AMySinglecastDelegateActor::BindUObject()
{
	mDelegate.BindUObject(this, &AMySinglecastDelegateActor::Func_One_Param);
}


void AMySinglecastDelegateActor::ExecuteCallback(int32 val)
{
	mDelegate.ExecuteIfBound(val);
}

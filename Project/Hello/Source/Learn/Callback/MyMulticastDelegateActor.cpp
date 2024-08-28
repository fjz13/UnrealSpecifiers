// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMulticastDelegateActor.h"
#include "LearnTypes.h"

AMyMulticastDelegateActor::AMyMulticastDelegateActor()
{
}

// Called when the game starts or when spawned
void AMyMulticastDelegateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyMulticastDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyMulticastDelegateActor::ExecuteCallback(int32 val)
{
	mDelegate.Broadcast(val);
}


void AMyMulticastDelegateActor::AddStatic()
{
	mDelegate.AddStatic(Func_One_Param_Static);
}

void AMyMulticastDelegateActor::AddStatic_WithPayload()
{
	mDelegate.AddStatic(Func_One_Param_Static2, 20);
}

void AMyMulticastDelegateActor::AddLambda()
{
	mDelegate.AddLambda([](int val)
	{
		FString str = FString::Printf(L"%s:%d", L"AddLambda", val);
		GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	});
}

void AMyMulticastDelegateActor::AddRaw()
{
	mDelegate.AddRaw(mCppObject, &LearnDelegateClass::PrintIntRaw);
}

void AMyMulticastDelegateActor::AddSP()
{
	mCppObjectPtr = MakeShareable(new LearnDelegateClass());
	TSharedRef<LearnDelegateClass> sharedRefObj = mCppObjectPtr.ToSharedRef();
	mDelegate.AddSP(sharedRefObj, &LearnDelegateClass::PrintIntSP);
}

void AMyMulticastDelegateActor::AddUFunction()
{
	mDelegate.AddUFunction(this, "Func_One_Param_UFUNCTION");
}


void AMyMulticastDelegateActor::UnbindAll()
{
	mDelegate.Clear();
}

void AMyMulticastDelegateActor::AddUObject()
{
	mDelegate.AddUObject(this, &AMyMulticastDelegateActor::Func_One_Param);
}

void AMyMulticastDelegateActor::AddDelegate()
{
	FMyMulticastDelegate_One::FDelegate mydel = FMyMulticastDelegate_One::FDelegate::CreateStatic(Func_One_Param_Delegate);
	//FMySinglecastDelegate2_One mydel = FMySinglecastDelegate2_One::CreateStatic(Func_One_Param_Delegate);
	mDelegate.Add(mydel);
}

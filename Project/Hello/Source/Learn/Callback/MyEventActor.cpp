// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEventActor.h"
#include "LearnTypes.h"

AMyEventActor::AMyEventActor()
{
}

// Called when the game starts or when spawned
void AMyEventActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyEventActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyEventActor::ExecuteCallback(int32 val)
{
	mEvent.Broadcast(val);
}


void AMyEventActor::AddStatic()
{
	mEvent.AddStatic(Func_One_Param_Static);
}

void AMyEventActor::AddStatic_WithPayload()
{
	mEvent.AddStatic(Func_One_Param_Static2, 20);
}

void AMyEventActor::AddLambda()
{
	mEvent.AddLambda([](int val)
	{
		FString str = FString::Printf(L"%s:%d", L"AddLambda", val);
		GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	});
}

void AMyEventActor::AddRaw()
{
	mEvent.AddRaw(mCppObject, &LearnDelegateClass::PrintIntRaw);
}

void AMyEventActor::AddSP()
{
	mCppObjectPtr = MakeShareable(new LearnDelegateClass());
	TSharedRef<LearnDelegateClass> sharedRefObj = mCppObjectPtr.ToSharedRef();
	mEvent.AddSP(sharedRefObj, &LearnDelegateClass::PrintIntSP);
}

void AMyEventActor::AddUFunction()
{
	mEvent.AddUFunction(this, "Func_One_Param_UFUNCTION");
}


void AMyEventActor::UnbindAll()
{
	mEvent.Clear();
}

void AMyEventActor::AddUObject()
{
	mEvent.AddUObject(this, &AMyEventActor::Func_One_Param);
}

void AMyEventActor::AddDelegate()
{
	FMyEvent_One::FDelegate mydel = FMyEvent_One::FDelegate::CreateStatic(Func_One_Param_Delegate);
	//FMySinglecastDelegate2_One mydel = FMySinglecastDelegate2_One::CreateStatic(Func_One_Param_Delegate);
	mEvent.Add(mydel);
}

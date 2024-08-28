// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProperty_BindWidget.generated.h"




UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()
	UMyProperty_BindWidget(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_NotFound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_SameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MyTextBlock_Bind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock* MyTextBlock_Optional1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget))
	class UTextBlock* MyTextBlock_Optional2;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetAnimation* MyAnimation_NotFound;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UWidgetAnimation* MyAnimation_SameName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MyAnimation_Bind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* MyAnimation_BindOptional;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* MyAnimation_BindOptional2;
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMyClickedMulticastDelegate);

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = MyEvent)
	FOnMyClickedMulticastDelegate MyClickedMulticastDelegate;

public:
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString, FOnMyClickedDelegate, int32, MyValue);

	UPROPERTY(EditAnywhere, Category = MyEvent)
	FOnMyClickedDelegate MyClickedDelegate_Default;

	UPROPERTY(EditAnywhere, Category = MyEvent)
	FOnMyClickedDelegate MyClickedEvent;

	UPROPERTY(EditAnywhere, Category = MyEvent, meta = (IsBindableEvent = "True"))
	FOnMyClickedDelegate MyClickedDelegate_Bind;

public:
	UPROPERTY(EditAnywhere, Category = Design)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, Category = Design, meta = (DesignerRebuild))
	int32 MyInt_DesignerRebuild = 123;
public:
	UFUNCTION(BlueprintCallable)
	void RunTest();
};


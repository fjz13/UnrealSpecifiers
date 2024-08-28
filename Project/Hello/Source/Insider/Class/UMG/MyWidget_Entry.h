// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "MyWidget_Entry.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyEntryItem :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
	FText Name;
};

//////////////////////////////////////////////////////////////////////////

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyEntryWidget :public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ValueTextBlock;
};

//////////////////////////////////////////////////////////////////////////

UINTERFACE(MinimalAPI)
class UMyCustomListEntry : public UUserObjectListEntry
{
	GENERATED_UINTERFACE_BODY()
};

class IMyCustomListEntry : public IUserObjectListEntry
{
	GENERATED_IINTERFACE_BODY()
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCustomEntryWidget :public UUserWidget, public IMyCustomListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ValueTextBlock;
};

//////////////////////////////////////////////////////////////////////////


UCLASS()
class INSIDER_API UMyListContainerWidget :public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, EntryClass = MyCustomEntryWidget, EntryInterface = MyCustomListEntry))
	class UListView* MyListView;
};
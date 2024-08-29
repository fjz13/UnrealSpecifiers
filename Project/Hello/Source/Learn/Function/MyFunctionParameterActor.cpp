// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionParameterActor.h"
#include "LearnTypes.h"

AMyFunctionParameterActor::AMyFunctionParameterActor()
{

}

// Called when the game starts or when spawned
void AMyFunctionParameterActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyFunctionParameterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyFunctionParameterActor::Func_Input(int32 val)
{
	FString str= FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


void AMyFunctionParameterActor::Func_Input_Const(const int32& val)
{
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Output(int32& val)
{
	val = 123;
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


int32 AMyFunctionParameterActor::Func_Return()
{
	int32 val = 234;
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	return val;
}

int32 AMyFunctionParameterActor::Func_Pure()
{
	int32 val = 456;
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	return val;
}

void AMyFunctionParameterActor::Func_InputRef(int32& val)
{
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	++val;
	str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


void AMyFunctionParameterActor::Func_InputOtherName(int32 val)
{
	FString str = FString::FromInt(val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

MyEnum AMyFunctionParameterActor::Func_Enum_Input(MyEnum val)
{
	return val;
}

void AMyFunctionParameterActor::Func_Enum_Output(MyEnum& val)
{
	val = MyEnum::Second;
}

void AMyFunctionParameterActor::Func_Enum_Ref(MyEnum& val)
{
	val = MyEnum::Second;
}

FMyVector AMyFunctionParameterActor::Func_Struct_Input(FMyVector val)
{
	val.X += 1.f;
	val.Y += 1.f;
	val.Z += 1.f;
	return val;
}

void AMyFunctionParameterActor::Func_Struct_Output(FMyVector& val)
{
	val.X = 1.f;
	val.Y = 1.f;
	val.Z = 1.f;
}

void AMyFunctionParameterActor::Func_Struct_Ref(UPARAM(ref) FMyVector& val)
{
	val.X += 1.f;
	val.Y += 1.f;
	val.Z += 1.f;
}

void AMyFunctionParameterActor::Func_Name_Input(FName name)
{
	FString str = name.ToString();
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Name_Output(FName& name)
{
	name = TEXT("Func_Name_Output");
}

void AMyFunctionParameterActor::Func_Name_Ref(UPARAM(ref) FName& name)
{
	name = TEXT("Func_Name_Ref");

}

void AMyFunctionParameterActor::Func_String_Input(FString str)
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_String_Input_Const(const FString& str)
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_String_Output(FString& str)
{
	str = TEXT("Func_String_Output");
}

void AMyFunctionParameterActor::Func_String_Ref(UPARAM(ref) FString& str)
{
	str = TEXT("Func_String_Ref");

}


void AMyFunctionParameterActor::Func_Text_Input(FText text)
{
	FString str = text.ToString();
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Text_Input_Const(const FText& text)
{
	FString str = text.ToString();
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Text_Output(FText& text)
{
	text = FText::FromString(TEXT("Func_Text_Output"));
}

void AMyFunctionParameterActor::Func_Text_Ref(UPARAM(ref) FText& text)
{
	text = FText::FromString(TEXT("Func_Text_Ref"));
}

void AMyFunctionParameterActor::Func_Array_Input(TArray<int32> items)
{
	FString str;
	for (int32 val:items)
	{
		str.AppendInt(val);
		str.AppendChar(L' ');
	}
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Array_Input_Const(const TArray<int32>& items)
{
	FString str;
	for (int32 val : items)
	{
		str.AppendInt(val);
		str.AppendChar(L' ');
	}
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Array_Output(TArray<int32>& items)
{
	items.Add(1);
	items.Add(2);
	items.Add(3);
	FString str;
	for (int32 val : items)
	{
		str.AppendInt(val);
		str.AppendChar(L' ');
	}
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Array_Ref(UPARAM(ref) TArray<int32>& items)
{
	items.Add(1);
	items.Add(2);
	items.Add(3);
	FString str;
	for (int32 val : items)
	{
		str.AppendInt(val);
		str.AppendChar(L' ');
	}
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

TArray<int32> AMyFunctionParameterActor::Func_Array_Return()
{
	TArray<int32> items;
	items.Add(1);
	items.Add(2);
	items.Add(3);

	FString str;
	for (int32 val : items)
	{
		str.AppendInt(val);
		str.AppendChar(L' ');
	}
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	return items;
}

void AMyFunctionParameterActor::Func_Class_Input(UMyItem* obj)
{
	if (obj==nullptr)
	{
		return;
	}

	FString str;
	str += FString::Printf(L"Id:%d Weight:%f", obj->Id, obj->Weight);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyFunctionParameterActor::Func_Class_Input_ConstPtr(const UMyItem* obj)
{
	if (obj == nullptr)
	{
		return;
	}
	FString str;
	str += FString::Printf(L"Id:%d Weight:%f", obj->Id, obj->Weight);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

UMyItem* AMyFunctionParameterActor::Func_Class_Output()
{
	UMyItem* item = NewObject<UMyItem>(this);
	item->Id = 10;
	item->Weight = 100;
	return item;
}

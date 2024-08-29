#include "MyWidget_Tick.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyWidget_WithNativeTick::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UKismetSystemLibrary::PrintString(nullptr, TEXT("WithNativeTick"), true);
}

void UMyWidget_DisableNativeTick::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UKismetSystemLibrary::PrintString(nullptr, TEXT("DisableNativeTick"), true);
}

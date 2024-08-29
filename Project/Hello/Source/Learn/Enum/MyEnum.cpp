#include "MyEnum.h"

FText GetMyCustomEnumDisplayName(int32 val)
{
	MyCustomEnum enumValue = (MyCustomEnum)val;
	switch (enumValue)
	{
	case MyCustomEnum::Dance:
		return FText::FromString(TEXT("Learn_Dance"));
	case MyCustomEnum::Rain:
		return FText::FromString(TEXT("Learn_Rain"));
	case MyCustomEnum::Song:
		return FText::FromString(TEXT("Learn_Song"));
	default:
		return FText::FromString(TEXT("Invalid MyEnum"));
	}
}

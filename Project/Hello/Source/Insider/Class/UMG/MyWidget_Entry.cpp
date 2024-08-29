#include "MyWidget_Entry.h"
#include "Components/TextBlock.h"

void UMyEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UMyEntryItem* item = Cast<UMyEntryItem>(ListItemObject))
	{
		if (ValueTextBlock != nullptr)
		{
			ValueTextBlock->SetText(item->Name);
		}
	}

	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}

UMyCustomListEntry::UMyCustomListEntry(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UMyCustomEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UMyEntryItem* item = Cast<UMyEntryItem>(ListItemObject))
	{
		if (ValueTextBlock != nullptr)
		{
			ValueTextBlock->SetText(item->Name);
		}
	}

	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}

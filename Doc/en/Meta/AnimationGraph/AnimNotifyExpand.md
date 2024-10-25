#AnimNotifyExpand

- **Function Description:** Allows properties under UAnimNotify or UAnimNotifyState to be directly expanded in the Details panel.
- **Usage Location:** UPROPERTY
- **Engine Module:** AnimationGraph
- **Metadata Type:** bool
- **Restriction Type:** Properties under UAnimNotify or UAnimNotifyState subclasses, specifically the FName attribute

Enables properties under UAnimNotify or UAnimNotifyState to be directly expanded in the Details panel.

No application examples were found in the source code.

## Principle:

Reviewing the source code reveals that it is hardcoded to only work with a few built-in engine classes, which is why custom test code does not take effect.

It is indeed not ideal for the code to be so rigidly written. I hope for future improvements, at which point there should be examples included in the source code.

```cpp

PropertyModule.RegisterCustomClassLayout( "EditorNotifyObject", FOnGetDetailCustomizationInstance::CreateStatic(&FAnimNotifyDetails::MakeInstance));

bool FAnimNotifyDetails::CustomizeProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property)
{
	if(Notify && Notify->GetClass() && Property->IsValidHandle())
{
	FString ClassName = Notify->GetClass()->GetName();
	FString PropertyName = Property->GetProperty()->GetName();
	bool bIsBoneName = Property->GetBoolMetaData(TEXT("AnimNotifyBoneName"));

	if(ClassName.Find(TEXT("AnimNotify_PlayParticleEffect")) != INDEX_NONE && PropertyName == TEXT("SocketName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if(ClassName.Find(TEXT("AnimNotifyState_TimedParticleEffect")) != INDEX_NONE && PropertyName == TEXT("SocketName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if(ClassName.Find(TEXT("AnimNotify_PlaySound")) != INDEX_NONE && PropertyName == TEXT("AttachName"))
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
	else if (ClassName.Find(TEXT("_SoundLibrary")) != INDEX_NONE && PropertyName == TEXT("SoundContext"))
	{
		CategoryBuilder.AddProperty(Property);
		FixBoneNamePropertyRecurse(Property);
		return true;
	}
	else if (ClassName.Find(TEXT("AnimNotifyState_Trail")) != INDEX_NONE)
	{
		if(PropertyName == TEXT("FirstSocketName") || PropertyName == TEXT("SecondSocketName"))
		{
			AddBoneNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
		else if(PropertyName == TEXT("WidthScaleCurve"))
		{
			AddCurveNameProperty(CategoryBuilder, Notify, Property);
			return true;
		}
	}
	else if (bIsBoneName)
	{
		AddBoneNameProperty(CategoryBuilder, Notify, Property);
		return true;
	}
}
}

```
# AnimNotifyExpand

功能描述: 使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。
使用位置: UPROPERTY
Feature: Editor
引擎模块: AnimationGraph
元数据类型: bool
限制类型: UAnimNotify或UAnimNotifyState子类下的FName属性
Status: NotUsed

使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里。

在源码里也没有找到应用的例子。

原理：

看源码，里面写死了只对有限的引擎自带的几个类起效，因此自己的测试代码并不能生效。

这种写法确实不应该这么写死，希望以后改进吧。到时应该就有源码里的例子了。

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
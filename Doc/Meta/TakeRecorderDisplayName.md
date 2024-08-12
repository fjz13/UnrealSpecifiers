# TakeRecorderDisplayName

Description: 指定UTakeRecorderSource的显示名字。
Usage: UCLASS
Feature: Blueprint
Group: Sequencer
Type: string="abc"
LimitedType: UTakeRecorderSource的子类上
Status: Done

指定UTakeRecorderSource的显示名字。

这个一般是引擎内部自己用，除非想自己自定义UTakeRecorderSource才会派上用场。因为原理和展示过于简单，因此就不自己构建测试代码。

源码例子：

```cpp
UCLASS(Category="Actors", meta = (TakeRecorderDisplayName = "Player"))
class UTakeRecorderPlayerSource : public UTakeRecorderSource
{}
```

测试效果：

在引擎源码中可见有多个UTakeRecorderSource，其上都标了名字。

![Untitled](TakeRecorderDisplayName/Untitled.png)

原理：

用TakeRecorderDisplayName指定的名字来作为菜单项的名字。

```cpp
TSharedRef<SWidget> SLevelSequenceTakeEditor::OnGenerateSourcesMenu()
{
		for (UClass* Class : SourceClasses)
		{
			TSubclassOf<UTakeRecorderSource> SubclassOf = Class;
		
			MenuBuilder.AddMenuEntry(
				FText::FromString(Class->GetMetaData(TEXT("TakeRecorderDisplayName"))),
				Class->GetToolTipText(true),
				FSlateIconFinder::FindIconForClass(Class),
				FUIAction(
					FExecuteAction::CreateSP(this, &SLevelSequenceTakeEditor::AddSourceFromClass, SubclassOf),
					FCanExecuteAction::CreateSP(this, &SLevelSequenceTakeEditor::CanAddSourceFromClass, SubclassOf)
				)
			);
		}
}
```
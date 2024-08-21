# EntryInterface

- **功能描述：** 限定EntryWidgetClass属性上可选类必须实现的接口，用在DynamicEntryBox和ListView这两个Widget上。
- **使用位置：** UCLASS, UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** string="abc"
- **限制类型：** UWidget子类
- **关联项：** [EntryClass](../EntryClass.md)
- **常用程度：** ★★★

限定EntryWidgetClass属性上可选类必须实现的接口，用在DynamicEntryBox和ListView这两个Widget上。

以ListView为例，术语Entry指的是列表中显示的子控件，而Item指的是列表背后的数据元素。比如列表背包有1000个元素(Item)，但是同时只能呈现10个控件(Entry)在界面上。

因此EntryInterface和EntryClass，顾名思义，指的是EntryWidget上要实现的接口和其基类。

用法展示，以下都用ListView举例，DynamicBox同理。

```cpp
//1. ListView作为别的Widget的属性，因此会在Property上进行Meta的提取判断。
//该属性必须是BindWidget，才能自动绑定到UMG里的控件，同时作为C++ property才能被枚举到。
 class UMyUserWidget : public UUserWidget
 {
		UPROPERTY(BindWidget, meta = (EntryClass = MyListEntryWidget,EntryInterface = MyUserListEntry ))
		UListViewBase* MyListView;
 }

//2. 如果在Property上没有找到改Meta，也会尝试在Widget Class身上直接找
UCLASS(meta = (EntryClass = MyListEntryWidget, EntryInterface = "/Script/UMG.UserObjectListEntry"))
class UMyListView : public UListViewBase, public ITypedUMGListView<UObject*>
{}

//3.之后在ClassPicker的时候，EntryClass指定其父类，EntryInterface指定类必须实现的接口
```

## 源码中的用法：

```cpp
UCLASS(Abstract, NotBlueprintable, hidedropdown, meta = (EntryInterface = UserListEntry), MinimalAPI)
class UListViewBase : public UWidget
{
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ListEntries, meta = (DesignerRebuild, AllowPrivateAccess = true, MustImplement = "/Script/UMG.UserListEntry"))
	TSubclassOf<UUserWidget> EntryWidgetClass;
}

UCLASS(meta = (EntryInterface = "/Script/UMG.UserObjectListEntry"), MinimalAPI)
class UListView : public UListViewBase, public ITypedUMGListView<UObject*>
{}

//其中UserObjectListEntry接口继承自UserListEntry，Entry Widget都得继承自该接口。
UINTERFACE(MinimalAPI)
class UUserObjectListEntry : public UUserListEntry
{}

SNew(SClassPropertyEntryBox)
.AllowNone(false)
.IsBlueprintBaseOnly(true)
.RequiredInterface(RequiredEntryInterface)
.MetaClass(EntryBaseClass ? EntryBaseClass : UUserWidget::StaticClass())
.SelectedClass(this, &FDynamicEntryWidgetDetailsBase::GetSelectedEntryClass)
.OnSetClass(this, &FDynamicEntryWidgetDetailsBase::HandleNewEntryClassSelected)
```

在FDynamicEntryWidgetDetailsBase中判断EntryInterface和EntryClass，然后在SClassPropertyEntryBox中限定属性细节面板ClassPicker的可选类。FDynamicEntryWidgetDetailsBase是FListViewBaseDetails和FDynamicEntryBoxDetails的基类，因此ListView和DynamicBox的属性细节面板都由它进行定制化。

## 测试代码：

```cpp
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
```

## 蓝图中的效果：

如果MyListView上没有指定EntryClass或EntryInterface，则在ListView的EntryWidgetClass属性上可以选择蓝图创建的UMG_MyEntry(继承自C++的UMyEntryWidget)。

![Untitled](Untitled.png)

如果如上面代码中所示，我们新创建一个接口为MyCustomListEntry，并且也新建一个新的MyCustomEntryWidget，然后在MyListView属性上指定EntryClass或EntryInterface（可以一起也可以单个），则ListView的EntryWidgetClass属性可选的类就被限制住了。

![Untitled](Untitled%201.png)

还有一种用法是当你想自定义一个ListView，可以选择继承自ListViewBase，然后在这个子类上直接限定EntryClass或EntryInterface，效果和上图是一样的。

```cpp
UCLASS(meta = (EntryClass = MyCustomEntryWidget, EntryInterface = MyCustomListEntry))
class UMyListView : public UListViewBase, public ITypedUMGListView<UObject*>
{}
```

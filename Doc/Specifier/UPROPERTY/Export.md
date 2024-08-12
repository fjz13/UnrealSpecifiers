# Export

Description: 只适用于Object属性（或Object数组）。说明Object被复制时（例如复制/粘贴操作）指定到此属性的Object应整体导出为一个子Object块，而非只是输出Object引用本身。只用在对象引用属性上，或者对象数组上。
指定该对象引用在被复制的时候，应该导出当做一个子对象，而不是仅仅复制引用。
其实就是浅复制和深复制的区别。
Type: bool
Feature: Behavior
LimitedType: Object属性，或Object数组
EPropertyFlags: CPF_ExportObject (../../Flags/EPropertyFlags/CPF_ExportObject.md)
Status: Done

主要是用在Export 操作的时候，用来决定如何导出Object*属性的内容。NoExport的话是只输出对象引用的路径，而Export的话会输出这个对象其再内部的的属性值。

![Untitled](Export/Untitled.png)

测试代码：

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ExportObject :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyValue = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Export :public UDataAsset
{
public:
public:
	GENERATED_BODY()
		UMyProperty_Export(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Export, Category = Behavior)
		UMyProperty_ExportObject* ObjectExport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UMyProperty_ExportObject* ObjectWithoutExport;
};
```

源码内作用的函数：

```cpp
void ExportProperties
(）
{
	FObjectPropertyBase* ExportObjectProp = (Property->PropertyFlags & CPF_ExportObject) != 0 ? CastField<FObjectPropertyBase>(Property) : NULL;
}
```

配置的对象值：

![Untitled](Export/Untitled%201.png)

导出的文本：

```jsx
Begin Object Class=/Script/Insider.MyProperty_Export Name="MyPropertyExportAsset" ExportPath=/Script/Insider.MyProperty_Export'"/Game/Property/MyPropertyExportAsset.MyPropertyExportAsset"'
   Begin Object Class=/Script/Insider.MyProperty_ExportObject Name="EO1" ExportPath=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO1.EO1"'
      "MyValue"=456
   End Object
   "ObjectExport"=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO1.EO1"'
   "ObjectWithoutExport"=/Script/Insider.MyProperty_ExportObject'"/Game/Property/EO2.EO2"'
End Object
```

可以看到ObjectExport的对象也导出的字段值，但是ObjectWithoutExport只有路径。

要注意一点的是，要让Export标记在ExportProperties起作用，export标记不能用在对象的sub object上，否则会走ExportInnerObjects的调用路线。上面例子中ObjectExport和ObjectWithoutExport都是指向了外部的另外一个对象，所以用DataAsset来产生资产。

在源码中搜索一下，用在一些内部Settings或配置的对象比较适合，这样可以拥有独立的两个配置。

from stuff: “This is used with UExporter classes (for example, for exporting objects as text). Object properties marked as ‘export’ will be fully exported (full object definition, including its properties) with the owning object instead of being exported as just the object name and path as the property value.”
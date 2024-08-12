# NoClear

Description: 阻止从编辑器将此Object引用设为空。隐藏编辑器中的清除（和浏览）按钮。
在属性编辑器中不可以设为None，隐藏Clear按钮。
对对象的指针有效，在下拉菜单里不出现Clear按钮。
Type: bool
Feature: DetailsPanel, Editor
LimitedType: UObject*
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_NoClear (../../Flags/EPropertyFlags/CPF_NoClear.md)
Status: Done

测试代码：

```cpp
UPROPERTY(EditAnywhere, Category = Object)
class UMyClass_Default* MyObject_Normal;
//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_NoClear | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
UPROPERTY(EditAnywhere, NoClear, Category = Object)
class UMyClass_Default* MyObject_NoClear;

//构造函数赋值：
MyObject_Normal = CreateDefaultSubobject<UMyClass_Default>("MyObject_Normal");
MyObject_NoClear = CreateDefaultSubobject<UMyClass_Default>("MyObject_NoClear");
```

蓝图的表现：

![Untitled](NoClear/Untitled.png)
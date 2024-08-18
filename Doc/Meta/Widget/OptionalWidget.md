# OptionalWidget

功能描述: 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。
使用位置: UPROPERTY
Feature: UMG
引擎模块: Widget Property
元数据类型: bool
限制类型: UWidget子类里属性
Example: UPROPERTY(meta=(BindWidget, OptionalWidget=true))
Status: Linked
Parent item: BindWidget (BindWidget.md)
常用程度: 3

必须配合BindWidget使用。

BindWidget+OptionalWidget=BindWidgetOptional
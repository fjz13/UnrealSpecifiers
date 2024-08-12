# OptionalWidget

Description: 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。
Usage: UPROPERTY
Feature: UMG
Group: Widget Property
Type: bool
LimitedType: UWidget子类里属性
Example: UPROPERTY(meta=(BindWidget, OptionalWidget=true))
Status: Linked
Parent item: BindWidget (BindWidget.md)

必须配合BindWidget使用。
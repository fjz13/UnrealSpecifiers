# OptionalWidget

Usage: UPROPERTY
Feature: UMG
Type: bool
Description: 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。
Example: UPROPERTY(meta=(BindWidget, OptionalWidget=true))
LimitedType: UWidget子类里属性
Status: Linked
Group: Widget Property
Parent item: BindWidget (BindWidget.md)

必须配合BindWidget使用。
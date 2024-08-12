# CLASS_RequiredAPI

Value: 0x00100000u
Description: 指定该类必须具有DLL导出，导出所有函数和属性
Feature: DllExport
Status: Not started
Trait: DefaultC++, Internal
UCLASS: UCLASS() (../../Specifier/UCLASS/UCLASS().md)

内部标记。标明这个类有用MODULENAME_API修饰，会导出函数和属性。如果不写，就不会有这个标记。
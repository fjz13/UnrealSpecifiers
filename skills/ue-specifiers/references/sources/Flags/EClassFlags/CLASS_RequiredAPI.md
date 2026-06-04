---
title: "CLASS_RequiredAPI"
id: "EClassFlags.CLASS_RequiredAPI"
kind: "flag"
symbol: "CLASS_RequiredAPI"
scope: "EClassFlags"
category: "EClassFlags"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该类必须具有DLL导出，导出所有函数和属性"
usage: "DllExport"
---

# CLASS_RequiredAPI

Value: 0x00100000u
Description: 指定该类必须具有DLL导出，导出所有函数和属性
Feature: DllExport
Status: Not started
Trait: DefaultC++, Internal
UCLASS: UCLASS_Empty (../../Specifier/UCLASS/UCLASS_Empty.md)

内部标记。标明这个类有用MODULENAME_API修饰，会导出函数和属性。如果不写，就不会有这个标记。
---
title: "CLASS_MatchedSerializers"
id: "EClassFlags.CLASS_MatchedSerializers"
kind: "flag"
symbol: "CLASS_MatchedSerializers"
scope: "EClassFlags"
category: "EClassFlags"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Value: 0x00000020u"
usage: "LoadConstruct"
---

# CLASS_MatchedSerializers

Value: 0x00000020u
Feature: LoadConstruct
Status: Done
Trait: DefaultC++, Internal
UCLASS: UCLASS_Empty (../../Specifier/UCLASS/UCLASS_Empty.md), MatchedSerializers (../../Specifier/UCLASS/MatchedSerializers.md)

在UClass::IsSafeToSerializeToStructuredArchives中被使用，只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出，只在编辑器情况下使用。
---
title: "FUNC_Private"
id: "EFunctionFlags.FUNC_Private"
kind: "flag"
symbol: "FUNC_Private"
scope: "EFunctionFlags"
category: "EFunctionFlags"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Function is accessible only in the class it is defined in (cannot be overridden, but function name may be reused in s..."
usage: "Trait"
---

# FUNC_Private

Value: 0x00040000
Description: Function is accessible only in the class it is defined in (cannot be overridden, but function name may be reused in subclasses. IOW: if overridden, parameters don't need to match, and Super.Func() cannot be accessed since it's private.)
Feature: Trait
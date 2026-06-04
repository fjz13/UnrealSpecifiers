# Meta Enum Struct And Bitmask

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Enum And Bitmask Metadata

> Doc root: `Meta/Enum/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Bitflags` | 设定一个枚举支持采用位标记赋值，从而在蓝图中可以识别出来是BitMask | UENUM | `Bitflags.md` |
| `Bitmask` | 设定一个属性采用Bitmask赋值 | UPROPERTY | `Bitmask.md` |
| `BitmaskEnum` | 使用位标记后采用的枚举名字 | UPROPERTY | `BitmaskEnum.md` |
| `Enum` | 给一个String指定以枚举里值的名称作为选项 | UPROPERTY | `Enum.md` |
| `EnumDisplayNameFn` | 在Runtime下为枚举字段提供自定义名称的函数回调 | UENUM | `EnumDisplayNameFn.md` |
| `EnumValueDisplayNameOverrides` | 改变枚举属性值上的显示名字 | UPROPERTY | `EnumValueDisplayNameOverrides.md` |
| `GetRestrictedEnumValues` | 指定一个函数来指定枚举属性值的哪些枚举选项是禁用的 | UPROPERTY | `GetRestrictedEnumValues.md` |
| `InvalidEnumValues` | 指定枚举属性值上不可选的枚举值选项，用以排除一些选项 | UPROPERTY | `InvalidEnumValues.md` |
| `UseEnumValuesAsMaskValuesInEditor` | 指定枚举值已经是位移后的值，而不是位标记的索引下标 | UENUM | `UseEnumValuesAsMaskValuesInEditor.md` |
| `ValidEnumValues` | 指定枚举属性值上可选的枚举值选项 | UPROPERTY | `ValidEnumValues.md` |

## UMETA Value Metadata

> Doc root: `Meta/Enum/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `DisplayValue` | Enum /Script/Engine.AnimPhysCollisionType | UENUM::UMETA | `UMETA/DisplayValue.md` |
| `Enum.UMETA.DisplayName` | 改变枚举值的显示名称 | UENUM::UMETA | `UMETA/DisplayName.md` |
| `Enum.UMETA.Hidden` | 隐藏UENUM的某个值 | UENUM::UMETA | `UMETA/Hidden.md` |
| `Grouping` | Enum /Script/Engine.EAlphaBlendOption | UENUM::UMETA | `UMETA/Grouping.md` |
| `Spacer` | 隐藏UENUM的某个值 | UENUM::UMETA | `UMETA/Spacer.md` |
| `TraceQuery` | Enum /Script/Engine.ECollisionChannel | UENUM::UMETA | `UMETA/TraceQuery.md` |

## Struct Metadata

> Doc root: `Meta/Struct/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `HasNativeBreak` | 为该结构指定一个C++内的UFunction函数作为Break节点的实现 | USTRUCT | `HasNativeBreak.md` |
| `HasNativeMake` | 为该结构指定一个C++内的UFunction函数作为Mreak节点的实现 | USTRUCT | `HasNativeMake.md` |
| `MakeStructureDefaultValue` | 存储BP中自定义结构里的属性的默认值 | UPROPERTY | `MakeStructureDefaultValue.md` |


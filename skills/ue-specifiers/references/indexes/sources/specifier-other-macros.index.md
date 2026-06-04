# Specifier Other Macros

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Specifier - UENUM

> Doc root: `Specifier/UENUM/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `BlueprintType` | 可以作为蓝图变量 | UENUM / BlueprintType | `BlueprintType.md` |
| `Flags` | 把该枚举的值作为一个标志来拼接字符串输出 | UENUM / Flags | `Flags.md` |
| `UENUM(标识符)` | UE5.8 UHT 通过 UhtEnumParser 识别 UENUM，创建 enum 类型并使用 UhtTableNames.Enum 的 keyword/specifier table 解析枚举 specifier。该页是 UENUM | UENUM | `../UENUM.md` |


## Specifier - UINTERFACE

> Doc root: `Specifier/UINTERFACE/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Blueprintable` | 可以在蓝图中实现 | UINTERFACE / Blueprint | `Blueprint/Blueprintable.md` |
| `ConversionRoot` | Sets IsConversionRoot metadata flag for this interface. | UINTERFACE / UHT | `UHT/ConversionRoot.md` |
| `MinimalAPI` | 指定该UInterface对象不导出到别的模块 | UINTERFACE / UHT | `UHT/MinimalAPI.md` |
| `NotBlueprintable` | 指定不可以在蓝图中实现 | UINTERFACE / Blueprint | `Blueprint/NotBlueprintable.md` |
| `UINTERFACE(标识符)` | UE5.8 UHT 通过 UhtInterfaceClassParser 识别 UINTERFACE，创建 interface class 并使用 UhtTableNames.Interface 的 keyword/specifier ta | UINTERFACE | `../UINTERFACE.md` |


## Specifier - UPARAM

> Doc root: `Specifier/UPARAM/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Const` | 指定该函数参数不可更改 | UPARAM / Blueprint | `Blueprint/Const.md` |
| `DisplayName` | 更改函数参数在蓝图节点上的显示名字 | UPARAM / Blueprint | `Blueprint/DisplayName.md` |
| `NotReplicated` | 只用于 ServiceRequest 产生的 replicated parameter，可把该参数标记为不参与 service request 参数复制 | UPARAM / Network | `NotReplicated.md` |
| `Required` | 指定函数的参数节点必须连接提供一个值 | UPARAM / Blueprint | `Blueprint/Required.md` |
| `UPARAM(标识符)` | UE5.8 UHT 在解析 property argument 时遇到 UPARAM 会切换到 property argument specifier table。该页是 UPARAM 条目索引，不是单个 specifier | UPARAM | `../UPARAM.md` |
| `ref` | 使得函数的参数变成引用类型 | UPARAM / Blueprint | `Blueprint/ref.md` |


## Specifier - USTRUCT

> Doc root: `Specifier/USTRUCT/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Atomic` | 指定该结构在序列化的时候总是一整个输出全部属性，而不是只输出改变的属性 | USTRUCT / UHT | `UHT/Atomic.md` |
| `BlueprintInternalUseOnly` | 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递 | USTRUCT / Blueprint | `Blueprint/BlueprintInternalUseOnly.md` |
| `BlueprintInternalUseOnlyHierarchical` | 在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制 | USTRUCT / Blueprint | `Blueprint/BlueprintInternalUseOnlyHierarchical.md` |
| `BlueprintType` | 允许这个结构在蓝图中声明变量 | USTRUCT / Blueprint | `Blueprint/BlueprintType.md` |
| `HasDefaults` | 指定该结构的字段拥有默认值。这样如果本结构作为函数参数或返回值时候，函数则可以为其提供默认值 | USTRUCT / UHT | `UHT/HasDefaults.md` |
| `HasNoOpConstructor` | 指定该结构拥有ForceInit的构造函数，这样在作为BP function返回值的时候，可以调用来初始化 | USTRUCT / UHT | `UHT/HasNoOpConstructor.md` |
| `IsAlwaysAccessible` | 指定UHT在生成文件的时候总是可以访问到改结构的声明，否则要在gen.cpp里生成镜像结构定义 | USTRUCT / UHT | `UHT/IsAlwaysAccessible.md` |
| `IsCoreType` | 指定该结构是核心类，UHT在用它的时候不需要前向声明 | USTRUCT / UHT | `UHT/IsCoreType.md` |
| `NoExport` | 指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据 | USTRUCT / UHT | `UHT/NoExport.md` |
| `USTRUCT(标识符)` | UE5.8 UHT 通过 UhtScriptStructParser 识别 USTRUCT，创建 script struct 并使用 UhtTableNames.ScriptStruct 的 keyword/specifier table | USTRUCT | `../USTRUCT.md` |
| `immutable` | UE5.8 中正在淘汰。Immutable 只允许 NoExportTypes.h 中的 mirror structs，项目自定义 USTRUCT 不应使用 | USTRUCT / Serialization | `immutable.md` |




# Meta Type Picker Assets And Objects

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - Asset

> Doc root: `Meta/Asset/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `DisallowedAssetDataTags` | 在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择 | UPROPERTY | `DisallowedAssetDataTags.md` |
| `ForceShowEngineContent` | 指定UObject*属性的资源可选列表里强制可选引擎的内建资源 | UPROPERTY | `ForceShowEngineContent/ForceShowEngineContent.md` |
| `ForceShowPluginContent` | 指定UObject*属性的资源可选列表里强制可选其他插件里的内建资源 | UPROPERTY | `ForceShowEngineContent/ForceShowPluginContent.md` |
| `GetAssetFilter` | 指定一个UFUNCTION来对UObject*属性的可选资源进行排除过滤 | UPROPERTY | `GetAssetFilter.md` |
| `RequiredAssetDataTags` | 在UObject*属性上指定Tags来进行过滤，必须拥有该Tags才可以被选择 | UPROPERTY | `RequiredAssetDataTags.md` |


## Meta - Object

> Doc root: `Meta/Object/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AssetBundles` | 标明该属性其引用的资产属于哪一些AssetBundles | UPROPERTY | `AssetBundles.md` |
| `CollapsableChildProperties` | 在TextureGraph模块中新增加的meta。用于折叠一个结构的内部属性 | UPROPERTY | `CollapsableChildProperties.md` |
| `DisplayThumbnail` | 指定是否在该属性左侧显示一个缩略图 | UPROPERTY | `DisplayThumbnail.md` |
| `ExposeFunctionCategories` | 指定该Object属性所属于的类里的某些目录下的函数可以直接在本类上暴露出来 | UPROPERTY | `ExposeFunctionCategories.md` |
| `FullyExpand` | 但是没有发现该Meta被使用的原理代码 | UPROPERTY | `FullyExpand.md` |
| `HideAssetPicker` | 隐藏Object类型引脚上的AssetPicker的选择列表 | UFUNCTION | `HideAssetPicker.md` |
| `IncludeAssetBundles` | 用于UPrimaryDataAsset的子对象属性，指定应该继续递归到该子对象里去探测AssetBundle数据 | UPROPERTY | `IncludeAssetBundles.md` |
| `LoadBehavior` | 用在UCLASS上标记这个类的加载行为，使得相应的TObjectPtr属性支持延迟加载。可选的加载行为默认为Eager，可改为LazyOnDemand | UCLASS | `LoadBehavior.md` |
| `MustBeLevelActor` | 意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思 | UPROPERTY | `MustBeLevelActor.md` |
| `ShowInnerProperties` | 在属性细节面板中显示对象引用的内部属性 | UPROPERTY | `ShowInnerProperties.md` |
| `ShowOnlyInnerProperties` | 把结构属性的内部属性直接上提一个层级直接展示 | UPROPERTY | `ShowOnlyInnerProperties.md` |
| `ThumbnailSize` | 改变缩略图的大小 | UCLASS, UPROPERTY | `ThumbnailSize.md` |
| `Untracked` | 使得TSoftObjectPtr和FSoftObjectPath的软对象引用类型的属性，不跟踪记录资产的 | UPROPERTY | `Untracked.md` |


## Meta - Path

> Doc root: `Meta/Path/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `ContentDir` | 使用UE的风格来选择Content以及子目录 | UPROPERTY | `ContentDir.md` |
| `FilePathFilter` | 设定文件选择器的扩展名，规则符合系统对话框的格式规范，可以填写多个扩展名 | UPROPERTY | `FilePathFilter.md` |
| `LongPackageName` | 使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名 | UPROPERTY | `LongPackageName.md` |
| `RelativePath` | 使得系统目录选择对话框的结果为当前运行exe的相对路径 | UPROPERTY | `RelativePath.md` |
| `RelativeToGameContentDir` | 使得系统目录选择对话框的结果为相对Content的相对路径 | UPROPERTY | `RelativeToGameContentDir.md` |
| `RelativeToGameDir` | 如果系统目录选择框的结果为Project的子目录，则转换为相对路径，否则返回绝对路径 | UPROPERTY | `RelativeToGameDir.md` |


## Meta - TypePicker

> Doc root: `Meta/TypePicker/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowAbstract` | 用于类属性，指定是否接受抽象类 | UPARAM, UPROPERTY | `AllowAbstract.md` |
| `AllowedClasses` | 用在类或对象选择器上，指定选择的对象必须属于某一些类型基类 | UPROPERTY | `AllowedClasses.md` |
| `AllowedTypes` | 为FPrimaryAssetId可以指定允许的资产类型 | UPROPERTY | `AllowedTypes.md` |
| `BaseClass` | 只在StateTree模块中使用，限制FStateTreeEditorNode选择的基类类型 | UPROPERTY | `BaseClass.md` |
| `BaseStruct` | 指定FInstancedStruct属性选项列表选择的结构都必须继承于BaseStruct指向的结构 | UPROPERTY | `BaseStruct.md` |
| `BlueprintBaseOnly` | 用于类属性，指定是否只接受可创建蓝图子类的基类 | UPROPERTY | `BlueprintBaseOnly.md` |
| `DisallowedClasses` | 用在类或对象选择器上，指定选择的对象排除掉某一些类型基类 | UPROPERTY | `DisallowedClasses.md` |
| `DisallowedStructs` | 只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类 | UPROPERTY | `DisallowedStructs.md` |
| `ExactClass` | 在同时设置AllowedClasses和GetAllowedClasses的时候，ExactClass指定只取这两个集合中类型完全一致的类型交集，否则取一致的交集再加上其子类 | UPROPERTY | `ExactClass.md` |
| `ExcludeBaseStruct` | 在使用BaseStruct的FInstancedStruct属性上忽略BaseStruct指向的结构基类 | UPROPERTY | `ExcludeBaseStruct.md` |
| `GetAllowedClasses` | 用在类或对象选择器上，通过一个函数来指定选择的对象必须属于某一些类型基类 | UPROPERTY | `GetAllowedClasses.md` |
| `GetDisallowedClasses` | 用在类选择器上，通过一个函数来指定选择的类型列表中排除掉某一些类型基类 | UPROPERTY | `GetDisallowedClasses.md` |
| `HideViewOptions` | 用于选择Class或Struct的属性上，隐藏在类选取器中修改显示选项的功能 | UPROPERTY | `HideViewOptions.md` |
| `MetaClass` | 用在软引用属性上，限定要选择的对象的基类 | UPROPERTY | `MetaClass.md` |
| `MetaStruct` | 设定到UScriptStruct*属性上，指定选择的类型的父结构 | UPROPERTY | `MetaStruct.md` |
| `MustImplement` | 指定TSubClassOf或FSoftClassPath属性选择的类必须实现该接口 | UPROPERTY | `MustImplement.md` |
| `OnlyPlaceable` | 用在类属性上，指定是否只接受可被放置到场景里的Actor | UPROPERTY | `OnlyPlaceable.md` |
| `RowType` | 指定FDataTableRowHandle 属性的可选行类型的基类 | UPROPERTY | `RowType.md` |
| `ShowDisplayNames` | 在Class和Struct属性上，指定类选择器显示另外的显示名称而不是类原始的名字 | UPROPERTY | `ShowDisplayNames.md` |
| `ShowTreeView` | 用于选择Class或Struct的属性上，使得在类选取器中显示为树形而不是列表 | UPROPERTY | `ShowTreeView.md` |
| `StructTypeConst` | 指定FInstancedStruct属性的类型不能在编辑器被选择 | UPROPERTY | `StructTypeConst.md` |




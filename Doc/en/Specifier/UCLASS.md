# UCLASS(specifier)

## UHT

| Name                                                       | engine module | function description                                                     | frequency of use |
| ---------------------------------------------------------- | -------- | ------------------------------------------------------------ | -------- |
| [NoExport](UCLASS/UHT/NoExport.md)                         | UHT      | Specifies that UHT should not be used to automatically generate registration code, but should only perform lexical analysis to extract metadata. | ☠️        |
| [Intrinsic](UCLASS/UHT/Intrinsic.md)                       | UHT      | Indicates that UHT will not generate any code for this class at all, and it must be written manually.                  | ☠️        |
| [Interface](UCLASS/UHT/Interface.md)                       | UHT      | Indicates that this class is an interface.                                 | ☠️        |
| [UCLASS()](UCLASS/UHT/UCLASS_Empty.md)                         | UHT      | The default behavior of leaving it blank is that it cannot be inherited in blueprints, variables cannot be defined in blueprints, but it retains reflection capabilities. | ★★★★★    |
| [Without_UCLASS](UCLASS/UHT/Without_UCLASS.md)                 | UHT      | Functions as an ordinary C++ object without reflection capabilities.                    | ★        |
| [CustomThunkTemplates](UCLASS/UHT/CustomThunkTemplates.md) | UHT      | Specifies the struct that contains the CustomThunk implementations | ☠️        |
| [CustomConstructor](UCLASS/UHT/CustomConstructor.md)       | UHT      | Prevents the automatic generation of constructor declarations.                                   | ☠️        |
| [CustomFieldNotify](UCLASS/UHT/CustomFieldNotify.md)       | UHT      | Prevents UHT from generating code related to FieldNotify for this class.                     | ☠️        |


## Blueprint

| Name                                                         | engine module  | function description                                                     | frequency of use |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------------ | -------- |
| [Blueprintable](UCLASS/Blueprint/Blueprintable/Blueprintable.md) | Blueprint | Can be inherited in blueprints and can also be used as a variable type implicitly                 | ★★★★★    |
| [NotBlueprintable](UCLASS/Blueprint/NotBlueprintable.md)     | Blueprint | Cannot be inherited in blueprints and its implicit use cannot be as a variable                     | ★★★★     |
| [BlueprintType](UCLASS/Blueprint/BlueprintType/BlueprintType.md) | Blueprint | Can be used as a variable type                                               | ★★★★★    |
| [NotBlueprintType](UCLASS/Blueprint/NotBlueprintType.md)     | Blueprint | Cannot be used as a variable type                                             | ★★★★     |
| [Abstract](UCLASS/Blueprint/Abstract/Abstract.md)            | Blueprint | Designates this class as an abstract base class, which can be inherited but objects cannot be instantiated from it.               | ★★★★★    |
| [Const](UPARAM/Blueprint/Const/Const.md)                     | Blueprint | Indicates that the internal properties of this class are not modifiable in blueprints; they are read-only and not writable.           | ★★★      |
| [ShowFunctions](UCLASS/Blueprint/ShowFunctions.md)           | Blueprint | Re-enables certain functions in the subclass's function override list.                     | ★★       |
| [HideFunctions](UCLASS/Blueprint/HideFunctions/HideFunctions.md) | Blueprint | Hides certain functions in the subclass's function override list.                       | ★★       |
| [SparseClassDataType](UCLASS/Blueprint/SparseClassDataType/SparseClassDataType.md) | Blueprint | Allows some repetitive and unchanging data of Actors to be stored in a common structure to reduce content usage | ★★★      |
| [NeedsDeferredDependencyLoading](UCLASS/Blueprint/NeedsDeferredDependencyLoading.md) | Blueprint |                                                              | ☠️        |


## DllExport

| Name                                       | engine module  | function description                                      | frequency of use |
| ------------------------------------------ | --------- | --------------------------------------------- | -------- |
| [MinimalAPI](UINTERFACE/UHT/MinimalAPI.md) | DllExport | Does not export the class's functions to the DLL, only exports type information as variables. | ★★★      |


## Category

| Name                                                         | engine module         | function description                                                     | frequency of use |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [ClassGroup](UCLASS/Category/ClassGroup/ClassGroup.md)       | Category | Specifies the grouping for components in the Actor's AddComponent panel and in the blueprint's right-click menu. | ★★★     |
| [ShowCategories](UCLASS/Category/ShowCategories/ShowCategories.md) | Category         | Displays certain Category properties in the class's ClassDefaults property panel.        | ★★★     |
| [HideCategories](UCLASS/Category/HideCategories/HideCategories.md) | Category         | Hides certain Category properties in the class's ClassDefaults property panel.        | ★★★★    |
| [CollapseCategories](UCLASS/Category/CollapseCategories/CollapseCategories.md) | Category         | Hides all properties with Category in the class's property panel, but only for properties with multiple nested Categories. | ★★      |
| [DontCollapseCategories](UCLASS/Category/DontCollapseCategories.md) | Category         | Invalidates the CollapseCategories specifier inherited from the base class.                 | ★★      |
| [AutoExpandCategories](UCLASS/Category/AutoExpandCategories/AutoExpandCategories.md) | Category         | Specifies the Category that should be automatically expanded for this class's objects in the details panel.           | ★       |
| [AutoCollapseCategories](UCLASS/Category/AutoCollapseCategories/AutoCollapseCategories.md) | Category         | The AutoCollapseCategories specifier invalidates the effect of the AutoExpandCategories specifier for categories listed on the parent class. | ★       |
| [DontAutoCollapseCategories](UCLASS/Category/DontAutoCollapseCategories.md) | Category         | Invalidates the AutoCollapseCategories specifier for the listed categories inherited from the parent class. | ★       |
| [PrioritizeCategories](UCLASS/Category/PrioritizeCategories/PrioritizeCategories.md) | Category         | Prioritizes the display of the specified attribute directory at the front of the details panel.                   | ★★★     |
| [ComponentWrapperClass](UCLASS/Category/ComponentWrapperClass/ComponentWrapperClass.md) | Category         | Designates this class as a simple encapsulation class, ignoring the Category-related settings of the subclass.   | ★★      |
| [AdvancedClassDisplay](UCLASS/Category/AdvancedClassDisplay/AdvancedClassDisplay.md) | Category         | Displays all properties under this class in the advanced directory by default                     | ★★★★    |


## TypePicker

| Name                                                         | engine module   | function description             | frequency of use |
| ------------------------------------------------------------ | ---------- | -------------------- | -------- |
| [HideDropDown](UCLASS/TypePicker/HideDropDown/HideDropDown.md) | TypePicker | Hides this class in the class selector | ★★       |

## Development

| Name                                                         | engine module    | function description                                                     | frequency of use |
| ------------------------------------------------------------ | ----------- | ------------------------------------------------------------ | -------- |
| [Deprecated](UCLASS/Development/Deprecated/Deprecated.md)    | Development | Indicates that this class is deprecated.                                           | ★★★      |
| [Experimental](UCLASS/Development/Experimental/Experimental.md) | Development | Indicates that this class is an experimental version, currently without documentation, and may be deprecated in the future.   | ★★★      |
| [EarlyAccessPreview](UCLASS/Development/EarlyAccessPreview/EarlyAccessPreview.md) | Development | Indicates that this class is a preliminary preview version, more complete than the experimental version, but not yet at the product level. | ★★★      |

## Instance

| Name                                                         | engine module | function description                                                     | frequency of use |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [Within](UCLASS/Instance/Within.md)                          | Instance | Specifies that when an object is created, it must depend on an object with the OuterClassName as its Outer.  | ★★★      |
| [DefaultToInstanced](UCLASS/Instance/DefaultToInstanced/DefaultToInstanced.md) | Instance | Specifies that all instance properties of this class are set to UPROPERTY(instanced) by default, meaning they create new instances rather than references to objects. | ★★★★     |
| [EditInlineNew](UCLASS/Instance/EditInlineNew/EditInlineNew.md) | Instance | Allows objects of this class to be created inline directly in the property details panel, coordinating with the attribute's Instanced setting. | ★★★★★    |
| [NotEditInlineNew](UCLASS/Instance/NotEditInlineNew.md)      | Instance | Cannot be created using the EditInline button                                   | ★        |


## Scene

| Name                                                         | engine module         | function description                                                     | frequency of use |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [NotPlaceable](UCLASS/Scene/NotPlaceable/NotPlaceable.md)    | Scene         | Indicates that this Actor cannot be placed in a level                                | ★★★     |
| [Placeable](UCLASS/Scene/Placeable/Placeable.md)             | Scene            | Indicates that this Actor can be placed in a level.                                | ★★★     |
| [ConversionRoot](UCLASS/Scene/ConversionRoot/ConversionRoot.md) | Scene            | Allows the Actor to be converted between itself and its subclasses in the scene editor              | ★       |

## Config

| Name                                                         | engine module         | function description                                                     | frequency of use |
| ------------------------------------------------------------ | ---------------- | ------------------------------------------------------------ | -------- |
| [Config](UCLASS/Config/Config.md)                            | Config           | Specifies the name of the configuration file to which the object's values are saved in the ini configuration file.        | ★★★★★   |
| [PerObjectConfig](UCLASS/Config/PerObjectConfig.md)          | Config           | In cases where there is already a config file name, specifies that values should be stored per object instance rather than per class. | ★★★★★   |
| [ConfigDoNotCheckDefaults](UCLASS/Config/ConfigDoNotCheckDefaults.md) | Config           | Specifies that the consistency check of the previous level's configuration values is ignored when saving configuration values.       | ★       |
| [DefaultConfig](UCLASS/Config/DefaultConfig/DefaultConfig.md) | Config           | Specifies that the configuration file level to save to is Project/Config/DefaultXXX.ini.    | ★★★     |
| [GlobalUserConfig](UCLASS/Config/GlobalUserConfig/GlobalUserConfig.md) | Config           | Specifies that the configuration file level to save to is Engine/Config/UserXXX.ini for global user settings. | ★★★     |
| [ProjectUserConfig](UCLASS/Config/ProjectUserConfig/ProjectUserConfig.md) | Config           | Specifies that the configuration file level to save to is Project/Config/UserXXX.ini for project user settings. | ★★★     |
| [EditorConfig](UCLASS/Config/EditorConfig/EditorConfig.md)   | Config   | Used to save information in the editor state.                                 | ★       |


## Serialization

| Name                                                         | engine module      | function description                                                     | frequency of use |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [Transient](UCLASS/Serialization/Transient/Transient.md)     | Serialization | Specifies that all objects of this class are skipped during serialization.                             | ★★★      |
| [NonTransient](UCLASS/Serialization/NonTransient.md)         | Serialization | Invalidates the Transient specifier inherited from the base class.                          | ★★★      |
| [Optional](UCLASS/Serialization/Optional/Optional.md)        | Serialization | Mark this class's objects as optional, allowing them to be ignored during Cooking. | ★        |
| [MatchedSerializers](UCLASS/Serialization/MatchedSerializers/MatchedSerializers.md) | Serialization | Specifies that the class supports text structure serialization                                     | ☠️        |
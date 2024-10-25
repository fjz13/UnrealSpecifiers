# USTRUCT(specifier)

 ## UHT

| Name                                                         | Engine module      | Function description                                                     | Common usage |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [NoExport](USTRUCT/UHT/NoExport/NoExport.md)                 | UHT           | Specifies that UHT should not be used to automatically generate registration code, but rather for lexical analysis to extract metadata only. | Star        |
| [Atomic](USTRUCT/UHT/Atomic/Atomic.md)                       | UHT           | Indicates that the structure always outputs all its properties during serialization, rather than just the changed ones. | Star        |
| [IsAlwaysAccessible](USTRUCT/UHT/IsAlwaysAccessible.md)      | UHT           | Ensures that UHT can always access the declaration of this structure when generating files; otherwise, a mirrored structure definition must be created in gen.cpp | Skull        |
| [HasDefaults](USTRUCT/UHT/HasDefaults.md)                    | UHT           | Indicates that the fields of this structure have default values, allowing functions to provide default values when the structure is used as a parameter or return value. | Skull        |
| [HasNoOpConstructor](USTRUCT/UHT/HasNoOpConstructor.md)      | UHT           | Signifies that the structure possesses a ForceInit constructor, which can be invoked to initialize when it is returned as a BP function's value | Skull        |
| [IsCoreType](USTRUCT/UHT/IsCoreType.md)                      | UHT           | Indicates that the structure is a core class, and UHT does not require a forward declaration when using it.          | Skull        |


 ## Blueprint

| Name                                                         | Engine module      | Function description                                                     | Common usage |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [BlueprintType](USTRUCT/Blueprint/BlueprintType/BlueprintType.md) | Blueprint     | Allows this structure to be declared as variables in Blueprints                                 | ★★★★★    |
| [BlueprintInternalUseOnly](USTRUCT/Blueprint/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md) | Blueprint     | Prohibits the definition of new BP variables but allows the structure to be exposed as member variables of other classes and passed as variables     | ★★       |
| [BlueprintInternalUseOnlyHierarchical](USTRUCT/Blueprint/BlueprintInternalUseOnlyHierarchical.md) | Blueprint     | Building on BlueprintInternalUseOnly, this adds a restriction that subclasses are also forbidden from defining new BP variables. | ★        |


 ## Serialization

| Name                                                         | Engine module      | Function description                                                     | Common usage |
| ------------------------------------------------------------ | ------------- | ------------------------------------------------------------ | -------- |
| [immutable](USTRUCT/Serialization/immutable.md)              | Serialization | Immutable is only legal in Object.h and is being phased out, do not use on new structs! | 💀        |
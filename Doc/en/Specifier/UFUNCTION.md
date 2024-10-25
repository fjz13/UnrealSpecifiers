# UFUNCTION(specifier)

## Editor

| Name                                                         | Engine Module | Function Description                                             | Usage Frequency |
| ------------------------------------------------------------ | -------- | ---------------------------------------------------- | -------- |
| [Category](UFUNCTION/Category/Category.md)                   | Editor   | Specify category grouping for the function in the right-click menu of the blueprint, allowing for multi-level nesting | ★★★★★    |
| [CallInEditor](UFUNCTION/Blueprint/CallInEditor/CallInEditor.md) | Editor   | This function can be invoked as a button on the property details panel.       | ★★★★★    |


## Blueprint

| Name                                                         | Engine Module  | Function Description                                              | Usage Frequency |
| ------------------------------------------------------------ | --------- | ----------------------------------------------------- | -------- |
| [BlueprintCallable](UFUNCTION/Blueprint/BlueprintCallable/BlueprintCallable.md) | Blueprint | Exposed to the blueprint for invocation                                  | ★★★★★    |
| [BlueprintPure](UFUNCTION/Blueprint/BlueprintPure/BlueprintPure.md) | Blueprint | Designated as a pure function, typically used in Get functions to return values.       | ★★★★★    |
| [BlueprintImplementableEvent](UFUNCTION/Blueprint/BlueprintImplementableEvent/BlueprintImplementableEvent.md) | Blueprint | Specify a function call point that can be overloaded within the blueprint.            | ★★★★★    |
| [BlueprintNativeEvent](UFUNCTION/Blueprint/BlueprintNativeEvent/BlueprintNativeEvent.md) | Blueprint | Implementation can be overridden in Blueprints, with a default implementation also provided in C++. | ★★★★★    |
| [BlueprintGetter](UFUNCTION/Blueprint/BlueprintGetter.md)    | Blueprint | Specify this function as a custom Get function for the property.                   | ★★       |
| [BlueprintSetter](UFUNCTION/Blueprint/BlueprintSetter.md)    | Blueprint | Specify this function as a custom Set function for the property.                   | ★★       |


## Behavior

| Name                                                         | Engine Module | Function Description                                                     | Usage Frequency |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [Exec](UFUNCTION/Exec/Exec.md)                               | Behavior | Register a function within a specific class as a console command, enabling parameter acceptance.       | ★★★      |
| [SealedEvent](UFUNCTION/Blueprint/SealedEvent/SealedEvent.md) | Behavior | This function cannot be overridden in subclasses. Use the SealedEvent keyword for events only. For non-event functions, declare them as static or final to seal them. | 💀        |


## Network

| Name                                                         | Engine Module | Function Description                                                     | Usage Frequency |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ | -------- |
| [BlueprintAuthorityOnly](UFUNCTION/Network/BlueprintAuthorityOnly/BlueprintAuthorityOnly.md) | Network  | This function is executable only on clients with network permissions.                       | ★★★      |
| [BlueprintCosmetic](UFUNCTION/Network/BlueprintCosmetic/BlueprintCosmetic.md) | Network  | Decorative function; not executable on DS.                           | ★★★      |
| [Client](UFUNCTION/Network/Client/Client.md)                 | Network  | Execute a RPC function on a Client-owned Actor (PlayerController or Pawn). This function runs only on the client. The corresponding implementation function will have an _Implementation suffix. | ★★★★★    |
| [Server](UFUNCTION/Network/Server/Server.md)                 | Network  | Execute a RPC function on a Client-owned Actor (PlayerController or Pawn). This function runs only on the server. The corresponding implementation function will have an _Implementation suffix | ★★★★★    |
| [NetMulticast](UFUNCTION/Network/NetMulticast/NetMulticast.md) | Network  | Define a multicast RPC function to be executed on both the server and the client. The corresponding implementation function will have an _Implementation suffix. | ★★★★★    |
| [Reliable](UFUNCTION/Network/Reliable.md)                    | Network  | Specify an RPC function as "reliable," which will be resent upon network errors to ensure delivery. Typically used in critical logic functions. | ★★★★★    |
| [Unreliable](UFUNCTION/Network/Unreliable.md)                | Network  | Specify an RPC function as "unreliable," which will be discarded upon network errors. Typically used in functions that express communication effects, where omissions are permissible. | ★★★★★    |
| [WithValidation](UFUNCTION/Network/WithValidation.md)        | Network  | Specify that an RPC function must be verified before execution, and it can only be executed if the verification is successful.    | ★★★★★    |
| [ServiceRequest](UFUNCTION/Network/ServiceRequest.md)        | Network  | This function is an RPC (Remote Procedure Call) service request. RPC service request             | 💀        |
| [ServiceResponse](UFUNCTION/Network/ServiceResponse.md)      | Network  | This function is an RPC service response. RPC service reply                             | 💀        |


## UHT

| Name                                                         | Engine Module       | Function Description                                                     | Usage Frequency |
| ------------------------------------------------------------ | -------------- | ------------------------------------------------------------ | -------- |
| [BlueprintInternalUseOnly](UFUNCTION/UHT/BlueprintInternalUseOnly/BlueprintInternalUseOnly.md) | Blueprint, UHT | Indicate that this function should not be exposed to end users. Internally called by the blueprint and not exposed to users.   | ★★★      |
| [CustomThunk](UFUNCTION/UHT/CustomThunk/CustomThunk.md)      | UHT            | Specify that UHT will not generate an auxiliary function for blueprint invocation of this function, and it requires user-defined implementation. | ★★★      |
| [Variadic](UFUNCTION/UHT/Variadic/Variadic.md)               | Blueprint, UHT | Mark a function capable of accepting multiple parameters of any type (including input/output)  | ★★★      |
| [FieldNotify](UFUNCTION/UHT/FieldNotify/FieldNotify.md)      | UHT            | Create a FieldNotify binding point for this function.                        | ★★★      |
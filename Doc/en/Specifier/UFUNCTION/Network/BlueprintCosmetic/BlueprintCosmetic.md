# BlueprintCosmetic

- **Function description:** This function is purely decorative and cannot be executed on the DS.

- **Metadata type:** bool
- **Engine module:** Network
- **Mechanism of action:** [FUNC_BlueprintCosmetic](../../../../Flags/EFunctionFlags/FUNC_BlueprintCosmetic.md) is added to the FunctionFlags
- **Commonly used:** ★★★

This function is decorative in nature, which means it is intended to present content unrelated to the logic, such as animations, sound effects, and visual effects. Since the DS lacks a visual output, these decorative functions are irrelevant to the DS and will be disregarded.

However, it is important to note that on a ListenServer or a Client, both are permitted to run. This is because both ends require a visual display.

## Test Code:

```cpp
UFUNCTION(BlueprintCallable, BlueprintCosmetic)
void MyFunc_BlueprintCosmetic();
```

## Test Blueprint:

The computer tag on the node indicates that the function will execute exclusively on the client side.

![Untitled](Untitled.png)

Result output

```cpp
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

## Principle:

```cpp
int32 AActor::GetFunctionCallspace( UFunction* Function, FFrame* Stack )
{
// Dedicated servers don't care about "cosmetic" functions.
if (NetMode == NM_DedicatedServer && Function->HasAllFunctionFlags(FUNC_BlueprintCosmetic))
{
	DEBUG_CALLSPACE(TEXT("GetFunctionCallspace Blueprint Cosmetic Absorbed: %s"), *Function->GetName());
	return FunctionCallspace::Absorbed;
}
}
```
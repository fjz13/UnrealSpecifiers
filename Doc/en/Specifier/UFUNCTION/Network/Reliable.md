# Reliable

- **Function Description:** Designate a RPC function as "reliable," which will automatically retry upon encountering network errors to ensure delivery. Typically applied to functions critical to the logic.

- **Metadata Type:** boolean
- **Engine Module:** Network
- **Operation Mechanism:** Add [FUNC_NetReliable](../../../Flags/EFunctionFlags/FUNC_NetReliable.md) to the function flags in FunctionOptions
- **Common Usage:** ★★★★★

Designate a RPC function as "reliable," which will automatically retry upon encountering network errors to ensure delivery. Typically applied to functions critical to the logic.

The underlying principle involves the logic of resending data packets.
# Unreliable

- **Function Description:** Designates an RPC function as "unreliable," meaning it will be abandoned in the event of a network error. Typically applied to functions where the communication effect is concerned, and it is acceptable if some calls are missed.

- **Metadata Type:** bool
- **Engine Module:** Network
- **Usage Frequency:** ★★★★★

Designates an RPC function as "unreliable," which will be discarded if a network error occurs. This is usually used for functions that convey communication effects, and it is not critical if some instances are not processed.
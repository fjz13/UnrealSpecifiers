# RepRetry

- **Function Description:** Applicable solely to structure properties. Should this property fail to be transmitted in full (for instance, an Object reference that cannot yet be serialized over the network), an attempt to copy it will be made anew. This is the default selection for simple references; however, for structures, it results in bandwidth consumption and is not the optimal choice. Consequently, this feature is disabled by default until the tag is explicitly specified.
- **Metadata Type:** bool
- **Engine Module:** Network
# Deprecated

- **Function Description:** Specifies the engine version number at which this element is to be deprecated.
- **Usage Location:** Any
- **Engine Module:** Development
- **Metadata Type:** string="abc"
- **Commonality:** ★

Specifies the engine version number at which this element is scheduled for deprecation.

This value merely serves as a record within the C++ code, indicating information without actually rendering an element deprecated. It is not used or displayed in any UI components elsewhere.

To discard an element, you still need to use other tags, such as **DeprecatedProperty DeprecatedFunction , etc.**
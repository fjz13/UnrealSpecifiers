# Spacer

- **Function Description:** Hide a specific value within UENUM
- **Usage Location:** UENUM::UMETA
- **Engine Module:** Enum Property
- **Metadata Type:** boolean
- **Restriction Type:** UENUM
- **Commonality:** ★★★★★

Spacer and Hidden share similar functionalities. The sole distinction is that Spacer remains visible when compared using '==' in blueprints.

Thus, it is still advisable to use Hidden whenever the goal is to conceal enumeration values.

![Untitled](Hidden/Untitled.png)

Refer to the Hidden section for additional sample code examples
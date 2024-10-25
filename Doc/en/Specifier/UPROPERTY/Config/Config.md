# Config

- **Function description:** Specifies that this property is a configuration property, which can be serialized, read and written to ini file (the path is specified by the config tag of uclass ).
- **Metadata type:** bool
- **Engine module:** Config
- **Action mechanism:** [CPF_Config](../../../Flags/EPropertyFlags/CPF_Config.md)
- **Commonly used:** ★★★

Specifies that this property is a configuration property that can be serialized, read and written to the ini file (the path is specified by the config tag of uclass).

It will be automatically loaded from the INI file upon loading. If no write marker is added, the property will implicitly be set to ReadOnly.

See sample code and effects of the config tag in UCLASS.
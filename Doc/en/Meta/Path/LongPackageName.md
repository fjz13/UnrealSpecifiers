# LongPackageName

- **Function description:** Utilizes the UE style for selecting Content and its subdirectories, or converts file paths into long package names.
- **Usage location:** UPROPERTY
- **Engine module:** Path Property
- **Metadata type:** bool
- **Restricted types:** FDirectoryPath, FFilePath
- **Commonly used:** ★★★

LongPackageName can be applied to both FDirectoryPath and FFilePath, both of which restrict the selection to within the Content directory.

When applied to FDirectoryPath, it restricts directories to Content or its subdirectories.

When used with FFilePath, it limits the selection to assets within Content and ultimately converts the selected file path into an object path of the form "/Game/ObjectPath".
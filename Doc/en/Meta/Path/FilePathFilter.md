# FilePathFilter

- **Function description:** Specifies the file extension for the file selector, adhering to the format specifications of the system dialog box. Multiple extensions can be entered.
- **Usage location:** UPROPERTY
- **Engine module:** Path Property
- **Metadata type:** string="abc"
- **Restriction type:** FFilePath
- **Commonly used:** ★★★

Usual extensions include ".umap" and ".uasset". However, it also supports custom filtering by using the "description | *.extension" format, following the same rules as the Windows file selection dialog, and multiple extensions can be specified simultaneously.
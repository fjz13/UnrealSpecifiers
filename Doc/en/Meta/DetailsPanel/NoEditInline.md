# NoEditInline

- **Function description:** Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inline in property windows . Useful for getting actor components to appear in the component tree but not inline in the root actor details panel .
- **Use Location:** UPROPERTY
- **Metadata Type:** bool
- **Restriction Type:** UObject*
- **Related Items:** EditInline (EditInline.md)

Object references cannot be EditInline by default, so there is no need to add this additionally. Unless after Instanced?

The structure attribute can be EditInline by default, and adding this has no effect, so there is no need to add this.

Found only in the source code:

```cpp
	UPROPERTY(VisibleAnywhere, Category = "Connection Point", meta = (NoEditInline))
	FLinearColor Color = FLinearColor::Black;
```
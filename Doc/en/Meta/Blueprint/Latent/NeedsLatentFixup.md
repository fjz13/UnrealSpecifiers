#NeedsLatentFixup

- **Function Description:** Used on the FLatentActionInfo::Linkage attribute to instruct the Blueprint VM to generate jump information
- **Usage Location:** UPROPERTY
- **Metadata Type:** boolean
- **Associated Items:** [Latent](Latent.md)
- **Commonality:** ★

## Applications in the Source Code:

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct FLatentActionInfo
{
	GENERATED_USTRUCT_BODY()

	/** The resume point within the function to execute */
	UPROPERTY(meta=(NeedsLatentFixup = true))
	int32 Linkage;

	//...
};

```

## Source Code Implementation:

Appears to handle the Linkage attribute separately, used for specialized jumps within the JumpTargetFixupMap

```cpp
void EmitLatentInfoTerm(FBPTerminal* Term, FProperty* LatentInfoProperty, FBlueprintCompiledStatement* TargetLabel)
{
	// Special case of the struct property emitter.  Needs to emit a linkage property for fixup
	FStructProperty* StructProperty = CastFieldChecked<FStructProperty>(LatentInfoProperty);
	check(StructProperty->Struct == LatentInfoStruct);

	int32 StructSize = LatentInfoStruct->GetStructureSize();
	uint8* StructData = (uint8*)FMemory_Alloca(StructSize);
	StructProperty->InitializeValue(StructData);

	// Assume that any errors on the import of the name string have been caught in the function call generation
	StructProperty->ImportText_Direct(*Term->Name, StructData, NULL, 0, GLog);

	Writer << EX_StructConst;
	Writer << LatentInfoStruct;
	Writer << StructSize;

	checkSlow(Schema);
	for (FProperty* Prop = LatentInfoStruct->PropertyLink; Prop; Prop = Prop->PropertyLinkNext)
	{
		if (TargetLabel && Prop->GetBoolMetaData(FBlueprintMetadata::MD_NeedsLatentFixup))
		{
			// Emit the literal and queue a fixup to correct it once the address is known
			Writer << EX_SkipOffsetConst;
			CodeSkipSizeType PatchUpNeededAtOffset = Writer.EmitPlaceholderSkip();
			JumpTargetFixupMap.Add(PatchUpNeededAtOffset, FCodeSkipInfo(FCodeSkipInfo::Fixup, TargetLabel));
		}
		else if (Prop->GetBoolMetaData(FBlueprintMetadata::MD_LatentCallbackTarget))
		{
			FBPTerminal CallbackTargetTerm;
			CallbackTargetTerm.bIsLiteral = true;
			CallbackTargetTerm.Type.PinSubCategory = UEdGraphSchema_K2::PN_Self;
			EmitTermExpr(&CallbackTargetTerm, Prop);
		}
		else
		{
			// Create a new term for each property, and serialize it out
			FBPTerminal NewTerm;
			if(Schema->ConvertPropertyToPinType(Prop, NewTerm.Type))
			{
				NewTerm.bIsLiteral = true;
				Prop->ExportText_InContainer(0, NewTerm.Name, StructData, StructData, NULL, PPF_None);

				EmitTermExpr(&NewTerm, Prop);
			}
			else
			{
				// Do nothing for unsupported/unhandled property types. This will leave the value unchanged from its constructed default.
				Writer << EX_Nothing;
			}
		}
	}

	Writer << EX_EndStructConst;
}
```
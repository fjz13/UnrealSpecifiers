# LatentInfo

- **Function description:** Used in conjunction with Latent to specify which function parameter is the LatentInfo parameter.
- **Use location:** UFUNCTION
- **Metadata type:** string="abc"
- **Related items:** [Latent](Latent.md)
- **Frequency:** ★★★

Latent functions require FLatentActionInfo to operate. FLatentActionInfo contains details such as the ID of the delayed operation and the name of the next function to be executed. In the blueprint virtual machine environment, when a Latent function is executed, the blueprint VM gathers the current function context information (e.g., the next node connected to the Latent function) and then assigns it to the FLatentActionInfo parameter of the Latent function, subsequently registering it with FPendingLatentAction in the FLatentActionManager. Once the time elapses or the trigger condition is met, FLatentActionManager invokes CallbackTarget->ProcessEvent(ExecutionFunction, &(LinkInfo.LinkID)), thereby resuming execution.

If function parameters are not specified using LatentInfo, the assignment operation for LatentInfo is disrupted, and thus the function will not operate correctly. The blueprint diagram can be found on the Latent page.

The value of LatentInfo, much like WorldContext, is automatically populated by the Blueprint VM system. This value population occurs within EmitLatentInfoTerm, where the values of LatentInfoStruct are filled into the function parameters of LatentInfo. The position of the LatentInfo parameter is not significant, and the function parameter pin specified by LatentInfo will be hidden.

```cpp
void EmitFunctionCall(FKismetCompilerContext& CompilerContext, FKismetFunctionContext& FunctionContext, FBlueprintCompiledStatement& Statement, UEdGraphNode* SourceNode)
{
	if (bIsUbergraph && FuncParamProperty->GetName() == FunctionToCall->GetMetaData(FBlueprintMetadata::MD_LatentInfo))
	{
				EmitLatentInfoTerm(Term, FuncParamProperty, Statement.TargetLabel);
	}
}

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

The collection of LatentInfo occurs in FKCHandler_CallFunction::CreateFunctionCallStatement
# LatentInfo

Description: 和Latent配合，指明哪个函数参数是LatentInfo参数。
Usage: UFUNCTION
Feature: Blueprint
Type: string="abc"
Example: LatentInfo="Parameter”
Status: Linked
Parent item: Latent (Latent.md)

Latent的函数需要FLatentActionInfo才能工作。FLatentActionInfo里记录着这个延迟操作的ID以及下一步要执行的函数名称等。在蓝图的虚拟机运行环境下，一个Latent函数执行的时候，蓝图VM会收集当前的函数上下文信息（典型的比如下Latent函数连接的下一个节点），然后继续赋值到Latent函数的FLatentActionInfo参数上，再配合FPendingLatentAction注册到FLatentActionManager里面去。等时间到达或者触发条件达成后，FLatentActionManager会触发CallbackTarget->ProcessEvent(ExecutionFunction, &(LinkInfo.LinkID))，从而继续执行下去。

如果没有用LatentInfo来指定函数参数，则因为断了LatentInfo的赋值操作，因此就无法正常工作，蓝图效果图见Latent页面。

LatentInfo值就像WorldContext一样，会被蓝图VM系统自动的填充值。填充值的操作是在EmitLatentInfoTerm里执行的。把LatentInfoStruct的值填充到LatentInfo的函数参数里去。LatentInfo的参数位置并不重要。LatentInfo指定的函数参数Pin会被隐藏。

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

LatentInfo信息的收集是在FKCHandler_CallFunction::CreateFunctionCallStatement里
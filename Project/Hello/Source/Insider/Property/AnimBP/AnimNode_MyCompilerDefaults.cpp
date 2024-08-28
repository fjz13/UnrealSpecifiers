#include "AnimNode_MyCompilerDefaults.h"

void FAnimNode_MyCompilerDefaults::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);

	Source.Initialize(Context);
}

void FAnimNode_MyCompilerDefaults::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(CacheBones_AnyThread)
	Source.CacheBones(Context);
}

void FAnimNode_MyCompilerDefaults::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	Source.Update(Context.FractionalWeight(1.f));
}

void FAnimNode_MyCompilerDefaults::Evaluate_AnyThread(FPoseContext& Output)
{
	Source.Evaluate(Output);
}

void FAnimNode_MyCompilerDefaults::GatherDebugData(FNodeDebugData& DebugData)
{

}

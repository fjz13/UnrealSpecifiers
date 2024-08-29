#include "MyClass_DebugTreeLeaf.h"

UMyClass_DebugTreeLeaf::UMyClass_DebugTreeLeaf()
{
	for (int32 i = 0; i < 100; i++)
	{
		IntArray.Add(i);
		IntSet.Add(i);
		IntStringMap.Add(i) = FString::FromInt(i);
	}
}

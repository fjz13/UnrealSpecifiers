# BlueprintProtected

- **功能描述：** 指定该函数或属性只能在本类以及子类中被调用或读写，类似C++中的protected作用域限制。不可在别的蓝图类里访问。
- **使用位置：** UFUNCTION, UPROPERTY
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **关联项：** [BlueprintPrivate](../BlueprintPrivate/BlueprintPrivate.md), [AllowPrivateAccess](../AllowPrivateAccess/AllowPrivateAccess.md)
- **常用程度：** ★★★

作用在函数上：

标记该函数只能在本类以及子类中被调用，类似C++中的protected函数的作用域限制。不可在别的蓝图类里调用。

作用在属性上时，标明该属性只能在本类或派生类里进行读写，但不能在别的蓝图类里访问。

指定该函数或属性只能在本类以及子类中被调用或读写，类似C++中的protected函数的作用域限制。不可在别的蓝图类里访问。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Access :public AActor
{
public:
	GENERATED_BODY()
public:
	//(BlueprintProtected = true, ModuleRelativePath = Function/MyFunction_Access.h)
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected = "true"))
	void MyNative_HasProtected() {}

	//(BlueprintPrivate = true, ModuleRelativePath = Function/MyFunction_Access.h)
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable, meta = (BlueprintPrivate = "true"))
	void MyNative_HasPrivate() {}
public:
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable)
	void MyNative_NativePublic() {}
protected:
	//FUNC_Final | FUNC_Native | FUNC_Protected | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable)
	void MyNative_NativeProtected() {}
private:
	//FUNC_Final | FUNC_Native | FUNC_Private | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable)
	void MyNative_NativePrivate() {}
};

```

## 测试效果：

蓝图中的子类（BPA_Access_Base继承自AMyFunction_Access ）效果：

可见BlueprintProtected可以被子类调用，但是BlueprintPrivate只能在本类（C++类中定义的只能在C++中调用，蓝图中定义的只能在蓝图本类中调用）。而在C++中用protected或private修饰的函数会相应的增加FUNC_Protected和FUNC_Private，但是实际上并不会发生作用。因为机制的设计目的就是如此（详见后文解释）。

而在BPA_Access_Base中直接定义的MyBPProtected和MyBPPrivate通过在函数细节面板上直接设置AccessSpecifier，可以在本类都可以调用，但是MyBPPrivate在更加的蓝图子类无法被调用。

![Untitled](Untitled.png)

蓝图中的子类（BPA_Access_Child继承自BPA_Access_Base）效果：

可见MyNative函数的访问一样。而MyBPPrivate则不能被调用了，这和我们预想的规则一样。

![Untitled](Untitled%201.png)

而在外部类中(BPA_Access_Other，继承自Actor)，通过BPA_Access_Base或BPA_Access_Child对象实例访问函数的时候，发现带有BlueprintProtected和BlueprintPrivate都不能被调用。BP的函数也只有AccessSpecifier为默认Public的可以调用。这个规则也很符合预期。

![Untitled](Untitled%202.png)

## 原理：

在蓝图右键上是否可以选择该函数的过滤逻辑：

如果是static函数，则总是可以。否则必须没有BlueprintProtected或BlueprintPrivate才可以是Public可以被选择出来的。

如果是Private，则外部类必须是定义的类本身。

如果是Protected，则外部类只需要是定义的类或子类。

```cpp
static bool BlueprintActionFilterImpl::IsFieldInaccessible(FBlueprintActionFilter const& Filter, FBlueprintActionInfo& BlueprintAction)
{
		bool const bIsProtected = Field.HasMetaData(FBlueprintMetadata::MD_Protected);
		bool const bIsPrivate   = Field.HasMetaData(FBlueprintMetadata::MD_Private);
		bool const bIsPublic    = !bIsPrivate && !bIsProtected;

		if( !bIsPublic )
		{
			UClass const* ActionOwner = BlueprintAction.GetOwnerClass();
			for (UBlueprint const* Blueprint : FilterContext.Blueprints)
			{
				UClass const* BpClass = GetAuthoritativeBlueprintClass(Blueprint);
				if (!ensureMsgf(BpClass != nullptr
					, TEXT("Unable to resolve IsFieldInaccessible() - Blueprint (%s) missing an authoratative class (skel: %s, generated: %s, parent: %s)")
					, *Blueprint->GetName()
					, Blueprint->SkeletonGeneratedClass ? *Blueprint->SkeletonGeneratedClass->GetName() : TEXT("[NULL]")
					, Blueprint->GeneratedClass ? *Blueprint->GeneratedClass->GetName() : TEXT("[NULL]")
					, Blueprint->ParentClass ? *Blueprint->ParentClass->GetName() : TEXT("[NULL]")))
				{
					continue;
				}

				// private functions are only accessible from the class they belong to
				if (bIsPrivate && !IsClassOfType(BpClass, ActionOwner, /*bNeedsExactMatch =*/true))
				{
					bIsFilteredOut = true;
					break;
				}
				else if (bIsProtected && !IsClassOfType(BpClass, ActionOwner))
				{
					bIsFilteredOut = true;
					break;
				}
			}
		}
}

bool UEdGraphSchema_K2::ClassHasBlueprintAccessibleMembers(const UClass* InClass) const
{
	// @TODO Don't show other blueprints yet...
	UBlueprint* ClassBlueprint = UBlueprint::GetBlueprintFromClass(InClass);
	if (!InClass->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists) && (ClassBlueprint == NULL))
	{
		// Find functions
		for (TFieldIterator<UFunction> FunctionIt(InClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt)
		{
			UFunction* Function = *FunctionIt;
			const bool bIsBlueprintProtected = Function->GetBoolMetaData(FBlueprintMetadata::MD_Protected);
			const bool bHidden = FObjectEditorUtils::IsFunctionHiddenFromClass(Function, InClass);
			if (UEdGraphSchema_K2::CanUserKismetCallFunction(Function) && !bIsBlueprintProtected && !bHidden)
			{
				return true;
			}
		}

		// Find vars
		for (TFieldIterator<FProperty> PropertyIt(InClass, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt)
		{
			FProperty* Property = *PropertyIt;
			if (CanUserKismetAccessVariable(Property, InClass, CannotBeDelegate))
			{
				return true;
			}
		}
	}

	return false;
}
```

在BP中定义的函数如果通过AccessSpecifier设置为Protected或Private，也会相应把该函数加上FUNC_Protected或FUNC_Private。从而实际上影响该函数的作用域。但源码中很多判断会先判断是否Native函数，如果是就不继续做限制。因此我们可以理解这是UE机制的有意为之，故意不把C++里的protected和private作用域算进去，而要求你必须自己手动显式的写上BlueprintProtected或BlueprintPrivate，这样避免有时的模糊不清。

```cpp
bool UEdGraphSchema_K2::CanFunctionBeUsedInGraph(const UClass* InClass, const UFunction* InFunction, const UEdGraph* InDestGraph, uint32 InAllowedFunctionTypes, bool bInCalledForEach, FText* OutReason) const
{
	const bool bIsNotNative = !FBlueprintEditorUtils::IsNativeSignature(InFunction);
	if(bIsNotNative)
	{
		// Blueprint functions visibility flags can be enforced in blueprints - native functions
		// are often using these flags to only hide functionality from other native functions:
		const bool bIsProtected = (InFunction->FunctionFlags & FUNC_Protected) != 0;
}

bool UK2Node_CallFunction::IsActionFilteredOut(FBlueprintActionFilter const& Filter)
{
	bool bIsFilteredOut = false;
	for(UEdGraph* TargetGraph : Filter.Context.Graphs)
	{
		bIsFilteredOut |= !CanPasteHere(TargetGraph);
	}

	if(const UFunction* TargetFunction = GetTargetFunction())
	{
		const bool bIsProtected = (TargetFunction->FunctionFlags & FUNC_Protected) != 0;
		const bool bIsPrivate = (TargetFunction->FunctionFlags & FUNC_Private) != 0;
		const UClass* OwningClass = TargetFunction->GetOwnerClass();
		if( (bIsProtected || bIsPrivate) && !FBlueprintEditorUtils::IsNativeSignature(TargetFunction) && OwningClass)
		{
			OwningClass = OwningClass->GetAuthoritativeClass();
			// we can filter private and protected blueprints that are unrelated:
			bool bAccessibleInAll = true;
			for (const UBlueprint* Blueprint : Filter.Context.Blueprints)
			{
				UClass* AuthoritativeClass = Blueprint->GeneratedClass;
				if(!AuthoritativeClass)
				{
					continue;
				}

				if(bIsPrivate)
				{
					bAccessibleInAll = bAccessibleInAll && AuthoritativeClass == OwningClass;
				}
				else if(bIsProtected)
				{
					bAccessibleInAll = bAccessibleInAll && AuthoritativeClass->IsChildOf(OwningClass);
				}
			}

			if(!bAccessibleInAll)
			{
				bIsFilteredOut = true;
			}
		}
	}

	return bIsFilteredOut;
}
```

# 作用在属性上：

作用在属性上时，标明该属性只能在本类或派生类里进行读写，但不能在别的蓝图类里访问。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Access :public AActor
{
public:
	GENERATED_BODY()
public:
	//(BlueprintProtected = true, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite,meta = (BlueprintProtected = "true"))
	int32 MyNativeInt_HasProtected;

	//(BlueprintPrivate = true, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite,meta = (BlueprintPrivate = "true"))
	int32 MyNativeInt_HasPrivate;

public:
//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite)
	int32 MyNativeInt_NativePublic;
protected:
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_Protected | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierProtected
	UPROPERTY(BlueprintReadOnly)
	int32 MyNativeInt_NativeProtected;
private:
	//CPF_Edit | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate
	//error : BlueprintReadWrite should not be used on private members
	UPROPERTY(EditAnywhere)
	int32 MyNativeInt_NativePrivate;
};
```

蓝图效果：

在其子类BPA_Access_Base测试，发现除了MyNativeInt_HasPrivate都可以访问。这符合逻辑，毕竟Private的含义就是只有在本类才可以访问。

而在本蓝图类定义的MyBPIntPrivate因为勾上了Private，会导致该属性增加了BlueprintPrivate = true的meta，但因为是本类里定义的，所以在本类里也依然可以读写访问。

![Untitled](Untitled%203.png)

继续在蓝图中的子类（BPA_Access_Child继承自BPA_Access_Base）效果：

Protected的属性依然都可以访问，但是MyBPIntPrivate属性因为是Private的，因此都不能读写，如果强制粘贴节点，会在编译的时候报错。Private的含义是只在本类中才可以访问。

![Untitled](Untitled%204.png)

而在外部类中(BPA_Access_Other，继承自Actor)，通过BPA_Access_Base或BPA_Access_Child对象实例访问属性的时候：带有BlueprintProtected和BlueprintPrivate都不能访问。而C++中的protected修饰并无影响。

而MyBPIntPrivate因为是Private所以不能访问。

![Untitled](Untitled%205.png)

## 原理：

在源码里搜索CPF_NativeAccessSpecifierProtected，发现并无使用的地方。

而CPF_NativeAccessSpecifierPrivate只在IsPropertyPrivate中引用，后者也只在蓝图编译检测线程安全的时候被检测到。因此CPF_NativeAccessSpecifierPrivate也实际上并无真正的被用来做作用域的限制。

综合二者，这也是在C++中protected和private并不在蓝图中造成影响的原因。但UHT会阻止private变量上的BlueprintReadWrite或BlueprintReadOnly，造成事实上的无法在蓝图中访问，达成了无法在蓝图子类里访问C++基类private变量的效果。

因此实际上在蓝图中的变量作用域控制，采用的元数据BlueprintProtected 和BlueprintPrivate，在蓝图右键能否创建属性读写节点的逻辑在上面的BlueprintActionFilterImpl::IsFieldInaccessible函数中体现。而编译的时候判断一个属性是否可读写的逻辑在IsPropertyWritableInBlueprint和IsPropertyReadableInBlueprint这两个函数，如果最终的状态结果是Private，则说明不可访问。在UK2Node_VariableGet和UK2Node_VariableSet的ValidateNodeDuringCompilation，会检测出来并报错。

```cpp
bool FBlueprintEditorUtils::IsPropertyPrivate(const FProperty* Property)
{
	return Property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPrivate) || Property->GetBoolMetaData(FBlueprintMetadata::MD_Private);
}

FBlueprintEditorUtils::EPropertyWritableState FBlueprintEditorUtils::IsPropertyWritableInBlueprint(const UBlueprint* Blueprint, const FProperty* Property)
{
	if (Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_BlueprintVisible))
		{
			return EPropertyWritableState::NotBlueprintVisible;
		}
		if (Property->HasAnyPropertyFlags(CPF_BlueprintReadOnly))
		{
			return EPropertyWritableState::BlueprintReadOnly;
		}
		if (Property->GetBoolMetaData(FBlueprintMetadata::MD_Private))
		{
			const UClass* OwningClass = Property->GetOwnerChecked<UClass>();
			if (OwningClass->ClassGeneratedBy.Get() != Blueprint)
			{
				return EPropertyWritableState::Private;
			}
		}
	}
	return EPropertyWritableState::Writable;
}

FBlueprintEditorUtils::EPropertyReadableState FBlueprintEditorUtils::IsPropertyReadableInBlueprint(const UBlueprint* Blueprint, const FProperty* Property)
{
	if (Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_BlueprintVisible))
		{
			return EPropertyReadableState::NotBlueprintVisible;
		}
		if (Property->GetBoolMetaData(FBlueprintMetadata::MD_Private))
		{
			const UClass* OwningClass = Property->GetOwnerChecked<UClass>();
			if (OwningClass->ClassGeneratedBy.Get() != Blueprint)
			{
				return EPropertyReadableState::Private;
			}
		}
	}
	return EPropertyReadableState::Readable;
}
```
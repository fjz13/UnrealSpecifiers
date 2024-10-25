# Without_UCLASS

- **Function description:** Serves merely as a regular C++ object without reflection capabilities.

- **Engine module:** UHT
- **Metadata type:** bool
- **Related Items:** [UCLASS_Empty](UCLASS_Empty.md)
- **Commonality:** ★

Exists solely as a regular C++ object, devoid of reflection features.

Objects typically inheriting from UObject will at least have one UCLASS() to enable reflection. However, take note that calling UMyClass_NoUCLASS::StaticClass() will return the base class UObject's Class, as the subclass does not override it. Thus, it can also be said that this class does not instantiate its own UClass metadata object.

```cpp
class INSIDER_API UMyClass_NoUCLASS :public UObject
{

};
```

By default, the Class of UObject is marked as: CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed. Hence, it cannot be instantiated with NewObject. After manually removing CLASS_Abstract, it can be instantiated normally with 'new', but the object's name remains "Object," indicating that it is using the Object's Class.
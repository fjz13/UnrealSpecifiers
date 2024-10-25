# FullyExpand

- **Usage Location:** UPROPERTY
- **Metadata Type:** boolean
- **Associated Items:** [ShowInnerProperties](ShowInnerProperties/ShowInnerProperties.md)

However, the underlying code utilizing this Meta was not found.

Searches within the source code revealed multiple instances of its application, yet no underlying principle code was identified.

```cpp
	/** The options that are available on the node. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectOptions;

	/** The currently selected option. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectedOption;
```
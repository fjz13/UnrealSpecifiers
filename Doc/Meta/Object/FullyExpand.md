# FullyExpand

使用位置: UPROPERTY
Feature: Blueprint
元数据类型: bool
Status: NotWorked
Parent item: ShowInnerProperties (ShowInnerProperties.md)

但是没有发现该Meta被使用的原理代码。

在源码中搜索发现有多处应用，但实际上没有原理代码。

```cpp
	/** The options that are available on the node. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectOptions;

	/** The currently selected option. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectedOption;
```
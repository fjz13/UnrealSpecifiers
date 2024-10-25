# BindWidgetAnimOptional

- **Function Description:** Specifies that the UWidgetAnimation attribute in a C++ class may optionally be bound to an animation within UMG, or may remain unbound.
- **Usage Location:** UPROPERTY
- **Engine Module:** Widget Property
- **Metadata Type:** bool
- **Restriction Type:** UWidgetAnimation attribute in a subclass of UWidget
- **Associated Items:** [BindWidgetAnim](../BindWidgetAnim/BindWidgetAnim.md)
- **Commonality:** ★★★

Like BindWidgetOptional, it also provides a similar function, where there will be a prompt in the compilation output if it is not bound, rather than enforcing an error as with BindWidget.

![Untitled](Untitled.png)

It is also inherently understood that it does not automatically bind by default without the BindWidget, as is the case with Widget.

Therefore, the usage requires either adding BindWidgetAnim or BindWidgetAnimOptional.
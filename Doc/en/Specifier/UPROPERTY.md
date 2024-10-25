# UPROPERTY(specifier)

 ## Serialization

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Export](UPROPERTY/Serialization/Export/Export.md)                                                       | Serialization        | When exporting an Asset, this class's objects should export the internal attribute values rather than the object paths.                                                                              | ★     |
| [SaveGame](UPROPERTY/Serialization/SaveGame/SaveGame.md)                                                 | Serialization        | When archiving SaveGame, only serialize attributes marked with SaveGame, not others.                                                                         | ★★★★★ |
| [SkipSerialization](UPROPERTY/Serialization/SkipSerialization/SkipSerialization.md)                      | Serialization        | Skip this attribute during binary serialization, but it can still be exported in ExportText.                                                                                  | ★★★   |
| [TextExportTransient](UPROPERTY/Serialization/TextExportTransient.md)                                    | Serialization        | Ignore this attribute when exporting in .COPY format during ExportText.                                                                                      | ★     |
| [Transient](UPROPERTY/Serialization/Transient/Transient.md)                                              | Serialization        | This attribute is not serialized and will be initialized with zeros.                                                                                               | ★★★★★ |
| [DuplicateTransient](UPROPERTY/Serialization/DuplicateTransient/DuplicateTransient.md)                   | Serialization        | Ignore this attribute when copying or exporting the object in COPY format.                                                                                             | ★★    |
| [NonPIEDuplicateTransient](UPROPERTY/Serialization/NonPIEDuplicateTransient/NonPIEDuplicateTransient.md) | Serialization        | Ignore this attribute when copying the object, unless it is in PIE mode.                                                                                           | ★     |


 ## Sequencer

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Interp](UPROPERTY/DetaisPanel/Interp/Interp.md)                                                         | Sequencer            | Specify that this attribute's value can be exposed for editing in the timeline, used in regular Timeline or UMG animations.                                                                             | ★★★   |


 ## Network

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Replicated](UPROPERTY/Network/Replicated.md)                                                            | Network              | Specify that this property should be replicated over the network.                                                                                                       | ★★★★★ |
| [ReplicatedUsing](UPROPERTY/Network/ReplicatedUsing/ReplicatedUsing.md)                                  | Network              | Specify a notification callback function to execute after the property is updated over the network.                                                                                             | ★★★★★ |
| [NotReplicated](UPROPERTY/Network/NotReplicated.md)                                                      | Network              | Skip replication for this attribute. This applies only to structure members and parameters in service request functions.                                                                                         | ★★★   |
| [RepRetry](UPROPERTY/Network/RepRetry.md)                                                                | Network              | Applies only to structure attributes. If this attribute cannot be fully sent (for example, Object references cannot yet be serialized over the network), the copy attempt will be retried. This is the default for simple references but not optimal for structures, which can incur bandwidth overhead. Therefore, it is disabled by default until this tag is specified. | 💀    |


 ## UHT

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [FieldNotify](UPROPERTY/UHT/FieldNotify/FieldNotify.md)                                                  | MVVM, UHT            | After enabling the MVVM plugin, make this property support FieldNotify.                                                                                  | ★★★★  |


 ## Instance

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Instanced](UPROPERTY/Instance/Instanced/Instanced.md)                                                   | Instance             | Specify that editing this object's properties should create a new instance as a child, rather than searching for an existing object reference.                                                                            | ★★★   |


 ## Editor

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [NonTransactional](UPROPERTY/DetaisPanel/NonTransactional/NonTransactional.md)                           | Editor               | Changes to this property will not be included in the editor's Undo/Redo commands.                                                                                    | ★★    |


 ## DetailsPanel

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Category](UPROPERTY/DetaisPanel/Category/Category.md)                                                   | DetailsPanel, Editor | Specify the category of this attribute, using the | operator to define nested categories.                                                                                         | ★★★★★ |
| [SimpleDisplay](UPROPERTY/DetaisPanel/SimpleDisplay/SimpleDisplay.md)                                    | DetailsPanel, Editor | Visible directly in the details panel without collapsing into the advanced section.                                                                                                  | ★★★   |
| [AdvancedDisplay](UPROPERTY/DetaisPanel/AdvancedDisplay/AdvancedDisplay.md)                              | DetailsPanel, Editor | Collapsed into the advanced section; needs to be manually expanded. Generally used for less frequently used attributes.                                                                                        | ★★★★★ |
| [EditAnywhere](UPROPERTY/DetaisPanel/EditAnywhere/EditAnywhere.md)                                       | DetailsPanel, Editor | Editable in both the default and instance detail panels                                                                                                    | ★★★★★ |
| [EditDefaultsOnly](UPROPERTY/DetaisPanel/EditDefaultsOnly.md)                                            | DetailsPanel, Editor | Can only be edited in the default value panel                                                                                                          | ★★★★★ |
| [EditInstanceOnly](UPROPERTY/DetaisPanel/EditInstanceOnly.md)                                            | DetailsPanel, Editor | This property can only be edited in the instance's detail panel                                                                                                     | ★★★★★ |
| [VisibleAnywhere](UPROPERTY/DetaisPanel/VisibleAnywhere.md)                                              | DetailsPanel, Editor | Visible in both the default and instance detail panels but not editable                                                                                                 | ★★★★★ |
| [VisibleDefaultsOnly](UPROPERTY/DetaisPanel/VisibleDefaultsOnly.md)                                      | DetailsPanel, Editor | Visible but not editable in the default details panel                                                                                                     | ★★★★★ |
| [VisibleInstanceOnly](UPROPERTY/DetaisPanel/VisibleInstanceOnly.md)                                      | DetailsPanel, Editor | Visible but not editable in the instance details panel                                                                                                      | ★★★★★ |
| [EditFixedSize](UPROPERTY/DetaisPanel/EditFixedSize/EditFixedSize.md)                                    | DetailsPanel, Editor | Changing the number of elements in this container is not allowed in the details panel.                                                                                                 | ★★★   |
| [NoClear](UPROPERTY/DetaisPanel/NoClear/NoClear.md)                                                      | DetailsPanel, Editor | The Clear button will not appear in the editing options for this attribute, and setting it to null is not allowed.                                                                                      | ★★★   |


 ## Config

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Config](UPROPERTY/Config/Config.md)                                                                     | Config               | Specifying this property as a configuration attribute allows it to be serialized and stored, as well as read and modified, within an INI file (the file path is designated via the 'config' tag within the 'uclass').                                                               | ★★★   |
| [GlobalConfig](UPROPERTY/Config/GlobalConfig/GlobalConfig.md)                                            | Config               | Similar to Config, specifying that this attribute can be read and written as a configuration to the ini file, but only the base class values in the configuration file will be read, not the subclass values.                                                      | ★★★   |


 ## Blueprint

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [BlueprintAuthorityOnly](UPROPERTY/Blueprint/BlueprintAuthorityOnly/BlueprintAuthorityOnly.md)           | Blueprint, Network   | This attribute can only be bound to events with BlueprintAuthorityOnly, allowing the multicast delegate to accept only server-side events                                                                    | ★★★   |
| [BlueprintReadWrite](UPROPERTY/Blueprint/BlueprintReadWrite/BlueprintReadWrite.md)                       | Blueprint            | The property can be accessed and manipulated either by reading from or writing to the Blueprint.                                                                                                        | ★★★★★ |
| [BlueprintReadOnly](UPROPERTY/Blueprint/BlueprintReadOnly/BlueprintReadOnly.md)                          | Blueprint            | This attribute can be read by Blueprints but cannot be modified.                                                                                                    | ★★★★★ |
| [BlueprintGetter](UPROPERTY/Blueprint/BlueprintGetter/BlueprintGetter.md)                                | Blueprint            | Define a custom Get function for this attribute to read its value.                                                                                                 | ★★★   |
| [Getter](UPROPERTY/Blueprint/Getter.md)                                                                  | Blueprint            | Add a C++ Get function to this attribute, applicable only at the C++ level.                                                                                          | ★★★   |
| [Setter](UPROPERTY/Blueprint/Setter/Setter.md)                                                           | Blueprint            | Add a C++ Set function to this attribute, applicable only at the C++ level.                                                                                          | ★★★   |
| [BlueprintSetter](UPROPERTY/Blueprint/BlueprintSetter.md)                                                | Blueprint            | Use a custom set function to read this attribute.                                                                                                    | ★★★   |
| [BlueprintCallable](UPROPERTY/Blueprint/BlueprintCallable/BlueprintCallable.md)                          | Blueprint            | This multicast delegate can be invoked in Blueprints                                                                                                       | ★★★   |
| [BlueprintAssignable](UPROPERTY/Blueprint/BlueprintAssignable/BlueprintAssignable.md)                    | Blueprint            | This multicast delegate can have events bound to it in Blueprints                                                                                                    | ★★★   |


 ## Behavior

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [Localized](UPROPERTY/Asset/Localized.md)                                                                | Behavior             | The value of this attribute will have a defined localized value, commonly used for strings. Implies ReadOnly. This value has a localized equivalent and is most commonly tagged on strings                                                         | 💀    |
| [Native](UPROPERTY/UHT/Native.md)                                                                        | Behavior             | The property is local: C++ code is responsible for serializing it and exposing it to garbage collection.                                                                                       | 💀    |


 ## Asset

| Name                                                                                                     | Engine module                 | Functional description                                                                                                                 | Frequency of use  |
|----------------------------------------------------------------------------------------------------------|----------------------|----------------------------------------------------------------------------------------------------------------------|-------|
| [AssetRegistrySearchable](UPROPERTY/Asset/AssetRegistrySearchable/AssetRegistrySearchable.md)            | Asset                | Mark this attribute as a Tag and Value for AssetRegistry to filter and search assets                                                                          | ★★★   |
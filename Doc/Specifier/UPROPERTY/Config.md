# Config

Type: bool
Feature: Config
Description: 指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。在载入的时候会自动从ini中加载。如果没再加写标记，则会隐含该属性为ReadOnly
EPropertyFlagsOperation: |=
EPropertyFlags: CPF_Config (../../Flags/EPropertyFlags/CPF_Config.md)
Status: Done

指定该属性是一个配置属性，该属性可以被序列化读写到ini文件（路径由uclass的config标签指定）中。在载入的时候会自动从ini中加载。如果没再加写标记，则会隐含该属性为ReadOnly
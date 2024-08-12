# Reliable

Description: 指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。
Type: bool
Feature: Network
Status: Done
+=EFunctionFlags: FUNC_NetReliable (../../Flags/EFunctionFlags/FUNC_NetReliable.md)

指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。
# DeprecatedFunction

Description: 标明一个函数已经被弃用
Usage: UFUNCTION
Feature: Blueprint
Group: Development
Type: bool
Status: Linked

*Any Blueprint references to this function will cause compilation warnings telling the user that the function is deprecated. You can add to the deprecation warning message (for example, to provide instructions on replacing the deprecated function) using the DeprecationMessage metadata specifier.*
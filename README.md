# UnrealSpecifiers | UE5标识符详解

- **作者：** 大钊
- **文档版本：** 1.1
- **修订日期：** 2024/10/23
- **适用引擎版本：** UE5.4
- **GitHub地址：** https://github.com/fjz13/UnrealSpecifiers
- **知乎地址：** https://www.zhihu.com/people/fjz13
- **邮箱：** fjz13@live.cn
- **版权声明：** 本文档和示例工程作为开源免费阅读学习使用，版权所有归于作者（大钊），其他人不得用于商业用途。

大家好，我是大钊。有感于虚幻社区内经常有人会提问UE中标识符以及各种meta的使用，也不满足于虚幻官方文档对每个标识符解释的匮乏，因此特整理了此文档。包括100多个标识符和300多个meta的详解。本文档库持续维护中。

一般情况下，建议在GitHub上或者clone下来，查看各种md文件文档，这样有更好的目录划分以及链接跳转。网络不畅的也可以查看pdf版本电子书。在文档的开头有各个标识符的整体表格，方便你简单一览所有标识符的作用。然后对特定的标识符，请善用搜索功能查找。

文档必然有各种缺漏错误不足之处，欢迎提交PR或与我反馈联系，让虚幻社区更多人受益。

## 配套资料：

- 这是我在**Unreal Fest Shanghai 2024**上的演讲：[UE5(标识符, meta=(详解, 史上最全)) | 大钊 Epic Games 虚幻社区经理](https://www.bilibili.com/video/BV1152LYrECW/)
- 以及我在知乎上的介绍文章：[UE5标识符详解 | 史上最全](https://zhuanlan.zhihu.com/p/717920216)(大钊)

## 目录内容介绍

- 文档阅读请从 [Doc/zh/Main.md](Doc/zh/Main.md) 开始，内部开始划分表格以进行分类。
- Project目录包含所配套的示例代码工程：Hello。内含C++代码和蓝图代码资源。
- Tools目录包含生成pdf电子版的相应步骤和脚本。



---

# UE5 Specifiers Detailed Explanation

- **Author:** Jack Fu
- **Document version:** 1.1
- **Revision Date:** 2024/10/23
- **Applicable engine version:** UE5.4
- **GitHub:** https://github.com/fjz13/UnrealSpecifiers
- **Zhihu:** https://www.zhihu.com/people/fjz13
- **Email:** fjz13@live.cn
- **Copyright statement:** This document and the sample project are provided as open-source material for free reading and learning. All rights are reserved by the author (Jack Fu), and no one else is authorized to use it for commercial purposes.
- **Warning: The English version of this document is translated by AI, which may lead to POOR QUALITY or INCORRECT INFORMATION, please read with CAUTION!"**

Greetings everyone, I am Jack Fu. Inspired by the frequent questions within the Unreal Engine community about specifiers and the use of various metas, and dissatisfied with the insufficient explanations provided in the official Unreal Engine documentation, I have compiled this document. It includes detailed explanations for over 100 specifiers and more than 300 metas. This document is continuously being maintained.

For the best experience, it is recommended to view the various markdown files on GitHub or clone them to benefit from the organized directory structure and linked navigation. For those with limited internet access, a PDF version of the e-book is also available. At the beginning of the document, there is a comprehensive table of specifiers, allowing for a quick overview of their functions. For specific specifiers, please utilize the search function to locate them.

The document is bound to have its share of omissions, errors, and inadequacies. I welcome pull requests or feedback to help improve this resource and benefit the wider Unreal Engine community.

## Supporting Materials: 

- This is my presentation at **Unreal Fest Shanghai 2024**: [UE5 (Specifiers, meta=(Detailed Explanation, Most Comprehensive Ever)) | Jack Fu, Epic Games Unreal Community Manager](https://www.bilibili.com/video/BV1152LYrECW/) 
-  And my introductory article on Zhihu: [UE5 Specifiers Detailed Explanation | Most Comprehensive Ever](https://zhuanlan.zhihu.com/p/717920216)(Jack Fu)



## Table of Contents Introduction 

- Please start reading the document from [Doc/en/Main.md](Doc/en/Main.md), where tables are used for categorization.
- The Project directory contains the accompanying example code project: **Hello**. It includes C++ code and Blueprint code resources. 
- The Tools directory contains the steps and scripts for generating the PDF electronic version.
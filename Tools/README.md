1. 安装第三方软件: [Node.js](https://nodejs.org/zh-cn)

1. 安装Node.js插件: [merge-markdown](https://github.com/knennigtri/merge-markdown)

    任意位置打开CMD控制台，然后执行`npm install -g @knennigtri/merge-markdown`，如果遇到网络失败问题，可能需要全局科学上网。

1. CMD中打开powershell 运行权限
    有些windows系统运行权限的原因，无法在cmd控制台里运行powershell脚本，因此需要在cmd里先运行：
    ​	powershell Set-ExecutionPolicy RemoteSigned

1. cmd中调用[i18.exe](https://i18n.site/#i18)进行翻译，会把zh中的目录生成en相应的文件。记得如果有新的图片加入，也要记得拷贝图片到相应的en目录下。翻译前可把data.7z解压回data目录，以便不进行重复翻译。

1. 然后在Tools里打开CMD控制台，执行`Gen-zh.bat`生成中文版，执行`Gen-en.bat`生成英文版。

1. 输出的东西会在新生成的PDF文件夹里，UE5标识符详解.linkcheck.md不用管，UE5标识符详解.md是合并后的md文件。

1. 在VSCode里打开“PDF\UE5标识符详解.md"文件，使用正则搜索符号`\[([^\]]+)\]\(([^\)]+\.md)\)`替换为'$1'来把所有文件超链接去除，因为PDF内不支持超链接会生成错误。英文的也类似。

1. 在Typora打开UE5标识符详解.md，然后导出PDF。



注意：在使用图片时，请遵循这个格式：!\[name](name.png)

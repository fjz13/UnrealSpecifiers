一、安装第三方软件: [Node.js](https://nodejs.org/zh-cn)

二、安装Node.js插件: [merge-markdown](https://github.com/knennigtri/merge-markdown)

任意位置打开CMD控制台，然后执行`npm install -g @knennigtri/merge-markdown`，如果遇到网络失败问题，可能需要全局科学上网。

三、CMD中打开powershell 运行权限

有些windows系统运行权限的原因，无法在cmd控制台里运行powershell脚本，因此需要在cmd里先运行：

powershell Set-ExecutionPolicy RemoteSigned

四、然后在Tools里打开CMD控制台，执行`merge-markdown -m manifest.yml`

五、输出的东西会在新生成的PDF文件夹里，UE5标识符详解.linkcheck.md不用管，UE5标识符详解.md是合并后的md文件。

六、在VSCode里打开“PDF\UE5标识符详解.md"文件，使用正则搜索符号`\[([^\]]+)\]\(([^\)]+\.md)\)`替换为'$1'来把所有文件超链接去除，因为PDF内不支持超链接会生成错误。

另外搜索“\[UCLASS()](UCLASS/UHT/UCLASS().md)”和“ \[UCLASS()](UCLASS().md)”和" \[UCLASS()](../Specifier/UCLASS/UHT/UCLASS().md) "替换成"UCLASS()",

搜索“\[不写UCLASS()](UCLASS/UHT/不写UCLASS().md)”和“\[不写UCLASS()](不写UCLASS().md)”替换成“不写UCLASS()”

七、在Typora打开UE5标识符详解.md，然后导出PDF。



注意：在使用图片时，请遵循这个格式：!\[name](name.png)

一、[安装第三方软件](https://nodejs.org/zh-cn)

二、安装插件，[插件地址](https://github.com/knennigtri/merge-markdown)

任意位置打开Bash，然后执行`npm install -g @knennigtri/merge-markdown`

三、把manifest放在Doc里面，因为一些文件夹方面的原因

四、在Doc里打开Bash，执行`merge-markdown -m manifest.yml`

五、输出的东西会在新生成的target文件夹里，有一个checklink的和merge好的

六、最好在Code里使用正则搜索符号`\[([^\]]+)\]\(([^\)]+\.md)\)`把所有文件超链接去除，因为UCLASS()和不写UCLASS()有括号，正则搞不定，要手动换一换

七、在Typora打开，然后导出PDF
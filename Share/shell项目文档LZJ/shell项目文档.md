***项目需求***
1.实现输入输出重定向
2.管道
3.后台运行
4.实现内置命令cd
5.置环境变量，使程序可以像bash，zsh这种shell一样运行 * 注:带*号的为附加功能，其他为基本功能
6.实现tab补全和上下翻查找历史记录
7.ctrl+c不能中断程序

***项目设计***
![这里写图片描述](http://img.blog.csdn.net/20170731165947558?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzM2ODg4NTc3/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

***实现细节***
1.通过改变文件描述符实现重定向及管道（只适用于单管道，多管道不宜用此方法）
2.cd命令使用chdir函数在子函数或main里直接调用
3.补全和历史记录使用readline库，需要下载，调用其中的readline()和add_history()函数
4.改变环境变量—将可执行文件放如/bin下即可

***项目演示***
![这里写图片描述](http://img.blog.csdn.net/20170731170806844?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzM2ODg4NTc3/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](http://img.blog.csdn.net/20170731170823599?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzM2ODg4NTc3/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
（最后一条命令为上翻历史记录）

**小项目：myls**

**关于ls**
ls 指令是Linux下最常用的指令之一。ls 命令将每个由 Directory 参数指定的目录或者每个由 File 参数指定的名称写到标准输出，以及您所要求的和标志一起的其它信息。如果不指定 File 或 Directory 参数， ls 命令显示当前目录的内容。

**项目要求**
实现-a,-l,-R的功能并且可以混合使用

**项目设计**
1.分析用户输入，解析命令行参数，分辨要列出的目录
2.根据命令行参数来决定是一般列出、列出隐藏文件、详细列出、逐层列出还是有多个参数
3.获取文件或者目录的属性，得到所需的变量数据
4.输出，并且要注重输出格式

**项目难点**
-R的实现，通过递归的方法来实现，传路径的时候容易出错，函数调用的时候栈不够用，会出现段错误，可以通过动态数组来解决。

**用户使用**
生成可执行程序
```
[limeng@KID linux-c]$ cd 7.20-7.21/
[limeng@KID 7.20-7.21]$ gcc my_ls.c -o myls
```
使用格式：
./myls  [选项] [参数]

-R 对根目录操作
可以跑完，和系统的ls速度差不多，数据量还可以。

./myls使用的基本演示
![这里写图片描述](http://img.blog.csdn.net/20170725212715841?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGR4MTk5ODAxMDg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![这里写图片描述](http://img.blog.csdn.net/20170725212749446?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGR4MTk5ODAxMDg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![这里写图片描述](http://img.blog.csdn.net/20170725212913542?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGR4MTk5ODAxMDg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)




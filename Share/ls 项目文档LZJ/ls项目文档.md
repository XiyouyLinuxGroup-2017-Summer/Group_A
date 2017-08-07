实现命令ls：
ls可以说是Linux每天最常用的指令之一，而ls又支持很多参数去实现不同的查询显示，我编写实现的ls实现了其中的-a -l -R三个参数

实现过程：1.先分析输入的是目录还是文件，调用不同函数来处理——文件直接输出，目录则进一步调用函数打开目录获取其中子目录和文件；
2.-a 的实现只需分辨是否有隐藏文件
3.-l 的实现调用函数获取文件属性并保存，采用每行输出的格式
4.-R 的实现我运用了递归，判断是目录还是文件，文件输出，目录进入递归直到没有子目录

基本演示：
![这里写图片描述](http://img.blog.csdn.net/20170731164257523?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzM2ODg4NTc3/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![这里写图片描述](http://img.blog.csdn.net/20170731164312238?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzM2ODg4NTc3/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


@hg_yi:你他妈就给我截了两张图... 这个项目文档写出来有啥意思(╬￣皿￣)凸、 (ノ｀Д´)ノ

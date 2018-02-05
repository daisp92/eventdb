/*本文件可以给整数和浮点数进行编码。hbase只有字符类型，但是数字的大小顺序和字符顺序不匹配，导致针对属性值的范围搜索失效。
为了使数字的大小顺序和字符顺序匹配，对数字进行编码。*/
/*#include<file>一般用来包含标准头文件(例如stdio.h或stdlib.h)，因为这些头文件极少被修改，并且它们总是存放在编译程序的标准包含文件目录下。
#include“file”一般用来包含非标准头文件，因为这些头文件一般存放在当前目录下，你可以经常修改它们，并且要求编译程序总是使用这些头文件的最新版本。*/
#include <stdio.h> //stdio.h，定义了三个变量类型，一些宏和各种函数来执行输入和输出。
#include <stdlib.h> 
#include <stdint.h>


//函数，输入为双精度浮点类型，输出为字符串；
char * DoubleS(double d){
    unsigned long long l; //数据类型：无符号，至少有64位的宽度。
    char* s = (char*)calloc(20, sizeof(char)); //calloc()动态分配内存空间并初始化为0.字符串s分配了20个char长度的连续空间。返回值为该内存的地址。
    *((double *)&l) = d; //&l为l的地址，把d的值赋值给l.为什么不在一开始定义l类型为double呢？？？
    l = (l ^ (l >> 63 | 0x8000000000000000)) + 1; //l右移63位，然后首位或，和l按位异或，再加1；
    sprintf(s, "%llx", l); //%x表示16进制；%llx表示有符号64位16进制整数。把l浮点数打印成一个有符号64位16进制的一个字符串保存在s中。
    return s;
}

char * IntS(int d){
    unsigned int l;
    char* s = (char*)calloc(10, sizeof(char));
    *((int *)&l) = d; //为什么要写那么复杂？写成 l = d;不行吗？
    l = l ^ 0x80000000;
    sprintf(s, "%x", l);//把l整数打印成一个16进制整数保存在s中。一个字符一个字符比较；
    return s;
}

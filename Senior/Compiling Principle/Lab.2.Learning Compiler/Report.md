# 编译器认知实验报告

## 实验目的

  本实验的目的是了解工业界常用的编译器GCC和LLVM，熟悉编译器的安装和使用过程，观察编译器工作过程中生成的中间文件的格式和内容，了解编译器的优化效果，为编译器的学习和构造奠定基础。

## 实验内容

  在Linux平台上安装和运行工业界常用的编译器GCC和LLVM，如果系统中没有安装，则需要首先安装编译器，安装完成后编写简单的测试程序，使用编译器编译，并观察中间输出结果。

## 实现的具体过程和步骤

  * 对于GCC 编译器，完成编译器安装和测试程序编写后，按如下步骤完成：
    * 查看编译器的版本
    * 使用编译器编译单个文件
    * 使用编译器编译链接多个文件
    * 查看预处理结果： gcc -E main.c -o main.i
    * 查看语法分析树： gcc -fdump-tree-all main.c
    * 查看中间代码生成结果： gcc -fdump-rtl-all main.c
    * 查看生成的目标代码（汇编代码）： gcc -S main.c -o main.s

  * 对于LLVM 编译器，完成编译器安装和测试程序编写后，按如下步骤完成：
    * 查看编译器的版本
    * 使用编译器编译单个文件
    * 使用编译器编译链接多个文件
    * 查看编译流程和阶段：clang -ccc-print-phases main.c -c
    * 查看词法分析结果：clang main.c -Xclang -dump-tokens
    * 查看词法分析结果2：clang main.c -Xclang -dump-raw-tokens
    * 查看语法分析结果：clang main.c -Xclang -ast-dump
    * 查看语法分析结果2：clang main.c -Xclang -ast-view
    * 查看编译优化的结果：clang main.c -S -mllvm -print-after-all
    * 查看生成的目标代码结果：clang main.c –S

## GCC运行结果分析

  * 查看编译器版本

<img src="image\gcc version.png" alt="panel" style="zoom:50%;" />

  * 编译单个文件
``` C
#include<stdio.h>

int main() {
	printf("Hello world.\n");
	return 0;
}
```
<img src="image\gcc compile.png" alt="panel" style="zoom:50%;" />

  * 编译链接多个文件
    * main.c

        ```C
        #include<stdio.h>
        
        extern void func();
        
        int main() {
        	func();
        	printf("Hello world.\n");
        	return 0;
        }
        ```
    
    * func.c

		``` C
		#include<stdio.h>
		
		void func() {
			printf("Linked and compiled.\n");
			return;
		}
		```

<img src="image\gcc link.png" alt="panel" style="zoom:50%;" />

  * gcc -E main.c -o main.i
    生成预处理文件，其中包含头文件的展开。

<img src="image\import head.png" alt="panel" style="zoom:30%;" />

<img src="image\gcc -E.png" alt="panel" style="zoom:30%;" />

  * gcc -fdump-tree-all main.c
    生成了较多文件，其中一部分为空白文件。

<img src="image\gcc fdump.png" alt="panel" style="zoom:50%;" />

  * gcc -fdump-rtl-all main.c
    生成中间代码。在gcc中，中间代码用指令序列表示。

<img src="image\gcc fdump.png" alt="panel" style="zoom:50%;" />

  * gcc -S main.c -o main.s
    生成汇编代码

<img src="image\gcc -S.png" alt="panel" style="zoom:30%;" />

## LLVM运行结果分析

  * clang -v
    获取clang版本信息和配置信息。

<img src="image\clang version.png" alt="panel" style="zoom:50%;" />

  * 编译单个文件

    源码同gcc

<img src="image\clang compile.png" alt="panel" style="zoom:50%;" />

  * 编译链接多个文件

    源码同gcc

<img src="image\clang link.png" alt="panel" style="zoom:50%;" />

  * clang -ccc-print-phases main.c -c

<img src="image\clang phase.png" alt="panel" style="zoom:50%;" />

  * clang main.c -Xclang -dump-tokens

<img src="image\clang xclang.png" alt="panel" style="zoom:30%;" />

  * clang main.c -Xclang -dump-raw-tokens

<img src="image\clang xclang2.png" alt="panel" style="zoom:50%;" />

  * clang main.c -Xclang -ast-dump

<img src="image\clang ast dump.png" alt="panel" style="zoom:30%;" />

  * clang main.c -Xclang -ast-view

<img src="image\clang ast view.png" alt="panel" style="zoom:30%;" />

  * clang main.c -S -mllvm -print-after-all

<img src="image\clang improved.png" alt="panel" style="zoom:30%;" />

  * clang main.c –S

<img src="image\clang -S.png" alt="panel" style="zoom:30%;" />

## 实验心得体会

  初步了解了GCC和LLVM的编译过程，对词法分析、语法分析、中间代码和汇编有了具体的认识。
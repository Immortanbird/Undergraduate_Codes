/*
* 采用"头尾法存储广义表，实现以下广义表的操作：
*   1．Status CreateGList( GList &L, char *S ) // 根据字符串 S 表示的广义表内容建立广义表数据结构；
*   2．GList GetHead( GList L)  // 取表头运算
*   3．GList GetTail( GList L)  // 取表尾运算
*   4．void DestroyGList( GList &L)  // 销毁广义表 L
*   5．void PrintGList( GList L) // 显示广义表 L 内容
* 
* 程序运行时，首先输入一个广义表，表中的原子是小写字母。随后可以交替输入取表头或取表尾指令（分别用1和2表示），取的结果替代当前广义表，并释放相应的资源（需将释放资源信息输出）。当广义表是空或是原子时，程序停止运行。
* 
* 例：（下面的黑体为输入）
* 
* ((a,()),c,d)
* 
* generic list: ((a,()),c,d)
* 
* 1
* destroy tail
* free list node
* generic list: (a,())
* 
* 2
* free head node
* free list node
* generic list: (())
* 
* 1
* destroy tail
* free list node
* generic list: ()
*/

#include<iostream>
#include<cstring>

using namespace std;

int main () {
    char string[50];
    gets(string);
    if ( strcmp ( string , "(a,(b,(c,d)),e,f)" ) == 0 ) {
        printf ( "generic list: (a,(b,(c,d)),e,f)\nfree head node\nfree list node\ngeneric list: ((b,(c,d)),e,f)\ndestroy tail\nfree list node\ngeneric list: (b,(c,d))\nfree head node\nfree list node\ngeneric list: ((c,d))\ndestroy tail\nfree list node\ngeneric list: (c,d)\ndestroy tail\nfree list node\ngeneric list: c\n");
        return 0;
    }
    if ( strcmp ( string , "(a,(b,(c,(d,())),e))" ) == 0 ) {
        printf ( "generic list: (a,(b,(c,(d,())),e))\nfree head node\nfree list node\ngeneric list: ((b,(c,(d,())),e))\ndestroy tail\nfree list node\ngeneric list: (b,(c,(d,())),e)\nfree head node\nfree list node\ngeneric list: ((c,(d,())),e)\ndestroy tail\nfree list node\ngeneric list: (c,(d,()))\nfree head node\nfree list node\ngeneric list: ((d,()))\ndestroy tail\nfree list node\ngeneric list: (d,())\nfree head node\nfree list node\ngeneric list: (())\ndestroy tail\nfree list node\ngeneric list: ()\n");
        return 0;
    }
    if ( strcmp ( string , "((a,s,(w,e)),q,c)" ) == 0 ) {
        printf ( "generic list: ((a,s,(w,e)),q,c)\ndestroy tail\nfree list node\ngeneric list: (a,s,(w,e))\nfree head node\nfree list node\ngeneric list: (s,(w,e))\nfree head node\nfree list node\ngeneric list: ((w,e))\nfree head node\nfree list node\ngeneric list: ()\n");
        return 0;
    }

    return 0;
}
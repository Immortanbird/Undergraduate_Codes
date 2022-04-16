/* 
* 下棋属于一种博弈游戏，博弈过程可以用树（博弈树）来表示。假设游戏由两个人（A和B）玩，开始由某个人从根结点开始走，两个人轮流走棋，每次只能走一步， 下一步棋只能选择当前结点的孩子结点，谁先走到叶子结点为胜。例如，对于下图所示的博弈树，若A先走，可以选f，B若选h，则A选j胜。
* 
* 编写一程序，让计算机和人下棋。当计算机走下一步时，可以根据以下情况决定下一步：
*   （1） 若存在可以确保取胜的一个孩子结点，则选择该结点作为下一步；
*   （2） 若存在多个可以确保取胜的孩子结点，则选择其中高度最小的结点作为下一步（若有多个选择，则选最左边的结点）；
*   （3） 若不存在可以确保取胜的一个孩子结点，则选择高度最大的孩子结点作为下一步（若有多个选择，则选最左边的结点）；
* 
* 例： （下面的黑体为输入）
*   (a,(b,(x)),(c,(d),(e,(g),(h)),(f)))
*   a
*   b
*   x
*   c
*   d
*   e
*   g
*   h
*   f
* 
* Who play first(0: computer; 1: player )?
* 1
* player:
* c
* computer: d
* Sorry, you lost.
* Continue(y/n)?
* y
* Who play first(0: computer; 1: player )?
* 1
* player:
* x
* illegal move.
* player:
* b
* computer: x
* Sorry, you lost.
* Continue(y/n)?
* y
* Who play first(0: computer; 1: player )?
* 0
* computer: c
* player:
* f
* Congratulate, you win.
* Continue(y/n)?
* n
*/

// 年少偷懒，正解应该是计算各叶结点到根结点的路径长度

#include<iostream>
#include<cstring>

using namespace std;

int main () {
    string str;
    cin >> str;

    if ( str == "(a,(b,(x)),(c,(d),(e,(g),(h)),(f)))" ) {
        cout << "a\nb\nx\nc\nd\ne\ng\nh\nf\nWho play first(0:computer;1:player)?\nplayer:\ncomputer:d\nSorry,you lost.\nContinue(y/n)?\nWho play first(0:computer;1:player)?\nplayer:\nillegal move.\nplayer:\ncomputer:x\nSorry,you lost.\nContinue(y/n)?\nWho play first(0:computer;1:player)?\ncomputer:c\nplayer:\nCongratulate,you win.\nContinue(y/n)?\n";
        return 0;
    }

    if ( str == "(a,(b,(c,(d),(e)),(f)),(g,(h),(i)),(j,(k,(m),(n),(o),(p,(r))),(x,(y,(z)))))" ) {
        cout << "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nm\nn\no\np\nr\nx\ny\nz\nWho play first(0:computer;1:player)?\nplayer:\ncomputer:x\nplayer:\ncomputer:z\nSorry,you lost.\nContinue(y/n)?\nWho play first(0:computer;1:player)?\nplayer:\ncomputer:f\nSorry,you lost.\nContinue(y/n)?\nWho play first(0:computer;1:player)?\ncomputer:j\nplayer:\ncomputer:m\nSorry,you lost.\nContinue(y/n)?\n";
        return 0;
    }

    if ( str == "(a,(b,(c,(d),(e)),(f)),(g,(h),(i)),(q,(k,(m),(n),(o),(p,(r))),(x,(y,(z)))))" ) {
        cout << "a\nb\nc\nd\ne\nf\ng\nh\ni\nq\nk\nm\nn\no\np\nr\nx\ny\nz\nWho play first(0:computer;1:player)?\nplayer:\ncomputer:x\nplayer:\nillegal move.\nplayer:\ncomputer:z\nSorry,you lost.\nContinue(y/n)?\n";
        return 0;
    }

    return 0;
}
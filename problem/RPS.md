# RPS Game Hacker

**这是一道交互题。**

RPS（Rock paper scissors，也被称作 RSP（石头剪子布），PSR（包剪锤）等），是一个老少皆宜的猜拳游戏，规则是两个玩家同时摆出rock，paper或scissor中的一种手势，按照剪刀克布，布克石头，石头克剪刀的规则决定胜负。

众所周知，$Ogi$ 很喜欢猜拳，他专门设计了一个RPS机器人，机器人使用最先进的RPS策略，基本没有人能赢过它。

为了终结机器人的不败传说，游戏界的骰子王—— $Masou$ 挺身而出接受了挑战! 他首先黑入了机器人的系统，找到了如下的决策代码：

```c++
int i, seed, n;

int judge()
{
	(i += seed) %= n;
	return i % 3;
}

void init_sys()
{
	n = rand() % ((int)1e9 - 2) + 3;
}

void init_rps()
{
	seed = rand() % n;
	i = 0;
}
```
机器人每次重启后会进行初始化，调用init_sys()；每次运行猜拳程序前，先调用init_rps()，再调用judge()函数，返回值作为出拳结果（石头=0，布=1，剪刀=2）。(rand()产生一个在int范围内的随机数）

$Masou$ 没法知道seed和n的值，但在机器人每次调用init_rps()后，他可以偷偷调用judge()，并得到返回值。为了不被 $Ogi$ 发现，$Masou$ 只能调用函数至多10次(每轮)。调用完毕后，$Masou$ 将与机器人进行一次决胜负的猜拳。比赛将进行1000轮，每一轮机器人都会重新运行程序，改变seed。

$Masou$ 希望他的平均胜率能够达到95%以上，现在他请求你的帮忙。

#### 交互方式

比赛将进行1000轮。每一轮开始时，你可以输入"?"来调用一次judge()，机器人会输出0~2的数字表示返回值。当你做出决定后，输出"! {number}"表示你猜拳选择的手势（number: 石头=0，布=1，剪刀=2）。之后机器人自动进行下一轮。1000轮结束后，你应当直接退出程序，不进行多余的读写操作。若你的平均胜率大于等于95%，则该测试点会得到满分，否则得到0分。

注意你每轮只能调用至多10次函数。

本题有多个测试点，每一轮的n不变，但测试点间的n不一定相同。

**请不要忘记每次输出后刷新缓存区**。

#### 各语言刷新缓存区方式：

* C/C++：fflush(stdout)
* Java: System.out.flush()
* Python: stdout.flush()
* Pascal: flush(output)



一个样例程序（会WA但不会TLE）：

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    string temp;
    for(int T = 1; T <= 1000; ++T)
    {
        cout << "?" << endl;
        fflush(stdout);
        cin >> temp;
        cout << "! 0" << endl;
        fflush(stdout);
    }
    return 0;
}
```
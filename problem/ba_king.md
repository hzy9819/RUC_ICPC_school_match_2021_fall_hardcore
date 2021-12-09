## Ogi is <font color=pink>BABA</font> AND <font color=yellow>Win</font>

#### Problem description

​	**BABA is You**是一款风靡全球的益智游戏，$Ogi$吃完饭在实验室摸鱼时，总会与实验室的小伙伴玩两把。

​	现在共有$n$个关卡，$Ogi$与$m-1$个小伙伴一起玩（从$1 \sim m$编号，$Ogi$是$1$号），只有当前关卡通关才能进入下一关，不允许跳关。

​	其中，$i$号小伙伴解决第$j$关花费的时间，服从参数为$\lambda_{ij}$的指数分布，即，
$$
T_{ij} \sim Exp(\lambda_{ij}) \\ P\{T_{ij} \le x \}=\left\{\begin{array}{cc}
1-e^{-\lambda_{ij} x} & , x \geq 0 \\
0 & , x<0
\end{array}\right.
$$
​	每个小伙伴解决每一关的时间是相互独立的，且只要当前关卡被某一个小伙伴解决，大家会马上开始下一关，并且解决此关的小伙伴过题数**+1**（如果有多个小伙伴**同时**解决，则都**+1**）。

​	你能算出每个小伙伴过题数的期望吗？

#### Input

​	第一行两个整数$n, m$;

​	接下来$n$行，每行$m$个实数$\lambda_{ij}$.

​	$1 \le n,m \le 1000, 1 \le \lambda_{ij} \le 20$

#### Output

​	第一行，如果$Ogi$的期望过题数最多（或并列，精度3位小数），则输出"Ogi is BABA AND WIN!"，不然，输出"NOT Ogi is BABA AND WIN!"。

​	接下来$n$行，每行一个实数，即$i$号小伙伴的期望过题数（保留3位小数）。

#### Input Sample

```
2 2
11.4514 19.19810
19.19810 11.4514
```

#### Output Sample

```
Ogi is BABA AND WIN!
1.000
1.000
```




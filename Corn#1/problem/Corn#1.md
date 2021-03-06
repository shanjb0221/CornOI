@import "Corn.less"

# "CornOI"CUP #1

---

![Corn#1.jpg](https://s2.ax1x.com/2019/04/25/EeGpoq.jpg)

---

| 题目名称 |  排课表   | 玉米田  |    评测机     |
| :------: | :-------: | :-----: | :-----------: |
| 英文名称 | `arrange` | `corn`  | `onlinejudge` |
| 时间限制 |   `1s`    |  `1s`   |     `2s`      |
| 空间限制 |  `128MB`  | `128MB` |    `128MB`    |
| 测试点数 |   `20`    |  `10`   |     `20`      |
| 附加样例 |    有     |   无    |      有       |
|  出题人  |   `SJB`   |  `YSJ`  |     `FR`      |

---

## 友情提示

命题人提醒您：

- > **数据千万条，清空第一条**。
  > **多测不清空，爆零两行泪。**
- > **`int`一时爽，溢出火葬场。**
- > **代码千万条，`long long`第一条。**
  > **乘积存`int`，爆`0`两行泪。**

---

## T1 排课表

英文名称：`arrange.*`  
时间限制：`1s`  
空间限制：`128MB`  
测试点数：`20`  

### 题目背景

新学期伊始，作为玉米高中的教务主任$\text{W}$某，又要安排学生们的课程表了。

$\text{W}$某想要知道所有可能的排课表方案，于是他开始在纸上列举所有方案，然而在写满了一摞$\text{A4}$纸后，他发现可能的方案太多了——用尽玉米高中所有的$\text{A4}$纸都写不完。

$\text{W}$某最终放弃了列举所有方案的想法，但他对排课表的方案数产生了兴趣。他的组合数学不太好，所以他找到了正在玉米高中就读的你，请你帮帮$\text{TA}$。

### 题目描述

简单地说，玉米高中共有 $T$ 个班级。

对于其中一个班级 $i$，这个班级每天要上 $m_i$ 节**互不相同**的课，一共有 $n_i$ 节课可供选择，但这 $n_i$ 节课不能随便安排，其中也有一些限制：

- 有 $a_i$ 节课不能安排在第一节上
- 有 $b_i$ 节课不能安排在最后一节上
- 没有任何一节课既不能在第一节上又不能在最后一节上

你需要求出每个班级排课表的方案数除以 $998,244,353$ 的余数。

### 输入格式

从文件 `arrange.in` 中读入数据。

第`1`行包含一个正整数 $T$，表示玉米高中的班级数。

第`2`行到第`T+1`行，每行包含四个整数，第`i+1`行的四个整数 $n_i$，$m_i$，$a_i$，$b_i$，分别表示班级 $i$ 可选的课程数，一天的课程数，不能在第一节上的课程数，不能在最后一节上的课程数。

### 输出格式

向文件 `arrange.out` 中输出答案。

输出`T`行，第`i`行表示班级 $i$ 的排课表方案数除以 $998,244,353$ 的余数。

### 样例1

> #### 输入
>
> ```
> 1
> 3 2 0 1
> ```
>
> #### 输出
>
> ```
> 4
> ```

见下发文件夹中的`arrange1.in/out`

#### 解释

设`3`节可选的课为`a`,`b`,`c`，其中`c`不能排在最后一节

`4`种排课表的方案分别为:`ab`,`ba`,`ca`,`cb`

### 样例2

> #### 输入
>
>   ```
>   1
>   5 3 1 1
>   ```
>
> #### 输出
>
>   ```
>   39
>   ```

见下发文件夹中的 `arrange2.in/out`

### 样例3

见下发文件夹中的 `arrange3.in/out`

### 样例4

见下发文件夹中的 `arrange4.in/out`

### 数据规模

所有测试点满足：

- $1 \leq T \leq 10^4$
- $2 \leq m_i \leq n_i \leq 10^5$
- $a_i + b_i \leq n_i$

| 测试点编号 |    $n_i$    |   $T$   |
| :--------: | :---------: | :-----: |
|  `1 ~ 2`   |  $\leq 5$   |  $=1$   |
|  `3 ~ 6`   |  $\leq 10$  |  $=10$  |
|  `7 ~ 10`  |  $\leq 20$  | $=10^2$ |
| `10 ~ 14`  | $\leq 10^3$ | $=10^3$ |
| `15 ~ 20`  | $\leq 10^5$ | $=10^4$ |

在测试点`7 ~ 20`中：

- 存在`2`个测试点满足：$m_i=n_i$
- 存在`2`个测试点满足：$a_i=b_i=0$
- 存在`4`个测试点满足：$a_i=0$

---

## T2 玉米田

英文名称：`corn.*`  
时间限制：`1s`  
空间限制：`128MB`  
测试点数：`10`  

### 题目背景

玉米中学的学生社会实践的内容是去玉米田中种玉米。

### 题目描述


玉米中学有 $n$ 块**不同**的玉米田，这些玉米田编号从 $1$ 到 $n$，且第 $i$ 号玉米田与第 $i+1$ 号玉米田相邻，特殊地，第 $n$ 号玉米田与第 $1$ 号玉米田相邻。

现在玉米中学购置了 $k$ 种不同的玉米，为了美观，学校要求相邻的玉米田中不能种植同一种玉米，现在$\text{W}$某想要知道种植玉米的方案总数。

由于$\text{W}$某耐心有限，因此只需要你求出对 $20011021$ 取模后的结果即可。


### 输入格式

从文件 `corn.in` 中读入数据。

一行两个整数 $n$，$k$，表示玉米田的数量和玉米的种类数。

### 输出格式

向文件 `corn.out` 中输出答案。

一行一个整数，表示种植玉米的方案数对 $20011021$ 取模后的结果。

### 样例1

> #### 输入
>
>   ```
>   4 2
>   ```
>
> #### 输出
>
>   ```
>   2
>   ```

#### 解释

设`2`种玉米为`a`,`b`

`2`种种植玉米的方案为:`abab`,`baba`

### 样例2

> #### 输入
>
>   ```
>   4 3
>   ```
>
> #### 输出
>
>   ```
>   18
>   ```

### 数据规模

所有测试点满足: $n,k \leq 10^9$

| 编号  |     $n$     |     $k$     |
| :---: | :---------: | :---------: |
|  `1`  |  $\leq 5$   |    $=2$     |
|  `2`  |  $\leq 5$   |    $=3$     |
|  `3`  |  $\leq 5$   |  $\leq 5$   |
|  `4`  |  $\leq 5$   |  $\leq 5$   |
|  `5`  | $\leq 10^5$ |    $=2$     |
|  `6`  | $\leq 10^5$ |    $=3$     |
|  `7`  | $\leq 10^5$ | $\leq 10^5$ |
|  `8`  | $\leq 10^9$ |    $=3$     |
|  `9`  | $\leq 10^9$ | $\leq 10^9$ |
| `10`  | $\leq 10^9$ | $\leq 10^9$ |

---

## T3 评测机

英文名称：`onlinejudge.*`  
时间限制：`2s`  
空间限制：`128MB`  
测试点数：`20`  

### 题目背景

玉米高中的`Online Judge`终于抛弃了陪伴自己十年的评测机，换上了一大批新的玉米评测机。

### 题目描述

这些玉米的排列方式很奇怪，它们形成了一个树形结构。

每个玉米都有自己的性能。由于玉米是很简单的生物，所以它们的性能值也很简单：没有 $2$、$3$、$5$、$7$、$11$ 之外的质因子（也就是都可以表示为 $ 2^b \cdot 3^c \cdot 5^d \cdot 7^e \cdot 11^f \left( b,c,d,e,f \geq 0 \right)$ 的形式）。

当一些玉米启动时，总的性能值是每个玉米的性能值之积的约数和 $\text{mod} ~ 20020421$ 的值。

现在$\text{LS}$要进行一些测试：每次选定树上一条链上的玉米启动，求总性能值。


### 输入格式

从文件 `onlinejudge.in` 中读入数据。

第`1`行两个整数 $n$ 和 $m$：玉米个数和测试次数。

第`2`行 $n$ 个整数 $a_1 … a_n$：每个玉米的性能。

第`3`行到第`n+1`行，每行两个整数 $x$ 和 $y$，表示 $x$ 和 $y$ 之间有一条边。

第`n+2`行到第`n+m+1`行，每行两个整数 $x$ 和 $y$，表示询问启动树上 $x$ 到 $y$ 的链上所有玉米的总性能值。


### 输出格式

向文件 `onlinejudge.out` 中输出答案。

输出`m`行，第`i`行表示第 $i$ 个询问的答案。

### 样例1

> #### 输入
>
> ```
> 5 3
> 18 12 25 7 33
> 1 2
> 2 3
> 2 4
> 3 5
> 1 4
> 2 4
> 2 5
> ```
>
> #### 输出
>
> ```
> 4800
> 224
> 33852
> ```

见下发文件夹中的 `onlinejudge1.in/out`

#### 解释

$1$ 号到 $4$ 号经过的玉米为 $1$ 号、$2$ 号和 $4$ 号，它们的性能分别为 $18$、$12$、$7$，性能之积为 $18 \times 12 \times 7 = 1512$

$1512$ 的约数有：$1 , 2 , 3 , 4 , 6 , 7 , 8 , 9 , 12 , 14 , 18 , 21 , 24 , 27 , 28 , 36 , 42 , 54 , 56 , 63 , 72 , 84 , 108 , 126 , 168 , 189 , 216 , 252 , 378 , 504 , 756 , 1512$
它们的和为 $4800$，即：$1512$ 的约数和为 $4800$

$2$ 号到 $4$ 号经过的玉米为 $2$ 号和 $4$ 号，性能之积为 $12 \times 7 = 84$
容易得出 $84$ 的约数和为 $224$

$2$ 号到 $5$ 号经过的玉米为 $2$、$3$、$5$ 号，性能之积为 $12 \times 25 \times 33 = 9900$
~~容易~~得出 $9900$ 的约数和为 $33852$

### 样例2

见下发文件夹中的 `onlinejudge2.in/out`

此样例与测试点`8`规模、性质相同

### 样例3

见下发文件夹中的 `onlinejudge3.in/out`

此样例与测试点`14`规模、性质相同

### 数据规模

所有测试点满足：

- $n,m \leq 10^5$
- $a_i = 2^b \cdot 3^c \cdot 5^d \cdot 7^e \cdot 11^f \left( b,c,d,e,f \geq 0 \right)$
- $a_i \leq 10^9$

| 测试点编号 |    $n,m$    |    $a_i$    |
| :--------: | :---------: | :---------: |
|    `1`     |  $\leq 5$   |  $\leq 20$  |
|    `2`     |  $\leq 10$  | $\leq 10^2$ |
|  `3 ~ 8`   | $\leq 10^3$ |     —      |
|  `9 ~ 14`  |     —      |   $= 2^k$   |
| `15 ~ 20`  |     —      |     —      |

数据存在**一定**梯度，编号为奇数的测试点**数据随机**
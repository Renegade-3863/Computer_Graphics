### 仿射组合（注意：不是仿射变换！）
- 给出定义，满足如下形式：$$ \alpha P + \beta Q + \gamma R，\space 其中 \alpha + \beta + \gamma = 1$$ 的组合，就是**仿射组合**
- <u>仿射组合可以实现几何意义上的统一，不管选取的参考系如何变化。</u>这是一个很有意义的图形学结论，在后续很多次生结论的推导中都有用到
- 几何意义统一，简单理解：
    - 比如有两个点 $P$ 和 $Q$，那么 $$\frac{1}{2}P + \frac{1}{2}Q$$ 就总是线段 $PQ$ 的中点，而独立于 $P$ 和 $Q$ 具体的坐标。

#### 个人证明：
我们可以假设，对于同一个 $n$ 维坐标点 $P$，在两个不同的坐标系（互相之间可以通过仿射变换互相转化）下的坐标分别为 $p$ 和 $p'$

也就是说：$ p' = Ap+b $（这是仿射变换的定义）

同时，基于上面提到的运算，我们可以计算：$$ p = \sum_1^{n}a_ip_i$$，且有 $$\sum_1^{n}a_i = 1$$

于是有 $$ \begin{align*} p' &= Ap+b \\
                            &= A(\sum_1^{n}a_ip_i)+b \\
                            &= A(\alpha_1p_1 + \alpha_2p_2 + ... + \alpha_np_n) + b \\
                            &= \sum_1^{n}\alpha_i(Ap_i+b) \\
                            &= \sum_1^{n}\alpha_ip_i'\end{align*}$$

从上面的推导，我们可以发现，p' 可以表示成与 p 同样权重的各个维度参数之和

因此，p' 所在的参考坐标系中的多个向量，在这种权重和为 1 的限制条件下的线性组合，实际上表示的 **相对关系** 与 p 所在的参考坐标系中是完全一致的

#### 重要结论
- 基于上面的规律，我们可以给出基于两点确定一条直线的参数化表示形式（区分于后文的隐式表示方法）:

$$ \gamma: R \xrightarrow{} R^2: t \xrightarrow{} (1-t)P + tQ$$
- 注意到，以这种方式定义的参数化直线，在移动坐标系的时候，代表的点的实际几何位置总是固定的，这也是这种表示方法被广泛使用的关键原因

#### 推论公式：
- 对于公式：$$\begin{align*} \alpha P + \beta Q + \gamma R\end{align*}$$
    - 基于 $\alpha + \beta + \gamma = 1$，可以转换为：
    $$ P + \beta(Q-P) + \gamma(R-P)$$
    - 这个公式在后面包括三角形与直线（光线）求交的问题中有很大用处

#### 矩阵乘法
- 只要学过线代的，基本算法就不会陌生，这里主要提书上的几个小点：

$$ v \cdot w = v^Tw = w^Tv $$

- 同时，基于行向量和列向量，矩阵乘法可以有两种表示形式：
    - 设矩阵 $A$ 的行向量为 $a_i$，那么有：
        - 如果 $w = Av$，则结果有两种表示方法：
        1. $$ \begin{bmatrix} a_1v_1 \\ a_2v_2 \\ ... \\ a_nv_n \end{bmatrix}, \space 其中 \space a_i \space 是 A 的行向量$$
        2. $$ v_1b_1+v_2b_2+...+v_nb_n, 其中 \space b_i \space 是 A 的列向量 $$

#### 隐式直线定义（简单理解为：用点，而不是其它代表直线性质的参数来定义一条直线）

我们以 2D 空间为例先建立对直线隐式表述的基本认知
- 设 2D 空间中存在两个点 P 和 Q，坐标分别为 $(x_P, y_P)$ 和 $(x_Q, y_Q)$
- 上面的两个点在 2D 空间中可以唯一确定一条直线 $PQ$
    - 我们可以通过 2D 空间中的叉积来算出和直线 $PQ$ 垂直的直线的方向向量 $\overline{n} = \times(Q-P) = \begin{bmatrix} -(y_P-y_Q) \\ x_Q-x_P\end{bmatrix}$
    - 之后，我们假设同平面内有另一顶点 $X$，坐标为 $(x_X, y_X)$
    - 要判断 $X$ 是否在直线 $PQ$ 上，等价于判断下式是否成立：$$ (X-P) \cdot \overline{n} = 0$$
    - 这个就是 2D 空间中直线的隐式表述

### 从直线（光线）与平面求交 到 直线（光线）与三角形求交

首先来推导一下直线与平面求交的过程：

- 假设有一条起点为 $P$，方向向量为 $d$（直线的隐式表达为：$P+td, \space t \geq 0$）的光线
- 以及有一个经过点 Q，法向量为 $n$ 的平面：$$ (X-Q) \cdot n = 0$$
- 我们要求解的就是这个唯一的 t 值：
    - $$ \begin{align*} ((P+td)-Q)\cdot n &= 0 \\
                        (P-Q+td) \cdot n &= 0 \\
                        (P-Q)\cdot n + td \cdot n &= 0 \\
                        td \cdot n &= -(Q-P) \cdot n \\
                        t &= \frac{(Q-P)\cdot n}{d \cdot n}\end{align*}$$
    - 注意，上面的结果表达式，存在除以 0 的问题！！这种情况对应的是：**光线与平面平行**
#### 再谈谈光线与平面上的一个三角形区域的交问题

首先，思考一下，我们如何表示一个平面上的三角形？假设我们只知道它三个顶点的坐标？

- 假设我们有一个三角形 $\triangle ABC$，我们取其中 $AB$ 边上的任意一点 $Q = (1-t)A+tB, \space 其中 \space 0 \leq t \leq 1$
- 之后取 $CQ$ 上另一点 $R = (1-s)Q + sC，\space 其中 \space 0 \leq s \leq 1$
- 那么便有：$$ R = (1-s)(1-t)A + (1-s)tB + sC$$
    - 这便是三角形的一种参数化表示形式
- 另一个重要的观察是：这个表达式里面，A、B 和 C 项的系数之和为 1 ！
$$ \begin{align*} (1-s)(1-t)+(1-s)t+s &= (1-s)((1-t)+t)+s \\ &= (1-s)+s \\ &= 1\end{align*}$$
- 我们把这三个系数分别简化一下表示：
    - 令 $\alpha = (1-s)(1-t), \space \beta = (1-s)t, \gamma = s$
- 就得到了三角形 $ABC$ 的重心表示法：$$\alpha A+\beta B+\gamma C$$

- 最后，用几何方式，并不难证明：
    - $\frac{Area\triangle PBC}{Area\triangle ABC} = \alpha, \space \frac{Area\triangle PAC}{Area\triangle ABC} = \beta, \space \frac{Area\triangle PAB}{Area\triangle ABC} = \gamma$
    - 感兴趣的可以自行尝试证明，用一些简单的相似三角形规律即可证明，这里不具体展开

回到最开始的问题：如何判定一条光线 $(P+td)$ 与一个平面上的三角形是否相交？

可以分为两步进行：
- step1: 判断光线是否与三角形所在的面相交
- step2: 判断交点是否在三角形内部
- 第一步求解方法和上面提到的光线与平面相交的算法一致
- 主要来看看第二步：
    - 有一个结论是：
        - 假设 P 是三角形 ABC 所在平面上的一点，那么一定可以找到对应的参数，使得： $P = \alpha A + \beta B + \gamma C，并且 \alpha + \beta + \gamma = 1 $
        - 这个证明可以用代数法进行。不难做，有兴趣的可以尝试，使用 AB 和 AC 作为平面基向量即可完成证明
    - 基于上面结论，我们假设光线和平面 $ABC$ 存在交点 $Q$
    - 那么 $Q$ 一定可以表述为：
        - $Q = \alpha A + \beta B + \gamma C, \space 其中 \space \alpha + \beta + \gamma = 1$
    - 那么有：$ Q-A = \alpha(A-B) + \gamma(C-B)$
    - **两边同时乘 $AB$ 的垂直向量 $a$**：
        - $(Q-A)\cdot a = \gamma(C-B) \cdot a $
        - 于是有：$$\gamma = \frac{(Q-A) \cdot a}{(C-B) \cdot a}$$        
    - 对 $\beta$ 同理
    - 最后：$\alpha = 1-\beta-\gamma$

基本的 C++ 实现代码在 [ray_triangle_intersection.cc](ray_triangle_intersection.cc) 中


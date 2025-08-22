# 基础数学

> [!Tips]
> 基础数学，请务必学扎实
> 前置知识：**九年义务教育数学**，矩阵（线性代数部分, optional）

<!---仅仅是我的备忘录罢了，别指望我加别的东西进去-->

## 向量 / 矢量

### 定义

有向线段，与标量对应

二者基本可以画上等号（我也不知道有啥区别）

数学上的定义：一种有大小和方向（$n$ 维欧几里得空间 $\mathbb{R}^n$ ，不局限于 $2$ 维和 $3$ 维）的量
计算机科学里的定义：数据结构，可表示为数组或列表等： $\left[a_1,a_2,a_3,a_4,\ldots,a_n\right]$

事实上，两者是互通的，$n$ 维欧几里得空间里的向量可以看作一个 $n$ 个元素的数组，反之亦然。

### 表示

（此处指的都是二维向量）  
在书写时，通常使用数对 $(x,y)$（高中阶段） 或 $2\times 1$ 的矩阵 $\left[\begin{matrix}x\\y\end{matrix}\right]$ 表示。  
这边我选择使用矩阵表示。

由于其有数对表示法，可以看出向量在直角坐标系中可以使用坐标表示，起点为原点，终点为向量坐标所表示的点。

顺理成章地，我们可以得知向量能被分解为水平和竖直两个分量，即 $\left[\begin{matrix}x\\y\end{matrix}\right]=x\left[\begin{matrix}1\\0\end{matrix}\right]+y\left[\begin{matrix}0\\1\end{matrix}\right]$。

又因为向量是有方向的线段，所以将其起点放在极坐标原点，终点为向量坐标所表示的点，即 $\left[\begin{matrix}x\\y\end{matrix}\right]=r\left[\begin{matrix}\cos\theta\\\sin\theta\end{matrix}\right]$，其中 $\theta$ 被称作极角，即向量与水平轴的夹角。

### 相关概念

模长：向量所对应线段的长度  
极角：向量与水平轴的夹角  
分量：能合成目标向量的各个向量  
单位向量：模长为 $1$ 的向量  
水平分量：向量在水平方向上的分量  
竖直分量：向量在竖直方向上的分量  

### 运算法则

|                                 | 几何意义                             | 代数意义                 | 表达式                                                                                                                                                    | 结果 | 备注                                                                                                                                                                                                                                                                                                     |
| ------------------------------- | ------------------------------------ | ------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------- | ---- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 相反数 $-\vec{v}$               | 反向                                 | 各分量取相反数           | $-\left[\begin{matrix}x\\y\end{matrix}\right]=\left[\begin{matrix}-x\\-y\end{matrix}\right]$                                                              | 向量 |                                                                                                                                                                                                                                                                                                          |
| 加法 $\vec{v_1}+\vec{v_2}$      | 首尾相连                             | 分量相加                 | $\left[\begin{matrix}x_1\\y_1\end{matrix}\right]+\left[\begin{matrix}x_2\\y_2\end{matrix}\right]=\left[\begin{matrix}x_1+x_2\\y_1+y_2\end{matrix}\right]$ | 向量 |                                                                                                                                                                                                                                                                                                          |
| 减法 $\vec{v_1}-\vec{v_2}$      | 反向拼接                             | 分量相减                 | $\left[\begin{matrix}x_1\\y_1\end{matrix}\right]-\left[\begin{matrix}x_2\\y_2\end{matrix}\right]=\left[\begin{matrix}x_1-x_2\\y_1-y_2\end{matrix}\right]$ | 向量 | 相当与加上一个相反的向量                                                                                                                                                                                                                                                                                 |
| 点乘 $\vec{v_1}\cdot\vec{v_2}$  | 一个向量的投影与另一个向量的模长之积 | 分量交叉相乘再相加       | $\left[\begin{matrix}x_1\\y_1\end{matrix}\right]\cdot\left[\begin{matrix}x_2\\y_2\end{matrix}\right]=x_1x_2+y_1y_2$                                       | 标量 |                                                                                                                                                                                                                                                                                                          |
| 叉乘 $\vec{v_1}\times\vec{v_2}$ | 构成的平行四边形面积                 | 分量交叉相乘再相减       | $\left[\begin{matrix}x_1\\y_1\end{matrix}\right]\times\left[\begin{matrix}x_2\\y_2\end{matrix}\right]=x_1y_2-x_2y_1$                                      | 标量 | 由此可以求出矢量三角形的面积，即为$\frac{1}{2}\left(\vec{v_1}\times\vec{v_2}\right)=\dfrac{1}{2}\left\|\left[\begin{matrix}x_1\\y_1\end{matrix}\right]\times\left[\begin{matrix}x_2\\y_2\end{matrix}\right]\right\|=\dfrac{\left\|x_1y_2-x_2y_1\right\|}{2}$，某位不愿透露姓名的丁仲博老师的「禁术」得证 |
| 数乘 $k\cdot\vec{v}$            | 各分量乘以 k                         | 向量各分量乘以 k         | $k\cdot\left[\begin{matrix}x\\y\end{matrix}\right]=\left[\begin{matrix}kx\\ky\end{matrix}\right]$                                                         | 向量 |                                                                                                                                                                                                                                                                                                          |
| 模长 $\left\|\vec{v}\right\|$   | 对应线段的长度，起点和终点的距离     | 向量各分量平方和的平方根 | $\left\|\left[\begin{matrix}x\\y\end{matrix}\right]\right\|=\sqrt{x^2+y^2}$                                                                               | 标量 |                                                                                                                                                                                                                                                                                                          |

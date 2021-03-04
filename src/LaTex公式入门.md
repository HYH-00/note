# LaTex公式入门

## 行内公式

```
$ f(x)=f(x-1)+f(x-2) $
```

$f(x)=f(x-1)+f(x-2)$

## 行间公式

```
$$
	f(x)=f(x-1)+f(x-2)
$$
```

$$
f(x)=f(x-1)+f(x-2)
$$

## 编号

```
$$
	f(x)=f(x-1)+f(x-2) \tag{1.1}
$$
```


$$
f(x)=f(x-1)+f(x-2) \tag{1.1}
$$

## 运算符号

```
+  +
-  -
*  *
/  /
=  =
·  \cdot
不等号  \neq
恒等  \equiv
取模  \bmod
```

$$
+
-
*
/
=
\cdot
\neq
\equiv
\bmod
$$

## 上下标

```
上标 ^ （内容不止一个需要用大括号）
下标 _ （内容不止一个需要用大括号）
求导 'a+b
```

$$
x^{a+b}x_{a+b}x'x''x'''x'''_{a+b}x_{2}^{3}
$$

## 根号、分式

```
平方根 \sqrt
次方根 \sqrt[n]
分式 \frac
```

$$
\sqrt{78}
\sqrt[3]{78}
\sqrt[7]{78}
\frac{a+b}{x+y}
$$

## 上下标记

```
上横线 \overline
下横线 \underline
上括号 \overbrace
下括号 \underbrace
```

$$
\overline{x+y-z}
\underline{x+y-z}
\overbrace{x+y-z}
\underbrace{x+y-z}
$$

## 向量

```
向量 \vec
箭头向右 \overrightarrow
箭头向左 \overleftarrow
```

$$
\vec{x}\overrightarrow{y}\overleftarrow{z}
$$

## 积分、极限、求和、乘积

```
积分 \int
极限 \lim
求和 \sum
乘积 \prod
上限 ^
下限 _
```

$$
\lim_{x \to \infty} x^2_{22} - \int_{1}^{5}x\mathrm{d}x + \sum_{n=1}^{20} n^{2} = \prod_{j=1}^{3} y_{j}  + \lim_{x \to -2} \frac{x-2}{x} 
$$

## 矩阵

&用于分隔列\用于分隔行

```
matrix
bmatrix
vmatrix
pmatrix
```

$$
\begin{matrix}
a & b \\
c & d \\
\end{matrix}
\begin{bmatrix}
a & b \\
c & d \\
\end{bmatrix}
\begin{vmatrix}
a & b \\
c & d \\
\end{vmatrix}
\begin{pmatrix}
a & b \\
c & d \\
\end{pmatrix}
$$


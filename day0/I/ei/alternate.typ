*多元 Lagrarge 反演公式*: 记 $bold(X) = X_1,dots,X_r$. 对于 $H in R ((bold(X)))$, $G_i in R [| bold(X) |]$, 如果对任意 $i$ 有 $G_i(0) in R^times$, 可以对于 $bold(F) =(F_1,dots,F_r)$ 递归定义 $F_i = X_i G_i(bold(F))$, 满足 Lagrarge 反演公式
$ [bold(X)^(bold(k))]H(bold(F)) = [bold(X)^(bold(k))] H dot.c bold(G)^(bold(k)) dot.c || delta_(i j) - (X_j)/(G_i(bold(X))) (diff G_i(bold(X)))/(diff X_j) ||, $
其中 $bold(X)^(bold(k)) = X_1^(k_1) dots.c X_r^(k_r)$.

现在我们考虑用 $X$ 计量白点, $Y$ 计量黑点的指数型生成函数. $W(X,Y)$ 表示白点为根的树, $B(X,Y)$ 表示黑点为根的树. 因为限制是 "黑点只能连向白点", 我们可以得到递推式
$ cases(
    W = X exp (W + B),
    B = Y exp W.
) $
所以根据 Lagrange 反演公式, 我们有
$ [X^n Y^m] H(W,B) &= [X^n Y^m] H(X,Y) e^(n (X+Y)) e^(m X) det mat(
    1 - X, -Y;
    -X, 1;
)\
&= [X^n Y^m] H(X,Y) e^((n+m) X + n Y) (1-X-X Y). $

而 $H = exp C$, $C$ 是一个环的情况, 我们首先计算不考虑奇偶的方案, 记为 $C_0$, 环的基本单元是 $B W$ 和 $W$, 所以
$ C_0 = log 1/(1-B W - W), $
那么 $C$ 是去掉 $B, W$ 均出现了奇数次的情况, 有
$ C(W,B) &= C_0 - 1/4 sum_(i,j=0)^1 (-1)^(i+j) C_0((-1)^i B, (-1)^j W) \
&= log 1/(1-B W - W) - 1/4 log ((1+ B W)^2-W^2)/((1-B W)^2-W^2),\
H(X,Y) &= exp C(X,Y) \
&= 1/(1-X Y - X) ( ((1-X Y)^2-X^2)/((1+X Y)^2-X^2) )^(1/4), $
所以我们有
$ "ans" = n!m![X^n Y^m]( ((1-X Y)^2-X^2)/((1+X Y)^2-X^2) )^(1/4) e^((n+m)X+n Y). $
设
$ a_n(Y) = [X^n] H(X,Y), $
根据方程
$ (1-2(1+Y^2)X^2+(1-Y^2)^2X^4) dot.c X (diff H)/(diff X) = - X Y (1 + X^2 (1-Y^2)) dot.c H, $
可以得到递推式
$ n a_n = -Y a_(n-1) + 2(n-2)(1+Y^2)a_(n-2) - Y(1-Y^2) a_(n-3) - (n-4)(1-Y^2)^2a_(n-4), $
由于我们要任意模数, 令 $a_n = b_n/(n!)$, 得到
$ b_n = &-Y b_(n-1) \
&+ 2(n-1)(n-2)(1+Y^2)b_(n-2) \
&- (n-1)(n-2) Y(1-Y^2) b_(n-3) \
&- (n-1)(n-2)(n-3)(n-4)(1-Y^2)^2b_(n-4). $

额外的 _comments_: 如果是模类似 998244353 状物, 由于 $( ((1-X Y)^2-X^2)/((1+X Y)^2-X^2) )^(1/4) e^((n+m)X+n Y)$ 是整式递推的, 我们其实可以在 $O(sqrt(n)log n+ sqrt(m)log m)$ 的时间内求出答案.

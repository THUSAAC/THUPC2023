{{ self.title() }}

{{ s('background') }}

葡萄藤上开不出百合花。

{{ s('description') }}

你落在一个巨大的葡萄架上，上面一共有$2^k$朵百合花（从$0$到$2^k-1$编号）和$m$条葡萄藤。你可以花费$c_i$的时间走过一条葡萄藤，还可以通过花费$a_k$的时间从$x$闪现到$y$，你只需要保证$x$和$y$的二进制表示下有$k$位不相同，问$s$出发到所有点的最短时间。葡萄藤可双向通行。

{{ s('input format') }}

{{ self.input_file() }}

第一行包含三个正整数 $k,m,s$，其含义如题目描述。

第二行包含 $k$ 个非负整数 $a_i$，表示通道花费的时间。

第 $3$ 至第 $(m+2)$ 行每行三个非负整数 $x_i,y_i,ci$。

保证 $k \leq 17,m \leq 2\times10^5, 0 \leq s,x_i,y_i \leq 2^k-1, a_i, c_i \leq 2^{30}-1$。

{{ s('output format') }}

{{ self.output_file() }}

输出一行$n$个数表示最短时间

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}

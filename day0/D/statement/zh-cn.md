{{ self.title() }}

{{ s('background') }}

各位亲爱的《La Lumière: Scarlet Intense Flame - Adventurous Scarlet -》玩家：

非常荣幸能与您携手度过了这四年的美好时光，衷心感谢大家的支持与陪伴！

现在，我们非常遗憾的宣布，《La Lumière: Scarlet Intense Flame - Adventurous Scarlet -》将于 2023 年 5 月 28 日 15:00 停止运营服务。

停止运营相关时间表如下：

……

{{ s('description') }}

在关服前，运营发起了一系列投票，调查哪些游戏内容给玩家带来了更深的印象。

作为系列的忠实玩家，你想知道有多少人参加了关服前的投票，但是运营只公开了最终的投票结果：对于一项包含 $N$ 个选项的投票，选择第 $i$ 个选项的玩家比例为 $P_i$（$1\le i\le N$）。运营在公布结果时进行了四舍五入，所有的 $P_i$ 仅保留到小数点后第 $L$ 位。假设实际有 $K$ 位玩家参加了投票，其中有 $D_i$ 位玩家选择了第 $i$ 个选项，则应该有

$$
P_i-\frac{1}{2}\times 10^{-L}\le\frac{D_i}{K}< P_i+\frac{1}{2}\times 10^{-L}
$$

显然，所有的 $D_i$ 必须是非负整数，而 $K=\sum_{i=1}^N D_i$ 则必须是正整数。现在，给定 $N$ 和 $P_i$，请你求出满足 $D_i$ 有非负整数解的最小的总投票数 $K$。

{{ s('input format') }}

{{ self.input_file() }}

输入的第一行包含一个正整数 $N$，表示投票的选项总数。保证 $1\le N\le 100$。

接下来 $N$ 行，每行包括一个 $[0, 1]$ 中的实数 $P_i$，表示选择第 $i$ 个选项的玩家比例。保证 $\sum_{i=1}^N P_i =1$，所有 $P_i$ 均保留到小数点后第 $L$ 位，且 $1\le L\le 6$。

{{ s('output format') }}

{{ self.output_file() }}

输出一个正整数，表示满足要求的最小总投票数 $K$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

最小的总投票数为 $6$，对应每个选项的投票数为 $1, 2, 3$。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

最小的总投票数为 $73$，对应每个选项的投票数为 $3, 8, 8, 12, 22, 5, 15$。

{{ s('sample', 3) }}

{{ self.sample_file() }}

{{ self.title_sample_description() }}

最小的总投票数为 $7766$，对应每个选项的投票数为 $12, 301, 123, 403, 629, 530, 1216, 808, 205, 1113, 1005, 1206, 215$。

{{ s('subtasks') }}

对于 $100\%$  的数据，保证 $1\le N\le 100, 0\le P_i\le 1$，$\sum_{i=1}^N P_i=1$，且 $P_i$ 最多统一保留到小数点后 $6$ 位。
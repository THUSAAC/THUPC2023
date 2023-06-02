{{ self.title() }}

{{ s('background') }}

_没有人听懂的傻话_

_还记得吗_

_写满青春的围墙_

_好努力练习的倔强_

_浅浅伤疤_

_勇敢是我们的翅膀_

_——张韶涵《还记得吗》_

{{ s('description') }}

故事的世界观大概是这样的。这个世界的人分为三类，根据其某种特点被直接命名为 Weak，Average 和 Strong。你可以理解为这是一个关于种族或者职业的分类。

两个队伍之间发生了一场回合制战斗。你知道双方做了什么，现在希望你把所有的细节还原出来。

下面是本题的一些技术细节。

{{ s('人物') }}

一个人有以下几种属性值：「种族」、「等级」、「体力上限」、「基础攻击指数」、「基础防御指数」、「主动技能等级」、「被动技能等级」。其中「体力上限」、「基础攻击指数」、「基础防御指数」完全由「种族」和「等级」决定。但是为了输入方便，本题中所有信息都会给出。在战斗中，每个人有一个「体力值」。在战斗开始时，「体力值」等于「体力上限」。当「体力值」小于等于 $0$ 时这个人就会「倒下」。对于同一个「种族」而言，「体力上限」、「基础攻击指数」、「基础防御指数」大致随「等级」指数增长。每个人持有一把「武器」。「武器」的细节在下一节给出。

{{ s('武器') }}

「武器」的属性只有两种：「武器类型」和「武器攻击力」。所有「武器」都有「普通攻击」和「特殊攻击」两种攻击方式。发起「攻击」指使用这两种方式中的任意一种。「普通攻击」的效果与「武器类型」无关，但不同的「武器类型」有着不同的「特殊攻击」效果。「武器」有三种类型，分别叫做「B」、「G」、「M」。

{{ s('战场与队伍') }}

交战双方的每一方包含不超过 $6$ 名队员，一字排开，从西到东的编号分别为 $5,3,1,2,4,6$（若不足 $6$ 名则删去较大的若干个编号）。方便起见，就叫两队为「南队」和「北队」。

{{ s('回合') }}

每个「回合」中，只有一个人可以「行动」。第奇数个「回合」是「南队」的队员「行动」，第偶数个「回合」是「北队」的队员「行动」。第一个「回合」和第二个「回合」中，「行动」的人是队伍里未「倒下」的编号最小的人。之后的「回合」中，若本队中没有编号比本队上一个「行动」的人大且未「倒下」的人，则由本队中编号最小的未「倒下」的人「行动」。否则由编号大于本队上一个「行动」者的人中，编号最小且未「倒下」的人「行动」。若一个队伍中的所有队员均已「倒下」，则判另一个队伍「胜利」。

{{ s('行动') }}

「行动」一共有三种。当前「回合」中「行动」的人必须选择三种之一来完成。

1. 「普通攻击」；
2. 「特殊攻击」；
3. 「主动技能」。

这些「行动」的效果会在之后介绍。「特殊攻击」和「主动技能」是有次数限制的，但是在本题中，保证所有「行动」均合法，所以你不需要考虑这个限制。

{{ s('伤害计算') }}

「伤害」指的是因为「普通攻击」或「特殊攻击」而造成的「体力值」减少。

「伤害」，即「体力值」减少的量，由「攻击强度」和受到「伤害」的人的「防御指数」决定。

一个人的「防御指数」等于这个人的「基础防御指数」乘以队伍的「防御加成」。

具体地，若一个人受到「攻击强度」为 $x$ 的「伤害」，那么这个人的「体力值」就会减少 $y$。其中 $y$ 的值等于 $x$ 除以这个人的「防御指数」下取整。

「攻击强度」等于「基础攻击强度」乘以发起「攻击」的人的「技能加成」乘以队伍的「攻击加成」乘以「种族克制加成」乘以「方位加成」。这些概念会在之后介绍。

{{ s('普通攻击') }}

选择一个敌方未「倒下」的队员作为「目标」。「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」的「伤害」。

{{ s('特殊攻击') }}

选择一个敌方未「倒下」的队员作为「目标」。

「武器」有三种，不同「武器类型」的「特殊攻击」效果如下：

- 「B」：「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $125\%$ 的「伤害」。
- 「G」：「目标」和「目标」东西两侧与「目标」距离最近的各一名未「倒下」的队员（如果存在）均受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $x\%$ 的「伤害」。其中 $x$ 的值等于 $135$ 除以将要受到「伤害」的人数。「伤害」按照「目标」、「目标」西侧、「目标」东侧的顺序计算。注意如果过程中有人「倒下」，那么这个人的「被动技能」将不再对该顺序中位于这个人之后的人的「伤害」结算起作用。特别地，所有「伤害」的「方位加成」以「目标」的「躲闪方位」来计算。
- 「M」：「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $115\%$ 的「伤害」。「目标」东西两侧与「目标」距离最近的各一名未「倒下」的队员（如果存在）分别受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $23\%$ 的「伤害」。「伤害」按照「目标」、「目标」西侧、「目标」东侧的顺序计算。注意如果过程中有人「倒下」，那么这个人的「被动技能」将不再对该顺序中位于这个人之后的人的「伤害」结算起作用。特别地，所有「伤害」的「方位加成」以「目标」的「躲闪方位」来计算。

{{ s('技能') }}

「技能」分为「主动技能」和「被动技能」。每个「种族」的人都有一个「主动技能」和一个「被动技能」。「技能」的效果因「种族」和「技能等级」的不同而不同。「技能等级」为一个 $0$ 到 $5$ 之间的整数。「技能等级」为 $0$ 表示没有该「技能」。

使用「主动技能」需要选择一个人作为「技能目标」。

「主动技能」描述如下：（$1$ 到 $5$ 级的「技能」效果由斜杠隔开，保证使用「主动技能」的人的「主动技能等级」不为 $0$）

- 「Weak 种族」：使本队一名未「倒下」的队员的「体力值」增加这名队员的「体力上限」乘以 $10\%/12\%/15\%/17\%/20\%$ 下取整。
- 「Average 种族」：选择一名敌方未「倒下」的队员，在使用该「主动技能」这一队的「回合」结束时，其「体力值」减去其「体力上限」的 $6\%/7\%/8\%/9\%/10\%$ 下取整。该效果持续 $3$ 个回合，即会触发 $3$ 次。若该队员已有同类型（可以是不同等级）的「技能」施加的效果，那么这个效果将会覆盖之前的效果。
- 「Strong 种族」：使本队一名未「倒下」的队员的「技能加成」变为 $2.1/2.17/2.24/2.32/2.4$。

一名队员的「被动技能」只有当该队员未「倒下」时才能发挥效果，「倒下」之后不再发挥效果。

「被动技能」描述如下：

- 「Weak 种族」：在本队的「回合」开始时，本队所有未「倒下」的成员的「体力值」增加该成员「体力上限」的 $1.3\%/1.6\%/1.9\%/2.2\%/2.5\%$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $5\%$。超过 $5\%$ 按照 $5\%$ 计算。「体力值」增加的量在效果叠加后需要下取整。
- 「Average 种族」：队伍的「防御加成」初始为 $1$。该技能使队伍的「防御加成」增加 $0.01/0.02/0.03/0.04/0.05$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $0.1$。超过 $0.1$ 按照 $0.1$ 计算。
- 「Strong 种族」：队伍的「攻击加成」初始为 $1$。该技能使队伍的「攻击加成」增加 $0.01/0.02/0.03/0.04/0.05$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $0.1$。超过 $0.1$ 按照 $0.1$ 计算。

一名队员的「体力值」增加时，不能超过这名队员的「体力上限」。若增加后的「体力值」超过了「体力上限」，则把这次增加「体力值」的效果改为将这名队员的「体力值」变成这名队员的「体力上限」。

{{ s('技能加成') }}

战斗开始时，所有人的「技能加成」都是 $1$。只有两种方式能够改变「技能加成」：

- 「Strong 种族」的「主动技能」。见「技能」的描述。
- 当一个人发起「攻击」且计算完这次「攻击」的所有「伤害」之后，这个人的「技能加成」变为 $1$。

{{ s('种族克制加成') }}

「种族克制加成」与发起「攻击」的人的「种族」以及受到「伤害」的人的「种族」有关。「种族克制加成」的值如下表：

{{ tbl('type') }}

{{ s('方位加成') }}

在「攻击」时，发起「攻击」的一方有一个「攻击方位」，「攻击」的「目标」有一个「躲闪方位」。「攻击方位」和「躲闪方位」分别为一个 $1$ 到 $6$ 之间的整数。当「攻击方位」为 $a$，「躲闪方位」为 $d$ 时，「方位加成」的值由下表所示：

{{ tbl('pos') }}

{{ s('input format') }}

{{ self.input_file() }}

第一行两个正整数 $n,m$，分别表示「南队」的人数和「北队」的人数。

接下来 $n$ 行，其中第 $i$ 行表示「南队」中编号为 $i$ 的队员的信息，格式如下：

`<Type> Lv=<Lv> maxhp=<maxhp> atk=<atk> def=<def> skillLv=<skillLv> passivesklLv=<passivesklLv> <weapontype> weaponatk=<weaponatk>`

其中尖括号中的内容表示一个变量。

`<Type>` 为 `Weak`，`Average`，`Strong` 中的一种，分别表示对应名称的「种族」。

`<Lv>` 为一个 $1$ 到 $100$ 之间的整数，表示队员的「等级」。

`<maxhp>` 为一个整数，表示队员的「体力上限」。

`<atk>` 为一个实数，表示队员的「基础攻击指数」。

`<def>` 为一个实数，表示队员的「基础防御指数」。

`<skillLv>` 为一个 $0$ 到 $5$ 之间的整数，表示队员的「主动技能等级」。

`<passivesklLv>` 为一个 $0$ 到 $5$ 之间的整数，表示队员的「被动技能等级」。

`<weapontype>` 为 `B`，`G`，`M` 中的一种，分别表示对应名称的「武器类型」。

`<weaponatk>` 为一个实数，表示队员的「武器攻击力」。

接下来 $m$ 行，其中第 $i$ 行表示「北队」中编号为 $i$ 的队员的信息，格式与「南队」相同。

接下来一行一个正整数 $T$，表示进行的「回合」数。

接下来 $T$ 行，其中第 $i$ 行表示第 $i$ 个「回合」的「行动」。

「行动」的描述以一个字符串开头，表示「行动」的类型。

`Basicattack target=<target> atkpos=<atkpos> ddgpos=<ddgpos>` 表示一次「普通攻击」。

`Specialattack target=<target> atkpos=<atkpos> ddgpos=<ddgpos>` 表示一次「特殊攻击」。

`Skill target=<target>` 表示使用 「主动技能」。保证该队员的「技能等级」不是 $0$。

其中，`<target>` 表示「目标」或「技能目标」的编号。若是「Weak 种族」或「Strong 种族」的「主动技能」，这个编号是一个己方队员的编号，否则是一个敌方队员的编号。

`<atkpos>` 为一个 $1$ 到 $6$ 之间的整数，表示「攻击方位」。

`<ddgpos>` 为一个 $1$ 到 $6$ 之间的整数，表示「躲闪方位」。

保证所有的「行动」均合法。

为了方便起见，本题中实数的表示方法较为特殊。具体的表示方法是，用 `<mag>e<exp>` 的方式来表示 `<mag>` 乘以 $10$ 的 `<exp>` 次方。其中 `<mag>` 是一个 $1$ 到 $99999$ 之间的正整数，`<exp>` 是一个 $-6$ 到 $0$ 之间的整数。如 $42.195$ 可以表示成 `42195e-3`，$6$ 可以表示成 `6e0` 或 `600e-2` 等，$0.04$ 可以表示成 `4e-2` 等。

{{ s('output format') }}

{{ self.output_file() }}

对于每个「回合」，按时间顺序把这个「回合」的信息输出来。

信息的格式如下：

`<team> <id> recovered +<heal> hp -> <curhp>/<maxhp>` 表示「Weak 种族」的「技能」所造成的「体力值」增加。如果在增加之前「体力值」就已经等于「体力上限」，那么不需要输出这一行。

`<team> <id> took <dmg> damage from <atkteam> <atkid> -> <curhp>/<maxhp>` 表示一名队员受到「伤害」。

`<team> <id> took <dmg> damage from skill -> <curhp>/<maxhp>` 表示「Average 种族」的「主动技能」所造成的「体力值」减少。

`<team> <id> applied <type> skill to <targetteam> <targetid>` 表示使用「主动技能」。

其中 `<team>` 表示队伍名称，为 `South` 或 `North` 之一。

`<id>` 表示「体力值」发生改变的人在队伍中的编号，为一个 $1$ 到 $6$ 之间的正整数。

`<heal>` 表示本应该增加的「体力值」数量（不考虑「体力上限」的限制），为一个正整数。

`<curhp>` 指的是「体力值」发生改变之后的「体力值」，为一个非负整数。若「体力值」减小到 $0$ 以下输出 $0$。

`<maxhp>` 表示「体力值」发生改变的人的「体力上限」，为一个正整数。

`<dmg>` 为受到的「伤害」或「Average 种族」的「主动技能」所造成的「体力值」减少，为一个非负整数。

`<type>` 为使用「主动技能」的人的「种族」，为 `Weak`，`Average`，`Strong` 之一。

`<atkteam>` 和 `<atkid>` 为发起「攻击」的人的队伍名称和编号，格式同 `<team>` 和 `<id>`。

`<targetteam>` 和 `<targetid>` 为「技能目标」的队伍名称和编号，格式同 `<team>` 和 `<id>`。

时间顺序如下：

「回合」开始时，可能触发「Weak 种族」的「被动技能」效果，按照编号从小到大输出。

如果是使用「主动技能」，则输出一行使用「主动技能」的信息。

然后输出「行动」所造成的「体力值」变化信息。若「伤害」为 $0$ 也要输出。若没有造成「伤害」则不输出。若「特殊攻击」改变了多个人的「体力值」，则按照「目标」、「目标」西边的人、「目标」东边的人的顺序输出。

「回合」结束时，可能出发「Average 种族」的「主动技能」效果，按照编号从小到大输出。

每个「回合」结束后输出两队的「体力值」信息，格式如下：

`<team>: [<curhp5>/<maxhp5>] [<curhp3>/<maxhp3>] <curhp1>/<maxhp1> [<curhp2>/<maxhp2>] [<curhp4>/<maxhp4>] [<curhp6>/<maxhp6>]`

其中，`<team>` 表示队伍名称，`<curhpi>` 表示队伍中编号为 $i$ 的人的「体力值」，`<maxhpi>` 表示队伍中编号为 $i$ 的人的「体力上限」。两个人的「体力值」信息之间有恰好一个空格，第一个「体力值」信息和冒号之间有恰好一个空格。已「倒下」的人的「体力值」信息也需要输出。方括号表示，若队伍中不存在编号为 $i$ 的人则不输出。注意这里按照位置顺序而不是编号顺序输出，即顺序为 $5,3,1,2,4,6$。

先输出一行「北队」的信息，再输出一行「南队」的信息。

每个「回合」的信息以一个空行结束。

所有「回合」结束后，若有一个队伍「胜利」，则输出一行 `Team <team> won.`。其中 `<team>` 是队伍名称，为 `South` 或 `North`。因为「行动」需要指定一个未「倒下」的人作为「目标」或「技能目标」，且所有「行动」均合法，所以，如果有队伍「胜利」，则一定是在最后一个「回合」结束后才「胜利」。若没有队伍「胜利」则不输出。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ s('sample', 2) }}

{{ self.sample_file() }}

{{ self.title_sample_description() }}

这个样例，无疑是善良的出题人无私的馈赠。中间忘了。出题人相信，这个美妙的样例，可以给拼搏于 AC 这道题的逐梦之路上的你，提供一个有力的援助。

{{ s('subtasks') }}

保证 $1\le n,m \le 6$。

保证 $1\le T \le 50000$。

保证「武器攻击力」的范围在 $300$ 到 $80000$ 之间。

「体力上限」「基础攻击指数」「基础防御指数」的范围见下表。

{{ tbl('status') }}

{{ s('后记') }}

_有一天我将会老去_

_希望你会觉得满意_

_我没有 对不起那个_

_十五岁的自己_

_——刘若英《继续-给十五岁的自己》_
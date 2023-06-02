for ((i=41;i<=49;++i)) do
    ./gen > $i.in
    ./std3 < $i.in > $i.ans
    ./stdcount < $i.in > $i.out
done
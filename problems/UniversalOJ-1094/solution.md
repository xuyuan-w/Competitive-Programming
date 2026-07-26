# 【UNR #10】麦田

Statement:
- <https://uoj.ac/problem/1094>
- <https://vjudge.net/problem/UniversalOJ-1094>

Submission:
- <https://uoj.ac/submission/860137>

Code:
- [Code](main.cpp)

This is an easy problem. $a_i$ can only be changed into one value and if and only if $l\le L_i$ and $R_i\le r$, where $L$ and $R$ can be calculated by finding the longest strictly decreasing subarray on each side of $i$. Then the problem can be solved using a binary indexed tree.

Bonus: This problem can be solved in $O(n)$.
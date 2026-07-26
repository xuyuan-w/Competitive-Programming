# [NOISG 2023 Finals] Curtains

Problem Links:
- <https://qoj.ac/problem/6393>
- <https://www.luogu.com.cn/problem/P11537>

Submission Link:
- <https://qoj.ac/submission/2599553>

Code:
- [Code](main.cpp)

Scan on the right position of queries and segments. Simply use a lazy segment tree can solve this problem. Amazingly, since the right vertex of the segment is increasing, the tags are already able to merge without further thinking.

Any other $O(n\log)$ solution without this observation? Divide and conqueer should work but it is $O(n\log^2)$.
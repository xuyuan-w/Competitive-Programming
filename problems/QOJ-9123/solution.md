# The 3rd Universal Cup. Stage 4: Hongō Problem K - Kth Sum

Statement:
- <https://qoj.ac/problem/9123>
- [PDF](statement.pdf)

Submission:
- <https://qoj.ac/submission/2603472>

If $n$ or $k$ was smaller, there are two ways to solve this problem. One way is to use a priority queue to get the smallest $k$ sums in $O(k\log)$, the other way is to binary search the answer of the problem and use iterate over which element is chosen in $a$, and use two pointers to count the ways to choose elements in $b$ and $c$, total complexity is $O(n^2\log)$. We can combine these two algorithms. We still use the second algorithm, but we first calculate smallest $B$ sums when we choose one element from only $b$ and $c$. Inside the `check` function of binary search, when the number of ways to choose element in $b$ and $c$ is smaller than $B$, we can just do another binary search on the $B$ elements we stored previously. Total complexity is $O(B\log+(n\frac kB+n\log)\log)$, and if we choose $B=\Theta(\sqrt{nk})$, time complexity will be $O(\sqrt{nk}\log+n\log^2)$, which is fast enough to pass this problem.

Sometimes look at the partial points will indeed help a lot in solving a problem. Always try to think of more than one way to solve a problem and see if combining them could end up with a faster solution.
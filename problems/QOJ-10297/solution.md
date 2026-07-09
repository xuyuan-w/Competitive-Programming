# [NOISG 2025 Finals] Flooding

Statement Links:
- <https://qoj.ac/contest/1977/problem/10297>
- <https://www.luogu.com.cn/problem/P12019>

Submission Link:
- <https://qoj.ac/submission/2599611>

The problem is broken into two parts. Part one is to find all rectangles that might contribute to the answer, and part two is to find the smallest rectangle covering each cell. For the first part iterate over the bottom line of the rectangle, and build a cartesian tree based on how many continuous black grids going up from each column of the bottom line. Then the bottom line of a rectangle that might contribute to the answer must be on one of the segments on the cartesian tree. For the second part, since $n\le 5000$, you have to find a effecient way to do rectangle `checkmin`. This can be easily done when there's only one dimension using either a sparse table or a DSU. By combining these two you can solve the problem in $O(n^2\log n)$.

Part two is very clever to think of combining two algorithms which one is $O(n\log+q)$ and the other one is $O(n+q\log)$. However, the bottleneck of the algorithm is in the second part. Are there other ways to solve part two?

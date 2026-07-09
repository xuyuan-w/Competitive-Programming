# [NOISG 2023 Finals] Toxic Gene

Problem Links:
- <https://qoj.ac/problem/6393>
- <https://www.luogu.com.cn/problem/P11537>

Submission Link:
- <https://qoj.ac/submission/2599553>

We can make the number of queries used in the process of binary search less by dividing the sequence into some small blocks first, since we have many target elements and they are posited randomly in the sequence. Also we can merge some queries that have different purposes, like we can merge queries for checking whether there is any T and queries for distinguishing R and S together.  

Try to prove the correctness of the algorithm, that is, the number of queries have a very low possibility to go beyond 150.

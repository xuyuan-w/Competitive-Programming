# 【UNR #10】分披萨

Statement:
- <https://uoj.ac/problem/1095>
- <https://vjudge.net/problem/UniversalOJ-1095>

Submission Link:
- Partial: <https://uoj.ac/submission/860960>
- Full: <https://uoj.ac/submission/863989>

Code:
- [Partial version](partial.cpp)
- [Full version](main.cpp)

Note that if we let $c$ equal to the satisfaction of each customer, then one sequence cannot have more than one $c$.

## Partial version

$a_i=0$.

Try to do this problem with a simple DP on DP. First of all iterate over $c$. The first DP is to check whether a sequence satisfy the condition or not. We now have $kc$ statuses $(x,y)$, each of them $0$ or $1$, indicating if it is possible to arrange colors for the first $i$ positions, exacatly $x$ customer is satisfied and the last customer has excatly $y$ colors. Note that status $(x,c)$ is identical with status $(x+1,0)$.

Represent status $(x,y)$ with $z=cx+y$. Notice that all statuses $z$ which equal to $1$ can form a range. Therefore, all those $2^{kc}$ statuses can be simplified to a range. This is enough to solve the problem in $O(n^4)$. By breaking the constraints of $l$ and $r$, we can calculate them separately, ends up solving this alt version in $O(n^3)$.

Actually this version has a $O(n\log^2n)$ solution using GF.

## Full version

We skip the proofs, and this solution can probably be proved using my solution of the partial version.

Also, iterate over $c$ first. The very first thing you have to know is that for a determined array, let $p_i$ equals to the right bound of the $i$-th segment, then we have $p_i\in[l_i,r_i]$. So the answer equals to $\sum[n\in[l_k,r_k]]=\sum[l_k\le n]-[r_k<n]$. We calculate the two parts seperately. For each part we do a dp. For the first part, let $dp_{i,j}$ represents the answer for the first $i-1$ elements when $i-1=l_j$. For the second part, let $dp_{i,v,j}$ represents the answer for the first $i$ elements when $i-1=r_j\land a_i=v$, as you have to know the value of the begin of next segment while doing dp.

The state transitions for the first dp should be trival. As for the second dp, you have to do some adding up to avoid a $O(n^5)$ transition. Also, carefully calculate the coefficients. They are kind of tricky.

The final time complexity should be $O(n^4)$.
#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 10005;

int fa[maxn], rnk[maxn];

void init()
{
    for(int i = 0; i < maxn; i++)
    {
        fa[i] = i;
        rnk[i] = 1;
    }
}

int Find(int x)
{
    int r = x;
    while(r != fa[r]) r = fa[r];
    int i = x, j;
    while(i != r)
    {
        j = fa[i];
        fa[i] = r;
        i = j;
    }
    return r;
}

int Find(int x)
{
    if(fa[x] != x) fa[x] = Find(fa[x]);
    return find[x];
}

void Union(int x, int y)
{
    x = Find(x); y = Find(y);
    if(x == y) return ;
    if(rnk[x] >= rnk[y])
    {
        fa[y] = x;
        rnk[x] += rnk[y];
    }
    else
    {
        fa[x] = y;
        rnk[y] += rnk[x];
    }
}
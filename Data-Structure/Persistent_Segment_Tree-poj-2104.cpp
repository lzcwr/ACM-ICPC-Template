// poj 2104
// 求静态区间第k大
#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
// #define lson l, m, rt  <<  1
// #define rson m + 1, r, rt  <<  1 | 1
// #define root 1, n, 1

const int maxn = 100005;
const int M = maxn * 30;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

int n, q, m, tot;
int a[maxn], t[maxm], T[maxn];
int lson[M], rson[M], c[M];

void init_hash()
{
    for(int i = 1; i <= n; i++)
        t[i] = a[i];
    sort(t + 1, t + n + 1);
    m = unique(t + 1, t + n + 1) - t - 1;
}

int build(int l, int r)
{
    int root = tot++;
    c[root] = 0;
    if(l != r)
    {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}

int hash(int x)
{
    return lower_bound(t + 1, t + 1 + m, x) - t;
}

int update(int root, int pos, int val)
{
    int newroot = tot++, ret = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(pos <= mid)
        {
            lson[newroot] = tot++; rson[newroot] = rson[root];
            newroot = lson[newroot]; root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = tot++; lson[newroot] = lson[root];
            newroot = rson[newroot]; root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return ret;
}

int query(int left_root, int right_root, int k)
{
    int l = 1, r = m;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(c[lson[left_root]] - c[lson[right_root]] >= k)
        {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        }
        else
        {
            l = mid + 1;
            k -= c[lson[left_root]] - c[lson[right_root]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}

int main()
{
    while(scanf("%d%d", &n, &q) != EOF)
    {
        tot = 0;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        init_hash();
        T[n + 1] = build(1, m);
        for(int i = n; i > 0; i--)
        {
            int pos = hash(a[i]);
            T[i] = update(T[i + 1], pos, 1);
        }
        while(q--)
        {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", t[query(T[l], T[r + 1], k)]);
        }
    }

    return 0;
}
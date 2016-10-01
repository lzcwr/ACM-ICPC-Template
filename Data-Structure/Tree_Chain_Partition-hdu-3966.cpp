// hdu 3966 树链剖分+树状数组
// 修改路径上的点权，查询单点值
#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 50010;
const int maxm = 1005;
const int mod = 10000;
const double eps = 1e-8;
const double pi = acos( -1.0);
const int inf = std::numeric_limits<int>::max();

struct Edge
{
    int to, nxt;
} edge[maxn << 1];

int head[maxn], tot, top[maxn], fa[maxn], deep[maxn];
int num[maxn], p[maxn], fp[maxn], son[maxn], pos;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 1;
    memset(son, -1, sizeof(son));
}

void addedge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}

void dfs1(int u, int pre, int d)
{
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != pre)
        {
            dfs1(v, u, d + 1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}

void getpos(int u, int sp)
{
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1) return ;
    getpos(son[u], sp);
    for(int i = head[u]; i != -1; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v);
    }
}

int lowbit(int x)
{
    return x & (-x);
}

int c[maxn], n;

int sum(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}

void add(int i, int val)
{
    while(i <= n)
    {
        c[i] += val;
        i += lowbit(i);
    }
}

void Change(int u, int v, int val)
{
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2)
    {
        if(deep[f1] < deep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        add(p[f1], val);
        add(p[u] + 1, -val);
        u = fa[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v]) swap(u, v);
    add(p[u], val);
    add(p[v] + 1, -val);
}

int a[maxn];

int main()
{
    int M, P;
    while(scanf("%d%d%d", &n, &M, &P) != EOF)
    {
        int u, v;
        int C1, C2, K;
        char op[10];
        init();
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        while(M--)
        {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        dfs1(1, 0, 0);
        getpos(1, 1);
        memset(c, 0, sizeof(c));
        for(int i = 1; i <= n; i++)
        {
            add(p[i], a[i]);
            add(p[i] + 1, -a[i]);
        }
        while(P--)
        {
            scanf("%s", op);
            if(op[0] == 'Q')
            {
                scanf("%d", &u);
                printf("%d\n", sum(p[u]));
            }
            else
            {
                scanf("%d%d%d", &C1, &C2, &K);
                if(op[0] == 'D') K = -K;
                Change(C1, C2, K);
            }
        }
    }

    return 0;
}
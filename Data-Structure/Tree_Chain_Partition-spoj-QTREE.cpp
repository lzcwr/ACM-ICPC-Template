// SPOJ QTREE 树链剖分+线段树
// 单条边权修改 查询路径边权最大值
#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 10010;
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
    pos = 0;
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

struct Node
{
    int l, r;
    int Max;
} segTree[maxn << 2];

void build(int l, int r, int rt)
{
    segTree[rt].l = l;
    segTree[rt].r = r;
    segTree[rt].Max = 0;
    if(l == r) return ;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}

void push_up(int rt)
{
    segTree[rt].Max = max(segTree[rt << 1].Max, segTree[(rt << 1) | 1].Max);
}

void update(int rt, int k, int val)
{
    if(segTree[rt].l == k && segTree[rt].r == k)
    {
        segTree[rt].Max = val;
        return ;
    }
    int m = (segTree[rt].l + segTree[rt].r) >> 1;
    if(k <= m) update(rt << 1, k, val);
    else update((rt << 1) | 1, k, val);
    push_up(rt);
}

int query(int l, int r, int rt)
{
    if(segTree[rt].l == l && segTree[rt].r == r)
        return segTree[rt].Max;
    int m = (segTree[rt].l + segTree[rt].r) >> 1;
    if(r <= m) return query(l, r, rt << 1);
    else if(l > m) return query(l, r, rt << 1 | 1);
    else return max(query(lson), query(rson));
}

int find(int u, int v)
{
    int f1 = top[u], f2 = top[v];
    int tmp(0);
    while(f1 != f2)
    {
        if(deep[f1] < deep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(p[f1], p[u], 1));
        u = fa[f1]; f1 = top[u];
    }
    if(u == v) return tmp;
    if(deep[u] > deep[v]) swap(u, v);
    return max(tmp, query(p[son[u]], p[v], 1));
}

int e[maxn][3];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n - 1; i++)
        {
            scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
            addedge(e[i][0], e[i][1]);
            addedge(e[i][1], e[i][0]);
        }
        dfs1(1, 0, 0);
        getpos(1, 1);
        build(0, pos - 1, 1);
        for(int i = 0; i < n - 1; i++)
        {
            if(deep[e[i][0]] > deep[e[i][1]])
                swap(e[i][0], e[i][1]);
            update(1, p[e[i][1]], e[i][2]);
        }
        char op[10];
        while(scanf("%s", op) != EOF)
        {
            if(op[0] == 'D') break;
            int u, v;
            scanf("%d%d", &u, &v);
            if(op[0] == 'Q')
                printf("%d\n", find(u, v));
            else update(1, p[e[u - 1][1]], v);
        }
    }

    return 0;
}
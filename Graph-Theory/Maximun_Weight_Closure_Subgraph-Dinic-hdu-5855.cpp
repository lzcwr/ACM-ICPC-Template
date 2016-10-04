#include <bits/stdc++.h>
using namespace std;

#define showtime printf("time=%.15f\n", clock() / (double)CLOCKS_PER_SEC);

const int maxn = 405;
const int maxm = 100010;
const int maxp = 205;
const int inf = 0x3f3f3f3f;

int node, source, dest, tot;
int head[maxn], to[maxm], nxt[maxm], flow[maxm], capa[maxm];
int dist[maxn], Q[maxn], work[maxn];
int pay[maxp], pro[maxp], t[maxp], pos[maxp][maxp];
int length[maxp], u[maxp];
int n, m, _l;

void init(int _node, int _source, int _dest)
{
    node = _node;
    source = _source;
    dest = _dest;
    for(int i = 0; i < node; i++)
        head[i] = -1;
    tot = 0;
}

void addedge(int u, int v, int _capa, int _capa_2)
{
    to[tot] = v; capa[tot] = _capa; flow[tot] = 0; nxt[tot] = head[u]; head[u] = tot++;
    to[tot] = u; capa[tot] = _capa_2; flow[tot] = 0; nxt[tot] = head[v]; head[v] = tot++;
}

bool bfs()
{
    memset(dist, -1, sizeof(dist));
    dist[source] = 0;
    int sizeQ = 0;
    Q[sizeQ++] = source;
    for(int _capa = 0; _capa < sizeQ; _capa++)
    {
        for(int k = Q[_capa], i = head[k]; i >= 0; i = nxt[i])
        {
            if(flow[i] < capa[i] && dist[to[i]] < 0)
            {
                dist[to[i]] = dist[k] + 1;
                Q[sizeQ++] = to[i];
            }
        }
    }
    return dist[dest] >= 0;
}

int dfs(int x, int exp)
{
    if(x == dest) return exp;
    for(int &i = work[x]; i >= 0; i = nxt[i])
    {
        int v = to[i], tmp;
        if(flow[i] < capa[i] && dist[v] == dist[x] + 1 && (tmp = dfs(v, min(exp, capa[i] - flow[i]))) > 0)
        {
            flow[i] += tmp;
            flow[i^1] -= tmp;
            return tmp;
        }
    }
    return 0;
}

int dinic()
{
    int ret(0);
    while(bfs())
    {
        for(int i = 0; i < node; i++)
            work[i] = head[i];
        while(true)
        {
            int delta = dfs(source, inf);
            if(delta == 0) break;
            ret += delta;
        }
    }
    return ret;
}

int judge(int x)
{
    init(n + m + 2, 0, n + m + 1);
    for(int i = 1; i <= n; i++)
    {
        if(t[i] <= x)
        {
            u[i] = 1;
            addedge(0, i, pay[i], 0);
        }
        else u[i] = 0;
    }
    int sum(0);
    for(int i = 1; i <= m; i++)
    {
        int temp(1);
        for(int j = 0; j < length[i]; j++)
            temp &= u[pos[i][j]];
        if(temp)
        {
            sum += pro[i];
            addedge(n + i, n + m + 1, pro[i], 0);
            for(int j = 0; j < length[i]; j++)
                addedge(pos[i][j], n + i, inf, 0);
        }
    }
    int res = sum - dinic();
    return res;
}

int main()
{
    int T, cas(0);
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &_l);
        int l(0), r(0);
        for(int i = 1; i <= n; i++)
            scanf("%d%d", &pay[i], &t[i]);
        for(int i = 1; i <= n; i++)
            r = max(r, t[i]);
        for(int i = 1; i <= m; i++)
        {
            int k;
            scanf("%d%d", &pro[i], &k);
            length[i] = k;
            for(int j = 0; j < k; j++)
                scanf("%d", &pos[i][j]);
        }
        r++;
        int high = r;
        while(l < r)
        {
            int m = (l + r) >> 1;
            int res = judge(m);
            if(res >= _l) r = m;
            else l = m + 1;
        }
        int ans = judge(r);
        printf("Case #%d: ", ++cas);
        if(r < high) printf("%d %d\n", r, ans);
        else printf("impossible\n");
    }

    return 0;
}
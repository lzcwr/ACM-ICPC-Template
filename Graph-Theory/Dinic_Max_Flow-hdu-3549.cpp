// hdu 3549 Flow Problem
#include <bits/stdc++.h>
using namespace std;

const int maxn = 405;
const int maxm = 100010;
const int inf = 0x3f3f3f3f;

int node, source, dest, tot;
int head[maxn], to[maxm], nxt[maxm], flow[maxm], capa[maxm];
int dist[maxn], Q[maxn], work[maxn];

void init(int _node, int _source, int _dest)
{
    node = _node;
    source = _source;
    dest = _dest;
    memset(head, -1, sizeof(head));
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

long long dinic()
{
    long long ret(0);
    while(bfs())
    {
        for(long long i = 0; i < node; i++)
            work[i] = head[i];
        while(true)
        {
            long long delta = dfs(source, inf);
            if(delta == 0) break;
            ret += delta;
        }
    }
    return ret;
}

int main()
{
    int t, cas(0);
    scanf("%d", &t);
    while(t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        init(n, 1, n);
        while(m--)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            addedge(u, v, c, 0);
        }
        printf("Case %d: %lld\n", ++cas, dinic());
    }

    return 0;
}
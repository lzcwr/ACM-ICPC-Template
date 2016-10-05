#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define root 1, n, 1

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 205;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

struct Edge
{
    int to, nxt, cap, flow, cost;
} edge[maxm];

int head[maxn], tol, pre[maxn], dis[maxn];
bool vis[maxn];
int N;

void init(int n)
{
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cap, int cost)
{
    edge[tol].to = v; edge[tol].cap = cap; edge[tol].cost = cost;
    edge[tol].flow = 0; edge[tol].nxt = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = 0; edge[tol].cost = -cost;
    edge[tol].flow = 0; edge[tol].nxt = head[v]; head[v] = tol++;
}

bool spfa(int s, int t)
{
    std::queue<int> Q;
    for(int i = 0; i < N; i++)
    {
        dis[i] = inf;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0; vis[s] = true;
    Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost)
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v])
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1) return false;
    else return true;
}

std::pair<int, int> min_Cost_max_Flow(int s, int t)
{
    int flow = 0, cost = 0;
    while(spfa(s, t))
    {
        int Min = inf;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
                Min = min(Min, edge[i].cap - edge[i].flow);
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return make_pair(cost, flow);
}

int dist(std::pair<int, int> a, std::pair<int, int> b)
{
    return (abs(a.first - b.first) + abs(a.second - b.second));
}

std::vector< std::pair<int, int> > man, house;
int main()
{
    int m, n;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && n == 0) break;
        man.clear(); house.clear();
        char ch;
        for(int i = 0; i < n; i++)
        {
            getchar();
            for(int j = 0; j < m; j++)
            {
                ch = getchar();
                if(ch == 'H') house.push_back(make_pair(i, j));
                if(ch == 'm') man.push_back(make_pair(i, j));
            }
        }
        int cntM = man.size(), cntH = house.size();
        init(cntM + cntH + 2);
        int S = cntM + cntH, T = cntM + cntH + 1;
        for(int i = 0; i < cntM; i++)
            addedge(S, i, 1, 0);
        for(int i = 0; i < cntH; i++)
            addedge(i + cntM, T, 1, 0);
        for(int i = 0; i < cntM; i++)
            for(int j = 0; j < cntH; j++)
                addedge(i, j + cntM, 1, dist(man[i], house[j]));
        printf("%d\n", min_Cost_max_Flow(S, T).first);
    }

    return 0;
}
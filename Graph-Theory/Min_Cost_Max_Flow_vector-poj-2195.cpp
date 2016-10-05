#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 205;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

typedef pair<int, int> P;  // first保存最短距离，second保存顶点编号

struct edge
{
    int to;        // 终点
    int cap;   // 容量
    int cost;  // 费用
    int rev;   // 反向边
    edge(int to, int cap, int cost, int rev) :to(to), cap(cap), cost(cost), rev(rev){}
};
int V;         // 顶点数
vector<edge> G[maxm];   // 图的邻接表
int h[maxm];  // 顶点的势
int dist[maxm];// 最短距离
int prevv[maxm];  // 最短路中的前驱节点
int preve[maxm];  // 最短路中的前驱节点对应的边
 
// 向图中增加一条从from到to的容量为cap费用为cost的边
void add_edge(int from, int to, int cap, int cost)
{
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
}
 
// 求解从s到t流量为f的最小费用流，如果没有流量为f的流，则返回-1
int min_cost_flow(int s, int t, int f)
{
    int res = 0;
    memset(h, 0, sizeof(h));
    while (f > 0)
    {
        // 使用Dijkstra算法更新h
        priority_queue<P, vector<P>, greater<P> > que;
        memset(dist, inf, sizeof(dist));
        dist[s] = 0;
        que.push(P(0, s));
        while (!que.empty())
        {
            P p = que.top(); que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); ++i)
            {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
                {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == inf)// 不能再增广
            return -1;
        for (int v = 0; v < V; ++v)
            h[v] += dist[v];
 
        // 沿s到t的最短路尽量增广
        int d = f;
        for (int v = t; v != s; v = prevv[v])
            d = min(d, G[prevv[v]][preve[v]].cap);
        f -= d;
        res += d * h[t];
        for (int v = t; v != s; v = prevv[v])
        {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
 
void clear()
{
    for (int i = 0; i < V; ++i)
        G[i].clear();
}

int distance_of(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(int argc, char *argv[])
{
    int N, M;
    while (scanf("%d%d", &N, &M), N && M)
    {
        vector<pair<int, int> > man;
        vector<pair<int, int> > house;
        for (int i = 0; i < N; ++i)
        {
            getchar();
            for (int j = 0; j < M; ++j)
            {
                switch (getchar())
                {
                    case 'm':
                        man.push_back(make_pair(i, j));
                        break;
                    case 'H':
                        house.push_back(make_pair(i, j));
                        break;
                }
            }
        }
        const int size = man.size();
        const int s = 0, t = 1 + size + size;
        V = t + 1;
        clear();
        for (int i = 0; i < size; ++i)
        {
            add_edge(s, i + 1, 1, 0);
            add_edge(i + 1 + size, t, 1, 0);
            for (int j = 0; j < size; ++j)
                add_edge(i + 1, size + j + 1, 1, distance_of(man[i], house[j]));
        }
        
        printf("%d\n", min_cost_flow(s, t, size));
    }
    
    return 0;
}
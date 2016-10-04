#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 105;
const int inf = std::numeric_limits<int>::max();

int mp[maxn][maxn], dist[maxn];
bool vis[maxn];
std::queue<int> Q;

int n, m;
void spfa(int s)
{
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < n; i++)
        dist[i] = inf;
    while(!Q.empty())  Q.pop();
    Q.push(s); vis[s] = true;
    while(!Q.empty())
    {
        int u = Q.front();
        vis[u] = false;
        Q.pop();
        for(int i = 0; i < n; i++)
        {
            if(mp[u][i] == inf) continue;
            if(dist[i] > dist[u] + mp[u][i])
            {
                dist[i] = dist[u] + mp[u][i];
                if(!vis[i]) { vis[i] = true; Q.push(i); }
            }
        }
    }
}

void init()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mp[i][j] = (i == j) ? 0 : inf;
}

int main()
{
    while(scanf("%d%d", &n, &m) != EOF)
    {
        init();
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            mp[u][v] = w;
        }
        int s, t;
        scanf("%d%d", &s, &t);
        spfa(s);
        if(dist[t] == inf) printf("-1\n");
        else printf("%d\n", dist[t]);
    }

    return 0;
}
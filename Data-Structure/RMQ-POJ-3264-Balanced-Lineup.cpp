#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 50010;
const int maxm = 1005;
const int mod = 10000;
const double eps = 1e-8;
const double pi = acos(-1.0);

int dp_max[maxn][20], dp_min[maxn][20];
int a[maxn];

void initRMQ(int n, int b[])
{
    for(int i = 1; i <= n; i++)
    {
        dp_max[i][0] = b[i];
        dp_min[i][0] = b[i];
    }
    for(int j = 1; j < log( (double)(n + 1) ) / log(2.0); j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            dp_max[i][j] = max(dp_max[i][j - 1], dp_max[i + (1 << (j - 1))][j - 1]);
            dp_min[i][j] = min(dp_min[i][j - 1], dp_min[i + (1 << (j - 1))][j - 1]);
        }

}

int RMQ_MAX(int x, int y)
{
    int k = (int)( log( (double)(y - x + 1) ) / log(2.0) );
    return max(dp_max[x][k], dp_max[y - (1 << k) + 1][k]);
}

int RMQ_MIN(int x, int y)
{
    int k = (int)( log( (double)(y - x + 1) ) / log(2.0) );
    return min(dp_min[x][k], dp_min[y - (1 << k) + 1][k]);
}

int main(int argc, char const *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    initRMQ(n, a);
    while(q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", RMQ_MAX(l, r) - RMQ_MIN(l, r));
    }

#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif

    return 0;
}

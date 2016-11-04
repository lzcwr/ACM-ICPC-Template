#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
// #define lson l, m, rt << 1
// #define rson m + 1, r, rt << 1 | 1
// #define root 1, n, 1
#define Key_value ch[ch[root][1]][0]

const int maxn = 50010;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;

int pre[maxn], ch[maxn][2], key[maxn], size[maxn];
int root, tot1, sum[maxn], rev[maxn], same[maxn];
int lx[maxn], rx[maxn], nx[maxn], s[maxn], tot2, a[maxn];
int n, q;

void NewNode(int &r, int father, int k)
{
    if(tot2) r = s[tot2--];
    else r = ++tot1;
    pre[r] = father;
    ch[r][0] = ch[r][1] = 0;
    key[r] = sum[r] = k;
    rev[r] = same[r] = 0;
    lx[r] = rx[r] = mx[r] = k;
    size[r] = l;
    return ;
}

void Update_Rev(int r)
{
    if(!r) return ;
    swap(ch[r][0], ch[r][1]);
    swap(lx[r], rx[r]);
    rev[r] ^= 1;
    return ;
}

void Update_Same(int r, int v)
{
    if(!r) return ;
    key[r] = v;
    sum[r] = v * size[r];
    lx[r] = rx[r] = mx[r] = max(v, v * size[r]);
    same[r] = l;
    return ;
}

void push_up(int r)
{
    int lson = ch[r][0], rson = ch[r][1];
    size[r] = size[lson] + size[rson] + 1;
    sum[r] = sum[lson] + sum[rson] + key[r];
    lx[r] = max(lx[lson], sum[lson] + key[r] + max(0, lx[rson]));
    rx[r] = max(rx[rson], sum[rson] + key[r] + max(0, rx[lson]));
    mx[r] = max(0, rx[lson]) + key[r] + max(0, lx[rson]);
    mx[r] = max(mx[r], max(mx[lson], mx[rson]));
    return ;
}

void push_down(int r)
{
    if(same[r])
    {
        Update_Same(ch[r][0], key[r]);
        Update_Same(ch[r][1], key[r]);
        same[r] = 0;
    }
    if(rev[r])
    {
        Update_Rev(ch[r][0]);
        Update_Rev(ch[r][1]);
        rev[r] = 0;
    }
    return ;
}

void Build(int &x, int l, int r, int father)
{
    if(l > r) return ;
    int mid = (l + r) >> 1;
    NewNode(x, father, a[mid]);
    Build(ch[x][0], l, mid - 1, x);
    Build(ch[x][1], mid + 1, r, x);
    push_up(x);
    return ;
}

void init()
{
    root = tot1 = tot2 = 0;
    ch[root][0] = ch[root][1] = size[root] = pre[root] = 0;
    same[root] = rev[root] = sum[root] = key[root] = 0;
    lx[root] = rx[root] = mx[root] = _inf;
    NewNode(root, 0, -1);
    NewNode(ch[root][1], root, -1);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    Build(Key_value, 0, n - 1, ch[root][1]);
    push_up(ch[root][1]);
    push_up(root);
}

void rotate(int x, int kind)
{
    int y = pre[x];
    push_down(y);
    push_down(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    push_up(y);
}

void Splay(int r, int goal)
{
    push_down(r);
    while(pre[r] != goal)
    {
        if(pre[pre[r]] == goal)
        {
            push_down(pre[r]);
            push_down(r);
            rotate(r, ch[pre[r]][0] == r);
        }
        else
        {
            push_down(pre[pre[r]]);
            push_down(pre[r]);
            push_down(r);
            int y = pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == r)
            {
                rotate(r, !kind);
                rotate(r, kind);
            }
            else
            {
                rotate(y, kind);
                rotate(r, kind);
            }
        }
    }
    push_up(r);
    if(goal == 0) root = r;
}

int Get_Kth(int r, int k)
{
    push_down(r);
    int t = size[ch[r][0]] + 1;
    if(t == k) return r;
    if(t > k) return Get_Kth(ch[r][0], k);
    else return Get_Kth(ch[r][1], k - t);
}

void Insert(int pos, int tot)
{
    for(int i = 0; i < tot; i++)
        scanf("%d", &a[i]);
    Splay(Get_Kth(root, pos + 1), 0);
    Splay(Get_Kth(root, pos + 2), root);
    Build(Key_value, 0, tot - 1, ch[root][1]);
    push_up(ch[root][1]);
    push_up(root);
}

void erase(int r)
{
    if(!r) return ;
    s[++tot2] = r;
    erase(ch[r][0]);
    erase(ch[r][1]);
}

void Delete(int pos, int tot)
{
    Splay(Get_Kth(root, pos), 0);
    Splay(Get_Kth(root, pos + tot + 1), root);
    erase(Key_value);
    pre[Key_value] = 0;
    Key_value = 0;
    push_up(ch[root][1]);
    push_up(root);
}

void Make_Same(int pos, int tot, int c)
{
    Splay(Get_Kth(root, pos), 0);
    Splay(Get_Kth(root, pos + tot + 1), root);
    Update_Same(Key_value, c);
    push_up(ch[root][1]);
    push_up(root);
}

void Reverse(int pos, int tot)
{
    Splay(Get_Kth(root, pos), 0);
    Splay(Get_Kth(root, pos + tot + 1), root);
    Update_Rev(Key_value);
    push_up(ch[root][1]);
    push_up(root);
}

int Get_sum(int pos, int tot)
{
    Splay(Get_Kth(root, pos), 0);
    Splay(Get_Kth(root, pos + tot + 1), root);
    return sum[Key_value];
}

int Get_MaxSum(int pos, int tot)
{
    Splay(Get_Kth(root, pos), 0);
    Splay(Get_Kth(root, pos + tot + 1), root);
    return mx[Key_value];
}

void In_Order(int r)
{
    if(!r) return ;
    In_Order(ch[r][0]);
    printf("%d\n", key[r]);
    In_Order(ch[r][1]);
}

void solve()
{
    while(scanf("%d%d", &n, &q) != EOF)
    {
        init();
        int x, y, z;
        while(q--)
        {
            char op[20];
            scanf("%s", &op);
            if(strcmp(op, "INSERT") == 0)
            {
                scanf("%d%d", &x, &y);
                Insert(x, y);
            }
            if(strcmp(op, "DELETE") == 0)
            {
                scanf("%d%d", &x, &y);
                Delete(x, y);
            }
            if(strcmp(op, "MAKE-SAME") == 0)
            {
                scanf("%d%d%d", &x, &y, &z);
                Make_Same(x, y, z);
            }
            if(strcmp(op, "REVRESE") == 0)
            {
                scanf("%d%d", &x, &y);
                Reverse(x, y);
            }
            if(strcmp(op, "GET-SUM") == 0)
            {
                scanf("%d%d", &x, &y);
                printf("%d\n", Get_sum(x, y));
            }
            if(strcmp(op, "MAX-SUM") == 0)
                printf("%d\n", Get_MaxSum(1, size[root] - 2));
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif

    solve();

#ifndef ONLINE_JUDGE
    // fclose(stdin);
    // fclose(stdout);
    system("bianma.txt");
    system("jiema.txt");
#endif

    return 0;
}

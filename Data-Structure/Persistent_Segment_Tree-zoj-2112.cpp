// zoj 2112
// 动态第k大 树状数组+主席树
#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
// #define lson l, m, rt  <<  1
// #define rson m + 1, r, rt  <<  1 | 1
// #define root 1, n, 1

const int maxn = 60005;
const int M = 2500010;
const int maxm = 1e5 + 5;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

int n, q, m, tot;
int a[maxn], t[maxm], T[maxn], S[maxn];
int lson[M], rson[M], c[M];

struct Query
{
	int kind;
	int l, r, k;
} query[10005];

void init_hash(int k)
{
	sort(t, t + k);
	m = unique(t, t + k) - t;
}

int hash(int x)
{
    return lower_bound(t, t + m, x) - t;
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

int update(int root, int pos, int val)
{
	int newroot = tot++, ret = newroot;
	int l = 0, r = m - 1;
	c[newroot] = c[root] + val;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(pos <= mid)
        {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
	}
	return ret;
}

int lowbit(int x)
{
	return x & (-x);
}

int use[maxn];
void add(int x, int pos, int val)
{
	while(x <= n)
	{
		S[x] = update(S[x], pos, val);
		x += lowbit(x);
	}
}

int sum(int x)
{
	int ret = 0;
	while(x > 0)
	{
		ret += c[lson[use[x]]];
		x -= lowbit(x);
	}
	return ret;
}

int Query(int left, int right, int k)
{
	int left_root = T[left - 1];
	int right_root = T[right];
	int l = 0, r = m - 1;
	for(int i = left - 1; i > 0; i -= lowbit(i))
		use[i] = S[i];
	for(int i = right; i > 0; i -= lowbit(i))
		use[i] = S[i];	
    while(l < r)
    {
        int mid = (l + r) >> 1;
        int tmp = sum(right) - sum(left - 1) + c[lson[right_root]] - c[lson[left_root]];
        if(tmp >= k)
        {
        	r = mid;
        	for(int i = left - 1; i > 0; i -= lowbit(i))
        		use[i] = lson[use[i]];
        	for(int i = right; i > 0; i -= lowbit(i))
        		use[i] = lson[use[i]];
        	left_root = lson[left_root];
        	right_root = lson[right_root];
        }
        else
        {
        	l = mid + 1; k -= tmp;
        	for(int i = left - 1; i > 0; i -= lowbit(i))
        		use[i] = rson[use[i]];
        	for(int i = right; i > 0; i -= lowbit(i))
        		use[i] = rson[use[i]];
        	left_root = rson[left_root];
        	right_root = rson[right_root];
        }
    }
    return l;
}

void Modify(int x, int p, int d)
{
	while(x <= n)
	{
		S[x] = update(S[x], p, d);
		x += lowbit(x);
	}
}

int main()
{
	int cas;
	scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d%d", &n, &q);
        tot = 0; m = 0;
        for(int i = 1; i <= n; i++)
        {
        	scanf("%d", &a[i]);
        	t[m++] = a[i];
        }
        char op[5];
        for(int i = 0; i < q; i++)
        {
        	scanf("%s", op);
        	if(op[0] == 'Q')
        	{
        		query[i].kind = 0;
        		scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
        	}
        	if(op[0] == 'C')
        	{
        		query[i].kind = 1;
        		scanf("%d%d", &query[i].l, &query[i].r);
        		t[m++] = query[i].r;
        	}
        }
        init_hash(m);
        T[0] = build(0, m - 1);
        for(int i = 1; i <= n; i++)
        	T[i] = update(T[i - 1], hash(a[i]), 1);
        for(int i = 1; i <= n; i++)
        	S[i] = T[0];
        for(int i = 0; i < q; i++)
        {
        	if(query[i].kind == 0)
        		printf("%d\n", t[Query(query[i].l, query[i].r, query[i].k)]);
        	else
        	{
        		Modify(query[i].l, hash(a[query[i].l]), -1);
        		Modify(query[i].l, hash(query[i].r), 1);
        		a[query[i].l] = query[i].r;
        	}
        }
    }

    return 0;
}
// ��̬�����߶��� ���� ����� 
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LLI long long
#define DBL double
const bool DEBUG = false;
const int max_v = 1e9;
const int maxn = 5e5 + 10;

int n,
	a[maxn];

// ��̬����, ֵ��[0, 1e9] 
struct Node {
	int s;
	//int l, r; // ���ұ߽� 
	int lc, rc; // ���Ҷ������ 
	// ����lazytag, ��Ϊֻ�赥���޸� 
}t[maxn * 20]; // ����ռ俪�������⣬����Ϊ����ˮ�����Ծ͹��ˣ� 
#define LC (t[x].lc)
#define RC (t[x].rc)
int root, tot;

int newNodeMax = 0;
int newNode() {
	newNodeMax++;
	t[++tot].s = 0;
	t[tot].lc = t[tot].rc = 0;
	return tot;
}

void pushup(int x) {
	t[x].s = t[LC].s + t[RC].s;
}

LLI query(int x, int tl, int tr, int l, int r) {
	if(tr < l || r < tl) return 0;
	if(l <= tl && tr <= r) return t[x].s;
	
	LLI ans = 0;
	int mid = tl + tr >> 1;
	if(l <= mid && t[x].lc)
		ans += query(t[x].lc, tl, mid, l, r);
	if(mid < r && t[x].rc)
		ans += query(t[x].rc, mid+1, tr, l, r);
	return ans;
}

void modify(int x, int tl, int tr, int pos, int v) {
	if(tr < pos || pos < tl) return;
	if(pos <= tl && tr <= pos) {
		t[x].s++; return;
	}
	
	int mid = tl + tr >> 1;
	int ret = 0;
	if(pos <= mid) {
		if(!t[x].lc) t[x].lc = newNode();
		modify(t[x].lc, tl, mid, pos, v);
	} else {
		if(!t[x].rc) t[x].rc = newNode();
		modify(t[x].rc, mid+1, tr, pos, v); 
	}
	pushup(x);
}

int main() {
	
	freopen("sgt_in.txt", "r", stdin);
	freopen("sgt_out.txt", "w", stdout);
	
	//printf("%dMB\n", sizeof(t) / 1024 / 1024);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	
	root = newNode();
	LLI ans = 0;
	for(int i = 1; i <= n; i++) {
		//printf("%d : %lld\n", i, query(root, a[i]+1, max_v));
		ans += query(root, 1, max_v, a[i]+1, max_v);
		modify(root, 1, max_v, a[i], 1);
	}
	printf("%lld\n", ans);
	printf("tot = %d\n", tot);
	printf("newNodeMax = %d\n", newNodeMax);
	
	return 0;
}


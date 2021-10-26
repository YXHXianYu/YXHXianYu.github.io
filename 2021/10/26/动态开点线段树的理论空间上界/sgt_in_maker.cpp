#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LLI long long
#define DBL double
const bool DEBUG = false;
const int maxn = 1e4 + 10;


int main() {
	
	freopen("sgt_in.txt", "w", stdout);
	
	printf("500000\n");
	for(int i = 1, j = 1; i <= 500000; i++, j = (j+2111)%(int(1e9))) {
		printf("%d ", j);
	}
	printf("\n");
	
	
	
	return 0;
}


/*
- sorting, greedy

> min: M smallest integers
> max: sort A, partition A into size [a, a, ..., b, b], where a = N/M+1 and b = N/M

*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

typedef long long LL;

const int maxn = 100005;

int N, M;
int A[maxn];

int main(int argc, char *argv[]) {
	
	scanf( "%d %d", &N, &M );
	REP(i,N) scanf( "%d", &A[i] );

	LL mn = 0;
	LL mx = 0;

	if ( N <= M ) {
		REP(i,N) mn += A[i];
		mx = mn;
	}
	else {
		sort(A,A+N);
		REP(i,M) mn += A[i];
		int x = 0;
		FOR(_,0,N%M-1) mx += A[x], x += N / M + 1;
		FOR(_,N%M,M-1) mx += A[x], x += N / M;
	}

	printf( "%lld %lld\n", mn, mx );
	
	return 0;
}

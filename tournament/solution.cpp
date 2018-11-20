#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

const int maxn = 16;
const int inf  = 1000000000;

int N;
int A[maxn][maxn];
vector <int> bit[maxn+5];

int  full(int n) { return (1 << n) - 1; }
bool is_on(int mask, int x) { return mask & (1 << x); }

int memo[maxn][1<<maxn];
bool can_win(int x, int mask) {
	if ( memo[x][mask] != -1 ) return memo[x][mask];
	int &ret = memo[x][mask] = false;
	int m = __builtin_popcount(mask);
	if ( m == 1 ) return ret = true;
	REP(i,bit[m/2].size()) if ( is_on(bit[m/2][i],x) && (mask | bit[m/2][i]) == mask ) {
		if ( !can_win(x,bit[m/2][i]) ) continue;
		int xbit = ~bit[m/2][i] & mask;
		REP(j,N) if ( is_on(xbit,j) ) {
			if ( !can_win(j,xbit) ) continue;
			if ( A[x][j] > 0 ) return ret = true;
		}
	}
	return ret;
}

int dp[maxn][1<<maxn];
int f(int x, int mask) {
	if ( dp[x][mask] != -1 ) return dp[x][mask];
	int &ret = dp[x][mask] = inf;
	int m = __builtin_popcount(mask);
	if ( m == 1 ) return ret = 0;
	REP(i,bit[m/2].size()) if ( is_on(bit[m/2][i],x) && (mask | bit[m/2][i]) == mask ) {
		if ( f(x,bit[m/2][i]) == inf ) continue;
		//if ( !can_win(x,bit[m/2][i]) ) continue;
		int recu = f(x,bit[m/2][i]);
		int xbit = ~bit[m/2][i] & mask;
		REP(j,N) if ( is_on(xbit,j) ) {
			//if ( !can_win(j,xbit) ) continue;
			if ( f(j,xbit) == inf ) continue;
			if ( A[x][j] < 0 ) continue;
			ret = min(ret,recu+A[x][j]);
		}
	}
	return ret;
}

int main(int argc, char *argv[]) {
	
	scanf( "%d", &N );
	N = 1 << N;
	REP(i,N) REP(j,N) scanf( "%d", &A[i][j] );

	REP(i,1<<N) bit[__builtin_popcount(i)].push_back(i);

	memset(memo,-1,sizeof(memo));
	memset(dp,-1,sizeof(dp));
	int ans = f(0,full(N));

	printf( "%d\n", ans == inf ? -1 : ans );
	
	return 0;
}

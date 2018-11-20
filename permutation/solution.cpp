#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

const int maxn = 100005;

char S[maxn];
char P[maxn];

int main(int argc, char *argv[]) {
	
	scanf( "%s", S );
	scanf( "%s", P );

	int cnt[256] = {0};
	REP(i,strlen(S)) cnt[S[i]]++;
	REP(i,strlen(P)) cnt[P[i]]--;

	bool okay = true;
	FOR(i,'a','z') if ( cnt[i] < 0 ) okay = false;

	printf( "%s\n", okay ? "YES" : "NO" );
	
	return 0;
}

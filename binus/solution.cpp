#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

const int maxn = 105;

int  N;
int  A[maxn];
int  x;
char s[15];

int main(int argc, char *argv[]) {
	
	scanf( "%d", &N );
	FOR(i,1,N) scanf( "%d", &A[i] );

	int one = 0, two = 0;
	int p;

	scanf( "%d %s", &x, s );
	p = s[0] == 'l' ? -1 : 1;
	while ( 1 <= x && x <= N ) one += A[x], x += p;

	scanf( "%d %s", &x, s );
	p = s[0] == 'l' ? -1 : 1;
	while ( 1 <= x && x <= N ) two += A[x] == 0 ? 1 : 0, x += p;

	printf( "%d %d\n", one, two );
	
	return 0;
}

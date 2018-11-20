/*
- maximum flow

suhendry.effendy
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

#define MAX_N 205

const int maxn = 55;
const int inf  = 10000000;
 
int n;
int cap[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
 
inline bool augment(int s, int t) {
	stack <int> q;
	bool visit[MAX_N] = { false };
	int parent[MAX_N];
	q.push(s); visit[s] = true; parent[s] = -1;
	while ( !q.empty() ) {
		int curr = q.top(); q.pop();
		REP(i,n) {
			if ( visit[i] || cap[curr][i]-flow[curr][i] <= 0 ) continue;
			q.push(i); visit[i] = true; parent[i] = curr;
			if ( i == t ) { 
				int p = t, value = inf;
				while ( parent[p] != -1 ) {
					value = min(value,cap[parent[p]][p]-flow[parent[p]][p]);
					p = parent[p];
				}
				p = t;
				while ( parent[p] != -1 ) {
					flow[parent[p]][p] += value;
					flow[p][parent[p]] -= value;
					p = parent[p];
				}
				return true;
			}
		}
	}
	return false;
}

int  N, Q;
bool A[maxn][26] = {false};
char line[1000005];

vector <char> crunch(string s) {
	vector <char> ret;
	REP(i,s.size()) if ( 'A' <= s[i] && s[i] <= 'Z' ) ret.push_back(s[i]);
	return ret;
}

int main(int argc, char *argv[]) {
	
	scanf( "%d %d\n", &N, &Q );
	REP(i,N) {
		scanf( "%[^\n]\n", line );
		for ( auto &c : crunch(line) ) A[i][c-'A'] = true;
	}

	while ( Q-- ) {
		scanf( "%s", line );
		vector <char> v = crunch(line);
		int M = v.size();

		if ( M > N ) { puts( "NO" ); continue; }

		memset(cap,0,sizeof(cap));
		memset(flow,0,sizeof(flow));

		int s = 0, t = 26 + N + 1;
		REP(i,M) cap[s][v[i]-'A'+1]++;
		REP(i,N) cap[27+i][t] = 1;
		REP(i,N) REP(j,26) cap[1+j][27+i] = A[i][j];

		n = t + 1;
		int nflow = 0;
		while ( augment(s,t) ) nflow++;

		puts( nflow == M ? "YES" : "NO" );
	}

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0; i < s.size(); i++ ) {
        if ( delim.find(s[i]) == string::npos ) t += s[i];
        else if ( !t.empty() ) { res.push_back(t); t = ""; }
    }
    if ( !t.empty() ) res.push_back(t);
    return res;
}
vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

const int maxl = 10000000;
char line[10000005];
vector <int> v;

int p[100005], r[100005];
void link(int x, int y) {
	if ( r[x] == r[y] ) r[x]++;
	if ( r[x]  < r[y] ) p[x] = y; else p[y] = x;
}
int find(int x) {
	if ( p[x] != x ) p[x] = find(p[x]);
	return p[x];
}

int main(int argc, char *argv[]) {
	
	int N, Q;
	int x, y;
	int a, b, L, R;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 2);
	N = v[0];
	Q = v[1];
	assert(1 <= N && N <= 100000);
	assert(1 <= Q && Q <= 100000);

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == N);
	REP(i,N) assert(1 <= v[i] && v[i] <= 1000000000);

	bool used[100005] = {false};

	FOR(i,1,N) p[i] = i, r[i] = 0;
	REP(_,N-1) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 2);
		x = v[0];
		y = v[1];
		assert(1 <= x && x <= N);
		assert(1 <= y && y <= N);
		assert(x != y);
		assert(!used[y]);
		used[y] = true;
		link(find(x),find(y));
	}
	
	FOR(i,1,N) assert(find(1) == find(i));

	REP(_,Q) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 4);
		a = v[0];
		b = v[1];
		L = v[2];
		R = v[3];
		assert(1 <= a && a <= N);
		assert(1 <= b && b <= N);
		assert(0 <= L && L <= R && R <= 1000000000);
	}

	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}

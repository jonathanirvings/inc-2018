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

const int maxl = 1000000;
char line[1000005];
vector <int> v;
vector <string> w;

int main(int argc, char *argv[]) {
	
	int N, M;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 2);
	N = v[0];
	M = v[1];
	assert(1 <= N && N <= 20000);
	assert(0 <= M && M <= 20000);

	set <pair<int,int> > s;
	REP(_,M) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 2);
		int a = v[0];
		int b = v[1];
		assert(1 <= a && a < b && b <= N);
		assert(s.find(make_pair(a,b)) == s.end());
		s.insert(make_pair(a,b));
	}

	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}

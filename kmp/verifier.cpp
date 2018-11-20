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
vector <string> w;

int main(int argc, char *argv[]) {
	
	int N, Q;

	assert( fgets(line,maxl,stdin) != 0);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 2);
	N = v[0];
	Q = v[1];
	assert(1 <= N && N <= 50);
	assert(1 <= Q && Q <= 1000);

	int S = 0, T = 0;

	REP(_,N) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		w = split(line);
		int space = 0;
		REP(i,strlen(line)) space += line[i] == ' ' ? 1 : 0;
		assert(w.size() == space + 1);
		assert(line[strlen(line)-1] != ' ' );
		assert(line[0] != ' ' );
		REP(i,w.size()) {
			assert('A' <= w[i][0] && w[i][0] <= 'Z');
			FOR(j,1,w[i].size()-1)
				assert('a' <= w[i][j] && w[i][j] <= 'z');
			S += w[i].size();
		}
	}
	assert(1 <= S && S <= 1000000);


	REP(_,Q) {
		assert( fgets(line,maxl,stdin) != 0);
		line[strlen(line)-1] = 0;
		w = split(line);
		assert(w.size() == 1);
		string s = w[0];
		REP(i,s.size())
			assert('A' <= s[i] && s[i] <= 'Z');
		T += s.size();
	}
	assert(1 <= T && T <= 1000000);

	line[0] = 0;
	assert( fgets(line,maxl,stdin) == 0 );
	assert( line[0] == 0 );
	
	return 0;
}

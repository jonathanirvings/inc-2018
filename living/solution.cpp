#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )

const int maxn = 20005;
const int inf  = 0x7fffffff;

struct tnode { int id, deg; };
bool operator < ( const tnode &a, const tnode &b ) { return a.deg != b.deg ? a.deg < b.deg : a.id < b.id; }

int N, M;
set <int> s[maxn];
vector <int> con[maxn];

int flag[maxn] = {0};
int dist[maxn];

int find_cycle(int start, int mx) {
	int ret = inf;
	queue <int> q;
	dist[start] = 0;
	flag[start] = start;
	q.push(start);
	q.push(start);
	while ( !q.empty() ) {
		int cur = q.front(); q.pop();
		int par = q.front(); q.pop();
		if ( dist[cur] * 2 >= min(mx,ret) ) break;
		for ( auto &next : con[cur] ) if ( next != par ) {
			if ( flag[next] == start ) {
				ret = min(ret,dist[cur]+dist[next]+1);
			}
			else {
				dist[next] = dist[cur] + 1;
				flag[next] = start;
				q.push(next);
				q.push(cur);
			}
		}
	}
	return ret;
}

int n_node[maxn];
int n_edge[maxn];
int p[maxn], r[maxn];
void link(int x, int y) {
	if ( r[x] == r[y] ) r[x]++;
	if ( r[x]  < r[y] ) p[x] = y; else p[y] = x;
}
int find(int x) {
	if ( p[x] != x ) p[x] = find(p[x]);
	return p[x];
}

void go_flag(int cur, int par, bool flag[]) {
	if ( flag[cur] ) return;
	flag[cur] = true;
	if ( con[cur].size() > 2 ) return;
	for ( auto &next : con[cur] ) if ( next != par )
		go_flag(next,cur,flag);
}

int degree[maxn];

vector <int> independent_set(vector <int> &non_tree) {
	priority_queue <tnode> pq;
	for ( auto &node : non_tree ) pq.push((tnode){node,degree[node]});
	vector <int> ret;
	bool flag[maxn] = {false};
	while ( !pq.empty() ) {
		tnode p = pq.top(); pq.pop();
		if ( flag[p.id] ) continue;
		ret.push_back(p.id);
		for ( auto &next : con[p.id] )
			go_flag(next,p.id,flag);
	}
	return ret;
}

int ceil_div(int a, int b) { return (a + b - 1) / b; }


int main(int argc, char *argv[]) {
	srand(time(0));

	scanf( "%d %d", &N, &M );
	REP(_,M) {
		int a, b;
		scanf( "%d %d", &a, &b );
		s[a].insert(b);
		s[b].insert(a);
	}

	set <tnode> pq;
	FOR(i,1,N) degree[i] = s[i].size();
	FOR(i,1,N) pq.insert((tnode){i,degree[i]});
	while ( !pq.empty() ) {
		tnode p = *(pq.begin());
		pq.erase(p);
		if ( p.deg  > 1 ) break;
		if ( p.deg == 0 ) continue;
		int next = *(s[p.id].begin());
		pq.erase((tnode){next,degree[next]});
		s[p.id].erase(next);
		s[next].erase(p.id);
		degree[p.id]--;
		degree[next]--;
		pq.insert((tnode){next,degree[next]});
	}
	FOR(i,1,N) for ( auto &p : s[i] ) con[i].push_back(p);


	FOR(i,1,N) p[i] = i, r[i] = 0;
	FOR(i,1,N) n_edge[i] = 0;;
	FOR(i,1,N) n_node[i] = 1;
	FOR(i,1,N) for ( auto &next : con[i] ) if ( i < next ) {
		if ( find(i) != find(next) ) {
			int a = find(i);
			int b = find(next);
			link(find(i),find(next));
			n_edge[find(i)] = n_edge[a] + n_edge[b];
			n_node[find(i)] = n_node[a] + n_node[b];
		}
		n_edge[find(i)]++;
	}

	vector <int> non_tree;
	FOR(i,1,N) if ( n_node[find(i)] <= n_edge[find(i)] )
		non_tree.push_back(i);

	vector <int> observe_node = independent_set(non_tree);

	random_shuffle(observe_node.begin(),observe_node.end());

	int ans = inf;
	for ( auto &node : observe_node )
		ans = min(ans,find_cycle(node,ans));

	printf( "%d\n", ans == inf ? -1 : ans );

	return 0;
}

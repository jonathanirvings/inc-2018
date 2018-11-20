//start of jonathanirvings' template v3.0.3 (BETA)

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef pair<string,string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

#ifdef TESTING
  #define DEBUG fprintf(stderr,"====TESTING====\n")
  #define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define DEBUG 
  #define VALUE(x)
  #define debug(...)
#endif

#define FOR(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define FORN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define FORD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define FORSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define FORC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define FOREACH(a,b) for (auto &(a) : (b))
#define REP(i,n) FOR(i,0,n)
#define REPN(i,n) FORN(i,1,n)
#define MAX(a,b) a = max(a,b)
#define MIN(a,b) a = min(a,b)
#define SQR(x) ((LL)(x) * (x))
#define RESET(a,b) memset(a,b,sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define TC(t) while(t--)

inline string IntToString(LL a){
  char x[100];
  sprintf(x,"%lld",a); string s = x;
  return s;
}

inline LL StringToInt(string a){
  char x[100]; LL res;
  strcpy(x,a.c_str()); sscanf(x,"%lld",&res);
  return res;
}

inline string GetString(void){
  char x[1000005];
  scanf("%s",x); string s = x;
  return s;
}

inline string uppercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
  return s;
}

inline string lowercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return s;
}

inline void OPEN (string s) {
  #ifndef TESTING
  freopen ((s + ".in").c_str (), "r", stdin);
  freopen ((s + ".out").c_str (), "w", stdout);
  #endif
}

//end of jonathanirvings' template v3.0.3 (BETA)

struct Node {
  Node* l;
  Node* r;
  LL val;
  
  Node(Node* _l, Node* _r, LL _val)
  {
    l = _l; r = _r;
    val = _val;
  }
};

const int MAXN = 100000;
int n,q;

int angka[MAXN + 5];
int h[MAXN + 5];
int x,y,L,R;
vi adj[MAXN + 5];
vi compress;
unordered_map<int,int> ix;
Node* superroot;
Node* root[MAXN + 5];
int parent[20][MAXN + 5];

Node* build(int ix,int L,int R)
{
  if (L == R) return new Node(NULL,NULL,0);
  int M = (L + R) >> 1;
  return new Node(build(ix*2+1,L,M),build(ix*2+2,M+1,R),0);
}

Node* build(int ix, int L, int R, int pos, LL add, Node* pre)
{
  if (pos < L || pos > R) return pre;
  if (L == R) return new Node(NULL,NULL,pre->val + add);
  int M = (L + R) >> 1;
  Node* now = new Node(NULL, NULL, 0);
  now->l = build(ix*2+1,L,M,pos,add,pre->l);
  now->r = build(ix*2+2,M+1,R,pos,add,pre->r);
  now->val = now->l->val + now->r->val;
  return now;
}

LL query(int ix,int L,int R,int x,int y,Node *now)
{
  if (x <= L && R <= y) return now->val;
  if (y < L || R < x) return 0;
  int M = (L + R) >> 1;
  return query(ix*2+1,L,M,x,y,now->l) + query(ix*2+2,M+1,R,x,y,now->r);
}

void dfs(int now)
{
  Node* pre = (now == 0 ? superroot : root[parent[0][now]]);
  root[now] = build(0,0,SIZE(compress)-1,ix[angka[now]],angka[now],pre);
  REP(i,SIZE(adj[now])) if (adj[now][i] != parent[0][now])
  {
    parent[0][adj[now][i]] = now;
    h[adj[now][i]] = h[now] + 1;
    dfs(adj[now][i]);
  }
}

int LCA(int x,int y)
{
  if (h[x] < h[y]) swap(x,y);
  FORD(i,19,0)
  {
    if (h[parent[i][x]] >= h[y]) x = parent[i][x];
  }
  if (x == y) return x;
  FORD(i,19,0)
  {
    if (parent[i][x] != parent[i][y])
    {
      x = parent[i][x];
      y = parent[i][y];
    }
  }
  return parent[0][x];
}

int main()
{
  scanf("%d %d",&n,&q);
  REP(i,n)
  {
    scanf("%d",&angka[i]);
    compress.pb(angka[i]);
  }
  SORT(compress);
  compress.erase(unique(ALL(compress)),compress.end());
  REP(i,SIZE(compress)) ix[compress[i]] = i;
  REP(i,n-1)
  {
    scanf("%d %d",&x,&y);
    --x; --y;
    adj[x].pb(y);
    adj[y].pb(x);
  }
  superroot = build(0,0,SIZE(compress)-1);
  dfs(0);
  FOR(i,1,20) REP(j,n) parent[i][j] = parent[i-1][parent[i-1][j]];
  TC(q)
  {
    scanf("%d %d %d %d",&x,&y,&L,&R);
    --x; --y;
    int l = lower_bound(ALL(compress),L) - compress.begin();
    int r = upper_bound(ALL(compress),R) - compress.begin() - 1;
    if (l > r)
    {
      puts("0");
      continue;
    }
    int z = LCA(x,y);
    LL risan = query(0,0,SIZE(compress)-1,l,r,root[x])
             + query(0,0,SIZE(compress)-1,l,r,root[y])
             - 2 * query(0,0,SIZE(compress)-1,l,r,root[z])
             + ((L <= angka[z] && angka[z] <= R) ? angka[z] : 0);
    printf("%lld\n",risan);
  }
  return 0;
}

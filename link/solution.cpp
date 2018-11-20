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
  int val;
  int version;
  Node* nxt;
  Node* nxtact;
  Node* pre;
  Node* preact;

  Node(int _val)
  {
    val = _val;
    version = 1;
    nxt = nxtact = pre = preact = NULL;
  }

  Node(int _val, int _version)
  {
    val = _val;
    version = _version;
    nxt = nxtact = pre = preact = NULL; 
  }
};

const int MAXN = 100000;

int n,q;
pii data[MAXN + 5];
Node* last[MAXN + 5];
int version[MAXN + 5];
Node* head;
Node* tail;
int tree[10 * MAXN + 5];
vi pos[MAXN + 5];
int current[MAXN + 5];

void print()
{
  debug("LINKED LIST\n");
  Node* now = head;
  while (now != tail)
  {
    debug("(%d, %d) -> ", now->val, now->version);
    now = now->nxt;
  }
  debug("============\n");
}

void printact()
{
  debug("ACTUAL LINKED LIST\n");
  Node* now = head;
  while (now != tail)
  {
    debug("(%d, %d) -> ", now->val, now->version);
    now = now->nxtact;
  }
  debug("============\n");
}

void update(int ix,int L,int R,int pos,int val)
{
  if (L == R) 
  {
    tree[ix] = val;
    return;
  }
  int M = (L + R) >> 1;
  if (pos <= M) update(ix*2+1,L,M,pos,val);
  else update(ix*2+2,M+1,R,pos,val);
  tree[ix] = tree[ix*2+1] + tree[ix*2+2];
}

int query(int ix,int L,int R,int x,int y)
{
  if (x <= L && R <= y) return tree[ix];
  if (y < L || R < x) return 0;
  int M = (L + R) >> 1;
  return query(ix*2+1,L,M,x,y) + query(ix*2+2,M+1,R,x,y);
}

int main()
{
  scanf("%d %d",&n,&q);
  REP(i,n)
  {
    last[i] = new Node(i);
    version[i] = 1;
  }
  head = new Node(-1); tail = new Node(-1);
  FORN(i,0,n-2) last[i]->nxt = last[i]->nxtact = last[i+1];
  last[n-1]->nxt = last[n-1]->nxtact = tail;
  FORD(i,n-1,1) last[i]->pre = last[i]->preact = last[i-1];
  last[0]->pre = last[0]->preact = head;
  head->nxt = head->nxtact = last[0];
  tail->pre = tail->preact = last[n-1];

  REP(i,q) 
  {
    scanf("%d %d",&data[i].fi,&data[i].se);
    --data[i].fi; --data[i].se;
    
    last[data[i].fi]->pre->nxt = last[data[i].fi]->nxt;
    last[data[i].fi]->nxt->pre = last[data[i].fi]->pre;

    Node* nw = new Node(data[i].fi,last[data[i].fi]->version + 1);
    if (last[data[i].se]->nxt == last[data[i].se]->nxtact)
    {
      Node* a = last[data[i].se];
      Node* b = last[data[i].se]->nxt;
      
      a->nxt = a->nxtact = nw;
      nw->pre = nw->preact = a;

      b->pre = b->preact = nw;
      nw->nxt = nw->nxtact = b;
    } else 
    {
      Node* a = last[data[i].se];
      Node* b = last[data[i].se]->nxt;
      Node* c = b->preact;
      // a ....... c nw b

      a->nxt = nw;
      c->nxtact = nw;
      nw->pre = a;
      nw->preact = c;

      b->pre = b->preact = nw;
      nw->nxt = nw->nxtact = b;
    }
    last[data[i].fi] = nw;
  }
  REP(i,n) pos[i].resize(last[i]->version);
  int m = 0;
  Node* now = head->nxtact;
  while (now != tail)
  {
    pos[now->val][now->version - 1] = m;
    ++m;
    now = now->nxtact;
  }
  // REP(i,n)
  // {
  //   debug("%d :",i);
  //   REP(j,SIZE(pos[i])) debug(" %d",pos[i][j]);
  //   debug("\n");
  // }
  REP(i,n) update(0,0,m-1,pos[i][current[i]],1);
  REP(i,q)
  {
    int a = pos[data[i].fi][current[data[i].fi]];
    int b = pos[data[i].fi][current[data[i].fi]+1];
    if (b < a)
    {
      printf("%d\n",-query(0,0,m-1,b,a)+1);
    } else
    {
      printf("%d\n",query(0,0,m-1,a,b)-1);
    }
    update(0,0,m-1,a,0);
    ++current[data[i].fi];
    update(0,0,m-1,b,1);
  }

  bool dah = 0;
  now = head->nxt;
  while (now != tail)
  {
    if (dah) printf(" ");
    dah = 1;
    printf("%d",now->val + 1);
    now = now->nxt;
  }
  puts("");
  return 0;
}










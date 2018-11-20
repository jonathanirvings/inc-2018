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

const int MAXN = 100000;

int n, s;
LL L[MAXN + 5], R[MAXN + 5];

LL greedy(int l,int r)
{
  LL cost = 0;
  FORN(i,l,r) cost += min(L[i],R[i]);
  return cost;
}

LL greedyWithout(set<int> x)
{
  LL cost = 0;
  REP(i,n) if(!x.count(i)) cost += min(L[i],R[i]);
  return cost;
}

pair<LL,int> greedyAtLeastSatu(int l, int r, int x, int y)
{
  // left -> x = -1
  // right -> x = 1

  // ambil yang paling besar -> y = 1
  // ambil yang paling kecil -> y = -1
  LL cost = 0;
  FORN(i,l,r) cost += min(L[i],R[i]);
  pair<LL,int> ret = mp(INFF,0);
  FORN(i,l,r)
  {
    if (x == -1)
      MIN(ret,mp(cost - min(L[i],R[i]) + L[i], y == 1 ? -i : i));
    else
      MIN(ret,mp(cost - min(L[i],R[i]) + R[i], y == 1 ? -i : i));
  }
  return mp(ret.fi, y == 1 ? -ret.se : ret.se);
}

LL calc(const vector<int> &order) {
  LL cost = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (order[i + 1] > order[i]) {
      cost += R[order[i]];
    } else {
      cost += L[order[i]];
    }
  }
  cost += min(L[order[n - 1]], R[order[n - 1]]);
  return cost;
}

vi min(vi a, vi b)
{
  return calc(a) <= calc(b) ? a : b;
}

void print(vi v)
{
  REP(i,SIZE(v)) debug("%d ",v[i]); debug("\n");
}

int main()
{
  scanf("%d %d",&n,&s);
  --s;
  REP(i,n)
  {
    scanf("%lld %lld",&L[i],&R[i]);
  }
  if (n == 1)
  {
    puts("1");
    return 0;
  }
  if (n == 2)
  {
    if (s == 0) puts("1 2");
    else puts("2 1");
    return 0;
  }
  vi risan;
  if (s == 0)
  {
    LL cost1 = R[0] + L[n - 1] + greedyWithout({0, n - 1});
    LL cost2 = R[0] + R[1] + greedyWithout({0, 1});
    if (cost1 <= cost2)
    {
      risan.pb(0);
      FORN(i,1,n-2) if(R[i] <= L[i]) risan.pb(i);
      risan.pb(n-1);
      FORD(i,n-2,1) if(R[i] > L[i]) risan.pb(i);
    } else 
    {
      risan.pb(0);
      FORD(i,n-1,2) if(R[i] > L[i]) risan.pb(i);
      risan.pb(1);
      FORN(i,2,n-1) if(R[i] <= L[i]) risan.pb(i);
    }
  } else if (s == n - 1)
  {
    LL cost1 = R[0] + L[n - 1] + greedyWithout({0, n - 1});
    LL cost2 = L[n - 2] + L[n - 1] + greedyWithout({n - 2, n - 1});
    if (cost1 <= cost2)
    {
      risan.pb(n-1);
      FORD(i,n-2,1) if(L[i] <= R[i]) risan.pb(i);
      risan.pb(0);
      FORN(i,1,n-2) if(L[i] > R[i]) risan.pb(i);
    } else 
    {
      risan.pb(n-1);
      FORN(i,0,n-3) if(L[i] > R[i]) risan.pb(i);
      risan.pb(n-2);
      FORD(i,n-3,0) if(L[i] <= R[i]) risan.pb(i);
    }
  } else 
  {
    vi kanan;
    FORN(tries,0,1)
    {
      // pertama kanan
      vi kanan_1, kanan_2;
      // paling kanan <-
      {
        LL cost1 = R[0] + R[s] + L[n - 1] + greedyWithout({0, s, n - 1});
        LL cost2 = L[s - 1] + R[s] + L[n - 1] + greedyWithout({s - 1, s, n - 1});
        LL cost3 = greedy(0,s-1) + R[s] + L[n - 1] + greedyAtLeastSatu(s+1,n-2,-1,1).fi;
        LL opt = min(min(cost1,cost2),cost3);
        if (opt == cost1 || opt == cost2)
        {
          kanan_1.pb(s);
          FORN(i,s+1,n-2) if(R[i] <= L[i]) kanan_1.pb(i);
          kanan_1.pb(n-1);
          FORD(i,n-2,s+1) if(R[i] > L[i]) kanan_1.pb(i);
          if (opt == cost1)
          {
            FORD(i,s-1,1) if(L[i] <= R[i]) kanan_1.pb(i);
            kanan_1.pb(0);
            FORN(i,1,s-1) if(L[i] > R[i]) kanan_1.pb(i);
          } else
          {
            FORN(i,0,s-2) if(R[i] <= L[i]) kanan_1.pb(i);
            kanan_1.pb(s-1);
            FORD(i,s-2,0) if(R[i] > L[i]) kanan_1.pb(i);
          }
        } else
        {
          int turning_point = greedyAtLeastSatu(s+1,n-2,-1,1).se;
          kanan_1.pb(s);
          kanan_1.pb(turning_point);
          FORN(i,1,n-2)
          {
            if (i == s || i == turning_point) continue;
            if (R[i] <= L[i]) kanan_1.pb(i);
          }
          kanan_1.pb(n - 1);
          FORD(i,n-2,1)
          {
            if (i == s || i == turning_point) continue;
            if (R[i] > L[i]) kanan_1.pb(i);
          }
          kanan_1.pb(0);
        }
      }
      // paling kanan ->
      if (s < n - 2)
      {
        int turning_point = greedyAtLeastSatu(s+1,n-2,-1,1).se;
        kanan_2.pb(s);
        kanan_2.pb(turning_point);
        FORD(i,turning_point-1,s+1) if(L[i] <= R[i]) kanan_2.pb(i);
        FORD(i,s-1,1) if(L[i] <= R[i]) kanan_2.pb(i);
        kanan_2.pb(0);
        FORN(i,1,n-2)
        {
          if (i == s || i == turning_point) continue;
          if (L[i] > R[i]) kanan_2.pb(i);
        }
        kanan_2.pb(n-1);
        kanan = min(kanan_1, kanan_2);
      } else 
      {
        kanan = kanan_1;
      }

      s = n - 1 - s;
      reverse(ALLA(L,n));
      reverse(ALLA(R,n));
      REP(i,n) swap(L[i],R[i]);
      if (tries == 0)
      {
        risan = kanan;
      } else 
      {
        REP(i,n) kanan[i] = n - 1 - kanan[i];
        risan = min(risan, kanan);
      }
    }
  }
  REP(i,n)
  {
    if (i > 0) printf(" ");
    printf("%d",risan[i] + 1);
  }
  puts("");
  return 0;
}

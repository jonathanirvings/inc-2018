
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

#ifdef __DEBUG
#define debug if (true)
#else
#define debug if (false)
#endif

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

// ax + by = gcd(a, b)
template <typename T>
T ext_gcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T xx, yy, g = ext_gcd(b, a % b, xx, yy);
  x = yy;
  y = xx - yy * (a / b);
  return g;
}

template<int MOD>
struct ModInt {
 public:
  using sum_type = int;
  using prod_type = long long;

  static_assert(MOD > 0, "MOD should be positive");
  static_assert(MOD <= numeric_limits<sum_type>::max() - MOD, "Plus should not overflow");
  static_assert(MOD <= numeric_limits<prod_type>::max() / MOD, "Multiply should not overflow");

  struct good_val {};

  ModInt() : val_(0) {}

  ModInt(int val) : val_(val % MOD) { fix(op_neg{}); }

  ModInt(ll val) : val_(val % MOD) { fix(op_neg{}); }

  ModInt(int val, good_val) : val_(val) {
#ifdef __DEBUG
    assert(val >= 0 && val_ < MOD);
#endif
  }

  ModInt& operator+=(const ModInt &o) { val_ += o.val_; fix(op_pos{}); return *this; }
  ModInt& operator-=(const ModInt &o) { val_ -= o.val_; fix(op_neg{}); return *this; }
  ModInt& operator*=(const ModInt &o) { val_ = static_cast<prod_type>(1) * val_ * o.val_ % MOD; return *this; }
  ModInt& operator/=(const ModInt &o) { return operator*=(o.inverse()); }

  friend ModInt operator+(ModInt a, const ModInt &b) { a += b; return a; }
  friend ModInt operator-(ModInt a, const ModInt &b) { a -= b; return a; }
  friend ModInt operator*(ModInt a, const ModInt &b) { a *= b; return a; }
  friend ModInt operator/(ModInt a, const ModInt &b) { a /= b; return a; }

  ModInt inverse() const {
    prod_type a, b, g = ext_gcd<prod_type>(val_, MOD, a, b);
    if (g != 1) {
      throw;
    }
    debug assert(((*this) * a).val_ == 1);
    return ModInt(a);
  }

  sum_type get() const { return val_; }

 private:
  sum_type val_;
  struct op_neg {};
  struct op_pos {};

  void fix(op_neg) { if (val_ < 0) val_ += MOD; }
  void fix(op_pos) { if (val_ >= MOD) val_ -= MOD; }
};

constexpr int MOD = 1e9 + 7;

using Int = ModInt<MOD>;

int brute(int n, vi a) {
  Int ans = 0;
  vi perm(n);
  iota(ALL(perm), 1);
  vi b;
  do {
    b = a;
    for (int i : perm) {
      for (int j = i; j <= n; j += i) {
        b[j - 1] = 0;
      }
      ans += accumulate(ALL(b), 0);
    }
  } while (next_permutation(ALL(perm)));
  Int fact = 1;
  for (int i = 1; i <= n; i++) {
    fact *= i;
  }
  debug cout << "? " << ans.get() << " " << (1 / fact).get() << endl;
  ans /= fact;
  return ans.get();
}

const int N = 1e5 + 5;

Int fact[N], inv[N];
Int pre[300];
int divCount[N];
unordered_map<int, Int> memo;

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = fact[i - 1] * i;
  }
  inv[N - 1] = 1 / fact[N - 1];
  for (int i = N - 2; i >= 0; i--) {
    inv[i] = inv[i + 1] * (i + 1);
  }
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divCount[j]++;
    }
  }
}

Int P(int n, int k) {
  return fact[n] * inv[n - k];
}

Int calc(int n, int k) {
  Int res = 0;
  for (int i = 1; i <= n - k + 1; i++) {
    res += P(n - k, i - 1) * k * fact[n - i] * (i - 1);
  }
  return res;
}

int solve2(int n, vi b) {
  memo.clear();
  Int ans = 0;
  for (int i = 0; i < n; i++) {
    if (memo.find(divCount[i + 1]) == end(memo)) {
      memo[divCount[i + 1]] = calc(n, divCount[i + 1]);
    }
    ans += memo[divCount[i + 1]] * b[i];
  }
  debug cout << "! " << ans.get() << " " << inv[n].get() << endl;
  return (ans * inv[n]).get();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  // int n = 5;
  // const int a[] = {4, 1, 2, 3, 4};
  // cout << brute(n, vi(a, a + n)) << endl;
  // cout << solve2(n, vi(a, a + n)) << endl;
  int n;
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  cout << solve2(n, a) << endl;
  return 0;
}

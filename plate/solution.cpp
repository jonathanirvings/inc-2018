#include <bits/stdc++.h>
#define REP(i,n) for (int i = 0; i < n; i++)

using namespace std;
using ll = long long;

ll A, B;

// dp[n][is_lower][last_parity]
ll dp[20][2][2];

ll solve(ll X) {
    vector<int> digits;
    for (ll x = X; x; x /= 10) {
        digits.push_back(x % 10);
    }
    reverse(digits.begin(), digits.end());
    int N = digits.size();

    memset(dp, 0, sizeof dp);
    dp[0][0][1] = 1;
    REP(i, N) REP(j, 2) REP(k, 2) {
        int max_digit = j ? 9 : digits[i];
        REP(d, max_digit+1) {
            int next_j = j || (d < digits[i]);
            int next_k = (d == 0) ? k : d%2;
            dp[i+1][next_j][next_k] += dp[i][j][k];
        }
    }
    return dp[N][0][0] + dp[N][1][0];
}

int main() {
    cin >> A >> B;
    ll even = solve(B) - solve(A-1);
    ll odd = B-A+1-even;
    cout << odd << " " << even << endl;
}

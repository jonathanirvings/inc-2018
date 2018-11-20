#include <bits/stdc++.h>
using namespace std;

int wa(int status = 0) {
  cout << "WA" << endl;
  cerr << status << endl;
  return 0;
}

int ac() {
  cout << "AC" << endl;
  return 0;
}

bool valid(int N, int S, vector<int> order) {
  if (order.size() != N) {
    return false;
  }
  if (order[0] != S) {
    return false;
  }
  
  sort(order.begin(), order.end());
  order.erase(unique(order.begin(), order.end()), order.end());
  return order.size() == N && order[0] == 1 && order[N - 1] == N;
}

long long calculate(int N, int S,
                    const vector<int> &L,
                    const vector<int> &R,
                    const vector<int> &order) {
  long long cost = 0;
  for (int i = 0; i < N - 1; ++i) {
    if (order[i + 1] > order[i]) {
      cost += R[order[i] - 1];
    } else {
      cost += L[order[i] - 1];
    }
  }
  cost += min(L[order[N - 1] - 1], R[order[N - 1] - 1]);
  return cost;
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  int N, S;
  tc_in >> N >> S;

  vector<int> L(N), R(N);
  for (int i = 0; i < N; ++i) {
    tc_in >> L[i] >> R[i];
  }
  
  vector<int> out(N);
  for (int i = 0; i < N; ++i) {
    tc_out >> out[i];
  }

  vector<int> con(N);
  for (int i = 0; i < N; ++i) {
    if (!(con_out >> con[i])) {
      return wa(1);
    }
  }

  int temp;
  if (con_out >> temp) {
    return wa(2);
  }
  if (!valid(N, S, con)) {
    return wa(3);
  }
  assert(calculate(N, S, L, R, out) <= calculate(N, S, L, R, con));
  return calculate(N, S, L, R, out) == calculate(N, S, L, R, con) ? ac() : wa(4);
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  return checks(strcmp(argv[1], "-") == 0 ? cin : tc_in,
                strcmp(argv[2], "-") == 0 ? cin : tc_out,
                strcmp(argv[3], "-") == 0 ? cin : con_out);
}

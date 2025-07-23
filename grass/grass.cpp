#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
#include <cstdio>

#define MAXN 100010

using namespace std;

vector<vector<int> > collapse(const vector<vector<int> >& E,
                              const vector<int>& L) {
  int N = E.size();
  vector<vector<int> > R(*max_element(L.begin(), L.end()) + 1, vector<int>());
  for(int i = 0; i < N; i++) {
    int x = L[i];
    for(int j = 0; j < E[i].size(); j++) {
      int y = L[E[i][j]];
      if(x != y) R[x].push_back(y);
    }
  }
  for(int i = 0; i < R.size(); i++) {
    sort(R[i].begin(), R[i].end());
    R[i].resize(unique(R[i].begin(), R[i].end()) - R[i].begin());
  }
  return R;
}

int scc_nidx;
int scc_idx[MAXN];
int scc_lnk[MAXN];

int scc_lbl;
int scc_sp;
int scc_stk[MAXN];
void scc_dfs(int u, const vector<vector<int> >& E, vector<int>& L) {
  int idx = scc_idx[u] = scc_nidx++;
  int& lnk = scc_lnk[u];
  lnk = idx;

  scc_stk[scc_sp++] = u;
  for(int i = 0; i < E[u].size(); i++) {
    int v = E[u][i];
    if(scc_idx[v] == -1) {
      scc_dfs(v, E, L);
      lnk = min(lnk, scc_lnk[v]);
    } else {
      lnk = min(lnk, scc_idx[v]);
    }
  }

  if(idx == lnk) {
    for(int y = -1; y != u; ) {
      y = scc_stk[--scc_sp];
      scc_idx[y] = E.size();
      L[y] = scc_lbl;
    }
    scc_lbl++;
  }
}
vector<int> scc(const vector<vector<int> >& E) {
  int N = E.size();
  vector<int> L(N, -1);

  memset(scc_idx, -1, sizeof(int) * N);
  scc_nidx = scc_lbl = scc_sp = 0;
  for(int i = 0; i < N; i++) {
    if(L[i] == -1) {
      scc_dfs(i, E, L);
    }
  }
  return L;
}

int memo[2][100010];
int solve(int cid, const vector<int>& W,
          const vector<vector<int> >& E, int s, int t) {
  if (s == t) {
    return 0;
  }

  int& ref = memo[cid][s];
  if (ref != -1) {
    return ref;
  }

  ref = -2;
  for (int i = 0; i < E[s].size(); i++) {
    int res = solve(cid, W, E, E[s][i], t);
    if (res >= 0) {
      ref = max(ref, W[s] + res);
    }
  }
  return ref;
}

int main() {
  freopen("grass.in", "r", stdin);  
  freopen("grass.out", "w", stdout);
  int N, M;
  cin >> N >> M;

  vector<vector<int> > E(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    E[u].push_back(v);
  }
  vector<int> L = scc(E);
  E = collapse(E, L);
  int st = L[0];

  vector<vector<int> > RE(E.size());
  for (int i = 0; i < E.size(); i++) {
    for (int j = 0; j < E[i].size(); j++) {
      RE[E[i][j]].push_back(i);
    }
  }
  vector<int> W(E.size(), 0);
  for (int i = 0; i < N; i++) {
    W[L[i]]++;
  }
  int result = W[st];
  memset(memo, -1, sizeof(memo));
  for (int i = 0; i < E.size(); i++) {
    int r1 = solve(0, W, E, i, st);
    if (r1 < 0) {
      continue;
    }
    for (int j = 0; j < E[i].size(); j++) {
      int r2 = solve(1, W, RE, E[i][j], st);
      if (r2 >= 0) {
        result = max(result, W[st] + r1 + r2);
      }
    }
  }
  cout << result << '\n';
}
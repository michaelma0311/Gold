#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N,K;
ll M;
int A[200001],B[200001]; //input
int P[100001]; //as described in analysis
int from[100001]; //from[i] = where the cow in position i originated from
vector<pair<int,int>>S[100001]; //as described in analysis, stores {pos, time}
int cnt[100001]; //array to keep track of uniquePos
int uniquePos; //# of unique reachable positions

//adds in all reachable positions from S_node where time<=bar
void add(int node, int bar){
  for (auto x:S[node]){
    if (x.second>bar) return;
    if (cnt[x.first]==0)
      uniquePos++;
    cnt[x.first]++;
  }
}

//removes all reachable positions from S_node where time<=bar
void remove(int node, int bar){
  for (auto x:S[node]){
    if (x.second>bar) return;
    if (cnt[x.first]==1)
      uniquePos--;
    cnt[x.first]--;
  }
}

vector<int>nodes; //stores nodes currently in cycle
bool vis[100001];

void dfs(int node){
  vis[node]=true;
  nodes.push_back(node);
  if (!vis[P[node]])
    dfs(P[node]);
}

int main(){
  cin>>N>>K>>M;
  for (int i=0;i<K;i++)
    cin>>A[i]>>B[i];
  for (int i=1;i<=N;i++){
    from[i]=i;
    S[i].push_back({i,0});
  }
  for (int i=0;i<K;i++){
    S[from[A[i]]].push_back({B[i],i+1});
    S[from[B[i]]].push_back({A[i],i+1});
    swap(from[A[i]],from[B[i]]);
  }
  for (int i=1;i<=N;i++)
    P[from[i]]=i;
  int ans[100001];
  for (int i=1;i<=N;i++)
    if (!vis[i]){
      dfs(i);
      ll D=M/K; 
      int R=M%K; 

      if (D>=(int)nodes.size()){ 
	D=nodes.size();
	R=0;
      }
      int j=D-1;

      for (int k=0;k<=j;k++)
	add(nodes[k],K);

      for (int i=0;i<nodes.size();i++){
	int newJ=(j+1)%(int)nodes.size();

	add(nodes[newJ],R);

	ans[nodes[i]]=uniquePos;

	remove(nodes[newJ],R);

	remove(nodes[i],K);

	add(nodes[newJ],K);
	j=newJ;
      }

      for (int k=0;k<=D-1;k++)
	remove(nodes[k],K);
      nodes.clear();
    }
  for (int i=1;i<=N;i++)
    cout<<ans[i]<<endl;
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dfs(map<string, vector<string>>& adj , string n){
    if (n == "out") return 1;

    int ret = 0;
  for (auto& ng : adj[n]) {
    ret += dfs(adj, ng);
  }
  return ret;

}

void solve(){
    string l;
    map<string , vector<string>>adj; //build adj list and count the paths from start to goal
    //we build adj list to get a track of what nodes are edges connected to 
    while(getline(cin , l)){
        stringstream ls(l);

        string k , v;
        ls >> k;
    if (!k.empty() && k.back() == ':') {
    k.pop_back();  // remove ':'
        }

        adj.insert({k , vector<string>()});

        while(ls >> v)adj[k].push_back(v);
    }
    cout << dfs(adj, "you") << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt" , "r" , stdin);

    auto start = chrono::high_resolution_clock::now();
  solve();
  auto end = chrono::high_resolution_clock::now();
  double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  time_taken *= 1e-6;
  cout << "Time taken: " << fixed << time_taken << setprecision(9) << " millis" //this whole code is for calculating my runtime
       << '\n';

}
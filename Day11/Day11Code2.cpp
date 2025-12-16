#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<tuple<string, bool, bool>, ll> n_vis;
//we have to calculate no. of apths containing fft & dac
ll dfs(map<string, vector<string>>& adj,
       map<tuple<string, bool, bool>, ll>& dp,
       string& n, bool fft, bool dac) {

    if (n == "out")
        return (fft && dac) ? 1 : 0;

    tuple<string, bool, bool> state = {n, fft, dac};

    if (dp[state] != -1)
        return dp[state];

    if (n_vis[state] > 0)
        return 0;   // cycle protection

    n_vis[state]++;

    bool n_fft = fft || (n == "fft");
    bool n_dac = dac || (n == "dac");

    ll ret = 0;
    for (auto& ng : adj[n]) {
        ret += dfs(adj, dp, ng, n_fft, n_dac);
    }

    dp[state] = ret;
    return ret;
}


void solve(){
    //tuples store multiple types of values together so we use a tuple to track
    ///normal adj list making and inserting ipts
    string l;
    map<string , vector<string>>adj;

    while(getline(cin , l)){
        stringstream ls(l);
        string k , v;

        ls >> k;
        if (!k.empty() && k.back() == ':') {
    k.pop_back();  // remove ':'
        }
        
        adj.insert({k , vector<string>()});

        while(ls >> v) adj[k].push_back(v);
    }
    //next part making seen dac and fft

    map<tuple<string , bool , bool> , ll> dp; //memoization of dfs , key -> tuple of string , bool , bool and ll is number of valid paths from this state to out

    //init the dp table
    for(auto& [k , v] : adj)
        for(bool fft : {true , false})
        for(bool dac : {true , false})
        dp.insert({{k , fft , dac} , -1}); //init dp states for all values of k , f f , tf , ft , tt and init all as -1

    for (auto& [k, v] : adj)
  for (bool fft : {true, false})
    for (bool dac : {true, false})
      n_vis.insert({{k, fft, dac}, 0});
//start dfs
    string start = "svr";
  cout << dfs(adj, dp, start, false, false) << "\n";

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
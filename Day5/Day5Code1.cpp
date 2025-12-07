#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<ll,ll>> ranges;
    vector<ll> avl;

    ifstream file("input.txt");
    string input;

    while(getline(file, input)){
        if(input.empty()) continue;

        if(input.find('-') != string::npos){
            stringstream ss(input);
            ll a, b;
            char dash;
            ss >> a >> dash >> b;
            ranges.emplace_back(a, b);
        } else {
            avl.push_back(stoll(input));
        }
    }

    // // Sort intervals by start
    // sort(ranges.begin(), ranges.end());

    // ll cnt = 0;
    // //first use bianry search to jump to the range in which x is just less , then lower that index and search in pre 
    // for(ll x : avl){
    //     int idx = upper_bound(ranges.begin(), ranges.end(), make_pair(x, LLONG_MAX)) - ranges.begin(); //this line founds upper bound idx and make pair is used to keep moving
        
    //     if(idx > 0){
    //         idx--;
    //         auto [a, b] = ranges[idx];
    //         if(a <= x && x <= b) cnt++;
    //     }
    // } // no need to do all this shi

    // cout << cnt << endl;
    ll countFresh = 0;

    for (ll x : avl) {
        bool fresh = false;
        for (auto &r : ranges) {
            if (x >= r.first && x <= r.second) {
                fresh = true;
                break; // no need to check more ranges
            }
        }
        if (fresh) countFresh++;
    }

    cout << countFresh << "\n"; //just do basic approahc
    return 0;
}

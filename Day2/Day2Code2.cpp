#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


bool check(ll i){
    string s = to_string(i);
    int n = s.size();
    
    for(int len = 1; len <= n / 2; len++){
        if(n % len != 0) continue; //for the detection of possible lengths , we do this and keep checking at placess

        string p = s.substr(0 , len); //detect uss length ki substrs 
        bool ok = true;

        for(int j = len; j < n; j += len){
            if(s.substr(j , len) != p){ //now run the pointer and keep checking the  equal substrs and flag them 
                ok = false;
                break;
            }
        }
        if(ok) return true;
    } //return
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt");
    string input;

    if(file.is_open()){
        getline(file , input);
        file.close();
    }

    vector<pair<ll , ll>>ranges;
    stringstream ss(input);
    string token;

    while(getline(ss , token , ',')){
        ll start;
        ll end;

        auto dash = token.find('-');
        start = stoll(token.substr(0 , dash));
        end = stoll(token.substr(dash + 1));

        ranges.push_back({start , end});
    }

    ll sum = 0;
    for(auto& vec : ranges){
        ll st = vec.first;
        ll ed = vec.second;

        for(ll i = st; i <= ed; i++){
            if(check(i)){
                sum += i;
            }
        }
    }

    cout << "Sum is -> " << sum << endl;
    return 0;
}
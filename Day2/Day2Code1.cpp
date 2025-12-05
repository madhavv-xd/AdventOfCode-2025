#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(long long i){
    string s = to_string(i);
    int n = s.size();

    // If odd length, it cannot be split equally
    if(n % 2 != 0) return false;

    int j = n / 2;

    // Compare first half and second half
    return s.substr(0, j) == s.substr(j);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt"); // open input.txt file from the same directory
    string input; // full input string

    if (file.is_open()) { 
        getline(file, input); // read input from file
        file.close();
    } 


    vector<pair<ll, ll>> ranges; 
    stringstream ss(input); // turn the entire input string into a stream
    string token; // to store each range

    while (getline(ss, token, ',')) { // split based on ',' separator
        ll start;
        ll end; // start and end values of each range

        auto dash = token.find('-'); // find position of '-'
        start = stoll(token.substr(0, dash)); // extract the left number (start)
        end = stoll(token.substr(dash + 1)); // extract the right number (end)

        ranges.push_back({start, end}); // store the parsed range
    }

    ll sum = 0;

    for(auto& vec : ranges){
        ll st = vec.first;
        ll end = vec.second;

        for(ll i = st; i <= end; i++){  
            if(check(i)){
                sum += i;
            }
        }
    }

    cout << "Sum is -> " << sum << endl;

    return 0;
}

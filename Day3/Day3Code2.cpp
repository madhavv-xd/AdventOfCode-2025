#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checkando(vector<string>& vec){

    // ll result = 0;
    // //basically we have to first push them all digits in a vector first so that they all becomes digits and then
    // //we proceed to do operations on it
    // for(auto& bank : vec){
    //     vector<int>digits;
    //     for(char c : bank){
    //         digits.push_back(c - '0'); //pushed into the digits array
    //     }

    //     //now perform operations on it -> first one will be reverse sort to find the top 12 digits
    //     vector<int>sorted = digits;
    //     sort(sorted.begin() , sorted.end() , greater<int>());
    //     sorted.resize(12);

    //     //now we have to find a way to preserve the order 
    //     //using an hashmap first count how many digits are left in the sorted array , keep a track

    //     unordered_map<int , int>mp;
    //     for(int d : sorted) mp[d]++;

    //     //now build the final string
    //     string build = "";
    //     for(char c : bank){
    //         int d = c - '0';
    //         if(mp[d] > 0){
    //             build.push_back(c);
    //             mp[d]--; //empty the map by keep decreasing the frequency counts
    //         }
    //         if(build.size() == 12) break;
    //     }
    //      //finally append it into the result
    //     if(!build.empty()){
    //         result += stoll(build);
    //     }
    // }
    // return result; 
    //wrong approach -> doesnt consider the position importance

    //new approach -> monotonic stack (position matters)
    ll total = 0;

    for(auto& bank : vec){
        vector<char>st;
        int n = bank.size();
        int k = 12; //k are the exact elemens we have to choose 

        for(int i = 0;  i < n; i++){
            char c = bank[i];

            //basic monotonic stack implementation
            while(!st.empty() && st.back() < c && (st.size() - 1 + (n - i) >= k)){
                st.pop_back();
            }
            if(st.size() < k) st.push_back(c);
        }
        string chosen(st.begin() , st.end());
        total += stoll(chosen);
    }
    return total;
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string>vec;
    ifstream file("input.txt");
    string input;

    while(getline(file , input)){
        if(input.empty()) continue;

        vec.push_back(input);
    }

    ll result = checkando(vec);

    cout << "Final sum is -> " << result << endl;

}
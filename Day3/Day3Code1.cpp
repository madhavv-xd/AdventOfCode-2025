#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checkando(vector<string>& vec){
    ll total = 0;
    //basically we scan from right to left because we have to keep track and it's so better to know what's coming after
    //than before , the question is basically then pick a tens digit and append it with the maximum number from the back 
    //and then keep replacing the best one with it
    for(auto& bank : vec){
        int best = 0;
        int maxRight = -1;
        
        for(int i = bank.size() - 1; i >= 0; i--){
            int curr = bank[i] - '0';

            if(maxRight != -1){
                //keep updating , keep updating
                int cdt = curr * 10 + maxRight; //cdt * 10 to make it in tens digit , and how would we ensure that it's the biggest ?
                //update the best var with this 
                best = max(best , cdt); 
            }
            //in the end , update maxright after each go 
            maxRight = max(maxRight , curr);
        }
        //append the best in the total
        total += best;
    }
    return total;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string>vec; //make sure that vector is string since there are strings
    ifstream file("input.txt");
    string input;

    while(getline(file, input)){
        if(input.empty()) continue; //line by line input and push them back in the vector line by line
        vec.push_back(input);
    }

    ll result = checkando(vec);

    cout << "Final sum is -> " << result << endl;

    return 0;
}

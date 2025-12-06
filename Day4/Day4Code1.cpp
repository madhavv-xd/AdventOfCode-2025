#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checkanddo(vector<string>& grid){
    ll n = grid.size(); //row size
    ll m = grid[0].size(); //col size
    ll ans = 0; //to overall count the answer , num of paper rolls;

    
    vector<pair<int , int>>dirs = {
        {-1 , -1} , {-1 , 0} , {-1 , 1} , {0,1} ,{1 , 0} , {1 , -1} , {0 , -1} , {1 , 1}
    }; //a vector to maintain the positions adjacent to the main element 

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '@'){
                ll cnt = 0; //for counting adjacents
                for(auto& d : dirs){
                    int ni = i + d.first;
                    int nj = j + d.second; //add the positions and then check 

                    if(ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == '@'){ //edges 
                        cnt++;
                    }
                }
                if(cnt < 4) ans++; //condition
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt");
    string input;
    vector<string>grid;
    while(getline(file , input)){
        if(input.empty()) continue;

        grid.push_back(input);
    }

    ll result = checkanddo(grid);

    cout << "Final result is -> " << result << endl;
    return 0;
}
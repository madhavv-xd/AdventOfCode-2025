#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dfs(int r, int c, vector<vector<string>>& grid, vector<vector<ll>>& memo, ll rows, ll cols){
    //always the first step should be checking the out of bound / border cases 
    //horizontal one (for cols)
    if(c < 0 || c >= cols) return 1; //OOB so just return 1
    //vertical one(for rows);
    if(r + 1 >= rows) return 1;

    //dp steps after recursion -> declare a dp array ,  store results in dp arrayy and then return results from that array
    //step , memo returnign
    if(memo[r][c] != -1) return memo[r][c];

    ll ans = 0;
    if(grid[r+1][c] == "^"){
        //split left and right and explore
        ans += dfs(r + 1 , c - 1, grid , memo , rows , cols);
        ans += dfs(r+1 , c+ 1 , grid , memo , rows , cols); //left and right trav
    }
    else{
        //just continue downward , REMEMBER WE'RE DOING DFS , WHICH GOES IN DEPTH 
        ans = dfs(r+1  , c , grid , memo , rows , cols);
    }

    return memo[r][c] = ans;
}

ll checkanddo(vector<vector<string>>& grid , ll rows , ll cols){
    //mark the starting point , and start dfs from there 
    ll sr = -1; //starting row 
    ll sc = -1; //starting col 

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(grid[i][j] == "S"){
                //then marks starting row and starting col as i and j and pass them for dfsing and the dfsstart 
                sr = i;
                sc = j; //break the loop here
                break;
            }
        }
        if(sr != -1) break;
    }

    //make a memo vector for memoization to keep track
    vector<vector<ll>>memo(rows ,vector<ll>(cols , -1)); //first init all the col values as zeroes

    //dfs calling
    ll result = dfs(sr , sc , grid , memo , rows , cols);


    return result; //returnig the result
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt");
    string input;
    vector<vector<string>>grid;

    while(getline(file , input)){
        vector<string>row;
        
        // *** Only fix: read each character as a separate cell ***
        for(char c : input){
            row.push_back(string(1, c));
        }

        grid.push_back(row);
    }
    
    ll rows = grid.size();
    ll cols = grid[0].size();

    ll result = checkanddo(grid , rows , cols);

    cout << "Final result is -> " << result;
}

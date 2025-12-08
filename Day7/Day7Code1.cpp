#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checkanddo(vector<vector<string>>& grid , ll rows , ll cols){
    int result = 0; //increase result when the beam is split

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){ ///this is only one parsing  , we have to maintain a while loop to ensure that the code keeps running on that condition

            if(i + 1 < rows){ //when i == rows - 1, i+1 becomes rows, which is out of range
                
                // FIRST check split condition
                if(grid[i][j] == "|" && grid[i+1][j] == "^"){
                    if(j - 1 >= 0 ) grid[i+1][j-1] = "|"; //left me append 
                    if(j + 1 < cols) grid[i+1][j+1] = "|"; //right me append , appending in cols
                    result++;
                }

                // THEN handle normal propagation or start condition
                else if(grid[i][j] == "S" || (grid[i][j] == "|" && grid[i+1][j] != "^")){
                    grid[i + 1][j] = "|"; //starting point
                }
            }
        }
    }
    return result;

    //for simulations always prefer using while loops
    // bool changed = true;
    // while(changed){ //wrong approach turned out to be 
    //     changed = false;

    //     for(int i = 0; i < rows; i++){
    //         for(int j = 0; j < cols; j++){
    //             if(i+1 < rows){ //since row wise moving, check OOB conditon
    //                 if(grid[i][j] == "|" && grid[i+1][j] == "^"){
    //                     if(j - 1 >= 0 && grid[i+1][j-1] != "|") {
    //                         grid[i+1][j-1] = "|"; //left me append 
    //                         changed = true;
    //                     }
    //                     if(j + 1 < cols && grid[i+1][j+1] != "|") {
    //                         grid[i+1][j+1] = "|"; //right me append , appending in cols
    //                         changed = true;
    //                     }

    //                     result++;
    //                 }
    //                 else if(grid[i][j] == "S" || (grid[i][j] == "|" && grid[i+1][j] != "^")){
    //                     if(grid[i+1][j] != "|"){
    //                         grid[i + 1][j] = "|"; //starting point
    //                         changed = true;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // return result;
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

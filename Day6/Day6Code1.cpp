#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checkanddo(vector<vector<string>>& grid , ll rows , ll cols){
    ll totalSum = 0;

    // Loop column-wise: each column is a problem
    for(ll c = 0; c < cols; c++){
        vector<string> finals; //creating a new vector of cols inputs in each iteration

        for(ll r = 0; r < rows; r++){
            if(grid[r][c] != "") // ensure not empty (spaces in puzzle)
                finals.push_back(grid[r][c]);
        }

        string op = finals.back();
        finals.pop_back();

        // Now finals contains only numbers as strings
        ll result;

        if(op == "*"){
            result = 1;
            for(auto& val : finals){
                result *= stoll(val);
            }
        }
        else if(op == "+"){
            result = 0;
            for(auto& val : finals){
                result += stoll(val);
            }
        }
        else{
            continue; //skip the unknown symbols
        }

        totalSum += result;
    }

    return totalSum;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //we have to take inputs of number in a grid ex
    //for the inputs to be vertical just put them in the matrix , and we can take both outputs to be rows and cols
    ifstream file("input.txt");
    string input;
    vector<vector<string>>grid;
    //take inputs through a grid , we have to take verticla inputs 
    string line;

    while(getline(file , line)){
        stringstream ss(line);
        vector<string>row;
        string value;

        while(ss >> value){
            row.push_back(value);
        }
        grid.push_back(row);
    }
    ll rows = grid.size();
    ll cols = grid[0].size();

    ll result = checkanddo(grid , rows , cols);

    cout << "Final result is  -> " << result;

    return 0;
} 
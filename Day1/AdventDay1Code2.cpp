#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ifstream file("day1code1input.txt");

    if(!file){
        cout << "error loading the file day1code1input.txt";
        return 1;
    }

    vector<pair<char , int>> data;
    string line;

    while(getline(file , line)){
        if(line.empty()) continue;

        char dir = line[0];
        int value = stoi(line.substr(1));

        data.push_back({dir , value});
    }
    
    file.close();

    long long start = 1000000000 + 50; 
    int count = 0;

    for(auto& [dir , value] : data){

        for(int i = 0; i < value; i++){   //simulate each click
            if(dir == 'L'){
                start -= 1;
            }
            else{
                start += 1;
            }

            if(start % 100 == 0){
                count++;
            }
        }
    }

    cout << "Final count -> " << count << endl;
    return 0;
}

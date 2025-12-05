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

    int start = 50; //start at 50 , the dial starts at 50 
    int count = 0;

    for(auto& [dir , value] : data){
        if(dir == 'L'){
            start -= value; 
        }
        else if(dir == 'R'){
            start += value;
        }
        start = ((start % 100 + 100) % 100);

        if(start == 0){
            count++;
        }

    }

    cout << "final position" << start << endl;
    cout << "final position" << count << endl;
    return 0;
}

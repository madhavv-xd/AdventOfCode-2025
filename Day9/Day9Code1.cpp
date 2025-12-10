#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//make a struct for red tiles , this could be done without structs also but this is a good method 
struct RedTile{
    int x;
    int y; 
};

//find area 
long long findArea(RedTile a , RedTile b){
    long long x = abs(a.x - b.x) + 1;
    long long y = abs(a.y - b.y) + 1;

    //return area of rect 
    return x*y;
}

int main(){
    //take input
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt");
    string line;
    long long result = 0;

    //store redlines in a vector
    vector<RedTile>redTiles;
    int id = 0;
    while(getline(file , line)){
        RedTile redTile;
        //scan each redtile and push them into the vector
        stringstream ss(line);
        char comma;
        ss >> redTile.x >> comma >> redTile.y;
        redTiles.push_back(redTile); //pushed into the vector
    } 
    vector<long long> areas;
    //proceed finding areas normally 
    for(int i = 0; i < redTiles.size(); i++){
        for(int j = i + 1; j < redTiles.size(); j++){
            long long area = findArea(redTiles[i] , redTiles[j]);
            areas.push_back(area);
        }
    }
    //sort the areas and find the biggest 
    sort(areas.begin() , areas.end() , greater<long long>());

    result = areas[0];

    cout << "Final result is -> "<<result;
}
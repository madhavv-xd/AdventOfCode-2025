//This quesions uses DSU with distances between the battery that are helpful in making ckts 
//writing basic DSU template code first 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//basic template code of DSU data str -> and why is DSU used ?  DSU is used whenever you need to group elements and quickly check whether they are in the same group (set) or not — and update these groups dynamically.
struct UnionFind{ //making a union find ds struct 
    //1st -> a size and parent vector 
    vector<int>parent , size;

    UnionFind(int n){
        parent.resize(n);
        size.resize(n , 1); //init size with 1 and resize it n 
        for(int i = 0;  i < n; i++){
            parent[i] = i;
        }
    } //union find , So each element is its own leader/root at the beginning. init each element to the parent itself , this is the constructor 

    //finding func
    int find(int x){ //finding x , this returns the root / leader of the node to which x belongs
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]); //chain becomes flat 
    } //finding and optimisation -> for path compression 

    void unite(int x , int y){ //uniting both the ints , a union in set , DSU  is like a tree, not a LL;
        int rootX = find(x);
        int rootY = find(y);

        if(rootX == rootY) return;
        
        if(size[rootX] < size[rootY]){
            //X is smaller -> attach it beneath the Y
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else{
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
    int getSize(int x){
        int root = find(x);
        return size[root]; //returns size from the root
    }
};

struct JunctionBox{
    int x , y , z;
    int id; //x y z are the coordinates because it's in 3d and then each juncation box consists of an id 
};

struct Connection{
    //connection is happening between 2 juncboxes so we link with 2 ids and distance 
    int id1 , id2;
    long long distance;
};

long long findDistance(JunctionBox a , JunctionBox b){
    //find 3d distacne between the 2 boxes each 
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;


    return dx*dx + dy*dy + dz*dz; //3d distance between 2 jund boxes find
}

int main(){
//gotta connect 1000 pairs together
ios::sync_with_stdio(false);
cin.tie(nullptr);

ifstream file("input.txt");
string line;

int attempts = 1000; //1000 inputs are mentioned , 1000 lines are default given in the input only 
long long result = 1;

vector<JunctionBox> junctionBoxes;
int id = 0;
while(getline(file , line)){
    JunctionBox junctionBox; //make use of junction box struct 
    stringstream ss(line);
    char comma; //to read and ignore commas

    ss >> junctionBox.x >> comma >> junctionBox.y >> comma >> junctionBox.z;
    junctionBox.id = id++; //accessed x , y , z and id

    junctionBoxes.push_back(junctionBox);
} //inputted and stored the junction boxes into the vector 

//setup connections 
vector<Connection>connections;
//traverse and store into connections vector and then find distances between them -> shortesst so we gotta sort them first 
for(int i = 0;  i < junctionBoxes.size(); i++){
    for(int j = i+ 1; j < junctionBoxes.size(); j++){
        JunctionBox box1 = junctionBoxes[i];
        JunctionBox box2 = junctionBoxes[j]; //setup box1 and box2 with these constructs
        
        //init connection
        Connection connection;
        connection.id1 = box1.id;
        connection.id2 = box2.id;
        connection.distance = findDistance(box1 , box2);
        connections.push_back(connection);
    }
}
//pushed connections
//normal sorting will throw an error because we're iterating on the struct for custom types , normals like int and strings has built in operators 
sort(connections.begin(), connections.end(), 
    [](const Connection &a, const Connection &b) {
        return a.distance < b.distance;
});
 //sorting is done because , for minimum spanning tree bwe have to process the shorted connections first 
//sorted now gotta write the main code of union and finding dists and merging them 

//KRUSKAL'S application , study it first;
//first select connections using union find 
UnionFind UF(junctionBoxes.size()); //pass the number of junctionboxes here
//build the connection unions 
for(auto& connection : connections){
    if(attempts-- == 0){
        break;
    }
    //only connect if they are in diff groups , ensure there is no looping 
    int junctionBox1 = connection.id1;
      int junctionBox2 = connection.id2;

      if(UF.find(junctionBox1) != UF.find(junctionBox2))
     UF.unite(junctionBox1, junctionBox2); ///only unite those who are in diff grops
}
vector<int>cktSizes;
for(int i = 0;  i < junctionBoxes.size(); i++){
    int root = UF.find(i);
    if(root == i) cktSizes.push_back(UF.getSize(i)); //find the leader and returns the size of that group 
}

sort(cktSizes.begin(), cktSizes.end(), greater<int>());

   for(int i = 0; i < 3; i++)
 result *= cktSizes[i]; //now sort in ascending and mult top 3s

 cout << "Final result  is -> " << result;

}
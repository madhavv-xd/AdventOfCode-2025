#include <bits/stdc++.h>
using namespace std;

//make a struct for red tiles , this could be done without structs also but this is a good method 
struct RedTile
{
   int x, y;
};

int main()
{
   system("cls");

   //taking input
   string line;
   ifstream file("input.txt");
   vector<RedTile> redTiles; //to store redtiles
   vector<int> xs;
   vector<int> ys; //all x coordinates go in xs vector and all y coords go in ys 
   
   while(getline(file, line))
   {
      RedTile tile;
      sscanf(line.c_str(), "%d,%d", &tile.x, &tile.y);
      redTiles.push_back(tile); //push into all the redtiles vector
      xs.push_back(tile.x);     //push back x
      ys.push_back(tile.y);     //push back y
   }
   file.close(); //file close , all inputs done

   //Starting the part of Coordination compression 
   sort(xs.begin(), xs.end());
   sort(ys.begin(), ys.end());

   map<int, int> xMap, yMap; //xmap and ymap for putting the x and y coords and mapping them to ids / idxs
   for (int i = 0; i < xs.size(); ++i) xMap[xs[i]] = i; //map as indexes
   for (int j = 0; j < ys.size(); ++j) yMap[ys[j]] = j; //another mapping of the index
   
   int H = ys.size(), W = xs.size();

   //hor and ver boundaries , starting me sab false 
   vector<vector<bool>> hor(H, vector<bool>(W, false));
   vector<vector<bool>> ver(W, vector<bool>(H, false));
   
   //finding the edges then after that we're telling if those are hor or ver edges
   int n = redTiles.size();
   for (int k = 0; k < n; ++k)
   {
      int x1 = redTiles[k].x, y1 = redTiles[k].y;
      int x2 = redTiles[(k+1)%n].x, y2 = redTiles[(k+1)%n].y;
      
      //case 1 -> vertical edge
      if (x1 == x2)
      {
         int i = xMap[x1];
         int j1 = yMap[y1], j2 = yMap[y2];
         if (j1 > j2) swap(j1, j2);

         //there is a boundary between these 
         for (int j = j1; j < j2; ++j)
         {
            ver[i][j] = true;
         }
      }
      else //case 2 -> horizontal edge
      {
         int j = yMap[y1];
         int i1 = xMap[x1], i2 = xMap[x2];
         if (i1 > i2) swap(i1, i2);

         for (int i = i1; i < i2; ++i)
         {
            hor[j][i] = true;
         }
      }
   }
   
   //FLOOD FILLING THE POLYGON REGION 
   //mark the boundaries and then perform the BFS ON IT 
   //flood fill all the outsides of those points , the marked points
   int cellH = H-1, cellW = W-1; 

   //creating outside grid of cells which are all initially false
   vector<vector<bool>> outside(cellH, vector<bool>(cellW, false));
   queue<pair<int,int>> q;
   
   //push open border cells , we are basically marking all the strarting points of the BFS
   for (int i = 0; i < cellW; ++i)
   {
      if (!hor[0][i]) // top row cell open 
      {
         outside[0][i] = true;
         q.push({0,i});
      }
      if(!hor[H-1][i]) // bottom row cell open
      {
         outside[cellH-1][i] = true;
         q.push({cellH-1,i});
      }
   }
   
   for (int j = 0; j < cellH; ++j)
   {
      if (!ver[0][j]) // leftmost cell open
      {
         outside[j][0] = true;
         q.push({j,0});
      }
      if (!ver[W-1][j]) // rightmost cell open
      {
         outside[j][cellW-1] = true;
         q.push({j,cellW-1});
      }
   }
   
   //BFS START 
   while (!q.empty())
   {
      int i = q.front().first;
      int j = q.front().second;
      q.pop(); //we have to perform BFS ON OPEN CELLS THAT WE MARKED AND PASSING IN QUEUE
      
      //move up
      if (i > 0 && !outside[i-1][j] && !hor[i][j])
      {
         outside[i-1][j] = true;
         q.push({i-1,j});
      }
      
      //move down
      if (i < cellH-1 && !outside[i+1][j] && !hor[i+1][j])
      {
         outside[i+1][j] = true;
         q.push({i+1,j});
      }
      
      //move left    
      if (j > 0 && !outside[i][j-1] && !ver[j][i])
      {
         outside[i][j-1] = true;
         q.push({i,j-1});
      }
      
      //move right
      if (j < cellW-1 && !outside[i][j+1] && !ver[j+1][i])
      {
         outside[i][j+1] = true;
         q.push({i,j+1});
      }
   }
   //BFS DONE 
   //FLOOD FILL DONE
   
   //MARK ALL THE INSIDE ELEMENTS INSIDE A VECTOR 
   vector<vector<bool>> inside(cellH, vector<bool>(cellW, false));
   for (int i = 0; i < cellH; ++i)
      for (int j = 0; j < cellW; ++j)
         inside[i][j] = !outside[i][j];
   
   //build a prefix sum inside for O n^2 to O 1
   vector<vector<int>> pref(cellH+1, vector<int>(cellW+1, 0));
   for (int i = 0; i < cellH; ++i)
   {
      for (int j = 0; j < cellW; ++j)
      {
         pref[i+1][j+1] =
            pref[i][j+1] +
            pref[i+1][j] -
            pref[i][j] +
            (inside[i][j] ? 1 : 0);
      }
   }
   
   //TO FIND THE INSIDE NUMBER OF CELLS IN THE PREFIX SUM THING BOUNDARY
   auto query = [&](int i1, int j1, int i2, int j2)
   {
      return pref[i2][j2] - pref[i1][j2] - pref[i2][j1] + pref[i1][j1];
   };
   
   //now the final part -> compare every side and find the areas of the rectangles
   vector<pair<int,int>> comp; //a comparison array
   for (auto& tile : redTiles)
   {
      comp.push_back({xMap[tile.x], yMap[tile.y]});
   }
   
   long long maxArea = 0;
   int m = comp.size();
   
   for (int a = 0; a < m; ++a)
   {
      int i1 = comp[a].first, j1 = comp[a].second;
      
      for (int b = a+1; b < m; ++b)
      {
         int i2 = comp[b].first, j2 = comp[b].second;
         
         int left = min(i1,i2),  right = max(i1,i2);
         int bottom = min(j1,j2), top = max(j1,j2);
         
         if (left == right || bottom == top) continue; //not a rectangle
         
         int cellCount  = (right - left) * (top - bottom);
         int insideCount = query(bottom, left, top, right);
         
         //if the whole rectangle is inside
         if (insideCount == cellCount)
         {
            long long width  = xs[right] - xs[left] + 1;
            long long height = ys[top]   - ys[bottom] + 1;
            long long area = width * height;
            
            if (area > maxArea) maxArea = area;
         }
      }
   }
   
   cout << "The answer is: " << maxArea << endl;
}

// //Use BFS ON buttons and XOR
// Because BFS explores the tree level-by-level, the first level where you find the target state also gives you the shortest path from source state to target.

// For `[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1)` as an example:

// My source state is `[False, False, False, False]` and target state is `[False, True, True, False]`.

// And I maintain a BFS queue [(steps, state)]. For each popped state, you can generate new states by going through all buttons and
// if this new state has not been seen before, add it to the queue: [(steps + 1, new_state)]. That's it. When you pop a state off and it equals `target` the steps for that state is the answer.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int patternToMask(string &s){
    //conver pattern to 0 & 1 strings
    int mask = 0;
    for(int i = 0; i < (int)s.size(); i++){
        if(s[i] == '#') mask |= (1 << i);
    }
    return mask;
}

int buttonToMask(vector<int>& btn){
    int mask = 0;
    for(int x : btn){
        mask |= (1 << x);
    } 
    return mask; //then push buttontomask in the buttons
}

int bfsSolve(int target , const vector<int>& buttons , int nLights){
    int MAX = 1 << nLights; //max states

    vector<int>dist(MAX , -1); //init all states by -1 first 
    queue<int>q; //bfs explore level by level 

    dist[0] = 0;
    q.push(0);

    while(!q.empty()){
        int s = q.front(); q.pop(); //each state , each btn bitmask

        if(s == target) return dist[s];

        for(int b : buttons){
            int next = s ^ b; //explored one option , now keep exploring next and next 
            if(dist[next] == -1){
                dist[next] = dist[s] + 1;
                q.push(next);
            }
        }
    }
    return -1;
}   

int main() {
    freopen("input.txt", "r", stdin);

    string line;
    long long total = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        // -------- Parse pattern --------
        int L = line.find('[');
        int R = line.find(']');
        string pattern = line.substr(L + 1, R - L - 1);

        int nLights = pattern.size();
        int target = patternToMask(pattern);

        // -------- Parse buttons --------
        vector<int> buttons;
        int pos = 0;

        while (true) {
            int l = line.find('(', pos);
            if (l == -1) break;

            int r = line.find(')', l);
            string inside = line.substr(l + 1, r - l - 1);

            vector<int> btn;
            if (!inside.empty()) {
                stringstream ss(inside);
                string tmp;
                while (getline(ss, tmp, ',')) {
                    btn.push_back(stoi(tmp));
                }
            }
            buttons.push_back(buttonToMask(btn));
            pos = r + 1;
        }

        int presses = bfsSolve(target, buttons, nLights);
        total += presses;
    }

    cout << total << endl;
}

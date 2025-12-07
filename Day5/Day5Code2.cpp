#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    vector<pair<ll,ll>> ranges;
    ifstream file("input.txt");
    string line;

    // read only the first section (stop at blank line)
    while (getline(file, line)) {
        if (line.empty()) break;

        ll a, b;
        char dash;
        stringstream ss(line);
        ss >> a >> dash >> b;
        ranges.push_back({a, b});
    }

    // sort ranges by start
    sort(ranges.begin(), ranges.end());

    // merge overlapping ranges
    vector<pair<ll,ll>> merged;
    merged.push_back(ranges[0]);

    for (int i = 1; i < ranges.size(); i++) {

        ll &prevStart = merged.back().first;
        ll &prevEnd   = merged.back().second;
        ll curStart   = ranges[i].first;
        ll curEnd     = ranges[i].second;

        if (curStart <= prevEnd) {
            prevEnd = max(prevEnd, curEnd); // extend overlap
        } else {
            merged.push_back(ranges[i]); // new separate interval
        }
    }

    // count distinct values
    ll total = 0;
    for (auto &p : merged) {
        total += (p.second - p.first + 1);  //always sort first in these types of questions
        
    }

    cout << total;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Haybale {
    int size, position;
    Haybale(int sizeIn, int positionIn) : size(sizeIn), position(positionIn) {}
};

struct PosComp {
    bool operator()(const Haybale &a, const Haybale &b) {
        return a.position < b.position;
    }
};

struct SizeComp {
    bool operator()(const Haybale &a, const Haybale &b) {
        return a.size > b.size;
    }
};

int main() {
    //ifstream cin("trapped.in");
    //ofstream cout("trapped.out");
    
    int n;
    cin >> n;
    vector<Haybale> bales;
    
    for (int i = 0; i < n; i++) {
        int size, position;
        cin >> size >> position;
        bales.emplace_back(size, position);
    }
    
    sort(bales.begin(), bales.end(), PosComp());
    
    vector<int> locations(n);
    map<int, int> mapIdx;
    map<int, int> locToSize;
    
    for (int i = 0; i < n; i++) {
        locations[i] = bales[i].position;
        mapIdx[locations[i]] = i;
        locToSize[locations[i]] = bales[i].size;
    }
    
    sort(bales.begin(), bales.end(), SizeComp());
    
    set<int> seen;
    int ans = 0;
    vector<bool> covered(n - 1, false);
    
    for (const Haybale &out : bales) {
        int index = mapIdx[out.position];
        
        if (!seen.empty() && *seen.rbegin() > index) {
            auto higherIt = seen.upper_bound(index);
            int higherIndex = *higherIt;
            int distance = locations[higherIndex] - locations[index];
            if (distance <= locToSize[locations[higherIndex]] && distance <= out.size) {
                int l = index, r = higherIndex;
                if (!covered[l]) {
                    for (int i = l; i < r; i++) {
                        covered[i] = true;
                    }
                }
            }
        }
        
        if (!seen.empty() && *seen.begin() < index) {
            auto lowerIt = prev(seen.lower_bound(index));
            int lowerIndex = *lowerIt;
            int distance = locations[index] - locations[lowerIndex];
            if (distance <= locToSize[locations[lowerIndex]] && distance <= out.size) {
                int l = lowerIndex, r = index;
                if (!covered[l]) {
                    for (int i = l; i < r; i++) {
                        covered[i] = true;
                    }
                }
            }
        }
        
        seen.insert(index);
    }
    
    for (int i = 0; i < covered.size(); i++) {
        if (covered[i]) {
            ans += locations[i + 1] - locations[i];
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
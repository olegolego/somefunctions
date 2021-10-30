#include <bits/stdc++.h>
#include <random>
using namespace std;
#define int long long
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a).size()

const int P = 37;
const int mxn = 1e6;
vector<int> mods{9834497, 433494437, 1336337 ,9369319, 562448657};
vector<array<int, 5>> ppows(mxn);

void build_ppows(){
    ppows[0][0] = 1;
    ppows[0][1] = 1;
    ppows[0][2] = 1;
    ppows[0][3] = 1;
    ppows[0][4] = 1;
    for(int i = 1; i < mxn; ++i){
        for(int j = 0; j < 5; ++j){
            ppows[i][j] = (ppows[i - 1][j] * P) % mods[j];
        }
    }
}

struct HASH{
    vector<array<int, 5>> pref;
    int n;
    
    void init(string &s){
        n = s.size();
        pref.resize(n + 1);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < 5; ++j){
                pref[i + 1][j] = (pref[i][j] * P + s[i]) % mods[j];
            }
        }
    }

    array<int, 5> get(int l, int r){
        return {
        (((pref[r + 1][0] - pref[l][0] * ppows[r - l + 1][0]) %  mods[0]) + mods[0]) % mods[0], 
        (((pref[r + 1][1] - pref[l][1] * ppows[r - l + 1][1]) %  mods[1]) + mods[1]) % mods[1], 
        (((pref[r + 1][2] - pref[l][2] * ppows[r - l + 1][2]) %  mods[2]) + mods[2]) % mods[2],
        (((pref[r + 1][3] - pref[l][3] * ppows[r - l + 1][3]) %  mods[3]) + mods[3]) % mods[3],
        (((pref[r + 1][4] - pref[l][4] * ppows[r - l + 1][4]) %  mods[4]) + mods[4]) % mods[4]
        };
    }
};


signed main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    
    build_ppows();

    string s;
    cin >> s;
    HASH a;
    a.init(s);
    

}
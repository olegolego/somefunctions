#include <bits/stdc++.h>
#include <random>
using namespace std;
#define int long long
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a).size()

const int logn = 22;
const int mx = 3e5;
vector<int> g[mx];
int n, m, timer = 0;
vector<int> tin, tout, d;
vector<array<int, logn>> up;

void dfs(int v, int p){
    tin[v] = timer++;
    up[v][0] = p;
    for(int i = 1; i < logn; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1]; 
    }

    for(auto u : g[v]){
        if(u == p)
            continue;
        d[u] = d[v] + 1;
        dfs(u, v);
    }

    tout[v] = timer++;
}


bool pr(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int get_lca(int v, int u) {
    if (pr(v, u)) {
        return v;
    }
    if (pr(u, v)) {
        return u;
    }

    if(d[u] < d[v]){
        swap(u, v);
    }

    for (int i = logn - 1; i >= 0; --i) {
        if (!pr(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

signed main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
}

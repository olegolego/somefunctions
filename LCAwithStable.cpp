#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1e5;
const int maxp = 20;

int n, m;
int last = 0;
int a[maxn * 2];
int height[maxn];
int log_[maxn * 2];
int first[maxn * 2];
int st[maxn * 2][maxp];
vector<int> g[maxn];

void PreCountLogs(){
    log_[1] = 0;
    for(int i = 2; i < maxn * 2; ++i){
        log_[i]  = log_[i / 2] + 1;
    }
}

void dfs(int v, int h, int p){
    height[v] = h;
    first[v] = last;
    a[last++] = v;
    for(auto u : g[v]){
        if(u == p){
            continue;
        }

        dfs(u, h + 1, v);
        a[last++] = v;
    }
}

void BuildSparceTable(){
    int pow = log_[last];
    for(int i = 0; i < last; ++i){
        st[i][0] = a[i];
    }

    for(int j = 1; j <= pow; ++j){
        for(int i = 0; i + (1 << j) < last; ++i){
            if(height[st[i][j - 1]] < height[st[i + (1 << (j - 1))][j - 1]]){
                st[i][j] = st[i][j - 1];
            }

            else{
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int quarysparsetable(int l, int r){
    int pow = log_[r - l + 1];
    int left = st[l][pow];
    int right = st[r - (1 << pow) + 1][pow];
    if(height[left] < height[right]){
        return left;
    }
    else{
        return right;
    }
}

int lca(int u, int v){
    u = first[u];
    v = first[v];
    if(u > v) swap(u, v);
    return quarysparsetable(u, v);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n - 1; ++i){
        int u;
        cin >> u;
        g[u].push_back(i);
        g[i].push_back(u);
    }

    PreCountLogs();
    dfs(0, 0, -1);
    BuildSparceTable();
}
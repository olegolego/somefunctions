#include <bits/stdc++.h>
#include <random>
using namespace std;
#define int long long
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a).size()

const int mod = 1e9 + 7;
const int mxn = 1e6;
vector<int> factorial(mxn);

int binpow (int a, int n, int modul) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return (binpow(a, n - 1, modul) * a) % modul;
	else {
		int b = (binpow(a, n / 2, modul)) % modul;
		return (b * b) % modul;
	}
}

void build_factorial(){
    factorial[0] = 1;
    factorial[1] = 1;
    for(int i = 2; i < mxn; ++i){
        factorial[i] = (factorial[i - 1] * i) % mod;
    }
}

int allot_power(int a){
    return (a, mod - 2, mod);
}

int find_binom(int n, int k){
    return (factorial[n] * allot_power((factorial[n - k] * factorial[k]) % mod)) % mod;
} 

vector<pair<int, int>> devisors(int n){
    vector<pair<int, int>> mp;
    int dif = 2;
    while (dif * dif <= n)
    {
        int cnt = 0;
        while(n % dif == 0){
            n /= dif;
            cnt++;
        }

        if(cnt != 0){
            mp.push_back({dif, cnt});
        }

        dif++;
    }
    
    if(n > 1){
        mp.push_back({dif, 1});
    }
    return mp;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
   
   
}
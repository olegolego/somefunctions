#include <bits/stdc++.h>
#include <random>
using namespace std;
#define int long long
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a).size()

class Treap {
    static minstd_rand generator;

    struct node{
        int priority;
        int value, size = 1, sum_on;
        node *left = nullptr, *right = nullptr; 
        node(int vakue) : priority(generator()), value(value), sum_on(value){};
    } *root = nullptr;

    static int get_Size(node *n){
        return n ? n -> size : 0;
    }

    static int get_Sum(node *n){
        return n ? n -> sum_on : 0;
    }

    static void update(node *&n){
        if(n){
            n->size = n->left->size + n->right->size + 1;
            n->sum_on = n->left->sum_on + n->right->sum_on + n->value;
        }
    }

    static void push(node *&a){

    }

    static node *merge(node *a, node *b){
        push(a);
        push(b);
        if(!a || !b){
            return a ? a : b;
        }

        if(a->priority > b->priority){
            a->right = merge(a->right, b);
            update(a);
            return a;
        }

        else{
            b -> left = merge(a, b -> left);
            update(b);
            return b;
        }
    }

    static void split(node *n, int key, node *&a, node *&b){
        push(n);
        if(!n){
            a = b = nullptr;
            return;
        }

        if(get_Size(n->left) < key){
            split(n->right, key - get_Size(n->left) - 1, n->right, b);
            a = n;
        }

        else{
            split(n->left, key, a, n->left);
            b = n;
        }

        update(a);
        update(b);
    }

public:
    int get(int index){
        node *less, *equal, *greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        int res = equal -> value;
        merge(merge(less, equal), greater);
        return res;
    }

    void insert(int index, int value){
        node *less, *greater;
        split(root, index, less, greater);
        root = merge(merge(less, new node(value)), greater);
    }

    int sumValue(int l, int r){
        node *less, *equal, *greater;
        split(root, l, less, greater); 
        split(greater, r - l + 1, equal, greater); 
        int result = get_Sum(equal);
        root = merge(merge(less, equal), greater);
        return result;
    }
};

minstd_rand Treap::generator;

signed main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
}
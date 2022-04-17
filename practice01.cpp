#include<bits/stdc++.h>

using namespace std;
 
#define ll long long
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define psi pair<string,ll>
#define mii map<int,int>
#define mp make_pair
#define MOD 1000000007
#define mod 1000003
#define pb push_back
#define eb emplace_back
#define lim 100000
#define ff first
#define ss second
#define endl "\n"
#define PI 3.1415926535
#define golden 1.6180339887498
#define pspii pair<string, pair<int, int>> 
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repl(i,a, b) for(int i = (a); i > (b); i--)
#define MAX 1e16
#define trav(x, k) for(auto& x : k)
 
// struct hash_pair {
//     template <class T1, class T2>
//     size_t operator()(const pair<T1, T2>& p) const {
//         auto hash1 = hash<T1> {}(p.first);
//         auto hash2 = hash<T2> {}(p.second);
//         return hash1 ^ hash2;
//     }
// };
 
ll power(ll a, ll b, ll c) { ll ans = 1; ll k = a; while (b > 0) { if (b & 1) { ans *= k; ans %= c; } k = (k * k) % c; b = b >> 1;} return ans;}
 
// ll ncr(ll n,ll r,ll*arr){
//     if(r==0) return 1;
//     ll res = 1;
//     return (arr[n]*(power(arr[n-r],MOD-2, MOD))%MOD*(power(arr[r],MOD-2, MOD))%MOD)%MOD;
// }
 
ll gcd(ll a, ll b) { if (a == 0) return b; if (b == 0) return a; return gcd(b, a % b); }
ll add_mod(ll a, ll b, ll m) {return ((a % m) + (b % m)) % m;}
ll sub_mod(ll a, ll b, ll m) {return ((a % m) - (b % m) + m) % m;}
ll mul_mod(ll a, ll b, ll m) {return ((a % m) * (b % m)) % m;}
void print(double val, int k) { cout << fixed << setprecision(k) << val << " ";}
ll toint(string s) {stringstream ss; ss << s; ll x; ss >> x; return x;}


// <------------------------------------------- WRITE CODE HERE ------------------------------------------------>


int pgSize, intSize = 4;;

class page{
public:
    page* prev;
    page* next;
    int space;
    int records;

    vi keys;

    page(){
        next = NULL;
        prev = NULL;
        records = 0;
        space = pgSize - (4*intSize);
    }

    page(page* x){
        x->next = this;
        this->prev = x;
        next = NULL;
        prev = NULL;
        records = 0;
        space = pgSize - (4*intSize);
    }

    void insert(int bt, int pk){
        records++;
        keys.pb(pk);
        space -= (bt + intSize);
    }

    pair <bool, int> search(int pk){
        for(int i = 0; i < records; i++){
            if(keys[i] == pk) return {true, i};
        }
        return {false, -1};
    }
};

class heap_file{
private:
    page* start;
    int size;
public:

    heap_file(){
        start = NULL;
        size = 0;
    }

    void insert(int bt, int pk){
        if (start == NULL) {
            start = new page();
            start->insert(bt, pk);
        } else {
            page* itr = start;
            while(itr != NULL){
                if(itr->space >= bt + intSize){
                    itr->insert(bt, pk);
                    return;
                }

                if(itr->next == NULL) break;
                itr = itr->next;
            }
            page* newPage = new page(itr);
            newPage->insert(bt, pk);
        }
        size++;
    }

    pii search(int pk){
        page* itr = start;
        int cnt = 0;
        while(itr != NULL){
            pair<bool, int> ans = itr->search(pk);
            if(ans.ff) return {cnt, ans.ss};
            itr = itr->next;
            cnt++;
        }
        return {-1, -1};
    }

    void status(){
        cout << size << " ";
        page* itr = start;
        while(itr != NULL){
            cout << itr->records << " ";
            itr = itr->next;
        }
        cout << endl;
    }

};
 
void solve(){
    cin >> pgSize;

    heap_file dir;

    while(1){
        int x;
        cin >> x;
        if (x == 1) {
            int a, b; cin >> a >> b;
            dir.insert(a, b);
        } else if (x == 2) {
            dir.status();
        } else if (x == 3) {
            int a; cin >> a;
            pii temp = dir.search(a);

            cout << temp.ff << " " << temp.ss << endl;
        } else {
            break;
        }
    }

}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE
 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
#endif
 
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
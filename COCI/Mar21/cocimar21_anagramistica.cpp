#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

/*
struct Node
{
    int node, len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 2001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

class Math{
    private:
        ll fact[MAX + 1] = {};
        ll ifac[MAX + 1] = {};
    public:
        Math(){
            fact[0] = 1;
            FOR(ll, i, 1, MAX)
                fact[i] = (fact[i - 1] * i) % MOD;
            ifac[MAX] = pow(fact[MAX], MOD - 2);
            FORR(ll, i, MAX - 1, 0)
                ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
        }

        ll pow(ll a, ll n){
            if (n == 0) return 1;
            ll ans = pow(a, n >> 1);
            ans *= ans, ans %= MOD;
            if (n & 1) return (ans * a) % MOD;
            return ans;
        }

        ll C(ll n, ll k){
            return (((fact[n] * ifac[k]) % MOD) * ifac[n - k]) % MOD;
        }
        
        ll P(ll n, ll k){
            return (fact[n] * ifac[n - k]) % MOD;
        }
        
        ll factorial(ll n){
            return fact[n];
        }
} math;

const ll BASE = 2001;
ll p[MAX];
ll hashStr(string s){
    ll cnt[26] = {};
    for (char c: s)
        cnt[c - 'a']++;
    
    ll number = 0;
    FOR(int, i, 0, 25)
        number += p[i] * cnt[i] % MOD, number %= MOD;
    return number;
};

mll cnt;
int n, k;
int quan[MAX];
int ways[MAX][MAX] = {};

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    p[0] = 1; FOR(int, i, 1, 25) p[i] = (p[i - 1] * BASE) % MOD;

    cin >> n >> k;
    FOR(int, i, 1, n){
        string s; cin >> s;
        cnt[hashStr(s)]++;
    }

    n = 0;
    for (pll i: cnt)
        quan[++n] = i.se;
    
    ways[0][0] = 1;
    FOR(int, i, 0, n - 1)
        FOR(int, j, 0, k)
            if (ways[i][j]){
                int tmp = ways[i][j];
                int allow = quan[i + 1];
                FOR(int, add, 0, allow){
                    int newPairs = j + (add * (add - 1) / 2);
                    if (newPairs > k) break;
                    ll more = tmp * math.C(allow, add) % MOD;
                    ways[i + 1][newPairs] += more,
                    ways[i + 1][newPairs] %= MOD;
                }
            }
    ll answer = ways[n][k];
    cout << answer;
}
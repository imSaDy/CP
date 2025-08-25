/*
Problem: Given n creepers in a line with explosive powers e[i].
Detonating creeper i kills all creepers in the range [i-e[i]+1, i+e[i]-1].
Some creepers have e[i] = 0 and cannot be detonated.
Find the minimum number of detonations to kill all creepers,
and output the sequence of detonations (any order if multiple solutions exist).
Output -1 if impossible.
*/
#include <bits/stdc++.h> 

using namespace std ; 
/*
template<typename T> using vc=vector<T>;
template<typename T> using vvc=vc<vc<T>>;
template<typename T> using vvvc=vc<vvc<T>>;

using vi=vc<int>;
using vll=vc<ll>;
using vvi=vc<vi>;
using vvll=vc<vll>;*/

typedef long long ll ; 
typedef pair<int, int> pii; 
typedef pair<pii, int> ppi;
typedef pair<ll, pii> pip;
typedef pair<ll, ll> pll; 
typedef long double ld; 
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <vi> vvi; 
typedef vector <pii> vp;
typedef vector <pll> vpl;
typedef vector <pair<pii, int>> vpi;
typedef vector <pair<pii, ll>> vppl;
typedef vector <bool> vb;
typedef vector <char> vch; 
typedef vector <vb> vvb;
typedef vector <vp> vvp;
typedef vector <vll> vvll;
typedef priority_queue <pll, vpl, greater<pll>> minheap; 

void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}

template <typename T>
inline T lowbit(T x) { return x & -x; }

#define debug(...)             cerr << "(" << #__VA_ARGS__ << "): ", debug_out(__VA_ARGS__)
#define hey                    cerr << "Ey BABA!\n"
#define MP                     make_pair
#define F                      first
#define S                      second
#define pb 					   push_back
#define ppb                    pop_back 
#define all(v)                 v.begin() ,v.end() 
#define len(v)                 (int) v.size()
#define uniq(v)                v.resize(unique(all(v)) - v.begin());
#define rep1(n) for(ll i=0; i<(ll)(n); ++i)
#define rep2(i,n) for(ll i=0; i<(ll)(n); ++i)
#define rep3(i,a,b) for(ll i=(ll)(a); i<(ll)(b); ++i)
#define rep4(i,a,b,c) for(ll i=(ll)(a); i<(ll)(b); i+=(c))
#define cut4(a,b,c,d,e,...) e
#define rep(...) cut4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define per1(n) for(ll i=((ll)n)-1; i>=0; --i)
#define per2(i,n) for(ll i=((ll)n)-1; i>=0; --i)
#define per3(i,a,b) for(ll i=((ll)a)-1; i>=(ll)(b); --i)
#define per4(i,a,b,c) for(ll i=((ll)a)-1; i>=(ll)(b); i-=(c))
#define per(...) cut4(__VA_ARGS__,per4,per3,per2,per1)(__VA_ARGS__)
#define rep_subset(i,s) for(ll i=(s); i>=0; i=(i==0?-1:(i-1)&(s)))

template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

const int maxn = 5e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const int lg = 12; 
const ll INF = 1e17; 
const int sq = 700;

template<typename T, class F = function<T(const T&, const T&)>>
struct SegTree {
    int n, N;
    T ID;
    F op;
    vector<T> seg;

    SegTree(int n_, T identity, F func) : n(n_), ID(identity), op(func) {
        N = 1;
        while (N < n) N <<= 1;
        seg.assign(2 * N, ID);
    }

    void build(const vector<T>& arr) {
        for (int i = 1; i <= n; i++) seg[N + i - 1] = arr[i];
        for (int i = N - 1; i > 0; i--)
            seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    void update(int pos, T val) {
        pos += N - 1;
        seg[pos] = min(val, seg[pos]);
        for (pos >>= 1; pos > 0; pos >>= 1)
            seg[pos] = op(seg[pos << 1], seg[pos << 1 | 1]);
    }

    T query(int l, int r) {
        T ansL = ID, ansR = ID;
        l += N - 1; r += N - 1;
        while (l <= r) {
            if (l & 1) ansL = op(ansL, seg[l++]);
            if (!(r & 1)) ansR = op(seg[r--], ansR);
            l >>= 1; r >>= 1;
        }
        return op(ansL, ansR);
    }
};

struct query {
    int l, r, id;
    query(int _l, int _r, int _id): l(_l), r(_r), id(_id){};
};
vector <query> Q[maxn];

void Main(){
    int n; 
    cin >> n; 
    vi e(n + 1), L(n + 1), R(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> e[i];
        if (e[i] == 0)
            continue;
        L[i] = max(1, i - e[i] + 1);
        R[i] = min(n, i + e[i] - 1);
        Q[i - 1].pb(query(L[i] - 1, i - 1, i));
        Q[L[i] - 1].pb(query(L[i] - 1, R[i], i));
    }
    vp dp(n + 1, {inf, -1});
    auto op = [](pii a, pii b){return min(a, b);};
    SegTree <pii> seg(n + 1, {inf, -1}, op);
    for (auto [l, r, idx] : Q[0]){
        dp[idx] = MP(1, -1);
    }
    for (int i = 1; i <= n; i++){
        seg.update(R[i], {dp[i].F, i});
        for (auto [l, r, idx] : Q[i]){
            pii ans = seg.query(l, r);
            dp[idx] = min(dp[idx], {ans.F + 1, ans.S});
        }
        //debug(i, dp[i].F, dp[i].S);
    }
    if (seg.query(n, n).F == inf){
        cout << -1 << endl; 
    }
    else {
        int cur = seg.query(n, n).S;
        vi vc; 
        while (cur != -1){
            vc.pb(cur); 
            cur = dp[cur].S;
        }
        sort(all(vc), [&](int a, int b){
            return e[a] < e[b];
        });
        cout << len(vc) << endl; 
        for (auto x : vc){
            cout << x << " ";
        }
        cout << endl;
    }
    for (int i = 0; i <= n; i++){
        Q[i].clear();
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tc = 1; 
    cin >> tc;
    while (tc--){
        Main();
    }
    return 0;
}
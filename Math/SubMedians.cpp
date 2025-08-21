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

const int maxn = 1.5e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const int lg = 12; 
const ll INF = 1e17; 
const int sq = 700;

template<typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    Fenwick(int n) : n(n) {
        bit.assign(n + 1, 0);
    }

    void add(int idx, T val) { // 1-based index
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    T sum(int idx) { // prefix sum [1..idx]
        T res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    T get(int l, int r) { // inclusive
        return sum(r) - sum(l - 1);
    }

    // smallest index idx such that sum(idx) >= target
    int lower_bound(T target) {
        int idx = 0;
        T accumulated = 0;
        // largest power of two <= n
        int maxPow = 1;
        while (maxPow <= n) maxPow <<= 1;
        for (int step = maxPow; step > 0; step >>= 1) {
            if (idx + step <= n && accumulated + bit[idx + step] < target) {
                accumulated += bit[idx + step];
                idx += step;
            }
        }
        return idx + 1; // 1-based index
    }
};

void Main(){
    int n, k; 
    cin >> n >> k; 
    vi a(n + 1); 
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    auto maxMedian = [&](){  // max median and subarray with length >= k(input)
        auto check = [&](int x){
            vi b(n + 1, 0);
            for (int i = 1; i <= n; i++){
                b[i] = b[i - 1] + (a[i] >= x) - (a[i] < x); 
            }
            int mn = 0; 
            int idx = 0; 
            for (int i = 1; i <= n; i++){
                if (i >= k){
                    if (mn > b[i - k])
                        idx = i - k;
                    mn = min(mn, b[i - k]);
                    if (b[i] >= mn)
                        return array<int, 3>{true, idx + 1, i};
                }
            }
            return array<int, 3>{false, -1, -1};
        };
    
        int l = 0, r = n + 1; 
        array <int, 3> ans; 
        while (l + 1 < r){
            int mid = (l + r) >> 1;
            auto tmp = check(mid);
            if (tmp[0]){ l = mid; ans = tmp;}
            else r = mid; 
        }
        return array<int, 3>{l, ans[1], ans[2]}; 
    };
    auto minMedian = [&](){    // min median
        auto check = [&](int x){
            //debug(x);
            vi b(n + 1, 0);
            for (int i = 1; i <= n; i++){
                b[i] = b[i - 1] - (a[i] > x) + (a[i] <= x); 
                //debug(i, b[i]);
            }
            int mn = 0; 
            int idx = 0; 
            for (int i = 1; i <= n; i++){
                if (i >= k){
                    if (mn > b[i - k])
                        idx = i - k;
                    mn = min(mn, b[i - k]);
                    if (b[i] >= mn)
                        return array<int, 3>{true, idx + 1, i};
                }
            }
            return array<int, 3>{false, -1, -1};
        };
    
        int l = 0, r = n + 1; 
        array <int, 3> ans; 
        while (l + 1 < r){
            int mid = (l + r) >> 1;
            auto tmp = check(mid);
            if (tmp[0]){ r = mid; ans = tmp;}
            else l = mid; 
        }
        return array<int, 3>{r, ans[1], ans[2]}; 
    };

    auto [mx, lx, rx] = maxMedian();
    auto [mn, ln, rn] = minMedian();
    // debug(mx, lx, rx);
    // debug(mn, ln, rn);
    vp ans(n + 1, {-1, -1}); 
    ans[mx] = {lx, rx};
    ans[mn] = {ln, rn};
    set <int> s; 
    for (int i = mn + 1; i < mx; i++){
        s.insert(i);
    }
    Fenwick <int> fen(n + 1);
    for (int i = ln; i <= rn; i++){
        fen.add(a[i], 1);
    }
    while (true){
        // debug(ln, rn);
        if (s.empty()) break;
        int len = rn - ln + 1;
        int med = fen.lower_bound((len + 1) / 2);
        // debug(med);
        auto it = s.lower_bound(med);
        if (it != s.end() && *it == med){
            ans[med] = {ln, rn};
            s.erase(med);
        }
        if (len % 2 == 0){
            int med2 = fen.lower_bound(len / 2 + 1);
            //debug(med2);
            while (true){
                if (it != s.end() && (*it) <= med2){
                    ans[(*it)] = {ln, rn}; 
                    s.erase(*it);
                }
                else {
                    break;
                }
                it = s.lower_bound(med);
            }
        }
        if (rn < rx){
            rn++;
            fen.add(a[rn], 1);
        }
        else if (ln > lx){
            ln--; 
            fen.add(a[ln], 1);
        }
        else if (rn > rx){
            fen.add(a[rn], -1);
            rn--; 
        }
        else if (ln < lx){
            fen.add(a[ln], -1);
            ln++;
        }
        else {
            break;
        }
    }
    cout << mx - mn + 1 << endl;
    for (int i = mn; i <= mx; i++){
        cout << i << " " << ans[i].F << " " << ans[i].S << endl;
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




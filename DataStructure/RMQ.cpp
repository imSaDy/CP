#include <bits/stdc++.h> 

using namespace std ; 

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
#define F                     first
#define S                     second
#define pb 					   push_back
#define ppb                    pop_back 
#define all(v)                 v.begin() ,v.end() 
#define len(v)                 (int) v.size()
#define uniq(v)                 v.resize(unique(all(v)) - v.begin());

const int maxn = 2e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const ll INF = 1e17; 

struct RMQ {
    int n, K;
    vector<vector<int>> st;
    vector<int> logv;

    RMQ(const vector<int>& arr) { // arr[1..n], arr[0] unused
        n = arr.size() - 1;
        K = __lg(n) + 1;
        st.assign(K, vector<int>(n + 1));
        logv.assign(n + 1, 0);

        for (int i = 2; i <= n; i++) logv[i] = logv[i / 2] + 1;

        for (int i = 1; i <= n; i++) st[0][i] = arr[i];

        for (int j = 1; j < K; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    int query(int l, int r) { // 1-based, inclusive
        int j = logv[r - l + 1];
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};


int n, q; 

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> q; 
    vi a(n + 1); 
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    RMQ rmq(a);
    while(q--){
        int l, r; 
        cin >> l >> r; 
        cout << rmq.query(l, r) << endl;
    }
    return 0;
}




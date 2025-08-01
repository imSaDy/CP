/*
    This code will answer the LCS of both string and integer arrays.
*/

#include <bits/stdc++.h> 

using namespace std ; 

typedef long long ll ; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef long double ld; 
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <vi> vvi; 
typedef vector <pii> vp;
typedef vector <bool> vb;
typedef vector <vb> vvb;
typedef vector <vp> vvp;

void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}

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

const int maxn = 1e3 + 5; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e18; 

template <typename T>
pair<int, vector<T>> lcs(const vector<T> a_input, const vector<T> b_input) {
    int n = a_input.size(), m = b_input.size();
    vector<T> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; ++i) a[i] = a_input[i - 1];
    for (int i = 1; i <= m; ++i) b[i] = b_input[i - 1];

    vvi dp(n + 1, vi(m + 1));
    vvp par(n + 1, vp(m + 1));
    vvb pick(n + 1, vb(m + 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (dp[i - 1][j] < dp[i][j - 1])
                par[i][j] = {i, j - 1};
            else
                par[i][j] = {i - 1, j};
            if (a[i] == b[j] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                par[i][j] = {i - 1, j - 1};
                pick[i][j] = true;
            }
        }
    }

    vector<T> ans;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (pick[i][j])
            ans.push_back(a[i]);
        tie(i, j) = par[i][j];
    }
    reverse(ans.begin(), ans.end());
    return {dp[n][m], ans};
}

pair<int, string> lcs(const string& a, const string& b) {
    vector<char> va(a.begin(), a.end()), vb(b.begin(), b.end());
    auto [len, vec] = lcs(va, vb);
    return {len, string(vec.begin(), vec.end())};
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vi a(n), b(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i]; 
    }
    string s = "LOVE", t = "MOVIE";
    auto [num, ans] = lcs(s, t);
    cout << num << endl; 
    for (auto x : ans){
        cout << x << " "; 
    }
    cout << ans; 
}



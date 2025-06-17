#include <bits/stdc++.h> 

using namespace std ; 

typedef long long ll ; 
typedef pair<int, int> pii ; 
typedef pair<ll, ll> pll ; 
typedef long double ld ; 
typedef vector <int> vi ;
typedef vector <ll> vll ;
typedef vector <vi> vvi ; 
typedef vector <pii> vp;

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

const int maxn = 1e6 + 5; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const ll INF = 1e18;

int lis(vi &a){
    int n = a.size();
    vi dp(n + 1, inf); 
    dp[0] = -inf; 
    for (int i = 0; i < n; i++){
        int l = upper_bound(all(dp), a[i]) - dp.begin();
        if (dp[l - 1] < a[i] && a[i] < dp[l]){
            dp[l] = a[i]; 
        }
    }
    int ans = 0; 
    for (int l = 0; l <= n; l++){
        if (dp[l] < inf){
            ans = l; 
        }
    }
    return ans; 
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    return 0 ;
}

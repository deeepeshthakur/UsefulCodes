#include<bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define full(a) a.begin(),a.end()
#define rfull(a) a.rbegin(),a.rend()

using namespace std;
const double pi=acos(-1.0);
const double pii=2*pi;
const double eps=1e-6;
const long long MOD=1e9+7;

void dfs(int ind, int par, int level, vector<bool>& v, vector<vector<int>>& tr, vector<int>& p, vector<int>& l){
    if(v[ind]){
        v[ind]=false;
        p[ind]=par;
        l[ind]=level;
        for( auto x:tr[ind])
            dfs(x,ind,level+1,v,tr,p,l);
    }
}

void fill_curr(int ind, vector<bool>& v, vector<int>& p, vector<vector<int>>& dp){
    if(v[ind]){
        v[ind]=false;
        if(p[ind]!=-1 && v[p[ind]]) fill_curr(p[ind],v,p,dp);
        dp[ind][0]=p[ind];
        for(int i=1;dp[ind][i-1]!=-1;i++) dp[ind][i]=dp[dp[ind][i-1]][i-1];
    }
}

void fill_dp(int n, int root, vector<vector<int>>& tr, vector<int>& parent, vector<int>& level, vector<vector<int>>& dp){
    // auto fill = [] ( vector<int>& a, int val) { for(auto &x:a) x=val;};
    // auto print_arr = [] ( vector<int>& a) { for(auto x:a) cout<<x<<" ";cout<<"\n";};
    parent = vector<int>(n,-1);
    level = vector<int>(n,-1);
    int lim=0,p2=1;
    while(n*2<=p2){lim++;p2*=2;} lim+=10;
    dp = vector<vector<int>>(n,vector<int>(lim,-1));
    vector<bool> vis(n,true);
    dfs(root,-1,1,vis,tr,parent,level);
    vis = vector<bool>(n,true);
    for(int i=0;i<n;i++) fill_curr(i,vis,parent,dp);
}

int find_lca(int x, int y, vector<int>& p, vector<int>& l, vector<vector<int>>& dp){
    if(l[x]>l[y]) swap(x,y);
    while(l[x]<l[y]){
        int nxt=y;
        for(int i=0;dp[y][i]!=-1 && l[dp[y][i]]<=l[x];i++) nxt=dp[y][i];
        y=nxt;
    }
    while(x!=y){
        int a=x,b=y;
        for(int i=0;dp[x][i]!=-1 && dp[y][i]!=-1 && dp[x][i]!=dp[y][i];i++){
            a=dp[x][i];
            b=dp[y][i];
        }
        x=p[a];
        y=p[b];
    }
    return x;
}

void solve(){
    int n;
    cin>>n;
    vector<vector<int>> tr(n);
    for(int i=0;i<n;i++){
        int m;cin>>m;
        for(int j=0;j<m;j++){
            int x=i,y;
            cin>>y;
            tr[x].pb(y);
            tr[y].pb(x);
        }
    }

    int root=0;
    vector<int> parent,level;
    vector<vector<int>> dp;

    fill_dp(n,root,tr,parent,level,dp);
    auto print_arr = [] ( vector<int>& a) { for(auto x:a) cout<<x<<" ";cout<<"\n";};
    print_arr(parent);
    print_arr(level);
    for(int i=0;i<n;i++) print_arr(dp[i]);
    cout<<endl;

    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int x,y;
        cin>>x>>y;
        cout<<find_lca(x,y,parent,level,dp)<<endl;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    solve();
    return 0;
}
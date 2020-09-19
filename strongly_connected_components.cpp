#include<bits/stdc++.h>
using namespace std;

struct scc_struct{
    int n,scc_count;
    vector<vector<int>> gr,rev_gr;
    vector<bool> v;
    vector<int> scc;
    stack<int> st;
    
    scc_struct(int nn=0){
        n=nn;
        scc_count=0;
        gr=vector<vector<int>>(n);
        rev_gr=vector<vector<int>>(n);
        scc=vector<int>(n,-1);
    }
    
    void add_edge(int x,int y){
        gr[x].push_back(y);
        rev_gr[y].push_back(x);
    }

    void dfs0(int ind){
        if(v[ind]){
            v[ind]=false;
            st.push(ind);
            for(auto x:gr[ind]) dfs0(x);
        }
    }

    void dfs1(int ind){
        if(v[ind]){
            v[ind]=false;
            scc[ind]=scc_count;
            for(auto x:rev_gr[ind]) dfs1(x);
        }
    }

    void find_scc(){
        v=vector<bool>(n,true);
        while(!st.empty()) st.pop();
        for(int i=0;i<n;i++)
            if(v[i])
                dfs0(i);
        v=vector<bool>(n,true);
        while(!st.empty()){
            if(v[st.top()]){
                dfs1(st.top());
                scc_count++;
            }
            st.pop();
        }
    }
};

int main(){
    int n,m;
    cin>>n>>m;
    scc_struct scc(n);
    for(int i=0,x,y;i<m;i++){
        cin>>x>>y;
        scc.add_edge(x-1,y-1);
    }
    scc.find_scc();
    return 0;
}
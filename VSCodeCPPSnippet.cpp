{
	"main_default": {
		"prefix": "main_default",
		"body": [
			"#include<bits/stdc++.h>",
			"#define F first",
			"#define S second",
			"#define pb push_back",
			"#define mp make_pair",
			"#define full(a) a.begin(),a.end()",
			"#define rfull(a) a.rbegin(),a.rend()",
			"",
			"using namespace std;",
			"const double pi=acos(-1.0);",
			"const double pii=2*pi;",
			"const double eps=1e-6;",
			"const long long MOD=1e9+7;",
			"",
			"void solve(){",
			"",
			"}",
			"",
			"int main(){",
			"    std::ios::sync_with_stdio(false);",
			"    std::cin.tie(NULL);",
			"    std::cout.tie(NULL);",
			"",
			"    solve();",
			"    return 0;",
			"}"
		],
		"description": "default template for main function"
	},

	"main_test_case": {
		"prefix": "main_test_case",
		"body": [
			"#include<bits/stdc++.h>",
			"#define F first",
			"#define S second",
			"#define pb push_back",
			"#define mp make_pair",
			"#define full(a) a.begin(),a.end()",
			"#define rfull(a) a.rbegin(),a.rend()",
			"",
			"using namespace std;",
			"const double pi=acos(-1.0);",
			"const double pii=2*pi;",
			"const double eps=1e-6;",
			"const long long MOD=1e9+7;",
			"",
			"void solve(){",
			"",
			"}",
			"",
			"int main(){",
			"    std::ios::sync_with_stdio(false);",
			"    std::cin.tie(NULL);",
			"    std::cout.tie(NULL);",
			"",
			"    int t;",
			"    cin >> t;",
			"    while(t--){",
			"        solve();",
			"    }",
			"    return 0;",
			"}"
		],
		"description": "template for main function when test cases"
	},
	
	"main_kick_start": {
		"prefix": "main_kick_start",
		"body": [
			"#include<bits/stdc++.h>",
			"#define F first",
			"#define S second",
			"#define pb push_back",
			"#define mp make_pair",
			"#define full(a) a.begin(),a.end()",
			"#define rfull(a) a.rbegin(),a.rend()",
			"",
			"using namespace std;",
			"const double pi=acos(-1.0);",
			"const double pii=2*pi;",
			"const double eps=1e-6;",
			"const long long MOD=1e9+7;",
			"",
			"void solve(int test_case){",
			"",
			"}",
			"",
			"int main(){",
			"    std::ios::sync_with_stdio(false);",
			"    std::cin.tie(NULL);",
			"    std::cout.tie(NULL);",
			"",
			"    int t;",
			"    cin >> t;",
			"    for(int i=1;i<=t;i++){",
			"        solve(i);",
			"    }",
			"    return 0;",
			"}"
		],
		"description": "template for main function for google kick start"
	},

	"snip_long_pow_mod": {
		"prefix": "snip_long_pow_mod",
		"body": [
			"long long pow_mod(long long a, long long b, long long mod){",
			"    long long ans=1;",
			"    a%=mod;",
			"    while(b>0){",
			"        if(b&1){",
			"            ans*=a;",
			"            ans%=mod;",
			"        }",
			"        b=b>>1;",
			"        a=(a*a)%mod;",
			"    }",
			"    return ans;",
			"}"
		],
		"description": "defination pow mod for type long long"
	},

	"snip_long_pow": {
		"prefix": "snip_long_pow",
		"body": [
			"long long pow_mod(long long a, long long b){",
			"    long long ans=1;",
			"    while(b>0){",
			"        if(b&1)",
			"            ans*=a;",
			"        b=b>>1;",
			"        a*=a;",
			"    }",
			"    return ans;",
			"}"
		],
		"description": "defination pow for type long long"
	},

	"snip_int_pow": {
		"prefix": "snip_int_pow",
		"body": [
			"int pow_mod(int a, int b){",
			"    int ans=1;",
			"    while(b>0){",
			"        if(b&1)",
			"            ans*=a;",
			"        b=b>>1;",
			"        a*=a;",
			"    }",
			"    return ans;",
			"}"
		],
		"description": "defination pow for type int"
	},

	"snip_vec_int_print": {
		"prefix": "snip_vec_int_print",
		"body": [
			"void print_vec(vector<int>& a, int n=-1){",
			"    n=(n==-1?a.size():n);",
			"    for(int i=0;i<n;i++)",
			"        cout<<a[i]<<(i<n-1?\" \":\"\\n\");",
			"}"
		],
		"description": "print vec of int"
	},

	"snip_vec_longlong_print": {
		"prefix": "snip_vec_longlong_print",
		"body": [
			"void print_vec(vector<long long>& a, int n=-1){",
			"    n=(n==-1?a.size():n);",
			"    for(int i=0;i<n;i++)",
			"        cout<<a[i]<<(i<n-1?\" \":\"\\n\");",
			"}"
		],
		"description": "print vec of int"
	}

}

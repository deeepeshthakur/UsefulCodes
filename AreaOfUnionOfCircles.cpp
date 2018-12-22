#include<bits/stdc++.h>
#define ll int
#define pll std::pair<ll,ll>
#define rep(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define per(i,a,b) for(ll i=(ll)a;i>(ll)b;i--)
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

inline double sq(double a){ return a*a;};

// checks if two circles intersect. Returns true even if they touch
bool inter(int i,int j,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r){
	double d = std::sqrt(sq(x[i]-x[j])+sq(y[i]-y[j]));
	if(d >= r[i] && d >= r[j]){
		if((r[i]+r[j]) >= d)
			return true;
		else
			return false;
	}

	if(d<std::max(r[i],r[j]) && (d+std::min(r[i],r[j]))>=std::max(r[i],r[j])){
		return true;
	}
	return false;
}

//solves for two roots of a quadratic equation with real roots. x1 and x2 are the two roots
void quadratic(double a,double b,double c,double& x1,double& x2){
	x1 = (-b-std::sqrt(sq(b)-4*a*c))/(2*a);
	x2 = (-b+std::sqrt(sq(b)-4*a*c))/(2*a);
}

//solves for y in equation of line for a given x
void lyx(double a,double b,double c,double& x, double& y){
	if(b){
		y=(c-a*x)/b;
	}
}

// solves for intersection of a circle and a line provided they intersect. (x1,y1) and (x2,y2) are required points
bool lcf(double x,double y,double r,double a,double b, double c,std::vector<double>& ans){
	double x1,x2,y1,y2;
	if(b)
	{
		quadratic(1+sq(a/b),-2*x-2*(a/b)*(c/b-y),sq(x)+sq(c/b-y)-sq(r),x1,x2);
		lyx(a,b,c,x1,y1);
		lyx(a,b,c,x2,y2);
		ans = {x1,y1,x2,y2};
	}
	else{
		quadratic(1,-2*y,sq(y)+sq(c/a-x)-sq(r),y1,y2);
		x1=c/a;
		ans={x1,y1,x1,y2};
	}
	return true;
}

// checks whether a circle j lies completely inside the other circle i
inline bool f4(int j,int i,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r){
	if(j!=i && (std::sqrt(sq(x[i]-x[j])+sq(y[i]-y[j]))+r[j])<=r[i]){
		return true;
	}
	return false;
}

inline double f3(double x){
	return (std::asin(x)+x*std::sqrt(1-sq(x)))/2.0;
}

inline double f2(double x,double y,double r,double lt,double rt,int a){
	return y*(rt-lt)+a*sq(r)*(f3((rt-x)/r)-f3((lt-x)/r));
}

double f1(double lt,double rt,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r){
	double mid=(lt+rt)/2;
	std::vector<std::pair<int,int>> a1{};
	std::vector<std::pair<double,int>> f{};
	int ptr=0;
	rep(i,0,x.size()){
		std::vector<double> ans(4,0.0);
		if(std::abs(mid-x[i])<=r[i])
		{
		    lcf(x[i],y[i],r[i],1.0,0.0,mid,ans);
			f.pb({ans[1],ptr});
			a1.pb({i,-1});
			ptr++;
			f.pb({ans[3],ptr});
			a1.pb({i,1});
			ptr++;
		}
	}

	std::sort(full(f));
	double rval = 0.0;
	rep(i,0,f.size()){
		int pc=0,nc=0,l=a1[f[i].S].F,h;
		while(pc==0 || (pc!=nc)){
			if(a1[f[i].S].S>0){
				pc++;
			}
			else{
				nc++;
			}
			i++;			
		}
		i--;
		h=a1[f[i].S].F;
		rval+=std::abs(f2(x[h],y[h],r[h],lt,rt,1)-f2(x[l],y[l],r[l],lt,rt,-1));
	}
	return rval;
}

double f(int n,std::vector<double> x,std::vector<double> y,std::vector<double> r){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	double ans=0.0;
	std::vector<double> intglim{};
	{
		std::vector<double> xlim{};
		rep(i,0,n){
			xlim.pb(x[i]-r[i]);
			xlim.pb(x[i]+r[i]);
			rep(j,i+1,n){
				if(inter(i,j,x,y,r)){
					std::vector<double> ans(4,0.0);
					if(lcf(x[i],y[i],r[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r[i])-sq(r[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans)){
						xlim.pb(ans[0]);
						xlim.pb(ans[2]);
					}
				}
			}
		}
		std::sort(full(xlim));
		rep(i,0,xlim.size()){
			if(i){
				if(xlim[i-1]!=xlim[i]){
					intglim.pb(xlim[i]);
				}
			}
			else{
				intglim.pb(xlim[i]);
			}
		}	
	}

	rep(i,1,intglim.size()){
		ans+=f1(intglim[i-1],intglim[i],x,y,r);
	}
	return ans;
}


//input format 
// n        for number of circles
// n lines each containing x y r for that respective circle
// modify as per your need... Welcome!
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n;
	std::cin>>n;
	std::vector<double> xp(n,0.0),yp(n,0.0),rp(n,0.0),x{},y{},r{};
	rep(i,0,n){
		std::cin>>xp[i]>>yp[i]>>rp[i];
		rp[i]=std::abs(rp[i]);
	}

	std::vector<bool> in(n,true);
	rep(i,0,n){
		rep(j,0,n){
			if(in[i]&&f4(j,i,xp,yp,rp)){
				in[j]=false;
			}
		}
	}
	rep(i,0,n){
		if(in[i]){
			x.pb(xp[i]);
			y.pb(yp[i]);
			r.pb(rp[i]);
		}
	}
	std::cout<<std::fixed<<std::setprecision(5)<<f(x.size(),x,y,r)<<"\n";
	return 0;
}
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

inline double r2d(double a){
	return a*180/pi;
}

void printvec(std::vector<std::vector<double>>& a){
	rep(i,0,a.size()){
		std::cout<<r2d(a[i][0])<<" "<<r2d(a[i][1])<<"  ";
	}
	std::cout<<std::endl;
}

inline double sq(double a){
	return a*a;
}

inline double gth(double x,double y){
	if(x>0.0&&y==0.0){ return 0.0;}
	if(x>0.0&&y>0.0){ return std::atan(y/x);}
	if(x==0.0&&y>0){ return pi/2.0;}
	if(x<0.0&&y>0.0){ return pi-std::atan(std::abs(y/x));}
	if(x<0.0&&y==0.0){ return pi;}
	if(x<0.0&&y<0.0){ return pi+std::atan(std::abs(y/x));}
	if(x==0.0&&y<0.0){ return 1.5*pi;}
	if(x>0.0&&y<0.0){ return pii-std::atan(std::abs(y/x));}
	return 0.0;
}

inline bool inter(double x1,double y1,double x2,double y2,double r1,double r2){
	double d=std::sqrt(sq(x1-x2)+sq(y1-y2));
	return (d>=r1+r2 || std::abs(r1-r2)>=d) ? false:true;
}

inline bool pincircle(double x1,double y1,double x,double y,double r){
	return (std::sqrt(sq(x1-x)+sq(y1-y))<r) ? true:false;
}

inline bool inside(double x1,double y1,double x2,double y2,double r1,double r2){
	return (r1-r2>=std::sqrt(sq(x1-x2)+sq(y1-y2))) ? true:false;
}

void f10(std::vector<std::vector<double>>& t,double& a,double& b){
	if(b>pii){
		t.pb({a,pii});
		t.pb({0.0,b-pii});
	}
	else{
		t.pb({a,b});
	}
}

inline double integrate(double th1,double th2,double x,double y,double r){
	// std::cout<<r2d(th1)<<" "<<r2d(th2)<<" "<<x<<" "<<y<<" "<<r<<std::endl;
	return x*r*(std::sin(th2)-std::sin(th1))+sq(r)*((th2+std::sin(th2)*std::cos(th2))-(th1+std::sin(th1)*std::cos(th1)))*0.5;
}

void quadratic(double a,double b,double c,double& x1,double& x2){
	x1 = (-b-std::sqrt(sq(b)-4*a*c))/(2*a);
	x2 = (-b+std::sqrt(sq(b)-4*a*c))/(2*a);
}

void lyx(double a,double b,double c,double& x, double& y){
	if(b){
		y=(c-a*x)/b;
	}
}

void lcf(double x,double y,double r,double a,double b, double c,std::vector<double>& ans){
	double x1,x2,y1,y2;
	if(b)
	{
		quadratic(1+sq(a/b),-2*x-2*(a/b)*(c/b-y),sq(x)+sq(c/b-y)-sq(r),x1,x2);
		lyx(a,b,c,x1,y1);
		lyx(a,b,c,x2,y2);
		ans={gth(x1-x,y1-y),gth(x2-x,y2-y)};
		if(ans[0]>ans[1]){
			std::swap(ans[0],ans[1]);
		}
	}
	else{
		quadratic(1,-2*y,sq(y)+sq(c/a-x)-sq(r),y1,y2);
		x1=c/a;
		ans={gth(x1-x,y1-y),gth(x1-x,y2-y)};
		if(ans[0]>ans[1]){
			std::swap(ans[0],ans[1]);
		}
	}
}

double f1(int n,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r1,std::vector<double>& r2){
	double ans=0.0;
	rep(i,0,n){
		//outer circle
		{
			std::vector<std::vector<double>> m{},z{},p{};
			rep(j,0,n){
				if(i!=j){
					if(inter(x[i],y[i],x[j],y[j],r1[i],r1[j])){
						if(inter(x[i],y[i],x[j],y[j],r1[i],r2[j])){
							std::vector<double> ans1{},ans2{};
							lcf(x[i],y[i],r1[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r1[i])-sq(r1[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans1);
							lcf(x[i],y[i],r1[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r1[i])-sq(r2[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans2);
							if(!pincircle(x[i]+r1[i]*std::cos((ans1[0]+ans1[1])*0.5),y[i]+r1[i]*std::sin((ans1[0]+ans1[1])*0.5),x[j],y[j],r1[j])){
								std::swap(ans1[0],ans1[1]);
							}

							if(!pincircle(x[i]+r1[i]*std::cos((ans2[0]+ans2[1])*0.5),y[i]+r1[i]*std::sin((ans2[0]+ans2[1])*0.5),x[j],y[j],r2[j])){
								std::swap(ans2[0],ans2[1]);
							}

							if(ans1[0]>ans1[1]){
								ans1[1]+=pii;
							}

							if(ans2[0]>ans2[1]){
								ans2[1]+=pii;
							}
							f10(z,ans1[0],ans2[0]);
							f10(z,ans2[1],ans1[1]);
							f10(m,ans2[0],ans2[1]);						
						}
						else{
							std::vector<double> ans1{};
							lcf(x[i],y[i],r1[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r1[i])-sq(r1[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans1);
							if(!pincircle(x[i]+r1[i]*std::cos((ans1[0]+ans1[1])*0.5),y[i]+r1[i]*std::sin((ans1[0]+ans1[1])*0.5),x[j],y[j],r1[j])){
								std::swap(ans1[0],ans1[1]);
							}

							if(ans1[0]>ans1[1]){
								ans1[1]+=pii;
							}

							f10(z,ans1[0],ans1[1]);
						}
					}
					else{
						if(inside(x[i],y[i],x[j],y[j],r1[i],r1[j])){
							if(inside(x[i],y[i],x[j],y[j],r1[i],r2[j])){
								m.pb({0.0,pii});
							}
							else{
								if(inter(x[i],y[i],x[j],y[j],r1[i],r2[j])){
									std::vector<double> ans1{0.0,pii},ans2{};
									lcf(x[i],y[i],r1[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r1[i])-sq(r2[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans2);

									if(!pincircle(x[i]+r1[i]*std::cos((ans2[0]+ans2[1])*0.5),y[i]+r1[i]*std::sin((ans2[0]+ans2[1])*0.5),x[j],y[j],r2[j])){
										std::swap(ans2[0],ans2[1]);
									}

									if(ans2[0]>ans2[1]){
										ans2[1]+=pii;
									}

									if(ans2[1]>pii){
										m.pb({ans2[1]-pii,ans2[0]});
										z.pb({0.0,ans2[1]-pii});
										z.pb({ans2[0],pii});
									}
									else{
										m.pb({0.0,ans2[0]});
										z.pb({ans2[0],ans2[1]});
										m.pb({ans2[1],pii});
									}
								}
								else{
									m.resize(0);
									z.resize(0);
									z.pb({0.0,pii});
									j=n+1;
								}
							}
						}
					}
				}
			}

			{
				p.resize(z.size()+m.size());
				rep(i,0,z.size()){
					p[i]=z[i];
				}
				rep(i,z.size(),z.size()+m.size()){
					p[i]=m[i-z.size()];
				}
			}

			std::sort(full(z));
			std::sort(full(m));
			std::sort(full(p));

			std::queue<std::pair<double,double>> qm{},qz{},qp{};
			{
				for(int i=0;i<z.size();i++){
					double s=z[i][0],e=z[i][1];
					while(i+1<z.size()&&e>=z[i+1][0]){
						e=std::max(e,z[i+1][1]);
						i++;
					}
					qz.push({s,e});
				}

				for(int i=0;i<m.size();i++){
					double s=m[i][0],e=m[i][1];
					while(i+1<m.size()&&e>=m[i+1][0]){
						e=std::max(e,m[i+1][1]);
						i++;
					}
					qm.push({s,e});
				}

				for(int i=0;i<p.size();i++){
					double s=p[i][0],e=p[i][1];
					while(i+1<p.size()&&e>=p[i+1][0]){
						e=std::max(e,p[i+1][1]);
						i++;
					}
					qp.push({s,e});
				}
			}

			{
				double s=0.0,e;
				while(!qp.empty()){
					e=qp.front().F;
					ans+=integrate(s,e,x[i],y[i],r1[i]);
					s=qp.front().S;
					qp.pop();
				}
				e=pii;
				ans+=integrate(s,e,x[i],y[i],r1[i]);

				while(!qm.empty()||!qz.empty()){
					if(qm.empty()||qz.empty()){
						if(qm.empty()){
							while(!qz.empty()){
								qz.pop();
							}
						}
						else{
							while(!qm.empty()){
								ans+=integrate(qm.front().S,qm.front().F,x[i],y[i],r1[i]);
								qm.pop();
							}
						}
					}
					else{
						if(qz.front().F<=qm.front().F){
							if(qz.front().S<=qm.front().F){
								qz.pop();
							}
							else{
								if(qz.front().S<=qm.front().S){
									qm.front().F=qz.front().S;
									qz.pop();
								}
								else{
									qz.front().F=qm.front().S;
									qm.pop();
								}
							}
						}
						else{
							if(qz.front().F<=qm.front().S){
								ans+=integrate(qz.front().F,qm.front().F,x[i],y[i],r1[i]);
								qm.front().F=qz.front().F;
							}
							else{
								ans+=integrate(qm.front().S,qm.front().F,x[i],y[i],r1[i]);
								qm.pop();
							}
						}
					}
				}
			}
		}
		// std::cout<<std::endl;
		//inner circle
		{
			std::vector<std::vector<double>> z{};
			rep(j,0,n){
				if(i!=j){
					if(inter(x[i],y[i],x[j],y[j],r2[i],r1[j])){
						if(inter(x[i],y[i],x[j],y[j],r2[i],r2[j])){
							std::vector<double> ans1{},ans2{};
							lcf(x[i],y[i],r2[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r2[i])-sq(r1[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans1);
							lcf(x[i],y[i],r2[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r2[i])-sq(r2[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans2);

							if(!pincircle(x[i]+r2[i]*std::cos((ans1[0]+ans1[1])*0.5),y[i]+r2[i]*std::sin((ans1[0]+ans1[1])*0.5),x[j],y[j],r1[j])){
								std::swap(ans1[0],ans1[1]);
							}

							if(!pincircle(x[i]+r2[i]*std::cos((ans2[0]+ans2[1])*0.5),y[i]+r2[i]*std::sin((ans2[0]+ans2[1])*0.5),x[j],y[j],r2[j])){
								std::swap(ans2[0],ans2[1]);
							}

							if(ans1[0]>ans1[1]){
								ans1[1]+=pii;
							}

							if(ans2[0]>ans2[1]){
								ans2[1]+=pii;
							}

							f10(z,ans1[0],ans2[0]);
							f10(z,ans2[1],ans1[1]);							
						}
						else{
							std::vector<double> ans1{};
							lcf(x[i],y[i],r2[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r2[i])-sq(r1[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans1);
							if(!pincircle(x[i]+r2[i]*std::cos((ans1[0]+ans1[1])*0.5),y[i]+r2[i]*std::sin((ans1[0]+ans1[1])*0.5),x[j],y[j],r1[j])){
								std::swap(ans1[0],ans1[1]);
							}

							if(ans1[0]>ans1[1]){
								ans1[1]+=pii;
							}

							f10(z,ans1[0],ans1[1]);
						}
					}
					else{
						if(inside(x[i],y[i],x[j],y[j],r2[i],r1[j])){
							if(!inside(x[i],y[i],x[j],y[j],r2[i],r2[j])){
								if(inter(x[i],y[i],x[j],y[j],r1[i],r2[j])){
									std::vector<double> ans2{};
									lcf(x[i],y[i],r2[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r2[i])-sq(r2[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans2);

									if(!pincircle(x[i]+r2[i]*std::cos((ans2[0]+ans2[1])*0.5),y[i]+r2[i]*std::sin((ans2[0]+ans2[1])*0.5),x[j],y[j],r2[j])){
										std::swap(ans2[0],ans2[1]);
									}

									if(ans2[0]>ans2[1]){
										ans2[1]+=pii;
									}

									if(ans2[1]>pii){
										z.pb({0.0,ans2[1]-pii});
										z.pb({ans2[0],pii});
									}
									else{
										z.pb({ans2[0],ans2[1]});
									}
								}
								else{
									z.resize(0);
									z.pb({0.0,pii});
									j=n+1;
								}
							}
						}
					}
				}
			}

			std::sort(full(z));
			std::queue<std::pair<double,double>> qz{};
			for(int i=0;i<z.size();i++){
				double s=z[i][0],e=z[i][1];
				while(i+1<z.size()&&e>=z[i+1][0]){
					e=std::max(e,z[i+1][1]);
					i++;
				}
				qz.push({s,e});
			}
		
			{
				double s=0.0,e;
				while(!qz.empty()){
					e=qz.front().F;
					ans-=integrate(s,e,x[i],y[i],r2[i]);
					s=qz.front().S;
					qz.pop();
				}
				e=pii;
				ans-=integrate(s,e,x[i],y[i],r2[i]);
			}
		}
		// std::cout<<std::endl;
	}
}

bool truef(int i,int j,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r1,std::vector<double>& r2){
	if(
		(x[i]<x[j]) || 
	    (x[i]==x[j] && y[i]<y[j]) ||
	    (x[i]==x[j] && y[i]==y[j] && r2[i]<r2[j]) ||
	    (x[i]==x[j] && y[i]==y[j] && r2[i]==r2[j] && r1[i]>=r1[j])
	  ){ return true;}
	return false;
}

void swapf(int i,int j,std::vector<double>& x,std::vector<double>& y,std::vector<double>& r1,std::vector<double>& r2){
	std::swap(x[i],x[j]);
	std::swap(y[i],y[j]);
	std::swap(r1[i],r1[j]);
	std::swap(r2[i],r2[j]);
}

double f(int n,std::vector<double>& xp,std::vector<double>& yp,std::vector<double>& r1p,std::vector<double>& r2p){
	std::vector<bool> flag(n,true);
	std::vector<double> x,y,r1,r2;
	
	{
		//n^2 sorting on basis of centre and then radius
		for(int i=0;i<n;i++){
			int cm=i;
			for(int j=i+1;j<n;j++){
				if(truef(j,cm,xp,yp,r1p,r2p)){
					cm=j;
				}
			}
			swapf(i,cm,xp,yp,r1p,r2p);
		}
	}

	rep(i,0,n){
		if(i+1<n){
			if(xp[i]==xp[i+1] && yp[i]==yp[i+1]){
				if(r2p[i+1]<=r1p[i] && r2p[i]<=r1p[i+1]){
					r1p[i+1]=std::max(r1p[i],r1p[i+1]);
					r2p[i+1]=std::min(r2p[i],r2p[i+1]);
					flag[i]=false;
				}
			}
		}
		if(flag[i]&&r2p[i]!=r1p[i]){
			x.pb(xp[i]);
			y.pb(yp[i]);
			r1.pb(r1p[i]);
			r2.pb(r2p[i]);
		}
	}
	return f1(x.size(),x,y,r1,r2);
}

//Input
//n    number of annuli/rings
//next n        lines each for on ring
//x y r2 r1     coordinates of center, inner radius, outer radius
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n;
	std::cin>>n;
	std::vector<double> x(n,0.0),y(n,0.0),r1(n,0.0),r2(n,0.0);
	rep(i,0,n){
		std::cin>>x[i]>>y[i]>>r2[i]>>r1[i];
	}
	std::cout<<f(n,x,y,r1,r2)<<std::endl;
	return 0;
}
#include<bits/stdc++.h>
using namespace std;


unsigned long long powf(unsigned long long a,unsigned long long b,unsigned long long mod){
	if(b<2){
		if(b==0){
			return 1;
		}
		if(b==1){
			return a%mod;
		}
	}
	unsigned long long x=powf(a,b/2,mod);
	x=(x*x)%mod;
	if(b%2){
		x=(x*a)%mod;
	}
	return x%mod;
}

//This function uses deterministic version of Miller-Rabin to test for primality
//n < 4759123141
//https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_variants
bool f(unsigned long long n){
	unsigned long long a,d,s;
	long long x[]={2,3,61},p2[40];
	p2[0]=1;
	for(int i=1;i<40;i++){
		p2[i]=p2[i-1]*2;
	}

	bool f;
	f=false;
	if(n<4||n==61){
		if(n!=1)
			f=true;
	}
	else{
		if(n%2){
			f=true;
			bool f2,f3;
			s=0;
			while((n-1)%p2[s+1]==0)
				s++;
			d=(n-1)/p2[s];
			for(int i=0;i<3;i++){
				f3=true;
				f2=false;
				a=x[i];
				if(powf(a,d,n)!=1)
					f2=true;
				for(int j=0;j<s;j++){
					if(powf(a,p2[j]*d,n)==n-1)
						f3=false;
				}

				if(f2&&f3){
					f=false;
					i=4;
				}
			}
		}
	}
	return f;
}

int main(){
	unsigned long long n;
	std::cin>>n;
	if(f(n))
		std::cout<<"1\n";
	else
		std::cout<<"0\n";	
	return 0;
}
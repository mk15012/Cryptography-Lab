#include <bits/stdc++.h>  
using namespace std; 
#define ll long long int

ll euclid(ll a, ll b, ll& x, ll& y) 
{ 
    if (b == 0) { 
        x = 1; 
        y = 0; 
        return a; 
    } 
    else { 
        ll g = euclid(b, a % b, x, y); 
        ll x1 = x, y1 = y; 
        x = y1; 
        y = x1 - (a / b) * y1; 
        return g; 
    } 
} 

void answer(ll a, ll b, ll c) 
{ 
    ll x, y; 
    if (a == 0 && b == 0) { 
		 if (c == 0) { 
            cout<<"Infinite Solutions Exist"<<endl; 
        }else { 
            cout<<"No Solution Possible"<<endl; 
        } 
    } 
    ll gcd = euclid(a, b, x, y); 

    if (c % gcd != 0)
        cout<<"No Solution Possible"<<endl; 
    else
    { 
    	 cout<<"Particular Solution : ("<<x * (c / gcd)<<", "<<y * (c / gcd)<<")";
		 cout<<"\nGeneral Solution : ("<<x * (c/gcd)<<"+"<<(b/gcd)<<"k, "<<y * (c/gcd)<<"-"<<(a/gcd)<<"k)";
    } 
} 
  
int main() 
{ 
    ll a, b, c; 
    cout<<"Enter the value of a,b and c :  "<<endl;
  	cin>>a>>b>>c;
    answer(a, b, c); 
    return 0; 
}

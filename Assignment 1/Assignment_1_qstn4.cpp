#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL)

ll gcd(ll a, ll b)
{
    if(b==0)
        return a;
    
    else
        return gcd(b,a%b);
}

ll mul_inverse(ll a, ll n) 
{ 
	a = a%n; 
	for (ll x=1;x<n;x++) 
    	if ((a*x) % n == 1) 
		    return x; 
} 

int main() 
{ 
    ll n;
    cout<<"Enter the value of n : ";
    cin>>n;
    cout<<"\nAdditive Inverse : \n";
    cout<<"\nNumber\t\tInverse\n";
    for(ll i=0;i<n;i++)
        cout<<i<<"\t\t"<<-i<<endl;

    cout<<"\n\nMultiplicative Inverse : \n";
    cout<<"\nNumber\t\tInverse\n";
    for(ll i=1;i<n;i++)
    {
        if(gcd(i,n) == 1)
            cout<<i<<"\t\t"<<mul_inverse(i, n)<<endl;
    }
        
	return 0; 
} 

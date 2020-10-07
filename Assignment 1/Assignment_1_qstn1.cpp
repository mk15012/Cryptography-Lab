#include<bits/stdc++.h>
using namespace std;
#define ll long long int

ll gcd(ll a, ll b)
{
    if(b==0)
        return a;
    
    else
        return gcd(b,a%b);
}

int main()
{
    ll t;
    cout<<"Enter the number of test cases :  ";
    cin>>t;
    while(t--)
    {
        ll a,b;
        cout<<"\nEnter the two integers :  ";
        cin>>a>>b;
        
        cout<<"The gcd of two numjbers is :  "<<gcd(a,b)<<endl;
    }

    return 0;
}

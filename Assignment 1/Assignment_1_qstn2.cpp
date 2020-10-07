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

int main()
{
    ll t;
    cout<<"Equation : a × s + b × t= gcd(a, b)"<<endl;
    cout<<"\nEnter the number of test cases : ";
    cin>>t;
    while(t--)
    {
        ll a,b,r1,r2,q,r,s1,s2,s,t1,t2,t;
        cout<<"\nEnter the values of a and b :  ";
        cin>>a>>b;
        r1=a,r2=b;
        s1=1,s2=0;
        t1=0,t2=1;
        
        while(r2>0)
        {
            q=r1/r2;
            r=r1%r2;
            s=s1-q*s2;
            t=t1-q-t2;
            r1=r2;
            r2=r;
            s1=s2;
            s2=s;
            t1=t2;
            t2=t;
        }
        
        cout<<"\nGCD of two numbers (a,b) is :  "<<r1;
        cout<<"\ns = "<<s1;
        cout<<"\nt = "<<t1<<endl;
    }

}
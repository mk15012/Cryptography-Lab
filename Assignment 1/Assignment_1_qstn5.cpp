#include<bits/stdc++.h>
#define ll long long int
using namespace std;
 
ll check_inverse(int a, ll n) 
{ 
	a = a%n; 
	for (ll x=1;x<n;x++) 
    	if ((a*x) % n == 1) 
		    return x; 
    
    return -1;
}
 
int main()
{
    ll n=3,k;
	ll mat[n][n], i, j;
	ll det = 0;
	
	cout<<"Enter elements of 3*3 matrix :\n";
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
           cin>>mat[i][j];
	
	cout<<"\nEnter the modulo value :  ";
	cin>>k;
	
	printf("\nGiven matrix is:\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++)
			cout<<mat[i][j]<<"\t";
		cout<<"\n";
	}

	for(i=0;i<n;i++)
		det = det + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
	
	cout<<"\n\nDeterminant: "<<det<<endl;
    det = check_inverse(det,k);
    	cout<<"\n\nDeterminant: "<<det<<endl;
    if(det == -1)
    {
        cout<<"Modulo Inverse Matrix does not exist\n";
    }
    else
    {
        cout<<"\n\nModulo Inverse of matrix is: \n";
    	for(i = 0; i < 3; i++)
    	{
    		for(j = 0; j < 3; j++)
    			cout<<(((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))* det)%k<<"\t";
    	 
    	    cout<<"\n";
    	}
    }

   return 0;
}

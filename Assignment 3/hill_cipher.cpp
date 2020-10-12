#include<bits/stdc++.h>
using namespace std;

string removeSpaces(string str) 
{ 
    int count = 0; 
  
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i];
            
    str.erase(count);
    return str;
}

int gcd(int a, int b)
{
    if(b==0)
        return a;
    
    else
        return gcd(b,a%b);
}

int mul_inverse(int a, int n) 
{ 
	if(gcd(a,n) != 1)
		return -1;
		
	a = a%n; 
	for (int x=1;x<n;x++) 
    	if ((a*x) % n == 1) 
		    return x; 
} 

int modulo(int a,int b)
{
	if(a>=0)
		return (a%b);
	else
		return b + a%b ;
}

string hill_encrypt(string str,int n,int key[3][3])
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);	
	str = removeSpaces(str);
	int m = n/3;
	
	if(n%3 !=0)
		m++;

	int plain[m][3];
	int start=0;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(start<n)
			{
				plain[i][j]=str[start]-'A';	
				start++;
			}
			else
				plain[i][j]=25;
		}
	}

	int cipher_mat[100][100];
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
			cipher_mat[i][j] = 0;


	for(int i=0;i<m;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
				cipher_mat[i][j] += plain[i][k] * key[k][j];
		}
	}
	
	for(int i=0;i<m;i++)
		for(int j=0;j<3;j++)
			cipher_mat[i][j]=cipher_mat[i][j]%26;
	
	string result="";
	
	for(int i=0;i<m;i++)
		for(int j=0;j<3;j++)
			result += cipher_mat[i][j] + 'A';
	
	cout<<"\nCipher text\t: "<<result<<endl;

	return result;
}

void hill_decrypt(string str, int n, int key[3][3])
{
	int det=0;
	for(int i=0;i<3;i++)
	    det += (key[0][i]*(key[1][(i+1)%3]*key[2][(i+2)%3] - key[1][(i+2)%3]*key[2][(i+1)%3]));
	
	int len;
	  	
	len=modulo(det,26);

	int inv = mul_inverse(len,26);

  	int cfr[3][3],adj[3][3];

  	for(int i=0;i<3;i++)
	{
      	for(int j=0;j<3;j++)
      	{
      		cfr[i][j] = ((key[(i+1)%3][(j+1)%3] * key[(i+2)%3][(j+2)%3]) - (key[(i+1)%3][(j+2)%3]*key[(i+2)%3][(j+1)%3]));
      		cfr[i][j] = modulo(cfr[i][j],26);
       }
   }
   
	for(int i=0;i<3;i++)
      	for(int j=0;j<3;j++)
			adj[j][i]=cfr[i][j];	  
   
   	int inverse[3][3];
   
	for(int i=0;i<3;i++)
	{
   	    for(int j=0;j<3;j++)
   	    	inverse[i][j]=modulo(adj[i][j]*inv,26);
	}
	
	int m = n/3;
	if(n%3 !=0)
		m++;
	
	int cipher_mat[m][3];
	int start=0;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<3;j++)
		{
			cipher_mat[i][j]=str[start]-'A';	
			start++;	
		}
	}
		
	int real[100][100];
	
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
			real[i][j] = 0;
			
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
				real[i][j]+=(cipher_mat[i][k]*inverse[k][j]);		
		}
	}

	for(int i=0;i<m;i++)
		for(int j=0;j<3;j++)
			real[i][j]=real[i][j]%26;
	
	
	string result="";

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<3;j++)
			result+= real[i][j] + 'a';
	}
		
	string ans=result.substr(0,n);
	cout<<"Plain Text\t: "<<ans<<endl;

}


int main()
{
	cout<<"<---------------------------HILL CIPHER------------------>\n\n";
	
	string str;
    cout<<"Enter the string  :  ";
	getline(cin,str);
	
	str = removeSpaces(str);
	
	int key[3][3];
	
	while(1)
	{
		cout<<"\n\nEnter the elements of key matrix: \n";
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				cin>>key[i][j];

		int det=0;
		for(int i=0;i<3;i++)
	      det = det + (key[0][i]*(key[1][(i+1)%3]*key[2][(i+2)%3] - key[1][(i+2)%3]*key[2][(i+1)%3]));
	
	  	int k;
	  	
		k=modulo(det,26);
	  	
	  	if(mul_inverse(k,26) == -1)
	  		cout<<"Invalid key matrix !! Enter valid marix\n";  	

		else
			break;
	}
	
	int n=str.length();

	string ans= hill_encrypt(str,n,key);	
	hill_decrypt(ans,n,key);

	return 0;
}

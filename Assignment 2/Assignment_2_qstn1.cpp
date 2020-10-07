#include<bits/stdc++.h>
using namespace std;
#define pb push_back

int additive_key = 0;
int multiplicative_key = 0;
int affine_key1 = 0, affine_key2 = 0;

int gcd(int a, int b)
{
    if(b==0)
        return a;
    
    else
        return gcd(b,a%b);
}

string additive_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	additive_key = rand()%1000;
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
	        int x = str[i]-'A';
	        int sum = (x + additive_key)%26;
        	str[i] = (char)(sum + 'A');	
		}
    }
	cout<<"\nKey :  "<<additive_key;
    cout<<"\nCipher text :  "<<str<<endl;

	return str;
}

void additive_decrypt(string str)
{
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
	        int x = str[i]-'A';
	        int sum = (x - additive_key)%26;
	        if(sum < 0)
	        	sum += 26;
	        
        	str[i] = (char)(sum + 'A');	
		}
    }
    
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<"Plain text :  "<<str<<endl;
}

int mul_inverse(int a, int n) 
{ 
	a = a%n; 
	for (int x=1;x<n;x++) 
    	if ((a*x) % n == 1) 
		    return x;
	
	return -1;
}

string multiplicative_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	multiplicative_key = rand()%1000;
	
	while(gcd(multiplicative_key,26) != 1)
		multiplicative_key = rand()%100;
	
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    		str[i] = ((str[i]-'A')*multiplicative_key)%26 +'A';
    }
        
    cout<<"\nKey :  "<<multiplicative_key;
    cout<<"\nCipher Text :  "<<str<<endl;
    return str;
}

void multiplicative_decrypt(string str)
{
	multiplicative_key = multiplicative_key%26;
	int key_inverse = mul_inverse(multiplicative_key,26);
	
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
			int x = (str[i]-'A')*key_inverse;
			x=x%26;
			str[i] = x + 'A';    		
		}
    }
        
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<"Plain text :  "<<str<<endl;
}


string affine_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	affine_key1 = rand()%1000;
	
	while(gcd(affine_key1,26) != 1)
		affine_key1 = rand()%1000;

	affine_key2 = rand()%1000;
	for(int i=0;i<str.length();i++)
		if(str[i] != ' ')
			str[i] = ((str[i]-'A')*affine_key1)%26 +'A';
    	
    	
    for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
    		int x = str[i]-'A';
	        int sum = (x + affine_key2)%26;
    	    str[i] = (char)(sum + 'A');
		}
	}
    
    cout<<"\nKey 1 :  "<<affine_key1;
    cout<<"\nKey 2 :  "<<affine_key2;
    cout<<"\nCipher text :  "<<str<<endl;
    
    return str;
}


void affine_decrypt(string str)
{
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
	        int x = str[i]-'A';
	        int sum = (x - affine_key2)%26;
	        if(sum < 0)
	        	sum += 26;
	        
        	str[i] = (char)(sum + 'A');	
		}
    }
	
	affine_key1 = (affine_key1)%26;
	int key_inverse = mul_inverse(affine_key1,26);
	
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
			int x = (str[i]-'A')*key_inverse;
			x=x%26;
			str[i] = x + 'A';    		
		}
    }
        
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<"Plain text :  "<<str<<endl;
}


string atbash_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
    		int x = str[i] - 'A';
			str[i] = (25 - x) +'A';    			
		}

    }
        
    cout<<"\nCipher Text :  "<<str<<endl;
	return str;
}

void atbash_decrypt(string str)
{
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
    		int x = str[i] - 'A';
			str[i] = (25 - x) +'A';    			
		}

    }

	transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<"Plain text :  "<<str<<endl;
}

string rot13_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
    		int x = str[i] - 'A';
    		if(x > 12)
		    	str[i] = ((str[i]-'A')-13)%26 +'A';    			
    		else
    			str[i] = ((str[i]-'A')+13)%26 +'A';    			
		}

    }
        
    cout<<"\nCipher Text :  "<<str<<endl;
    return str;
}

void rot13_decrypt(string str)
{
	for(int i=0;i<str.length();i++)
    {
    	if(str[i] != ' ')
    	{
    		int x = str[i] - 'A';
    		if(x > 12)
		    	str[i] = ((str[i]-'A')-13)%26 +'A';    			
    		else
    			str[i] = ((str[i]-'A')+13)%26 +'A';    			
		}

    }
        
	transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout<<"Plain text :  "<<str<<endl;
}


int main()
{
	cout<<"<----------------------MENU DRIVEN PROGRAM for ENCRYPTION and DECRYPTION-------------------->";
	
	srand(time(0));

	string str;
	int choice;
	cout<<"\n\nEnter the String :  ";
	getline(cin,str);	

	while(1)
	{

		cout<<"\n1. Additive Cipher";
		cout<<"\n2. Multiplicative Cipher";
		cout<<"\n3. Affine Cipher";
		cout<<"\n4. Atbash Cipher";
		cout<<"\n5. ROT-13 Cipher";
		cout<<"\n6. Exit";
		
		cout<<"\n\nEnter Choice :  ";
		cin>>choice;
		
		if(choice == 6)
			break;
			
		switch(choice)
		{
			case 1 :
			{
				string ans = additive_encrypt(str);
				additive_decrypt(ans);
				break;
			}
			
			case 2 :
			{
				string ans = multiplicative_encrypt(str);
				multiplicative_decrypt(ans);
				break;
			}
			
			case 3 :
			{
				string ans = affine_encrypt(str);
				affine_decrypt(ans);
				break;
			}
			
			case 4 :
			{
				string ans = atbash_encrypt(str);
				atbash_decrypt(ans);
				break;
			}
			
			case 5 :
			{
				string ans = rot13_encrypt(str);
				rot13_decrypt(ans);			
				break;
			}
						
			default :
			{
				cout<<"Invalid Input\n";
				break;
			}
		}
	}
	
    return 0;
}

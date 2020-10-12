#include<bits/stdc++.h>
using namespace std;
#define ll long long int

char adfgvx_mat[36];
string key;

string removeSpaces(string str) 
{ 
    int count = 0; 
  
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i];
            
    str.erase(count);
    return str;
}

string adfgvx_encrypt(string str)
{
	string polybis_key;
	cout<<"\nEnter the keyword for the Polybis Matrix :  ";
	cin>>polybis_key;
	
	polybis_key = removeSpaces(polybis_key);
	
	cout<<"\nEnter the agreed upon key :  ";
	cin>>key;
	
	transform(key.begin(), key.end(), key.begin(), ::toupper);	
	transform(str.begin(), str.end(), str.begin(), ::toupper);	
	transform(polybis_key.begin(), polybis_key.end(), polybis_key.begin(), ::toupper);	
	
	int j=0;
	int vis[26]= {0};
	int vis1[10] = {0};
	for(int i=0;i<polybis_key.length();i++)
	{
		if(!vis[polybis_key[i]-'A'])
		{
			adfgvx_mat[j++] = polybis_key[i];
			vis[polybis_key[i]-'A'] = 1;
		}
	}	
	
	for(int i=0;i<26;i++)
	{
		if( !vis[i] )
		{
			adfgvx_mat[j++] = i+'A';
			vis[i] = 1;
		}
	}
	
	for(int i=0;i<10;i++)
	{
		if(!vis1[i])
		{
			adfgvx_mat[j++] = i+'0';
			vis1[i] = 1;
		}
	}
	
	string ans="";
	char pos[6] = {'A','D','F','G','V','X'};
		
	for(int i=0;i<str.length();i++)
	{
		if(str[i] == ' ')
			ans+= " ";	
					
		else
		{
			for(j=0;j<36;j++)
			{
				if(adfgvx_mat[j] == str[i])
				{
					ans+= pos[j/6];
					ans+= pos[j%6];
					break;
				}	
			}
		}
	}
	
	vector<string> adfgvx_vec(26);
	for(int i=0;i<26;i++)
	{
		adfgvx_vec[i] = "";
		adfgvx_vec[i]+= '#';
	}
	
	j=0;
	for(int i=0;i<ans.length();i++)
	{
		j=j%key.length();
		int temp = key[j] - 'A';
		adfgvx_vec[temp] += ans[i];
		j++;
	}
	
	while(j<key.length())
	{
		int temp = key[j] - 'A';
		adfgvx_vec[temp] += 'P';
		j++;
	}
		
	string result = "";
	int idx=0;
	for(int i=0;i<26;i++)
	{
		if(adfgvx_vec[i].length() > 1)
		{
			adfgvx_vec[i].erase(adfgvx_vec[i].begin()+0);
			result+= adfgvx_vec[i];
		}		
	}
	
	cout<<"\nPolybis Keyword\t:  "<<polybis_key;
	cout<<"\nADFGX Key\t:  "<<key;
	cout<<"\nCipher Text\t:  "<<result<<endl;

	return result;
}


void adfgvx_decrypt(string str)
{
	string adfgx_key = key;
	string result="",result1="";
	char pos[6] = {'A','D','F','G','V','X'};
	
	int len = adfgx_key.length();
	int len1 = str.length() / len;
	sort(adfgx_key.begin(),adfgx_key.end());
	
	vector<string> adfgx_vec(26);
	for(int i=0;i<26;i++)
	{
		adfgx_vec[i] = "";
		adfgx_vec[i]+= '#';
	}
	
	int k=0;
	for(int i=0;i<str.length();i=i+len1)
	{
		for(int j=i;j<i+len1;j++)
			adfgx_vec[adfgx_key[k]-'A']+= str[j];

		k++;
	}
	
	string ans[len];
	for(int i=0;i<len;i++)
		ans[i] = "";
			
	int j=0;
	for(int i=0;i<key.length();i++)
	{
		ans[j] += adfgx_vec[key[i]-'A'];
		ans[j].erase(ans[j].begin() + 0);
		j++;
	}
	
	int n = ans[0].length();
	for(int i=0;i<n;i++)
	{
		for(j=0;j<len;j++)
		{
			if(ans[j][i] != 'P')
			{
				result1 += ans[j][i];
			}
		}
	}
	
	for(int i=0;i<result1.length();i=i+2)
	{
		if(result1[i] == ' ')
		{
			result += " ";
			i--;
			continue;
		}
		
		char x = result1[i];
		char y = result1[i+1];
		int pos1=0,pos2=0;
		
		for(int p=0;p<6;p++)
		{
			if(pos[p] == x)
			{
				pos1 = p;
				break;
			}
		}
		
		for(int p=0;p<6;p++)
		{
			if(pos[p] == y)
			{
				pos2 = p;
				break;
			}
		}
	
		result += adfgvx_mat[6*pos1 + pos2];
	}
	
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	cout<<"Plain Text\t:  "<<result<<endl;
}

int main() 
{ 
	cout<<"<--------ADFGVX CIPHER-------------------->\n\n";
    
	string str,key;
	cout<<"Enter the plain text :  ";
  	getline(cin,str);	
	
	
	string ans = adfgvx_encrypt(str);
	adfgvx_decrypt(ans);   
	
	return 0; 
} 

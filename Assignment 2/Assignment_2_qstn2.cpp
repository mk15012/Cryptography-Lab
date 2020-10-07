#include<bits/stdc++.h>
using namespace std;
#define pb push_back

int bifid_size;

vector<vector<int> > vec_bifid(26,vector<int> (2, 0));

vector<vector<int> > vec_trifid(26,vector<int> (2, 0));
char mat1[9],mat2[9],mat3[9];
	
char nilhist_mat[25];
string nilhist_key;

string removeSpaces(string str) 
{ 
    int count = 0; 
  
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i];
            
    str.erase(count);
    return str;
}

string bifid_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);	
	string key;	
	cout<<"\nEnter the agreed keyword for the Polybis Matrix :  ";
	cin>>key;
	
	key = removeSpaces(key);
	
	transform(key.begin(), key.end(), key.begin(), ::toupper);	
	cout<<"Enter the block size :  ";
	cin>>bifid_size;
	
	string ans="";
	
	char mat[25];
	int j=0;
	int vis[26]= {0};
	for(int i=0;i<key.length();i++)
	{
		if(!vis[key[i]-'A'])
		{
			mat[j++] = key[i];
			vis[key[i]-'A'] = 1;
			
			int test = key[i]-'A';
			if(test == 8)
				vis[9] = 1;
			
			if(test == 9)
				vis[8] = 1;
		}
	}	
	
	for(int i=0;i<26;i++)
	{
		if( !vis[i] )
		{
			mat[j++] = i+'A';
			vis[i] = 1;
			if(i == 8)
				vis[9] = 1;
			
			if(i == 9)
				vis[8] = 1;
		}
	}

	for(int i=0;i<26;i++)
		vec_bifid[i][0] = -1, vec_bifid[i][1] = -1;
	
	for(int i=0;i<25;i++)
	{
		int x = mat[i]-'A';
		vec_bifid[x][0] = i/5;
		vec_bifid[x][1] = i%5;
	}
	
	if(vec_bifid[9][0] == -1)
	{
		vec_bifid[9][0] = vec_bifid[8][0];
		vec_bifid[9][1] = vec_bifid[8][1];		
	}

	if(vec_bifid[8][0] == -1)
	{
		vec_bifid[8][0] = vec_bifid[9][0];
		vec_bifid[8][1] = vec_bifid[9][1];
	}

	int n = str.length();
	n = n/bifid_size;
	if((str.length()%bifid_size) != 0)
		n++;
		
	int k=0;
	j=0;
	
	string sans[n];
	for(int i=0;i<n;i++)
		sans[i] = "";

	for(int i=0;i<str.length();i++)
	{
		if(str[i] != ' ')
		{
			if(i%bifid_size == bifid_size-1)
			{
				sans[k] += vec_bifid[str[i]-'A'][0] + '0';
				for(int p=j;p<=i;p++)
					sans[k] += vec_bifid[str[p]-'A'][1] + '0';				
				
				k++;
				j=i+1;
			}
			
			else
				sans[k] += vec_bifid[str[i]-'A'][0] + '0';
		}
	}
	
	for(int i=0;i<n;i++)
	{
		for(int p=0;p<sans[i].length();p=p+2)
		{
			int x = sans[i][p] - '0';
			int y = sans[i][p+1] - '0';
			
			for(int h=0;h<26;h++)
			{
				if(vec_bifid[h][0] == x  &&  vec_bifid[h][1] == y)
				{
					ans+= h + 'A';
					break;
				}
			}
		}
	}

	cout<<"\nPolybis Keyword : "<<key;
	cout<<"\nCipher Text :  "<<ans<<endl;
	return ans;
}

void bifid_decrypt(string str)
{
	string ans="";
	int n = str.length();
	n = n/bifid_size;
	if((str.length()%bifid_size) != 0)
		n++;
	
	string sans[n];
	for(int i=0;i<n;i++)
		sans[i] = "";
	
	int j=0,k=0;
	for(int i=0;i<str.length();i++)
	{
		if(i%bifid_size == bifid_size - 1)
		{
			sans[k] += vec_bifid[str[i]-'A'][0] + '0';
			sans[k] += vec_bifid[str[i]-'A'][1] + '0';
			k++;
		}
	
		else
		{
			sans[k] += vec_bifid[str[i]-'A'][0] + '0';
			sans[k] += vec_bifid[str[i]-'A'][1] + '0';
		}
	}
		
	for(int i=0;i<n;i++)
	{
		for(int p=0;p<sans[i].length()/2;p++)
		{
			int x = sans[i][p] - '0';
			int y = sans[i][p+bifid_size] - '0';
		
			for(int h=0;h<26;h++)
			{
				if(vec_bifid[h][0] == x  &&  vec_bifid[h][1] == y)
				{
					ans += h + 'A';
					break;
				}
			}
		}
	}	
	
	transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
	cout<<"Plain text : "<<ans<<endl;
}

string trifid_encrypt(string str)
{
	string key,ans="";	
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	
	cout<<"\nEnter the agreed keyword for the Polybis Matrix :  ";
	cin>>key;
		
	key = removeSpaces(key);
	transform(key.begin(), key.end(), key.begin(), ::toupper);

	for(int i=0;i<9;i++)
	{
		mat1[i] = '+';
		mat2[i] = '+';
		mat3[i] = '+';
	}
	
	int j=0;
	int i,vis[26]= {0};
	for(i=0;i<key.length();i++)
	{
		if(!vis[key[i]-'A'])
		{
			vec_trifid[key[i]-'A'][0] = j/3;
			vec_trifid[key[i]-'A'][1] = j%3;
			mat1[j++] = key[i];
			vis[key[i]-'A'] = 1;
		}
		
		if(j==9)
			break;
	}	
	
	j=0;
	for(i=0;i<key.length();i++)
	{
		if(!vis[key[i]-'A'])
		{
			vec_trifid[key[i]-'A'][0] = j/3;
			vec_trifid[key[i]-'A'][1] = j%3;
			mat2[j++] = key[i];
			vis[key[i]-'A'] = 1;
		}
		
		if(j==9)
			break;
	}	
	
	j=0;
	for(i=0;i<key.length();i++)
	{
		if(!vis[key[i]-'A'])
		{
			vec_trifid[key[i]-'A'][0] = j/3;
			vec_trifid[key[i]-'A'][1] = j%3;
			mat3[j++] = key[i];
			vis[key[i]-'A'] = 1;
		}
		
		if(j==9)
			break;
	}
		
	for(j=0;j<9;j++)
	{
		if(mat1[j] == '+')
			break;
	}
	
	if(j<9)
	{
		for(i=0;i<26;i++)
		{
			if(!vis[i])
			{
				vec_trifid[i][0] = j/3;
				vec_trifid[i][1] = j%3;
				mat1[j++] = i+'A';
				vis[i] = 1;
			}
				
			
			if(j==9)
				break;
		}
	}
	
	for(j=0;j<9;j++)
	{
		if(mat2[j] == '+')
			break;
	}
	
	if(j<9)
	{
		for(i=0;i<26;i++)
		{
			if(!vis[i])
			{
				vec_trifid[i][0] = j/3;
				vec_trifid[i][1] = j%3;
				mat2[j++] = i+'A';
				vis[i] = 1;
			}
			
			if(j==9)
				break;
		}
	}
	
	for(j=0;j<9;j++)
	{
		if(mat3[j] == '+')
			break;
	}
	
	if(j<9)
	{
		for(i=0;i<26;i++)
		{
			if(!vis[i])
			{
				vec_trifid[i][0] = j/3;
				vec_trifid[i][1] = j%3;
				mat3[j++] = i+'A';
				vis[i] = 1;
			}
		}
	}
	
	int f,add;
	for(i=0;i<str.length();i++)
	{
		if(str[i] == ' ')
		{
			ans += " ";
			continue;
		}
		
		add=0;
		f=0;
		char temp = str[i];
		if(f==0)
		{
			for(j=0;j<9;j++)
			{
				if(mat1[j] == temp)
				{
					f=1;
					add = 1;
					break;
				}
			}			
		}
		
		if(f==0)
		{
			for(j=0;j<9;j++)
			{
				if(mat2[j] == temp)
				{
					f=1;
					add = 2;
					break;
				}
			}			
		}

		if(f==0)
		{
			for(j=0;j<9;j++)
			{
				if(mat3[j] == temp)
				{
					f=1;
					add = 3;
					break;
				}
			}			
		}
		
		ans+= add+'0';
		ans+= (1 + vec_trifid[temp-'A'][0] ) + '0';
		ans+= (1 + vec_trifid[temp-'A'][1] ) + '0';
	}	
	
	cout<<"\nKey :  "<<key;
	cout<<"\nCipher Text :  "<<ans<<endl;
		
	return ans;
}

void trifid_decrypt(string str)
{
	int add;
	string ans="";
	for(int i=0;i<str.length();i=i+3)
	{
		if(str[i] == ' ')
		{
			ans+= " ";
			i=i-2;
			continue;
		}
		
		add=0;
		if(str[i]-'0' == 1)
			add=1;
		else if(str[i]-'0' == 2)
			add=2;
		else if(str[i]-'0' == 3)
			add=3;
		
		int x = 3*(str[i+1] - '0' - 1);
		x=x+(str[i+2] - '0' - 1);		
		
		if(add == 1)
			ans+= mat1[x];
			
		else if(add == 2)
			ans+= mat2[x];
		
		else
			ans+= mat3[x];
	}
	
	transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
	cout<<"Plain text :  "<<ans<<endl;
	
	return;
}

string nilhist_encrypt(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);	

	string key,ans="",add="";
		
	cout<<"\nEnter the keyword for the Polybis Matrix :  ";
	cin>>key;
	
	key = removeSpaces(key);
	
	transform(key.begin(), key.end(), key.begin(), ::toupper);	
	
	cout<<"\nEnter the agreed upon key :  ";
	cin>>nilhist_key;
	transform(nilhist_key.begin(), nilhist_key.end(), nilhist_key.begin(), ::toupper);	
	
	int j=0;
	int vis[26]= {0};
	for(int i=0;i<key.length();i++)
	{
		if(!vis[key[i]-'A'])
		{
			nilhist_mat[j++] = key[i];
			vis[key[i]-'A'] = 1;
			
			int test = key[i]-'A';
			if(test == 8)
				vis[9] = 1;
			
			if(test == 9)
				vis[8] = 1;
		}
	}	
	
	for(int i=0;i<26;i++)
	{
		if( !vis[i] )
		{
			nilhist_mat[j++] = i+'A';
			vis[i] = 1;
			if(i == 8)
				vis[9] = 1;
			
			if(i == 9)
				vis[8] = 1;
		}
	}
	
	int h=0;
	for(int i=0;i<str.length();i++)
	{
		if(str[i] == ' ')
		{
			ans+= " ";
			add+= " ";
		}
			
		else
		{
			for(j=0;j<26;j++)
			{
				if(nilhist_mat[j] == str[i])
				{
					ans+= (1 + j/5) + '0';
					ans+= (1 + j%5) + '0';
					break;
				}	
			}
			
			for(j=0;j<26;j++)
			{
				if(nilhist_key[h] == nilhist_mat[j])
				{
					add+= (1 + j/5) + '0';
					add+= (1 + j%5) + '0';
					break;
				}	
			}
			
			h++;
			h = h%(nilhist_key.length());
		}
	}
	
	string result = "";
	for(int i=0;i<ans.length();i=i+2)
	{
		if(ans[i] == ' ')
		{
			result += " ";
			i--;
			continue;
		}
		
		int x1 = ans[i] - '0';
		int x2 = ans[i+1] - '0';
		int y1 = add[i] - '0';
		int y2 = add[i+1] - '0';
		
		int p = 10*x1 + x2;
		int q = 10*y1 + y2;
		
		int z1 = (p+q)/10;
		int z2 = (p+q)%10;
		
		result += z1 + '0';
		result += z2 + '0';
	}
	
	cout<<"\nPolybis Keyword :  "<<key;
	cout<<"\nNilhist Key :  "<<nilhist_key;
	cout<<"\nCipher Text :  "<<result<<endl;
	nilhist_key = add;

	return result;
}

void nilhist_decrypt(string str)
{
	string ans="",result="";
	
	for(int i=0;i<str.length();i=i+2)
	{
		if(str[i] == ' ')
		{
			ans+= " ";
			i--;
			continue;
		}
		
		int x1 = str[i] - '0';
		int x2 = str[i+1] - '0';
		int y1 = nilhist_key[i] - '0';
		int y2 = nilhist_key[i+1] - '0';
	
		int p = 10*x1 + x2;
		int q = 10*y1 + y2;
		
		int z1 = (p-q)/10;
		int z2 = (p-q)%10;
		
		ans += z1 + '0';
		ans += z2 + '0';
	}
	
	for(int i=0;i<ans.length();i=i+2)
	{
		if(ans[i] == ' ')
		{
			result+= " ";
			i--;
			continue;
		}
		
		int x1 = ans[i] - '0';
		int x2 = ans[i+1] - '0';
		
		for(int j=0;j<25;j++)
		{
			if(j/5 == x1-1 && j%5 == x2-1)
			{
				result += nilhist_mat[j];
				break;
			}
		}
	}
	
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	cout<<"Plain Text :  "<<result<<endl;
}

int main()
{
	cout<<"<----------------------MENU DRIVEN PROGRAM for POLYALPHABETIC ENCRPYPTION AND DECRYPTION---------------------->";
	srand(time(0));

	string str;
	int choice;
	cout<<"\n\nEnter the String :  ";
	getline(cin,str);	
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	
	while(1)
	{
		cout<<"\n1. Bifid Cipher";
		cout<<"\n2. Trifid Cipher";
		cout<<"\n3. Nihist Cipher";
		cout<<"\n4. Exit";
		
		cout<<"\n\nEnter Choice :  ";
		cin>>choice;
		
		switch(choice)
		{
			case 1 :
			{
				string ans = bifid_encrypt(str);
				bifid_decrypt(ans);
				break;
			}
			
			case 2 :
			{
				string ans = trifid_encrypt(str);
				trifid_decrypt(ans);
				break;
			}
			
			case 3 :
			{
				string ans = nilhist_encrypt(str);
				nilhist_decrypt(ans);
				break;
			}
			
			case 4 :
			{
				exit(0);
				break;
			}
				
			default :
			{
				cout<<"Invalid Input\n";
				break;
			}
		}
	}
	
	cout<<endl;

    return 0;
}

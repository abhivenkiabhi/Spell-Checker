#include<bits/stdc++.h>
using namespace std;
#define SIZE 26
struct Trienode
{ 
	string s;
	bool isword;
	Trienode *child[SIZE];
	
};

Trienode* getnode()
{
  //Trienode *root = NULL;
 // root= (Trienode *)malloc(sizeof(Trienode));
  Trienode* root = new Trienode();
  root->isword =false;
for(int i=0;i<SIZE;i++)
	root->child[i]=NULL;
return root;
}
void insert(Trienode* root,string key)
{
	int length=key.size();
	string str;
	for(int i=0;i<length;i++)
	{
		int idx=(int)(key[i]-'a');
		str+=key[i];
		if(root->child[idx]!=NULL)
		{
			root=root->child[idx];
		}
		else
		{
			Trienode* temp=getnode();
			root->child[idx]=temp;
			root->child[idx]->s=str;
			root=root->child[idx];
		}
	}
	root->isword=true;

}
bool search(Trienode* root,string key)
{
	int length=key.size();
	for(int i=0;i<length;i++)
	{
		int idx=(int)(key[i]-'a');
		if(root->child[idx]!=NULL)
			root=root->child[idx];
		else
			return false;
	}
	if(root->isword and root!=NULL)
		return true;
}
bool hasnochild(Trienode *root)
{
	for(int i=0;i<SIZE;i++)
	{
		if(root->child[i]!=NULL)
			return false;
	}
	return true;
}
bool deletehelper(Trienode* cur,string s,int length,int level)
{
	if(cur==NULL)
	{
		cout<<"key does not Exit\n";
		return false;
	}
	if(level==length)
	{
		if(hasnochild(cur))
		{
			cur=NULL;
			return true;
		}
		else
		{
			cur->isword=false;
			return false;
		}
	}
	else
	{
		int idx=(int)(s[level]-'a');
		bool childdeleted=deletehelper(cur->child[idx],s,length,level+1);
		if(childdeleted)
		{
         cur->child[idx]=NULL;
         if(cur->isword or hasnochild(cur)==false)
         	return false;
         else
         {
         	cur=NULL;
         	return true;
         }
		}
		else
			return false;
	}

}
void deleteword(Trienode *root,string key)
{
	if(root==NULL )
	{
		cout<<"Empty Trie error or null key\n";
		return;
	}
	deletehelper(root,key,key.length(),0);
}
void printsuggetion(Trienode* root)
{
	for(int i=0;i<26;i++)
	{
			if(root->child[i]!=NULL)
			printsuggetion(root->child[i]);
	}
		if(root->isword and root->s!="")
		cout<<root->s<<endl;
	
}
void suggest(Trienode* root,string key,int pos)
{
	
   for(int i=0;i<key.length();i++)
   {
   	int idx=(int)key[i]-'a';
   	if(root->child[idx]!=NULL)
   	root=root->child[idx];
   else
   	break;
   }
   	printsuggetion(root);
}

int main(int argc,char *argv[])
{
	Trienode *root=NULL;
	ifstream in("wordfile.txt");
	root=getnode();
	while(in)
	{
		string s;
		in>>s;
		insert(root,s);
	}
	in.close();
	cout<<"enter the word\n";
    string s1;
	cin>>s1;
	if(search(root,s1))
		cout<<"correct spelling\n";
	else
		{
			cout<<"incorrect spelling, suggetions are \n";
			suggest(root,s1,0);
		}

}

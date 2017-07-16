#include <iostream>
#include <string>
#include <fstream>
#include<map>
using namespace std;
struct ST
{
	string Type;
	string Desc;
};
typedef map <string, ST > T;
int main()
{
	ifstream input;
	T SymbolTable;
	string inputvalue;
	ifstream token;
	string previoustype;
	input.open("input.txt");
	if(!input.is_open())
	{
		cout << "Unable to open input file";
		return 0;
	}
	token.open("token.txt");
	if(!token.is_open())
	{
		cout << "Unable to open Token file";
		return 0;
	}
	string tokenvalue="";
	string previoustoken;
	string pretoken;
	int prepos;
	while(!input.eof())
	{
		previoustoken=tokenvalue;
		getline(input,inputvalue,' ');
		getline(token,tokenvalue,' ');
		if(tokenvalue=="id")
		{
			ST t;
			t.Type="";
			if(previoustoken=="function")
			{
				t.Desc="Function";
			}
			else
			t.Desc="Variable";
			SymbolTable.insert(T::value_type( inputvalue,t));	
		}
		else if(tokenvalue=="integer"||tokenvalue=="real")
		{
			

			for(auto elem :SymbolTable )
			{
				if(elem.second.Desc=="Variable"&&elem.second.Type=="")
				{
					SymbolTable[elem.first].Type=tokenvalue;
				}
				if(elem.second.Desc=="Function"&&elem.second.Type=="")
				{
					prepos=token.tellg();
					pretoken=tokenvalue;
					getline(token,tokenvalue,' ');
					if(tokenvalue==";")
					SymbolTable[elem.first].Type=pretoken;
					token.seekg(prepos);
					tokenvalue=pretoken;
				}
			}
		}
		else if (tokenvalue==";")
		{
			for(auto elem :SymbolTable )
			{
				if(elem.second.Desc=="Variable"&&elem.second.Type=="")
				{
					SymbolTable[elem.first].Type=" ";
				}
				if(elem.second.Desc=="Function"&&elem.second.Type=="")
				{
					prepos=token.tellg();
					pretoken=tokenvalue;
					getline(token,tokenvalue,' ');
					if(tokenvalue==";")
					SymbolTable[elem.first].Type=" ";
					token.seekg(prepos);
					tokenvalue=pretoken;
				}
			}
		}
	}
	cout<<"Name "<<"......|"<<" Type .....|"<<" Descrip "<<endl;
	for(auto elem :SymbolTable )
	{
		cout<<elem.first<<".....|"<<elem.second.Type<<".....|"<<elem.second.Desc<<endl;
	}
	return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include<map>
using namespace std;
//Data Structure that store information that needed for variable or function
struct ST
{
	string Type;
	string Desc;
};
// Map Variable or function Name to Data Structure to directly variable or function name to symbol Table entry
typedef map <string, ST > T;
int main()
{
	ifstream input;
	T SymbolTable;
	string inputvalue;
	ifstream token;
	string previoustype;
	input.open("input.txt");
	//Check if Code file exists
	if(!input.is_open())
	{
		cout << "Unable to open input file";
		return 0;
	}
	//Check if Token File exists
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
	//Read Data from Input file and corresponding token entry to get information for Symbol Table
	// When a new variable or function comes. Store its relative information in Symbole Table
	while(!input.eof())
	{
		previoustoken=tokenvalue;
		getline(input,inputvalue,' ');
		getline(token,tokenvalue,' ');
		// Checks if Token is Identifier and Function then add entry for that in Symbol Table
		if(tokenvalue=="id")
		{
			ST temp;
			temp.Type="";
			if(previoustoken=="function")
			{
				temp.Desc="Function";
			}
			else
			temp.Desc="Variable";
			SymbolTable.insert(T::value_type( inputvalue,temp));	
		}
		// Store Type of Identifier or Function Return type in Symbol Table 
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
		// Deals the variables and function with no types
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
	// Prints the Symbol Table 
	cout<<"Name "<<"......|"<<" Type .....|"<<" Descrip "<<endl;
	for(auto elem :SymbolTable )
	{
		cout<<elem.first<<".....|"<<elem.second.Type<<".....|"<<elem.second.Desc<<endl;
	}
	return 0;
}

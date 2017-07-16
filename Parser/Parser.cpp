#include <iostream>
#include <fstream>
#include<string>
#include <stack>
#include<map>
using namespace std;
typedef map<string,int> T;
stack <string> st;
int main()
{
	int lineno=0;
	T terminal;//Keep Record of all terminal
	T nonterminal;// Keep Record of all non-terminals
	ifstream parse_table;
	string parsetable[33][33];// Keep Record of complete parsing table
	parse_table.open("parsingtable1.txt");
	if (parse_table.is_open()) 
	{
		string line;
		int start=1;
		int i=0;
		int val=0;
		int valnt=0;
		int colno=0;
		int row; 
		int col;
		// Load Parsing Table in parse_table matrix
		while ( getline (parse_table,line) )
		{
			for(int j=1; j<=line.length();j++)
			{
				// Load terminals in terminal map struture
				if (lineno==0)
				{
					if(line[j]=='\t'||j==line.length())
					{
					
						terminal.insert(T::value_type( line.substr (start,j-start),val));
						val=val+1;
						start=j+1;
					}
				}
				if (lineno>0)
				{
					if(line[j]=='\t' && start==0)
					{
						// Load Non-terminals in nonterminal map struture
						nonterminal.insert(T::value_type( line.substr (start,j-start),valnt));
						valnt=valnt+1;
						start=j+1;
					}
					else if(line[j]=='\t'||j==line.length())
					{
						parsetable[lineno-1][colno]=line.substr (start,j-start);
						start=j+1;
						colno=colno+1;
					}
				}
			}
			colno=0;
			lineno++;
			start=0;	
		}
		st.push("$");
		//Push Start Symbol on Stack
		st.push("Pro");
		ifstream token;
		string production;
		string previous;
		// Read space seperated tokens from file.
		token.open("token.txt");
		int end;
		cout<<st.top();
		if (token.is_open()) 
		{
			while ( st.top()!="$" )
			{
				getline (token,line,' ');
				int ln=line.length()-1;
				if(line[ln]=='\n')
				{
					line=line.substr(0,ln);
				}
				while(terminal.count(st.top()) == 0)
				{
					cout<<" Next Iteration "<<'\n';
					row=nonterminal[st.top()];
					col=terminal[line];
					production=parsetable[row][col];
					previous=st.top();
					st.pop();
					if(production=="$")
					{
						continue;
					}
					if(production=="_")
					{
						st.push(previous);
						break;
					}
					end=production.length()-1;
					for(int i=production.length()-1; i>=0;i--)
					{
						if(isspace(production[i])|| i==0)
						{
							if(i==0)
							st.push(production.substr(i,end-i+1));
							else
							st.push(production.substr(i+1,end-i));
							cout<<st.top()<<'\n';
							end=i-1;
						}
				    }
				}
				if (st.top()==line)	
				{
					cout<<"match terminal"<<"  "<<st.top()<<'\n';
					st.pop();
				}
				else if(terminal.count(st.top()) == 1||production=="_")
				{
					if(production=="_")
					cout<<"Entry not found in Parsing Table. \n Program is not Parsed";
					else
					cout<<"Mismatch of Terminal Error Occured.  \n Program is not Parsed"<<'\n';
					cout<<" Stack Top  "<<st.top()<<"  Token  "<<line;
					break;
				}
			}
			if(st.top()=="$"&&token.eof())
			{
				cout<<"Parsing Complete Successfully";
			}
			else
			cout<<" Input not fully Parsed"	;
		}
		else
		cout<<"Tokens File is not opened";
	}
	else
	cout<<"Parsing Table is not opened";
	
}

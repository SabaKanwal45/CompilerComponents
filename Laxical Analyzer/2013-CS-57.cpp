//Implicit Laxical Analzer implementation
// basic file operations
#include <iostream>
#include <fstream>
#include<string>
using namespace std;
//Generate Tokens for Identifiers and Detect Error within Identifiers
int identifier(int* i, string line)
{
	
	for(int j=*i+1;j<line.length();j++)	
	{
		if(isspace(line[j])||line[j]=='/n')
		{
			*i=j;
			return 1;
		}
		else if(!(isalpha(line[j])||isdigit(line[j])))
		{
		
			*i=j;
			return 0;
		}
				
	}
	*i=line.length();
	return 1;	
}
//Generate Tokens for Assignment Operator and Detect Error within it
int Assignmentoper(int* i,string line)
{
	
	if(line[*i+1]=='=')
	{
		*i=*i+2;
		if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
		return 1;						
		else
		return 0;	
	}
	else
	{
		*i=*i+1;
		return 0;
	
	}
}
//Generate Tokens for Multiplication Operators and Detect Error within it
int Muloperator(int* i, string line)
{
	if(isspace(line[*i+1])||line[*i+1]=='/n'||*i+1==line.length())
	{
		*i=*i+1;
		return 1;
	}
	else
	{
		*i=*i+1;
		return 0;
	}
}
//Generate Tokens for relational Operators and Detect Error within it
int relationalop(int *i, string line)
{
    if(line[*i]=='<')
	{
		if(line[*i+1]=='=')
		{
			*i=*i+2;
			if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(line[*i+1]=='>')
		{
			*i=*i+2;
			if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(isspace(line[*i+1])||line[*i+1]=='/n'||*i+1==line.length())
		{
			*i=*i+1;
			return 1;
		}
		else
		{
			*i=*i+1;
			return 0;
		}
	}
	else if(line[*i]=='=')
	{
		*i=*i+1;	
		if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(line[*i]=='>')
	{
		
		if(line[*i+1]=='=')
		{
			*i=*i+2;
			if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(isspace(line[*i+1])||line[*i+1]=='/n'||*i+1==line.length())
		{
		    *i=*i+1;
		    return 1;	
		}
		else
		{
			*i=*i+1;
		    return 0;	
		}
	
	}
}
//Generate Tokens for numbers(Scientific numbers, floating, integers) and Detect Error within it
int numbers(int* i, string line, int* notype)
{
	if(line[*i]=='+'||line[*i]=='-')
	*i=*i+1;	
	for(int j=*i+1;j<line.length();j++)
	{
		if(isspace(line[j])||line[j]=='/n')
		{
			*i=j;
			*notype=0;
			return 1;
		}
	    else if(line[j]=='.')
		{
			if(isdigit(line[j+1]))
			{
				for(int k=j+2;k<line.length();k++)
				{
					if(isspace(line[k])||line[k]=='/n')
					{
						*notype=1;
						*i=k;
						return 1;		
					}
					else if(line[k]=='E'||line[k]=='e')
					{
						k=k+1;
						if(isdigit(line[k])||((line[k]=='+'||line[k]=='-')&&isdigit(line[k+1])))
						{
							if(line[k]=='+'||line[k]=='-')
							k=k+1;	
							for(int l=k+1;l<line.length();l++)
							{
								if(isspace(line[l])||line[l]=='/n')
						        {
						            *notype=2;
									*i=l;
									return 1;
								}
								else if(!isdigit(line[k]))
								{
									*i=l;
									return 0;
								}						
							}
							*i=line.length();
							*notype=2;
							return 1;
						}
						else
						{
							*i=j+1;
							return 0;
						}
							
					}
					else if(!isdigit(line[k]))			
					{
						*i=k;
						return 0;
					}		
				}
				*i=line.length();
				*notype=1;
				return 1;
			}
			else
			{
				*i=j+1;
				return 0;
			}
		}
		else if (line[j]=='E'||line[j]=='e')
		{
			j=j+1;
			if(isdigit(line[j])||((line[j]=='+'||line[j]=='-')&&isdigit(line[j+1])))
			{
				if(line[j]=='+'||line[j]=='-')
				j=j+1;	
				for(int l=j+1;l<line.length();l++)
				{
				    if(isspace(line[l])||line[l]=='/n')
					{
						*i=l;
						*notype=2;
						return 1;
					}
					else if(!isdigit(line[l]))
					{
						*i=l;
						return 0;
						
					}
				}
				*i=line.length();
				*notype=2;
				return 1;
			}
			else
			{
				*i=j;
				return 0;
			}
							
		}
		else if(!isdigit(line[j]))
		{
			*i=j;
			return 0;
		}
	}
	*i=line.length();
	*notype=0;
	return 1;		
}
//Generate Tokens for add operators and Detect Error within it
int Addoperator(int*i, string line)
{
	*i=*i+1;
	if(isspace(line[*i])||line[*i]=='/n'||*i==line.length())
	return 1;
	else
	return 0;
}
//Generate Tokens Commments and Detect Error within it
int Comment(int *i, string line, int* cmflag)
{
	for(int j=*i+1;j<line.length();j++)
	{
		if(line[j]=='{')
		{
			*i=j;
			return 0;
		}
		else if(line[j]=='}')
		{
			*i=j;
			*cmflag=0;
			return 1;
		}
	}
	*cmflag=1;
}



int main ()
{
	string line;
	ifstream myfile;
	ofstream out;
	out.open("output.txt");
	myfile.open("input.txt");
	const int Id=101;
	const int integer=102;
	const int real=103;
	const int scientific=104;
	const int relop=105;
	const int Addop=106;
	const int Assignop=107;	
	const int Mulop=108;
	int status=0;
	int row=1;
	int bfor=0;   //to help to stop the analysis when error occur in input file
	int bwhile=0; // to help to stop the analysis when error occur in input file
	int cmflag=0; // Comment flag is 1 when a comment start and 0 when comment ends
	if (myfile.is_open()) 
	{
		while ( getline (myfile,line) )
		{
			for(int i=0; i<=line.length(); i++)
			{
				bfor=0;
				bwhile=0;
				int helper;
				int notype;
				if(cmflag==0)
				{
					//identifier
					if(isalpha(line[i]))
				    {
				    	helper=identifier(&i,line);
					    if(helper==1)
					    {
					    	out<<Id;
							out<<" ";
							if(line[i]=='/n')
							{
								bfor=1;
							}
						}
						if(helper==0)
					    {
					    	bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					//Assignment operator
					else if(line[i]==':')
					{
						helper=Assignmentoper(&i,line);
						if(helper==1)
						{
							out<<Assignop;
							out<<" ";
							if(line[i]=='/n')
							bfor=1;
						}
						if(helper==0)
						{
							bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
				// Multiply operator
					else if((line[i]=='*'||line[i]=='/'))
			    	{
			    		helper=Muloperator(&i,line);
						if(helper==1)
					    {
					    	out<<Mulop;
							out<<" ";
							if(line[i]=='/n')
						    bfor=1;
						}
						if(helper==0)
					    {
					    	bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					//relational operator
					else if(line[i]=='>'||line[i]=='<'||line[i]=='=')
				    {
				    	helper=relationalop(&i,line);
						if(helper==1)
					    {
					    	out<<relop;
							out<<" ";
							if(line[i]=='/n')
						    bfor=1;
						}
						if(helper==0)
						{
							bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					//Numbers
					else if(isdigit(line[i])||((line[i]=='+'||line[i]=='-')&&isdigit(line[i+1])))
				    {
				    	helper=numbers(&i,line,&notype);
						if(helper==1)
					    {
					    	if(notype==0)
							out<<integer;
							else if(notype==1)
							out<<real;
							else if(notype==2)
							out<<scientific;
							out<<" ";
							if(line[i]=='/n')
							bfor=1;
						}
						if(helper==0)
						{
							bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					//Add operators
					else if((line[i]=='+'||line[i]=='-'))
				    {
				    	helper=Addoperator(&i,line);
						if(helper==1)
					    {
					    	out<<Addop;
							out<<" ";
							if(line[i]=='/n')
							bfor=1;
						}
						if(helper==0)
						{
							bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					else if(line[i]=='{')
					{
						helper=Comment(&i, line,&cmflag);
						if(helper==0)
					    {
					    	bfor=1;
							bwhile=1;
							cout<<" Error in row "<<row<<" and col "<<i;
						}
					}
					else if (!(isspace(line[i])||line[i]=='\n'||i==line.length()||line[i]=='\t'))
					{
						bfor=1;
						bwhile=1;
						cout<<" Error in row "<<row<<" and col "<<i;	
					}
				}
				if (cmflag==1)
				{
					helper=Comment(&i, line,&cmflag);
					if(helper==0)
					{
					    bfor=1;
						bwhile=1;
						cout<<" Error in row "<<row<<" and col "<<i;
					}	
				}
				if(bfor==1)
				{
					break;
				}
			}
			
			if(bwhile==1)
			{
				break;
			}
			row=row+1;
		}
	
	}
	else 
	cout<<"file is not opened";
}

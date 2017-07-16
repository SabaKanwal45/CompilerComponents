#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include <sstream>
#include<map>
#include <thread>
#define ID 101
#define Inte 102
#define Realno 103
#define Scientific 104
#define Relop 105
#define Addop 106
#define Assignop 107
#define Mulop 108
using namespace std;
// map struture to store keywords
typedef map<string,int> Keyword;
// Get col of Transition Table according to char entered
void Get_col_of_TT(char ch,int* col,int* lineno,int* colno);
// Read N characters from file and Store them in Buffer
void Read_N_Char(char* str, ifstream&file, int Bsize);
//Checks if forward pointers points to Buffer1 
bool Is_End_of_B(char* pointer,char* str);
int main()
{
	string line;
	int table[34][17];
	ifstream Trantable;
	Trantable.open("transitiontable.csv");
	int lineno=0;
	int colno=0;
	int row=0;
	int col=0;
	int Key=0;
	if (Trantable.is_open()) 
	{
		// Load Transition Table in table matrix
		while ( getline (Trantable,line) )
		{
			if(lineno>0)
			{
				std::string str = line;
				std::vector<int> vect;
				std::stringstream ss(str);
				int i;
				while (ss >> i)
				{
					vect.push_back(i);
					if (ss.peek() == ',')
					ss.ignore();
				}
				for (i=1; i< vect.size(); i++)
				{
					table[row][col]=vect.at(i);
					col=col+1;
				}
				row=row+1;
				col=0;
			}
			lineno=lineno+1;
		}
		// LOAD KEYWORDS FROM FILE iNTO MAP STRUTURE KEYWORD NAMED KEY
		ifstream keywords;
		keywords.open("keyword.txt");
		Keyword key;
		if (keywords.is_open()) 
		{
			int val=0;
			while ( getline (keywords,line) )
			{
				key.insert(Keyword::value_type(line,val));
				val=val+1;
			}
		}
		else cout<<"KEYWORDS are not loaded from file";
		// OPEN FILE FOR INPUT AND OUTPUT
		ifstream myfile;
		ofstream out;
		out.open("output.txt");
		myfile.open("input.txt");
		int state=0;
		lineno=1;
		std::string str;
		if (myfile.is_open()) 	//generate tokens
		{
			int Buffer_size=40;
			//Create and initilize two Buffers
			char Buffer[Buffer_size];
			// First Buffer Range
			int FBLB=0;
			int FBHB=Buffer_size/2-1;
			// Second Buffer Range
			int SBLB=Buffer_size/2;
			int SBHB=Buffer_size-1;
			// Initial Position of forward and start_lexeme Pointer
			char* start_lexeme=&Buffer[0];
			char* forward=&Buffer[0];
			int colno=1;
			int position=0;
			//create thread
			std::thread t1(Read_N_Char,&Buffer[0],std::ref(myfile),SBLB);
			t1.join();
			int stop=0;
			int stopfor=0;
			while ( stop==0 )
			{
				// Double Buffering with multiple threads
				for(int i=0; i<=Buffer_size/2; i++)
				{
					if(*forward==EOF)
					{
						if (Is_End_of_B(forward,&Buffer[FBHB]))// End of first Buffer
						{
							// IF END OF FIRST BUFFER LOAD SECOND BUFFER
							std::thread t2(Read_N_Char,&Buffer[SBLB],std::ref(myfile),SBLB);
							t2.join();
							forward=forward+1;
							if(forward-1==start_lexeme)
							start_lexeme=forward;
						}
						else if(Is_End_of_B(forward,&Buffer[SBHB]))
						{
							// IF SECOND BUFFER END LOAD FIRST BUFFER
							std::thread t1(Read_N_Char,&Buffer[FBLB],std::ref(myfile),SBLB);
							t1.join();
							if(forward==start_lexeme)
							start_lexeme=&Buffer[FBLB];
							forward=&Buffer[FBLB];
						}
						else // End of file Occurs
						{
							stop=1;
							break;	
						}
					}
					Get_col_of_TT(*forward,&col,&lineno,&colno);
					state=table[state][col];
					switch(state)
					{
						case 3:
						stop=1;
						stopfor=1;
						// ERROR HANDLING WITH lINE AND COLUMN IN TEXT FILE AND THE LEXEME 
						// WITH POSITION OF ERROR SPECIFIED
						out<<"ERROR IN Source Code LINE "<<lineno<<" AND COLUMN "<<colno<<" And lexeme ";
						cout<<"ERROR IN Source Code LINE "<<lineno<<" AND COLUMN "<<colno<< " And lexeme ";
						while(start_lexeme!=forward)
						{
							if(*start_lexeme==EOF)
							{
								if (Is_End_of_B(start_lexeme,&Buffer[FBHB]))
								start_lexeme=start_lexeme+1;
								else if (Is_End_of_B(start_lexeme,&Buffer[SBHB]))
								start_lexeme=&Buffer[FBLB];
								else
								break;
							}
							else
							{
								out<<*start_lexeme;
								cout<<*start_lexeme;
								++start_lexeme;
								position+=1;
							}
						}
						if(forward==start_lexeme)
						{
							out<<*forward;
							cout<<*forward;
							forward++;
							position+=1;
							while(!isspace(*forward))
							{
								if(*forward==EOF)
								{
									if (Is_End_of_B(forward,&Buffer[FBHB]))
									{
										std::thread t2(Read_N_Char,&Buffer[SBLB],std::ref(myfile),SBLB);
										t2.join();
										forward=forward+1;
										continue;
									}
									else if (Is_End_of_B(forward,&Buffer[SBHB]))
									{
										std::thread t1(Read_N_Char,&Buffer[FBLB],std::ref(myfile),SBLB);
										t1.join();
										forward=&Buffer[FBLB];
										continue;
									}
									else
									break;
								}
								out<<*forward;
								cout<<*forward;
								++forward;	
							}
							out<<" has error at Position "<<position;
							cout<<" has error at Position "<<position;
						}	
						// Error Handling Complete
						break;
						case 4:	
						if(Key==0)
						{
							if(isupper(*forward))
							str+=*forward;
							else 
							Key=1;
						}
						break;
						case 5:
							if(Key==0)
							{
								// KEY IS MAP DATA STRUTURE THAT CONTAINS ALL KEYWORDS
								if(key.count(str) == 0)
								out<<ID<<',';
								else
								out<<'\n'<<str<<'	';
							}
							else 
							out<<ID<<',';
							str.clear();
							Key=0;
							start_lexeme=forward+1;
						break;
						case 8:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 13:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 14:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 16:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 17:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 11:
							out<<Relop<<',';
							start_lexeme=forward+1;
						break;
						case 20:
							out<<Assignop<<',';
							start_lexeme=forward+1;
						break;
						case 22:
							out<<Inte<<',';
							start_lexeme=forward+1;
						break;
						case 32:
							out<<Realno<<',';
							start_lexeme=forward+1;
						break;
						case 27:
							out<<Scientific<<',';
							start_lexeme=forward+1;
						break;
						case 29:
							out<<Addop<<',';
							start_lexeme=forward+1;
						break;
						case 31:
							out<<Mulop<<',';
							start_lexeme=forward+1;
						break;		
					}
					if(stopfor==1)
					break;
					forward++;
					colno++;
				}	
			}
		}
	}
	else cout<<"Transition Table is not Loaded";
	return 0;	
}
void Get_col_of_TT(char ch,int* col,int* lineno,int* colno)
{
	if(ch=='\n')
	{
		// Keep track of line no
		*lineno=*lineno+1;
		*colno=0;
	}
	if(ch=='<')
	*col=0;
	else if(ch=='>')
	*col=1;
	else if(ch=='E'||ch=='e')
	*col=2;
	else if(ch=='=')
	*col=3;
	else if(isalpha(ch))
	*col=4;
	else if(isdigit(ch))
	*col=5;
	else if(ch==':')	*col=6;
	else if(ch=='*')
	*col=7;
	else if(ch=='/')
	*col=8;
	else if(ch=='+')
	*col=9;
	else if(ch=='-')
	*col=10;
	else if (isspace(ch)||ch=='\n')
	*col=11;
	else if(ch=='\t')	
	*col=12;
	else if(ch=='{')
	*col=13;			
	else if(ch=='}')
	*col=14;
	else if(ch=='.')
	*col=15;
	else
	*col=16;
	return;
}
void Read_N_Char(char* str, ifstream&file, int Bsize)
{
	for (int i=0;i<Bsize-1;i++)
	{
		str[i]=file.get();
		if(file.eof())
		{
			str[i]=EOF;
			return;
		}
	}
	str[Bsize-1]=EOF;
	return;
}
//Checks if forward pointers points to Buffer1 
bool Is_End_of_B(char* pointer,char* str)
{
	if (&str[0] == pointer)
    return true;
	else	
	return false;
}

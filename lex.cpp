#include <iostream>
#include <string>

using namespace std;

/*string keywords[] = [
	"auto", 
	"break"
];

char *keywords1 = "case";
*/

char keywords[] = {"switch","auto"};
char keywrd[25];
//if (kewords[0] == keywords1 || kewords[1] == kewords2))
int main ()
{
	int i;
	char c[10];
	for(i=0;i<10;i++)
	{
		cin>>c[i];
		switch(c[i])
		case 'a' :  
		case's' : 	while(c[i]!='\0'||' ')
				{
				
				keywrd[i]=keywords[i];
				i++;
				}
				if(keywrd=="auto"||"switch")
			cout<<"keyword";
				
			 
			  
	}

}

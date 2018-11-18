#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>

using namespace std;

void readtoken(string str1)
{
    ifstream fs(str1);
    cout<<"success\n";
    char ch; int line=1,pos=0;
    while((ch=fs.get())!=EOF)
    {
        ++pos;
       if (ch=='\n') 
        {          ++line;
            pos=1;         
        }
        if(isalnum(ch)|| ch == '_' )
        {

            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"identifier"<<" "<<ch<<"\n" ;
        }
        else if(ch=='\''||ch=='\"'|| ch=='\t'||ch=='\?'||ch=='\\'||ch=='\n'||ch=='\a'||ch=='\b'||ch=='\f'||ch=='\r'||ch=='\v')

        {
            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"constant"<<" "<<ch<<"\n" ;

        }
        else if(ch=='['||ch==']'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='.'||ch=='+'||ch=='-'||ch=='&'||ch=='*'||ch=='+'||ch=='-'||ch=='~'||ch=='!'
                ||ch=='%'||ch=='<'||ch=='>'||ch=='='||ch=='^'||ch=='|'||ch=='?'||ch==':'||ch==';'||ch==','||ch=='#')
             {
             
                 char c=fs.peek();
                     if(c=='+')
   
                   cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"punctuator"<<" "<<ch<<"\n" ;

                     else

                           cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"punctuator"<<" "<<ch<<"\n" ;


         }

        
        
        }

    }




int main(int argc,char *argv[])
{ 
    int i;
    //std::cout<<argc<<"\n";

    for( i=0;i<argc;i++)
    {
        std::cout<<i<<" "<<argv[i]<<"\n";
    }

    string str; str=argv[1];

    if (str.compare("--tokenize")==0)
    {
        readtoken(argv[2]);   

    }






    return 0;

}


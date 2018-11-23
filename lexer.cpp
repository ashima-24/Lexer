#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void readtoken(string str1)
{ 
    char sl[1000]={'\0'};
    char c;  
    ifstream fs(str1);
    cout<<"success\n";
    int i;    char ch; int line=1,pos=0;
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
        else if(ch=='\''|| ch=='\t'||ch=='\?'||ch=='\\'||ch=='\n'||ch=='\a'||ch=='\b'||ch=='\f'||ch=='\r'||ch=='\v')

        {
            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"constant"<<" "<<ch<<"\n" ;

        }
        else if(ch=='['||ch==']'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='.'||ch=='+'||ch=='-'||ch=='&'||ch=='*'||ch=='+'||ch=='-'||ch=='~'||ch=='!'
                ||ch=='%'||ch=='<'||ch=='>'||ch=='='||ch=='^'||ch=='|'||ch=='?'||ch==':'||ch==';'||ch==','||ch=='#')
        {


            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"punctuator"<<" "<<ch<<"\n" ;


        }
        else if(ch=='\"')
        {
            sl[0]='\"'; 
            i=1;

           while(c=fs.get()!='\"')
            {
               sl[i]=c;
                ++i;
            }
              sl[i]='\"';
           cout<<i;
           for(int e=0;e<=i+1;e++)
               cout<<sl[e]<<"";
//            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"string-literal" <ch<<"\n" ;




        }


        else if(ch=='/')
        { char r; int len;
            c=fs.peek();

            if(c=='*')
            {
                while((c=fs.get())!='*'&& (c=fs.peek())!='/')
                {
                     
                    if(c=='\n')
                        ++line;


                }

                cout<<c<<"\n";

                if(c=='*')
                {
                    cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"comment  multi line"<<" "<<"/* */"<<"\n" ;


                }






            }



            else if(c=='/')
            {
                cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"comment single line"<<" "<<ch<<c<<"\n" ;


                while((ch=fs.get())!='\n');

                ++line; 
                pos=0;
            } 



            else if (c=='=')
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


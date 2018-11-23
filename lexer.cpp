#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void readtoken(string str1)
{ 

    char c;

    string keywrd="char";
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
            string sl = "\"";

            while((c=fs.get()) !='\"')
            {
                sl += c;
                //        cout<<"sl +"<<c <<" ="<<sl<<"\n";
            }

            sl += '\"';
            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"string-literal"<<" "<<sl<<"\n" ;

        }


        else if(ch=='/')
        { char r, k;
            int len,count=0;
            c=fs.peek();

            if(c=='*')
            {  
                c = fs.get();
                char currCh;
                char nextCh;
                while(1) {
                    currCh = fs.get();
                    nextCh = fs.peek();

                    if (currCh == '*' && nextCh == '/') {
                        cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"comment  multi line"<<" "<<"/* */"<<"\n" ;
                        break;
                    } else {
                        cout<<currCh<<"\t"<<nextCh<<"\n";
                        count++;
                        if (currCh == '\n') {
                            ++line;
                        }
                    }
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


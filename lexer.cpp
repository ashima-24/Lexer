#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void readtoken(string str1)
{ int count_str=0; 
    char c;
    char  *key[]={"char","auto","break","case","char","const","continue","default","do","double","else",
        "enum","extern","float", "for","goto","if","inline","int","long","register","restrict","return","short",
        "signed","sizeof","static","struct","switch","typedef","union","unsigned""void","volatile","while",
        "_Alignas","_Alignof","_Atomic","_Bool","_Complex","_Generic","_Imaginary","_Noreturn","_Static_assert",
        "_Thread_local" };

    string keywrd;
    ifstream fs(str1);
    cout<<"success\n";
    int i,flag=0;    char ch; int line=1,pos=0;

    while((ch=fs.get())!=EOF)
    { 


        if (ch=='\n') 
        {          ++line;
            pos=1;         
        }    


        if(isalpha(ch)|| ch == '_' )
        {
            flag=0;            ++pos;
            string iden;
            iden+=ch;
            while(  (isalnum(ch=fs.get() ) ) || ch=='_' && ch !='EOF')
            {

                iden+=ch;
                //cout<<iden<<" "<<"ch="<<ch<<"\n";

            }

            // cout<<iden<<"\n";
            for(int h=0;h<44;h++)
            {
                keywrd=key[h]; 
                if((iden.compare(keywrd))==0)
                    flag=1;
            }
            //       cout<<"flag="<<flag<<"\n";
            if(flag==1)
                cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"Keyword"<<" "<<iden<<"\n" ;

            else   
                cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"identifier"<<" "<<iden<<"\n" ;


        }

        if(ch=='\''|| ch=='\t'||ch=='\?'||ch=='\\'||ch=='\n'||ch=='\a'||ch=='\b'||ch=='\f'||ch=='\r'||ch=='\v')

        {
            cout<<str1<<":"<<line<<":"<<pos<<":"<<" "<<"constant"<<" "<<ch<<"\n" ;

        }
        if(ch=='['||ch==']'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='.'||ch=='+'||ch=='-'||ch=='&'||ch=='*'||ch=='+'||ch=='-'||ch=='~'||ch=='!'
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
                        //         cout<<currCh<<"\t"<<nextCh<<"\n";
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


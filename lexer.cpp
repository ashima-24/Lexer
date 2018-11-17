#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>

using namespace std;

int main(int argc,char *argv[])
{ 
    ifstream fs("--tokenize test.c",std::ifstream::binary);
    int i;
    std::cout<<argc<<"\n";
    for( i=0;i<argc;i++)
        std::cout<<i<<" "<<argv[i]<<"\n";

    string str; str=argv[1];
    cout<<str<<"\n";
    if (str.compare(argv[1])==0)
    {
        cout<<"success\n";
        char ch; int line=0;
        while((ch=fs.get())!=EOF)
        { 
            line++;
            if(isalnum(ch) || ('_'))

                cout<<line<<":"<<":"<<" "<<"identifier"<<" "<<ch<<"\n" ;

            else
                cout<<line<<":"<<":"<<" "<<"diff"<<" "<<ch<<"\n" ;



        }



    }
    return 0;

}


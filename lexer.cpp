#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int main()
{ char ch;
    int line=0;    std::ifstream fs("--tokenize.txt");
    if(fs)
    { 
        while(fs.get(ch))
                { 
         if(ch =='_'|| 'a'||0)
            {
                line++;
                std::cout<<line<<":"<<":"<<" "<<"identifier"<<" "<<ch<<"\n";
            }
            else if(ch==':')

            {
                line++;
                std::cout<<line<<":"<<":"<<" "<<"diff"<<" "<<ch<<"\n";

            }

        }


    }
    if(fs.eof())
        std::cout<<"end reached";




    fs.close();


    return 0;

}


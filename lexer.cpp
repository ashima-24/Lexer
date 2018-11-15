#include<iostream>
#include<fstream>
#include<string>

using namespace std;
 int main()
{ char ch;
    std::ifstream fs("--tokenize.txt");
if(fs)
{ while(fs.get(ch))
   // std::cout<<ch<<"\n";
}
    if(fs.eof())
    std::cout<<"end reached";




fs.close();


return 0;

}


#include <iostream>
#include <string>

using namespace std;


//char keywords[] = {"switch","auto"};
char keywrd[25];
//if (kewords[0] == keywords1 || kewords[1] == kewords2))
int main ()
{
    std::ifstream file "tokenize.txt";
    char c; 
    while(file.get(c))
    {    std::cout<<c;
    
    
file.close();
    }

}

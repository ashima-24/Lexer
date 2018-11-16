#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int main(int argc,char *argv[])
{ int i;
    std::cout<<argc<<"\n";
    for( i=0;i<argc;i++)
std::cout<<i<<" "<<argv[i]<<"\n";
char * str; str=argv[1];
cout<<str<<"\n";
if (str=="--tokenize")
{
    cout<<"\nsuccess";


}
else
{

//stderr: file not there;

return 1;
}
    return 0;

}


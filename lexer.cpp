#include<iostream>
using namespace std;
int main()


{
	int w,b,t,n;
float f,c;
cout<<"hello,";
cout<<"world \c";
cout<<"\n";
/*cin>>f;
c=0.56*f-32;
cout<<"temp in celsius"<<c;

for( f;f>=0;f--)
{
c=0.56*f-32;
cout<<"celsius temp"<<\n<<c;
} 
char ch;
cin>>ch;
if(ch!=EOF)
	cout<<"t";
	else cout<<"n";
cout<<EOF<<"\n"; */
char test[13];
int i,j;
for(i =0;i<13;i++)
cin>>test[i];
for( j=0;j!=EOF;j++)
{
if(test[j]=='\n')
	n++;
else if(test[j]=='\t')
	t++;
else if(test[j]==' ')
	b++;
else  w++;
}
cout<<"wrd"<<w;
cout<<"gap"<<b;
cout<<"tab"<<t;
cout<<"line"<<n;



}






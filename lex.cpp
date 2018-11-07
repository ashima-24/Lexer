#include<iostream>
using namespace std;
int main ()
{
	int i;
char c[10];
for(i=0;i<10;i++)
{
cin>>c[i];
switch(c[i])
	case 'a': if(c[i]=='auto'||'break'||'case'||'char'||'const'||'continue'||
	 'default'||'do'||'double'||'else'||'enum'||'extern'||'float'||'for'||'goto'||'if'
	 ||'inline'||'int'||'long'||'register'||'restrict'||'return'||'short'||'signed'||
	 'sizeof'||'static'||'struct'||'switch'||'typedef'||'union'||
'unsigned'||'void'||'volatile'||'while'||' _Alignas'||' _Alignof'||' _Atomic'||' _Bool'||
'_Complex'||' _Generic'||' _Imaginary'||' _Noreturn'||' _Static_assert'||' _Thread_local')
{
cout<<"keyword";
}
else cout<<"other token";
}

}

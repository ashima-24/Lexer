#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void readtoken(string filename)
{
    
   string  key[] = {"char",
                    "auto",
                    "break",
                    "case",
                    "char",
                    "const",
                    "continue",
                    "default",
                    "do",
                    "double",
                    "else",
                    "enum",
                    "extern",
                    "float",
                    "for",
                    "goto",
                    "if",
                    "inline",
                    "int",
                    "long",
                    "register",
                    "restrict",
                    "return",
                    "short",
                    "signed",
                    "sizeof",
                    "static",
                    "struct",
                    "switch",
                    "typedef",
                    "union",
                    "unsigned",
                    "void",
                    "volatile",
                    "while",
                    "_Alignas",
                    "_Alignof",
                    "_Atomic",
                    "_Bool",
                    "_Complex",
                    " _Generic",
                    "_Imaginary",
                    "_Noreturn",
                    "_Static_assert",
                    "_Thread_local" };
    
    ifstream fs(filename);
    char ch;
    int line = 1, pos = 0;
       
    while((ch = fs.get()) != EOF)
    {
        if (ch == '\n') 
        { 
            ++line;
            pos = 0;         
        }    
        else if(ch == ' ')
        {
            ++pos;
        
        }
        else if(isalpha(ch) || ch == '_' )
        {
            bool iskeyword = false;  
            int temp = 1;
            ++pos;
            string iden;
            iden += ch;
         
            while((isalnum(ch = fs.get()) || ch == '_') && ch != EOF)
            {
                iden += ch;
                ++temp;  
            }

            for(int h = 0; h < (sizeof(key)/sizeof(string)); h++) 
            {
                if(iden == key[h]) 
                    iskeyword = true;
            }

            if(iskeyword)
                cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"Keyword"<<" "<<iden<<"\n" ;
            else   
                cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"identifier"<<" "<<iden<<"\n" ;
        
            pos += temp;
        }
        else if(isdigit(ch))
        {  
            ++pos;

            int temp = 0;
            string constVal;
            char currChar = ch;
            char nextChar = fs.peek();
           
            while(isdigit(currChar) || 
                    (currChar == '.' && isdigit(nextChar)))
            {
                constVal += currChar;
                temp++;
                
                currChar = fs.get();
                nextChar = fs.peek();
            }

            cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"constant"<<" "<<constVal<<"\n" ;
            pos += temp;
        }
        else if(ch == '\'')
        {
            char currChar = fs.get();
            char nextChar = fs.peek();
            if ((isalnum(currChar) ||
                currChar == '\?' ||
                currChar == '\\' ||
                currChar == '\a' ||
                currChar == '\b' ||
                currChar == '\f' ||
                currChar == '\r' || 
                currChar == '\v') && (nextChar == '\'') ) 
            { 
                ++pos;
                cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"character constant"<<" "<<currChar<<"\n" ;
            }
        }
        else if(ch == '[' || 
                ch == ']' || 
                ch == '(' || 
                ch == ')' ||
                ch == '{' ||
                ch == '}' ||
                ch == '.' ||
                ch == '+' ||
                ch == '-' ||
                ch == '&' ||
                ch == '*' ||
                ch == '+' ||
                ch == '-' ||
                ch == '~' ||
                ch == '!' ||
                ch == '%' ||
                ch == '<' ||
                ch == '>' ||
                ch == '=' ||
                ch == '^' ||
                ch == '|' ||
                ch == '?' ||
                ch == ':' ||
                ch == ';' ||
                ch == ',' ||
                ch == '#')
        {
            ++pos;
            cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"punctuator"<<" "<<ch<<"\n" ;
        }
        else if(ch == '\"' )
        {
            ++pos;
            string sl = "\"";
            char nextChar = ' ';
            while((nextChar = fs.get()) != '\"')
            {
                sl += nextChar;
            }

            sl += '\"';
            cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"string-literal"<<" "<<sl<<"\n" ;
        }
        else if(ch == '/')
        {   
            ++pos;
            int count = 0;
            int temp = 0;
            char currChar = ch;
            char nextChar = fs.peek();
          
            if(nextChar == '*')
            {  
                while(1)
                {
                    currChar = fs.get();
                    nextChar = fs.peek();

                    if (currChar == '*' && nextChar == '/') 
                    {
                        cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"comment  multi line"<<" "<<"/* */"<<"\n" ;
                        line = line + temp; 
                        break;
                    } 
                    else
                    {
                        count++;

                        if (currChar == '\n')
                        {
                            ++temp;
                        }
                    }
                   
                    if(currChar != '*' && nextChar != '/' && currChar == EOF) 
                    {
                        cout<<filename<<":"<<line<<":"<<pos<<":"<<"error: Multi line comment unterminated"<<"\n";
                        break;
                    }
                }

            }
            else if(nextChar == '/')
            {
                ++pos;
                cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"comment single line //"<<"\n" ;

                while((ch = fs.get()) != '\n');
               
                ++line; 
                pos = 0;
            } 
            else if (nextChar == '=')
            { 
                ++pos;
                cout<<filename<<":"<<line<<":"<<pos<<":"<<" "<<"punctuator"<<" "<<ch<<"\n" ;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    string str = argv[1];
    if (str.compare("--tokenize") == 0)
    {
        readtoken(argv[2]);   
    }
    else 
    {
        cout<<"error:Invalid Arguments"<<"\n";
        return 1;
    }

    return 0;
}


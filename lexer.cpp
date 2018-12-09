#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void printError(string fileName, int line, int column, const string &message) {
    cerr<<fileName<<":"<<line<<":"<<column<<": error : "<<message<<"\n";
}

void printOutput(string fileName, int line, int column, const string &output, const string &message) {
    cout<<fileName<<":"<<line<<":"<<column<<": "<<output<<" "<<message<<"\n";
}

bool isPunctuatorChar(char ch) {
    char punctuators[] = {
        '+', '-', '/', '%', '~' , 
        '[', ']', '(', ')', '{', '}', '.',
        '&', '*', '!', '?', ':', ';', '<', '>',
        '=', '#', ',', '|', '^'
    };

    for(int i = 0; i < (sizeof(punctuators) / sizeof(char)); i++)
    {

        if(ch == punctuators[i])
            return true;
    }

    return false;
}

bool isPunctuator(string str) {
    string punctuators[] = {
        "[", "]", "(", ")", "{", "}", ".", "->",
        "++", "--", "&", "*", "+", "-", "~", "!",
        "/", "%", "<<", ">>", "<", ">", "<=", ">=",
        "?", ":" , ";", "...",
        "=", "*=", "/=", "%=", "+=", "-=", "<<=",
        ",", "#", "##","|","^"
            "<:", ":>", "<%", "%>", "%:", "%:%:",
        "==", ">>=", "!=", "&=", "^=", "&&", "||", "|="  
    };

    for(int i = 0; i < (sizeof(punctuators) / sizeof(string)); i++)
    {

        if(str.compare(punctuators[i]) == 0)
            return true;    
    }

    return false;
}

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

    string currState;

    char xyz;
    while((ch = fs.get()) != EOF)
    {
        currState += ch;

       if (ch == '\n') 
        {
            ++line;
            pos = 0;

            currState = "";
        }    
        else if(ch == ' ')
        {
            ++pos;
            currState = "";

        }
        else if(isalpha(ch) || ch == '_' )
        {
            bool iskeyword = false;  
            int temp = 0;
            char tempChar = ch;
            ++pos;
            string iden;
            iden += ch;

            while((isalnum(tempChar = fs.peek()) || tempChar == '_') && tempChar != EOF)
            {
                iden += tempChar;
                ++temp;  
                tempChar = fs.get();
            }

            for(int h = 0; h < (sizeof(key)/sizeof(string)); h++) 
            {
                if(iden == key[h]) 
                    iskeyword = true;
            }

            if(iskeyword)
                printOutput(filename, line, pos, "keyword", iden);
            else   
                printOutput(filename, line, pos, "identifier", iden);

            pos += temp;

            currState = "";
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

            printOutput(filename, line, pos, "constant", constVal);
            pos += temp;
            currState = "";
        }
        else if(ch == '\'')
        {   
            char currChar = fs.get();
            string tmp = "";
            tmp += ch;
            tmp += currChar;
           char nextChar = fs.peek();

            if ((isalnum(currChar) ||
                        currChar == '\?' || 
                        currChar == '\"' ||
                        currChar == '\\' ||
                        currChar == '\a' ||
                        currChar == '\f' ||
                        currChar == '\b' ||
                        currChar == '\v') && (nextChar == '\'') ) 
            { 
                ++pos;
                tmp += fs.get();
                printOutput(filename, line, pos, "constant", tmp);
                pos += 2;
            }
            else if(currChar =='\'')
            {   ++pos;
                printOutput(filename, line, pos, "constant", tmp);
                pos += 1;
            }
            else if (nextChar == EOF )
                printError(filename, line, pos, "unterminated constant");
        
            currState = "";
        }
        else if(isPunctuatorChar(ch))
        {
            ++pos;

            string nextState = currState;
            nextState += fs.peek();

            if (nextState == "//")
            {   
                char currChar = fs.get();
                char nextChar = fs.peek();
                if((currChar=fs.get()) == '\\')
                {   
                    nextChar = fs.peek();
                    currChar = fs.get();

                    if (currChar == '\n') 
                    {
                        //printOutput(filename, line, pos, "two line comment", "//\\");
                        ++line;
                        
                        while((ch = fs.get()) != '\n'); 
                       
                        ++line; 
                        pos = 0;
                        currState = "";
                      
                    }
                    else
                    {
                       //printOutput(filename, line, pos, "single line comment", "//");
                        while((ch = fs.get()) != '\n' );
                        ++line; 
                        pos = 0;
                        currState = "";
                    }

                }

                else
                {
                    //printOutput(filename, line, pos, "single line comment", "//");
                    while((ch = fs.get()) != '\n' );

                    ++line; 
                    pos = 0;
                    currState = "";
                }
            }

            else if (nextState == "/*")
            {
                int temp = 0;
                char currChar = fs.get();
                char nextChar = fs.peek();
                
                while(1)
                {
                    currChar = fs.get();
                    nextChar = fs.peek();
                    string crlf ;
                    crlf += currChar;
                    
                    if (currChar == '*' && nextChar == '/') 
                    {
                          // printOutput(filename, line, pos, "multi-line comment", "/* */");
                        line = line + temp; 
                        fs.get();
                        break;
                    } 
                    else if ((currChar == '\n') )
                    {
                        ++temp;
                    }
                    else if(currChar == EOF) 
                    {
                        printError(filename, line, pos, "unterminated comment");
                        break;
                    }
                }

                currState = "";
            }

            else if(isPunctuator(currState) && !isPunctuator(nextState)) 
            {
                int punctuatorPos = pos - currState.length() + 1;
                printOutput(filename, line, punctuatorPos, "punctuator", currState);
                currState = "";
            }

        }
        else if(ch == '\"' )
        {
            ++pos;
            string sl = "\"";
            char nextChar = ' ';

            while(((nextChar = fs.peek()) != '\"') && (nextChar != EOF))
            {
                sl += nextChar;
                nextChar = fs.get();
                
            }

            if(nextChar == EOF)
                printError(filename, line, pos, "unterminated string");
            else
            {
                sl += fs.get();
                printOutput(filename, line, pos, "string-literal", sl);
            }
            currState = "";
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


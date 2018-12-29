#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

void printError(string fileName, int line, int column, const string &message) {
    cerr<<fileName<<":"<<line<<":"<<column<<": error: "<<message<<"\n";
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

int readtoken(string filename)
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

    while((ch = fs.get()) != EOF)
    {
        currState += ch;
        
        if (ch == '\n' ) 
        {
            ++line;
            pos = 0;

            currState = "";
        }    

        else if(ch == '\t')
        {
            ++pos;
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
            fs.unget();
            temp -= 1 ;
            printOutput(filename, line, pos, "constant", constVal);
            pos += temp;
            currState = "";
        }
        else if(ch == '\'')
        {   
            ++pos;
            int charPos = 0;
            char currChar = fs.get();
            string tmp = "";
            tmp += ch;
            tmp += currChar;
            charPos += 2;

            char nextChar = fs.peek();

            if ((currChar != '\\') && (currChar != '\''))
            {
                if (nextChar == '\'') 
                {
                    nextChar = fs.get();
                    tmp += nextChar;
                    ++charPos;
                    printOutput(filename, line, pos, "constant", tmp);
                    pos += charPos;

                } else 
                {
                    printError(filename, line, pos, "invalid  constant ");
                   return 1;

                }
            } else if((nextChar == 'a' ||
                        nextChar == 'b' ||
                        nextChar == 'r' ||
                        nextChar == 't' ||
                        nextChar == 'v' ||
                        nextChar == 'f' ||
                        nextChar == '\'' ||
                        nextChar == '\"' ||
                        nextChar == '\?' ||
                        nextChar == '\\' ||
                        nextChar == 'n') && (currChar == '\\' ))
            {
                tmp += fs.get();
                nextChar = fs.get();

                if(nextChar == '\'')
                {   
                    //  valid escape sequence
                    tmp += nextChar;
                    printOutput(filename, line, pos, "constant", tmp);
                    pos += 3;
                } else
                {
                    printError(filename, line, pos, "unterminated constant");
                       return 1;
                }       
            }
            else if(currChar =='\'')
            {          
                printError(filename, line, pos, "empty character");
                pos += 1;
                 return 1;
            }
            else if (nextChar == EOF )
            {
                printError(filename, line, pos, "unterminated constant");
                  return 1;

            }
            else
            {
                printError(filename, line, pos, "invalid constant");
                 return 1;
            }
            currState = "";
        }
        else if(isPunctuatorChar(ch))
        {
            ++pos;

            string nextState = currState;
            nextState += fs.peek();

            if (nextState == "//")
            {
                char prevChar = fs.get();
                char currChar = fs.get();
                char nextChar = fs.peek();

                while(currChar != EOF) 
                {
                    if (currChar == '\\'  ) 
                        {
                            if (nextChar =='\n' || nextChar =='\r')
                            {
                                ++line;
                            }   
                        else if( nextChar == EOF)
                        {
                            printError(filename, line, pos, "unterminated comment");
                            return 1;
                        }
                    }
                    else if( prevChar == '\\' && currChar=='\r' && nextChar=='\n')
                    {
                            //++line;
                            break;
                    }
                    else if(prevChar != '\\' && currChar == '\n')
                    {
                            ++line;
                          break;
                    }
                    
                    prevChar = currChar;
                    currChar = fs.get();
                    nextChar = fs.peek();
                }
                pos = 0;
                currState = "";
            }
            else if (nextState == "/*")
            {
                int temp = 0;
                char currChar = fs.get();
                char nextChar = fs.peek();
                ++pos;
                while(currChar != EOF)
                {
                    currChar = fs.get();
                    nextChar = fs.peek();

                    if (currChar == '*' && nextChar == '/') 
                    {
                        pos += 2;
                        line = line + temp;  
                        fs.get();
                        break;
                    } 
                    else if(currChar == '\n' || currChar == 0x0a || currChar == '\r' || currChar == 0x0d || ((currChar == '\r' || currChar == 0x0d ) && (nextChar == '\n' || nextChar == 0x0a ) ))
                    {
                        ++temp;
                        if((currChar == '\r' || currChar == 0x0d) && (nextChar == '\n' || nextChar == 0x0a))
                            fs.get();
                    }
                ++pos;
                }
                if (currChar == EOF)
                {
                    printError(filename, line, pos, "unterminated comment");
                       return 1;
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
            char currChar = fs.get();
            char nextChar = fs.peek();
            char prevChar = ' ';
            int charPos = 0;
            int tempLine = 0 ;
            int count_space = 29;

            ++charPos;
            int count = 0;
            while((currChar != '\"') && (currChar != EOF))
            {

                if (currChar == '\n' || currChar == '\r')
                {
                    if ((prevChar == '\\' && currChar == '\n') ||
                            (prevChar == '\\' && currChar == '\r' && nextChar == '\n'))
                    {
                        sl.pop_back();
                        ++tempLine;
                        charPos = 0;
                        ++count;
                        if(prevChar == '\\' && currChar == '\r' && nextChar == '\n')
                        {   
                            currChar = fs.get();
                        }
                        currChar = fs.get();
                    }
                    else if (currChar == '\n' || (currChar == '\r' && nextChar == '\n'))
                    {    ++tempLine;
                        charPos = 0 ; 
                    }
                }
                else if (currChar == '\\' && nextChar == 'f')
                {
                sl += "\n";
                fs.get();
                currChar = fs.get();
                
                for(int i = 0 ; i < count_space; ++i)
                    sl += " ";
               
                charPos += 2;
                }
                else if(!(nextChar == 'a' ||
                            nextChar == 'b' ||
                            nextChar == 'r' ||
                            nextChar == 't' ||
                            nextChar == 'v' ||
                            nextChar == 'f' ||
                            nextChar == 'n' ||
                            nextChar == '\'' ||
                            nextChar == '\"' ||
                            nextChar == '\?' ||
                            nextChar == '\n' ||
                            nextChar == '\r' ||
                            nextChar == '\\') && (currChar == '\\' ))
                {
                    printError(filename, line, pos, "invalid escape sequences in string");
                      return 1;
                }
                else if (currChar == '\f' || currChar == 0x0c)
                {
                    sl += currChar;
                    currChar = fs.get();
                }

                sl += currChar;

                ++charPos;
                ++count_space;
                prevChar = currChar;
                currChar = fs.get();
                nextChar = fs.peek();
            }

            if(currChar == EOF || currChar == '\n' || (currChar == '\r' && nextChar == '\n') )
            {
                printError(filename, line, pos, "unterminated string");
                   return 1;

            } 
            else
            {
                sl += currChar;
                printOutput(filename, line, pos, "string-literal", sl);

                if(count > 0)
                    pos = charPos + 1;
                else 
                    pos += charPos;
                line += tempLine;
            }
            currState = "";
        }

    }

    return 0;
}

int main(int argc, char *argv[])
{
    string str = argv[1];
    if (str.compare("--tokenize") == 0)
    {
        return readtoken(argv[2]);   
    }
    else if (str.compare("--parse") == 0)
    {
        return readtoken(argv[2]); 
    }
    else 
    {
        cout<<"error:Invalid Arguments"<<"\n";
        return 1;
    }
}


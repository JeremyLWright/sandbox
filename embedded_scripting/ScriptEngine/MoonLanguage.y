%{
#define YYDEBUG 1
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <map>
using namespace std;
extern "C"
{
int yylex();
void yyerror(char* s);
extern int yylineno;
}

map<string, function<void(int)>> scriptInterface;

%}


%union {
    int token;
    string* identifier;
    int placeholder;
    int number;
}

%error-verbose

%token <token> SELECT NEWLINE UNSELECT ACCEL TURN
%token <identifier> IDENTIFIER
%token <number> NUMBER
%type<placeholder> stmtlist stmt

%start stmtlist

%%
stmtlist: 
        | stmtlist NEWLINE {$$ = $1;}
        | stmtlist stmt NEWLINE
            {
                $$ = $1; //Copy the statement to the next line
            }
stmt: SELECT NUMBER { scriptInterface["select"]($2); }
    | UNSELECT NUMBER { scriptInterface["unselect"]($2); }
    | ACCEL NUMBER { scriptInterface["accel"]($2); }
    | TURN IDENTIFIER { scriptInterface["turn"](static_cast<char>($2->c_str()[0])); }

%%

void doSelection(int ship)
{
    cout << "Dynamically Selecting " << ship << endl;
}

void doUnselection(int ship)
{
    cout << "Dynamically Unselecting " << ship << endl;
}

#if 0
int main()
{
    scriptInterface["select"] = doSelection;
    scriptInterface["unselect"] = doUnselection;

    yylineno = 1;
    return yyparse();
}
#endif
void yyerror (char* s)  
{
    cout << s << endl;
}


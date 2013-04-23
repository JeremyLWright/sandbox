%option noyywrap yylineno
%{
#include <iostream>
#include <cstdlib>
using namespace std;
#include "MoonLangParser.hpp"
extern "C"
{
    int yylex();
}
%}

%%
[\n]                    { return yylval.token = NEWLINE; };
"select"                { return yylval.token = SELECT; };
"unselect"                { return yylval.token = UNSELECT; };
"accel"                 { return yylval.token = ACCEL; };
"turn"                 { return yylval.token = TURN; };
[-+]?[0-9]+                 { yylval.number = atoi(yytext);
                            return NUMBER;}
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.identifier = new string(yytext);
                            return IDENTIFIER; };


//
// Created by jason on 2/13/22.
//

#ifndef COMP_442_PARSER_H
#define COMP_442_PARSER_H
#include <vector>
#include <string>
#include <unordered_set>
#include "../lexer/lexer.h"
#include "../lexer/Token.h"
#include "../AST/ast.h"
#include "../AST/astFactory.h"
//Input file constants
const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/parser/";
const std::string FOLLOW = "first_follow_v";
const std::string PARSE = "parse_table_v";
const std::string VERSION ="40.csv";
//int constants
const int ADDOP =1;
const int CLOSEADDOP = 2;
const int NUM = 3;
const int NOT = 4;
const int INTEGER = 5;
const int FLOAT = 6;
const int ID = 7;
const int ASSIGNOP = 8;
const int CLOSEASSIGNOP = 9;
const int MULTOP = 10;
const int CLOSEMULTOP = 11;
const int SIGN = 12;
const int CLOSESIGN = 13;
const int CLOSENOT = 14;
const int EMPTY = 15;
const int VARDECL = 16;
const int ENDVARDECL = 17;
const int TYPE = 18;
const int FUNCDEF = 19;
const int ENDFUNCDEF = 20;
const int FPARAMLIST = 21;
const int ENDFPARAMLIST = 22;
const int DIMLIST =23;
const int ENDDIMLIST = 24;
const int FPARAM = 25;
const int ENDFPARAM = 26;
const int STATBLOCK = 27;
const int ENDSTATBLOCK = 28;
const int CLASSDECL = 29;
const int ENDCLASSDECL = 30;
const int MEMBDECL = 31;
const int ENDMEMBDECL = 32;
const int FUNCDECL = 33;
const int ENDFUNCDECL = 34;
const int PROG = 35;
const int ENDPROG = 36;
const int ARITHEXPR = 37;
const int ENDARITHEXPR = 38;
const int FACTOR = 39;
const int ENDFACTOR = 40;
const int TERM = 41;
const int ENDTERM = 42;
const int EXPR = 43;
const int ENDEXPR = 44;
const int RELOP = 45;
const int RELEXPR = 46;
const int ENDRELEXPR = 47;
const int IF = 48;
const int ENDIF = 49;
const int WHILE = 50;
const int ENDWHILE = 51;
const int GET = 52;
const int ENDGET = 53;
const int PUT = 54;
const int RETURN = 56;
const int ENDRETURN = 57;
const int ENDPUT = 58;
const int SCOPE = 59;
const int ENDSCOPE = 60;




//ooutput constants
const int ERROR = -1;
const std::string SRCSUFFIX = ".txt";
const std::string OUT = ".outderivation";
const std::string ERR = ".outsyntaxerrors";
const std::string LOG ="logs/";
//unordered map with function pointers...not sure this needs to be a map. could just be a set
//TODO refactor this so that it corresponds to an integer so I can use a swtich statement to call the semantic action function
inline const std::unordered_map<std::string, int> SEMANTIC_ACTIONS = {
        {"_addOp", ADDOP},
        {"_closeAddOp", CLOSEADDOP},
        {"_num", NUM},
        {"_id", ID},
        {"_not", NOT},
        {"_type", TYPE},
        {"_assignOp", ASSIGNOP},
        {"_closeAssignOp", CLOSEASSIGNOP},
        {"_multOp", MULTOP},
        {"_closeMultOp", CLOSEMULTOP},
        {"_sign", SIGN},
        {"_endSign", CLOSESIGN},
        {"_not", NOT},
        {"_endNot", CLOSENOT},
        {"_epsilon", EMPTY},
        {"_varDecl", VARDECL},
        {"_endVarDecl", ENDVARDECL},
        {"_funcDef", FUNCDEF},
        {"_endFuncDef", ENDFUNCDEF},
        {"_fparamList", FPARAMLIST},
        {"_endFparamList", ENDFPARAMLIST},
        {"_dimList", DIMLIST},
        {"_endDimList", ENDDIMLIST},
        {"_fParam", FPARAM},
        {"_endFparam", ENDFPARAM},
        {"_statBlock", STATBLOCK},
        {"_endStatBlock", ENDSTATBLOCK},
        {"_classDecl", CLASSDECL},
        {"_endClassDecl", ENDCLASSDECL},
        {"_membDecl",MEMBDECL},
        {"_endMembDecl", ENDMEMBDECL},
        {"_funcDecl", FUNCDECL},
        {"_endFuncDecl", ENDFUNCDECL},
        {"_prog", PROG},
        {"_endProg", ENDPROG},
        {"_arithExpr", ARITHEXPR},
        {"_endArithExpr", ENDARITHEXPR},
        {"_factor", FACTOR},
        {"_endFactor", ENDFACTOR},
        {"_term",TERM},
        {"_endTerm", ENDTERM},
        {"_expr", EXPR},
        {"_endExpr", ENDEXPR},
        {"_relOp", RELOP},
        {"_relExpr", RELEXPR},
        {"_endRelExpr", ENDRELEXPR},
        {"_if",IF},
        {"_endIf", ENDIF},
        {"_while", WHILE},
        {"_endWhile", ENDWHILE},
        {"_get", GET},
        {"_endGet", ENDGET},
        {"_put", PUT},
        {"_endPut", ENDPUT},
        {"_return", RETURN},
        {"_endReturn", ENDRETURN},
        {"_scopeSpec", SCOPE},
        {"_endScope", ENDSCOPE}

};

inline const std::unordered_map<std::string, std::string> TOKEN_NODE_TRANSLATIONS ={
        {"integer", "type"},
        {"intlit", "num"},
        {"plus", "addOp"},
        {"minus", "addOp"},
        {"or", "addOp"},
        {"mult", "multOp"},
        {"div", "multOp"},
        {"and", "multOp"},
        {"equal", "assignStat"},
        {"not", "not"},
        {"let", "varDecl"},
        {"eq", "relOp"},
        {"neq", "relOp"},
        {"lt", "relOp"},
        {"gt", "relOp"},
        {"leq", "relOp"},
        {"geq", "relOp"},

};
class Parser {
private:
    std::vector<std::vector<std::string>> parseTable;
    std::vector<std::vector<std::string>>firstFollow;
    std::unordered_set<std::string> terminals;
    Lexer lexer;
    std::vector<std::string> parseStack{};
    std::vector<Node*> semanticStack{};
    NodeFactory factory{};
    std::string sourceFile;
    std::string outFiles[2];
public:
    Parser(std::string src);
    ~Parser();
    std::vector<std::vector<std::string>>loadTable(std::string fileName);
    void readSource();
    Node * parse();
    void skipError();
    void inverseRHSMultiPush(std::string rules);
    Token getNextToken();
    std::vector<std::string>whitespace_split(const std::string& str);
    void log();
    bool first(std::string top, std::string _lookAhead);
    bool follow(std::string top, std::string _lookAhead);
    void handleSemanticActions(int choice, Token token);
    //AST creation functions
    void createLeaf(Token tok);
    void createTypeLeaf(Token tok);
    void openAddOpTree(Token tok);
    void closeAddOpTree();
    void openAssignOp(Token tok);
    void closeAssignOp();
    void openMultOp(Token tok);
    void closeMultOp();
    void openNot(Token tok);
    void closeNot();
    void openSign(Token tok);
    void closeSign();
    void createVarDecl(Token tok);
    void endVrDecl();
    void createEpsilon();
    void createFparamList();
    void endFparamList();
    void createFuncDef();
    void endFuncDef();
    void createDimList();
    void endDimList();
    void createFparam();
    void endFparam();
    void createStatBlock();
    void endStatBlock();
    void createClassDef();
    void endClassDef();
    void membDecl();
    void endMembDecl();
    void generalDecl(std::string type);
    void endGeneralDecl(std::string type);
};


#endif //COMP_442_PARSER_H

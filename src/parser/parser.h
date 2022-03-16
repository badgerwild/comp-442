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
const std::string VERSION ="25.csv";
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
       // {"_integer", INTEGER},
        // {"_float", FLOAT},
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
        {"_endStatBlock", ENDSTATBLOCK}

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
        {"let", "varDecl"}
};
class Parser {
private:
    std::vector<std::vector<std::string>> parseTable;
    std::vector<std::vector<std::string>>firstFollow;
    std::unordered_set<std::string> terminals;
    Lexer lexer;
    std::vector<std::string> parseStack{};
    std::vector<Node*> semanticStack{};
    Node* semanticTree;
    NodeFactory factory{};
    std::string sourceFile;
    std::string outFiles[2];
public:
    Parser(std::string src);
    ~Parser();
    std::vector<std::vector<std::string>>loadTable(std::string fileName);
    void readSource();
    bool parse();
    void skipError();
    void inverseRHSMultiPush(std::string rules);
    Token getNextToken();
    std::vector<std::string>whitespace_split(const std::string& str);
    void log();
    bool first(std::string top, std::string _lookAhead);
    bool follow(std::string top, std::string _lookAhead);
    //AST creation functions
    void createLeaf(Token tok);
    void createTypeLeaf(Token tok);
    Node* createSubTree();
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






};


#endif //COMP_442_PARSER_H

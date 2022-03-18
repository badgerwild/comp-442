//
// Created by jason on 3/16/22.
//

#ifndef COMP_442_SYMBOLTABLE_H
#define COMP_442_SYMBOLTABLE_H


#include <string>
#include <vector>
#include <iostream>
class SymbolTable;
class SymbolTableRow{
private:
    std::string name;
    std::string kind;
    std::string symbolType;
    SymbolTable* subTable;
public:
    SymbolTableRow();
    SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                   SymbolTable *subTable);
    virtual ~SymbolTableRow();
    const std::string &getName() const;
    const std::string &getKind() const;
    const std::string &getSymbolType() const;
    SymbolTable *getSubTable() const;
    void insertSubTable(SymbolTable* subTable);
    //TODO this might be wonky with pointers, ngl?
    //friend std::ostream &operator <<(std::ostream &out, SymbolTableRow &S);
};

class FuncTableRow: public SymbolTableRow{
private:
    std::vector<int> params;
public:
    FuncTableRow();

    FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                 const std::vector<int> &params, SymbolTable *subTable);

    virtual ~FuncTableRow();

};

class SymbolTable {
private:
 std::vector<SymbolTableRow> tableEntries;
 std::string scope;
 int size;
 int table_level;
 SymbolTable* parentTable;
public:
    SymbolTable();
    SymbolTable(std::string scope, SymbolTable *parent, int level);
    virtual ~SymbolTable();
    const std::string &getScope() const;
    void setScope(const std::string &scope);
    void insert(SymbolTableRow row);
    SymbolTableRow createNewTable(std::string scope);
    //TODO figure out what this method is supposed to return
    SymbolTableRow search(std::string id_);
    friend std::ostream &operator << (std::ostream &out, SymbolTable &S);
    void printAll();
    void deleteAll();


};


#endif //COMP_442_SYMBOLTABLE_H

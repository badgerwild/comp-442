//
// Created by jason on 3/16/22.
//

#ifndef COMP_442_SYMBOLTABLE_H
#define COMP_442_SYMBOLTABLE_H


#include <string>
#include <list>
class SymbolTable;
class SymbolTableRow{
private:
    std::string name;
    std::string kind;
    std::string symbolType;
    SymbolTable* subTable;
public:
    SymbolTableRow();

    SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType);
    virtual ~SymbolTableRow();
    const std::string &getName() const;
    const std::string &getKind() const;
    const std::string &getSymbolType() const;
    SymbolTable *getSubTable() const;
    //TODO this might be wonky with pointers, ngl?
    friend std::ostream &operator <<(std::ostream &out, SymbolTableRow &S);
};

class SymbolTable {
private:
 std::list<SymbolTableRow> row;
 std::string scope;
public:
    SymbolTable();
    virtual ~SymbolTable();
    const std::string &getScope() const;
    void setScope(const std::string &scope);
    void Insert(SymbolTableRow row);
    //TODO figure out what this method is supposed to return
    void search(std::string id_);
    void printAll();
    void deleteAll();


};


#endif //COMP_442_SYMBOLTABLE_H

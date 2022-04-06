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
    int size{};
    int offSet{};

public:
    std::string moonTag;
    SymbolTableRow();

    SymbolTableRow(const std::string &name, const std::string &kind, SymbolTable *subTable);

    SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                   SymbolTable *subTable);

    void setSubTable(SymbolTable *subTable);

    virtual ~SymbolTableRow();
    const std::string &getName() const;
    const std::string &getKind() const;
    const std::string &getSymbolType() const;
    SymbolTable *getSubTable() const;
    void insertSubTable(SymbolTable* subTable);
    friend std::ostream &operator << (std::ostream &out, SymbolTableRow &S);

    int getSize() const;

    void setSize(int size);

    int getOffSet() const;

    void setOffSet(int offSet);
};

class FuncTableRow: public SymbolTableRow{
private:
    std::vector<int> params;
public:
    FuncTableRow();

    FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                 SymbolTable *subTable);

    FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                 const std::vector<int> &params, SymbolTable *subTable);

    const std::vector<int> &getParams() const;

    virtual ~FuncTableRow();
    friend std::ostream &operator << (std::ostream &out, FuncTableRow &S);

};

class VarDeclRow: public SymbolTableRow{
private:
    std::vector<std::string> dims;
public:
    VarDeclRow();

    VarDeclRow(const std::string &name, const std::string &kind, const std::string &symbolType, SymbolTable *subTable,
               const std::vector<std::string> &dims);

    virtual ~VarDeclRow();
    friend std::ostream &operator << (std::ostream &out, VarDeclRow &S);

};


class SymbolTable {
private:
 std::vector<SymbolTableRow> tableEntries;
 std::string scope;
 //int size;
//int table_level;
 SymbolTable* parentTable;
public:
    int tableOffset{};
    int tableSize{};
    std::string moonTag;
    SymbolTable();
    SymbolTable(std::string scope, SymbolTable *parent, int level);
    virtual ~SymbolTable();
    const std::string &getScope() const;
    void setScope(const std::string &scope);
    void insert(SymbolTableRow row);
    std::vector<SymbolTableRow> &getTableEntries();

    SymbolTable *getParentTable() const;

    void setParentTable(SymbolTable *parentTable);

    SymbolTableRow search(std::string id_);
    friend std::ostream &operator << (std::ostream &out, SymbolTable &S);


};


#endif //COMP_442_SYMBOLTABLE_H

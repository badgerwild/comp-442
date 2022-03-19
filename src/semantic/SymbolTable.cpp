//
// Created by jason on 3/16/22.
//

#include "SymbolTable.h"

SymbolTableRow::SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                               SymbolTable *subTable) : name(
        name), kind(kind), symbolType(symbolType), subTable(subTable) {}

SymbolTableRow::~SymbolTableRow() {

}

const std::string &SymbolTableRow::getName() const {
    return name;
}

const std::string &SymbolTableRow::getKind() const {
    return kind;
}

const std::string &SymbolTableRow::getSymbolType() const {
    return symbolType;
}




SymbolTable *SymbolTableRow::getSubTable() const {
    return subTable;
}

SymbolTableRow::SymbolTableRow() {}



FuncTableRow::FuncTableRow() {}

FuncTableRow::FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                           const std::vector<int> &params, SymbolTable *subTable) : SymbolTableRow(name, kind, symbolType, subTable), params(params) {}

FuncTableRow::~FuncTableRow() {

}
SymbolTable::SymbolTable() {}
SymbolTable::SymbolTable(std::string scope, SymbolTable *parent, int level) {
    this->scope = scope;
    this-> parentTable = parent;
    this->table_level = level;
}

SymbolTable::~SymbolTable() {

}

const std::string &SymbolTable::getScope() const {
    return scope;
}

void SymbolTable::setScope(const std::string &scope) {
    this->scope = scope;
}
/*
SymbolTableRow SymbolTable::createNewTable(std::string scope){
    SymbolTable* temp = new SymbolTable(scope);


}
 */

void  SymbolTable::insert(SymbolTableRow row) {
    tableEntries.push_back(row);
}

//TODO create nulltable entry.....
SymbolTableRow SymbolTable::search(std::string id_) {
    SymbolTableRow foundValue;
    bool found = false;
    for (auto &a: this->tableEntries) {
        if (a.getName() == id_) {
            foundValue = a;
            found = true;

        }
        if (!found) {
            if (parentTable != nullptr) {
                foundValue = parentTable->search(id_);
                found = true;
            }
        }
        return foundValue;
    }
}
std::ostream &operator << (std::ostream &out, SymbolTable &S){
    out <<"------------------------------------------------------" <<std::endl;
    out<<"table name --> " << S.scope<<std::endl;
    /*if (S.parentTable != nullptr) {
        out<<"Parent table -->" <<S.parentTable->scope <<std::endl;
    }
*/
    out<< "Name | Kind  | Symbol Type | SubTable "<< std::endl;
    out <<"------------------------------------------------------" <<std::endl;
    for (auto &a : S.tableEntries) {
        out<< a.getName() <<" | " << a.getKind() << " | " << a.getSymbolType() << " | ";
        if (a.getSubTable() != nullptr ){
            out<< a.getSubTable()->getScope()<< std::endl;
        }
        else{
            out<<"no sub table" <<std::endl;
        }
    }
    out <<"------------------------------------------------------" <<std::endl;
    return out;
   }


VarDeclROW::VarDeclROW(const std::string &name, const std::string &kind, const std::string &symbolType,
                       SymbolTable *subTable, const std::vector<std::string> &dims) : SymbolTableRow(name, kind, symbolType,
                                                                                        subTable), dims(dims) {}

VarDeclROW::VarDeclROW() {}

VarDeclROW::~VarDeclROW() {

}

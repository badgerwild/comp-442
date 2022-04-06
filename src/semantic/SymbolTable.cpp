//
// Created by jason on 3/16/22.
//

#include "SymbolTable.h"

SymbolTableRow::SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                               SymbolTable *subTable) : name(
        name), kind(kind), symbolType(symbolType), subTable(subTable) {
}

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

 void SymbolTableRow::insertSubTable(SymbolTable *subTable) {
    this->subTable = subTable;
}
SymbolTableRow::SymbolTableRow() {
    subTable = nullptr;
}

SymbolTableRow::SymbolTableRow(const std::string &name, const std::string &kind, SymbolTable *subTable) : name(name),
                                                                                                          kind(kind),
                                                                                                          subTable(
                                                                                                                  subTable) {}


std::ostream &operator << (std::ostream &out, SymbolTableRow &S){
   out << S.getName() << " | " << S.getKind() << " | " << S.moonTag<< " | " << S.getSymbolType() <<" | "<<"Size: "<< S.getSize() <<" | ";
   out << "Offset: "<< S.getOffSet()<<" | ";
   if (S.getSubTable()!= nullptr){
        out << S.getSubTable()->getScope()<< std::endl;
    }
    else{
        out << "no subtable"<<std::endl;
    }
    return out;
}

void SymbolTableRow::setSubTable(SymbolTable *subTable) {
    SymbolTableRow::subTable = subTable;
}

int SymbolTableRow::getSize() const {
    return size;
}

void SymbolTableRow::setSize(int size) {
    SymbolTableRow::size = size;
}

int SymbolTableRow::getOffSet() const {
    return offSet;
}

void SymbolTableRow::setOffSet(int offSet) {
    SymbolTableRow::offSet = offSet;
}

FuncTableRow::FuncTableRow(){
}

//TODO deal with param here
FuncTableRow::FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                           const std::vector<int> &params, SymbolTable *subTable) : SymbolTableRow(name, kind, symbolType, subTable), params(params) {}

FuncTableRow::~FuncTableRow() {

}

FuncTableRow::FuncTableRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                           SymbolTable *subTable) : SymbolTableRow(name, kind, symbolType, subTable) {

}

std::ostream &operator << (std::ostream &out, FuncTableRow &S){
    out << S.getName() << " | " << S.moonTag <<" | " << S.getKind() << " | " << S.getSymbolType() <<" | ";
    if (S.getSubTable()!= nullptr){
        out << S.getSubTable()->getScope()<< std::endl;
    }
    else{
        out << "no subtable"<<std::endl;
    }
    return out;
}

const std::vector<int> &FuncTableRow::getParams() const {
    return params;
}

VarDeclRow::VarDeclRow(const std::string &name, const std::string &kind, const std::string &symbolType,
                       SymbolTable *subTable, const std::vector<std::string> &dims) : SymbolTableRow(name, kind, symbolType,
                                                                                                     subTable), dims(dims) {}

VarDeclRow::VarDeclRow() {}

VarDeclRow::~VarDeclRow() {

}
std::ostream &operator << (std::ostream &out, VarDeclRow &S){
    out << S.getName()<< "( ";
    for (std::string &s: S.dims){
        out<< s << " ";
    }
    out <<")";
    out<< " | "<< S.moonTag<< " | " << S.getKind() << " | " << S.getSymbolType() <<" | ";
    if (S.getSubTable()!= nullptr){
        out << S.getSubTable()->getScope()<< std::endl;
    }
    else{
        out << "no subtable"<<std::endl;
    }
    return out;
}
SymbolTable::SymbolTable() {}
SymbolTable::~SymbolTable() {

}

const std::string &SymbolTable::getScope() const {
    return scope;
}

void SymbolTable::setScope(const std::string &scope) {
    this->scope = scope;
}

void  SymbolTable::insert(SymbolTableRow row) {
    tableEntries.push_back(row);
}

SymbolTableRow SymbolTable::search(std::string id_) {
    SymbolTableRow foundValue;
    bool found = false;
    for (auto &a: this->tableEntries) {
        if (a.getName() == id_) {
            foundValue = a;
            found = true;
            // return foundValue;
        }
        }
        if (!found) {
            if (parentTable != nullptr) {
                foundValue = parentTable->search(id_);
                found = true;
            }
        }
    return foundValue;
}



std::ostream &operator << (std::ostream &out, SymbolTable &S){
    out <<"------------------------------------------------------" <<std::endl;
    out <<"Symbol table size --> " << S.tableSize<<std::endl;
    out<<"table scope --> " << S.scope<< " Offset --> " << S.tableOffset<< std::endl ;
    out<< "Name | Moon tag | Kind  | Symbol Type | Size | offset | SubTable "<< std::endl;
    out <<"------------------------------------------------------" <<std::endl;
    for (auto &a : S.tableEntries) {
        out<<a;
    }
    out <<"------------------------------------------------------" <<std::endl;
    return out;
   }
   std::vector<SymbolTableRow> &SymbolTable::getTableEntries() {
    return tableEntries;
}

SymbolTable *SymbolTable::getParentTable() const {
    return parentTable;
}

void SymbolTable::setParentTable(SymbolTable *parentTable) {
    this->parentTable = parentTable;
}



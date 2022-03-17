//
// Created by jason on 3/16/22.
//

#include "SymbolTable.h"

SymbolTableRow::SymbolTableRow(const std::string &name, const std::string &kind, const std::string &symbolType) : name(
        name), kind(kind), symbolType(symbolType) {}

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

SymbolTable::SymbolTable() {}

SymbolTable::~SymbolTable() {

}

const std::string &SymbolTable::getScope() const {
    return scope;
}

void SymbolTable::setScope(const std::string &scope) {
    SymbolTable::scope = scope;
}

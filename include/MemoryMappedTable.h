//
// Created by Joshua McDonagh on 22/05/2024.
//

#ifndef PYNEX_MEMORYMAPPEDTABLE_H
#define PYNEX_MEMORYMAPPEDTABLE_H

#include <windows.h>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <sstream>

using DataVariant = std::variant<int, double, std::string, bool>;

class MemoryMappedTable {
public:
    MemoryMappedTable(std::string  filename, size_t initialRowCount, size_t rowSize);
    ~MemoryMappedTable();

    std::vector<DataVariant> operator[](size_t index);
    void addRow(const std::vector<DataVariant>& data);
    void setColumn(size_t columnIndex, const std::vector<DataVariant>& newColumn);
    std::vector<DataVariant> getColumn(size_t columnIndex);

private:
    void resize(size_t newRowCount);
    std::string serialize(const std::vector<DataVariant>& row);
    std::vector<DataVariant> deserialize(const std::string& data);

    std::string filename_;
    size_t rowCount_;
    size_t rowSize_;
    HANDLE fileHandle_;
    HANDLE mapHandle_;
    char* data_;
    size_t currentCapacity_;
};

#endif //PYNEX_MEMORYMAPPEDTABLE_H

//
// Created by Joshua McDonagh on 22/05/2024.
//

#include "../include/MemoryMappedTable.h"
#include <iostream>
#include <cstring>
#include <utility>

// Constructor: opens the file, sets its size, and memory-maps it
MemoryMappedTable::MemoryMappedTable(std::string  filename, size_t initialRowCount, size_t rowSize)
        : filename_m(std::move(filename)), rowCount_m(0), rowSize_m(rowSize), currentCapacity_m(initialRowCount) {
    // Open or create file
    fileHandle_m = CreateFile(
            filename_m.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle_m == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Unable to open file");
    }

    // Set initial file size
    LARGE_INTEGER fileSize;
    fileSize.QuadPart = initialRowCount * rowSize * sizeof(char); // Adjust for char
    if (!SetFilePointerEx(fileHandle_m, fileSize, NULL, FILE_BEGIN) || !SetEndOfFile(fileHandle_m)) {
        CloseHandle(fileHandle_m);
        throw std::runtime_error("Unable to set file size");
    }

    // Create file mapping
    mapHandle_m = CreateFileMapping(fileHandle_m, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (mapHandle_m == NULL) {
        CloseHandle(fileHandle_m);
        throw std::runtime_error("Unable to create file mapping");
    }

    // Map view of file
    data_m = static_cast<char*>(MapViewOfFile(mapHandle_m, FILE_MAP_ALL_ACCESS, 0, 0, initialRowCount * rowSize * sizeof(char)));
    if (data_m == NULL) {
        CloseHandle(mapHandle_m);
        CloseHandle(fileHandle_m);
        throw std::runtime_error("Unable to map view of file");
    }
}

// Destructor: unmaps the file and closes the file and mapping handles
MemoryMappedTable::~MemoryMappedTable() {
    if (data_m) {
        UnmapViewOfFile(data_m);
    }
    if (mapHandle_m != NULL) {
        CloseHandle(mapHandle_m);
    }
    if (fileHandle_m != INVALID_HANDLE_VALUE) {
        CloseHandle(fileHandle_m);
    }
}

// Resize the memory-mapped file to accommodate more rows
void MemoryMappedTable::resize(size_t newRowCount) {
    if (newRowCount <= currentCapacity_m) {
        return; // No need to resize
    }

    // Unmap the current memory
    UnmapViewOfFile(data_m);
    CloseHandle(mapHandle_m);

    // Set the new capacity and resize the file
    currentCapacity_m = newRowCount;
    LARGE_INTEGER fileSize;
    fileSize.QuadPart = currentCapacity_m * rowSize_m * sizeof(char);
    if (!SetFilePointerEx(fileHandle_m, fileSize, NULL, FILE_BEGIN) || !SetEndOfFile(fileHandle_m)) {
        throw std::runtime_error("Unable to resize file");
    }

    // Create new file mapping
    mapHandle_m = CreateFileMapping(fileHandle_m, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (mapHandle_m == NULL) {
        throw std::runtime_error("Unable to create file mapping");
    }

    // Map view of file with the new size
    data_m = static_cast<char*>(MapViewOfFile(mapHandle_m, FILE_MAP_ALL_ACCESS, 0, 0, currentCapacity_m * rowSize_m * sizeof(char)));
    if (data_m == NULL) {
        throw std::runtime_error("Unable to map view of file");
    }
}

// Add a row to the table, resizing if necessary
void MemoryMappedTable::addRow(const std::vector<DataVariant>& newRow) {
    if (rowCount_m >= currentCapacity_m) {
        resize(currentCapacity_m * 2); // Double the capacity
    }
    std::string serializedRow = serialize(newRow);
    if (serializedRow.size() > rowSize_m) {
        throw std::runtime_error("Row size exceeds allocated row size");
    }
    std::memcpy(&data_m[rowCount_m * rowSize_m], serializedRow.c_str(), serializedRow.size());
    rowCount_m++;
}

void MemoryMappedTable::addColumn(const std::vector<DataVariant>& newColumn) {
    if (rowCount_m == 0) {
        // If the table is empty, initialize it with rows from the new column
        for (const auto& item : newColumn) {
            std::vector<DataVariant> newRow = { item };
            addRow(newRow);
        }
    } else {
        if (newColumn.size() != rowCount_m) {
            throw std::invalid_argument("Column size does not match row count");
        }

        for (size_t i = 0; i < rowCount_m; ++i) {
            std::vector<DataVariant> row = (*this)[i];
            row.push_back(newColumn[i]);
            std::string serializedRow = serialize(row);
            if (serializedRow.size() > rowSize_m) {
                throw std::runtime_error("Row size exceeds allocated row size");
            }
            std::memcpy(&data_m[i * rowSize_m], serializedRow.c_str(), serializedRow.size());
        }
    }
}

void MemoryMappedTable::setColumn(size_t columnIndex, const std::vector<DataVariant>& newColumn) {
    if (newColumn.size() != rowCount_m) {
        throw std::invalid_argument("Column size does not match row count");
    }

    for (size_t i = 0; i < rowCount_m; ++i) {
        std::vector<DataVariant> row = (*this)[i];
        if (columnIndex >= row.size()) {
            throw std::out_of_range("Column index out of range");
        }
        row[columnIndex] = newColumn[i];
        std::string serializedRow = serialize(row);
        if (serializedRow.size() > rowSize_m) {
            throw std::runtime_error("Row size exceeds allocated row size");
        }
        std::memcpy(&data_m[i * rowSize_m], serializedRow.c_str(), serializedRow.size());
    }
}

std::vector<DataVariant> MemoryMappedTable::getColumn(size_t columnIndex) {
    std::vector<DataVariant> columnData;

    for (size_t i = 0; i < rowCount_m; ++i) {
        std::vector<DataVariant> row = (*this)[i];
        if (columnIndex >= row.size()) {
            throw std::out_of_range("Column index out of range");
        }
        columnData.push_back(row[columnIndex]);
    }

    return columnData;
}

// Overloaded operator[]: provides access to the rows
std::vector<DataVariant> MemoryMappedTable::operator[](size_t index) {
    if (index >= rowCount_m) {
        throw std::out_of_range("Index out of range");
    }
    std::string serializedRow(&data_m[index * rowSize_m], rowSize_m);
    return deserialize(serializedRow);
}

// Serialize a row into a string
std::string MemoryMappedTable::serialize(const std::vector<DataVariant>& row) {
    std::ostringstream oss;
    for (const auto& item : row) {
        if (std::holds_alternative<int>(item)) {
            oss << "int:" << std::get<int>(item) << ";";
        } else if (std::holds_alternative<double>(item)) {
            oss << "double:" << std::get<double>(item) << ";";
        } else if (std::holds_alternative<std::string>(item)) {
            oss << "string:" << std::get<std::string>(item) << ";";
        } else if (std::holds_alternative<bool>(item)) {
            oss << "bool:" << std::get<bool>(item) << ";";
        }
    }
    return oss.str();
}

// Deserialize a string into a row
std::vector<DataVariant> MemoryMappedTable::deserialize(const std::string& data) {
    std::vector<DataVariant> row;
    std::istringstream iss(data);
    std::string item;
    while (std::getline(iss, item, ';')) {
        size_t sep = item.find(':');
        if (sep != std::string::npos) {
            std::string type = item.substr(0, sep);
            std::string value = item.substr(sep + 1);
            if (type == "int") {
                row.push_back(std::stoi(value));
            } else if (type == "double") {
                row.push_back(std::stod(value));
            } else if (type == "string") {
                row.push_back(value);
            } else if (type == "bool") {
                row.push_back(value == "1");
            }
        }
    }
    return row;
}

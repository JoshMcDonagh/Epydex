//
// Created by Joshua McDonagh on 22/05/2024.
//

#include "../include/MemoryMappedTable.h"
#include <iostream>
#include <cstring>
#include <utility>

// Constructor: opens the file, sets its size, and memory-maps it
MemoryMappedTable::MemoryMappedTable(std::string  filename, size_t initialRowCount, size_t rowSize)
        : filename_(std::move(filename)), rowCount_(0), rowSize_(rowSize), currentCapacity_(initialRowCount) {
    // Open or create file
    fileHandle_ = CreateFile(
            filename_.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle_ == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Unable to open file");
    }

    // Set initial file size
    LARGE_INTEGER fileSize;
    fileSize.QuadPart = initialRowCount * rowSize * sizeof(char); // Adjust for char
    if (!SetFilePointerEx(fileHandle_, fileSize, NULL, FILE_BEGIN) || !SetEndOfFile(fileHandle_)) {
        CloseHandle(fileHandle_);
        throw std::runtime_error("Unable to set file size");
    }

    // Create file mapping
    mapHandle_ = CreateFileMapping(fileHandle_, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (mapHandle_ == NULL) {
        CloseHandle(fileHandle_);
        throw std::runtime_error("Unable to create file mapping");
    }

    // Map view of file
    data_ = static_cast<char*>(MapViewOfFile(mapHandle_, FILE_MAP_ALL_ACCESS, 0, 0, initialRowCount * rowSize * sizeof(char)));
    if (data_ == NULL) {
        CloseHandle(mapHandle_);
        CloseHandle(fileHandle_);
        throw std::runtime_error("Unable to map view of file");
    }
}

// Destructor: unmaps the file and closes the file and mapping handles
MemoryMappedTable::~MemoryMappedTable() {
    if (data_) {
        UnmapViewOfFile(data_);
    }
    if (mapHandle_ != NULL) {
        CloseHandle(mapHandle_);
    }
    if (fileHandle_ != INVALID_HANDLE_VALUE) {
        CloseHandle(fileHandle_);
    }
}

// Resize the memory-mapped file to accommodate more rows
void MemoryMappedTable::resize(size_t newRowCount) {
    if (newRowCount <= currentCapacity_) {
        return; // No need to resize
    }

    // Unmap the current memory
    UnmapViewOfFile(data_);
    CloseHandle(mapHandle_);

    // Set the new capacity and resize the file
    currentCapacity_ = newRowCount;
    LARGE_INTEGER fileSize;
    fileSize.QuadPart = currentCapacity_ * rowSize_ * sizeof(char);
    if (!SetFilePointerEx(fileHandle_, fileSize, NULL, FILE_BEGIN) || !SetEndOfFile(fileHandle_)) {
        throw std::runtime_error("Unable to resize file");
    }

    // Create new file mapping
    mapHandle_ = CreateFileMapping(fileHandle_, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (mapHandle_ == NULL) {
        throw std::runtime_error("Unable to create file mapping");
    }

    // Map view of file with the new size
    data_ = static_cast<char*>(MapViewOfFile(mapHandle_, FILE_MAP_ALL_ACCESS, 0, 0, currentCapacity_ * rowSize_ * sizeof(char)));
    if (data_ == NULL) {
        throw std::runtime_error("Unable to map view of file");
    }
}

// Add a row to the table, resizing if necessary
void MemoryMappedTable::addRow(const std::vector<DataVariant>& newRow) {
    if (rowCount_ >= currentCapacity_) {
        resize(currentCapacity_ * 2); // Double the capacity
    }
    std::string serializedRow = serialize(newRow);
    if (serializedRow.size() > rowSize_) {
        throw std::runtime_error("Row size exceeds allocated row size");
    }
    std::memcpy(&data_[rowCount_ * rowSize_], serializedRow.c_str(), serializedRow.size());
    rowCount_++;
}

// Overloaded operator[]: provides access to the rows
std::vector<DataVariant> MemoryMappedTable::operator[](size_t index) {
    if (index >= rowCount_) {
        throw std::out_of_range("Index out of range");
    }
    std::string serializedRow(&data_[index * rowSize_], rowSize_);
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

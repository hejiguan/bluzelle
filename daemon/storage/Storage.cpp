#include <iostream>
#include "Storage.h"


Storage::Storage(const string& filepath) {
    /* Create a file at filepath to write data to.
     * Data is writtent in CSV format. First column is key, second is value, CR/LF
     * */
}

Storage::~Storage() {
    // Flush to disk.
}

void Storage::create(const string& key, const string& value) {
    // Open file, add line, flush, close file.
    std::cout << "Storage: " << "[C] " << key << ":" << value << std::endl;
    kv_store_[key] = value;
}

string Storage::read(const string& key) {
    // Open file, read lines, find one starting with key, read value, close file, return value.
    auto value = kv_store_[key];
    std::cout << "Storage: " << "[R] " << key << ":" << value << std::endl;
    return value;
}

void Storage::update(const string& key, const string& value) {
    std::cout << "Storage: " << "[U] " << key << ":" << value << std::endl;
    kv_store_[key] = value;
}

void Storage::remove(const string& key) {
    auto value = kv_store_[key];
    std::cout << "Storage: " << "[D] " << key << ":" << value << std::endl;
    kv_store_.erase(key);
}
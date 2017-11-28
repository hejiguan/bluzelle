#include <unordered_map>

using std::unordered_map;

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
}

string Storage::read(const string& key) {
    // Open file, read lines, find one starting with key, read value, close file, return value.
}

void Storage::update(const string& key, const string& value) {
    //...
}

void Storage::remove(const string& key, const string& value) {
    // ...
}
#ifndef BLUZELLE_STORAGE_H
#define BLUZELLE_STORAGE_H

#include <string>

using std::string;

// Key/value pairs storage class
// Implements basic CRUD

class Storage {
public:
    Storage(const string& filepath);
    ~Storage();

    void create(const string& key, const string& value);
    string read(const string& key);
    void update(const string& key, const string& value);
    void remove(const string& key, const string& value);
};

#endif //BLUZELLE_STORAGE_H

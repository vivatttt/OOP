#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

const int BASE_TABLE_SIZE = 10;

enum OccupationStatus {
    EMPTY,
    OCCUPIED,
    DELETED,
};

template<typename KeyType, typename ValueType>
class HashTable {
    protected:
        struct HashNode {
            KeyType key;
            ValueType value;
            OccupationStatus status;

            HashNode() : status(EMPTY) {}
        };
        std::vector<HashNode> table;
        int numElements;
        
        void rehash();
        int getHash(const KeyType& key, int tableSize);
        struct ObtainedObject {
            bool is_found;
            ValueType value;

            ObtainedObject(bool found, const ValueType& val) : is_found(found), value(val) {}
            ObtainedObject() : is_found(false), value(ValueType()) {}
        };
    public:
        HashTable();
        HashTable(const HashTable &other);
        ~HashTable();

        void insert(const KeyType& key, const ValueType& value);
        ObtainedObject get(const KeyType& key);
        bool pop(const KeyType& key);
        bool contains(const KeyType& key);
        void clear();
        int getNumberOfItems();

        bool operator ==(HashTable<KeyType, ValueType>& other);
        ValueType operator [](const KeyType& key);
        HashTable operator &&(HashTable<KeyType, ValueType>& other);

        void saveToFile(std::string filename);
        void loadFromFile(std::string filename);
        void printTable();
};

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable() : numElements(0), table(BASE_TABLE_SIZE) {}

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(const HashTable &other) : numElements(other.numElements), table(other.table) {}

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {}


template<typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::getHash(const KeyType& key, int tableSize) {
    static std::hash<KeyType> hashFunction;
    return hashFunction(key) % tableSize;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash(){
    int newLength = table.size();
    std::vector<HashNode> newTable(newLength);

    for (HashNode& node : table) {
        if (node.status == OCCUPIED) {
            int index = getHash(node.key, newLength);
            while (newTable[index].status == OCCUPIED) {
                index = (index + 1) % newLength;
            }
            newTable[index] = node;
        }
    }

    table = std::move(newTable);
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
        int index = getHash(key, table.size());
        while (table[index].status == OCCUPIED) {
            // идем до тех пор пока либо не найдем пустой бакет
            // либо элемент с таким же ключом (в таком случае значение по этому ключу обновляем на пришедшее)
            if (table[index].key == key) {
                return;
            }
            index = (index + 1) % table.size();
        }

        table[index].key = key;
        table[index].value = value;
        table[index].status = OCCUPIED;
        numElements++;

        if (numElements > table.size() / 2) {
            rehash();
        }
    }


template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::ObtainedObject HashTable<KeyType, ValueType>::get(const KeyType& key) {
    int index = getHash(key, table.size());

    while (table[index].status != EMPTY) {
        if (table[index].status == OCCUPIED && table[index].key == key) {
            return ObtainedObject(true, table[index].value);
        }
        index = (index + 1) % table.size();
    }
    return ObtainedObject(false, ValueType());
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::pop(const KeyType& key) {
    int index = getHash(key, table.size());

    while (table[index].status != EMPTY) {
        if (table[index].status == OCCUPIED && table[index].key == key) {
            table[index].status = DELETED;
            numElements--;
            return true;
        }
        index = (index + 1) % table.size();
    }
    return false;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::operator==(HashTable<KeyType, ValueType>& other) {
    if (numElements != other.numElements) {
        return false;
    }

    for (HashNode& node : table) {
        if (node.status == OCCUPIED) {
            ObtainedObject obj = other.get(node.key);
            if (!obj.is_found || obj.value != node.value) {
                return false;
            }
        }
    }
    return true;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::contains(const KeyType& key) {
    return get(key).is_found;
}

template<typename KeyType, typename ValueType>
ValueType HashTable<KeyType, ValueType>::operator [](const KeyType& key) {
    ObtainedObject obj = get(key);
    if (obj.is_found) {
        return obj.value;
    } else {
        throw std::out_of_range("Key not found");
    }
}

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType> HashTable<KeyType, ValueType>::operator &&(HashTable<KeyType, ValueType>& other) {
    HashTable<KeyType, ValueType> result;

    for (HashNode& node : table) {
        if (node.status == OCCUPIED) {
            ObtainedObject obj = other.get(node.key);
            if (obj.is_found) {
                // !!!
                // кладем в результирующую коллекцию значение исходной хэш-таблицы
                result.insert(node.key, node.value);
            }
        }
    }

    return result;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
    table.clear();
    numElements = 0; 
    table.resize(BASE_TABLE_SIZE);
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::printTable() {
    std::cout << "--------" << std::endl;
    for (HashNode& node : table) {
        std::cout << node.key << ": " << node.value << std::endl; 
    }
    std::cout << "--------" << std::endl;
}

template<typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::getNumberOfItems() {
    return numElements;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::saveToFile(std::string filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error while opening file for writing" << std::endl;
        return;
    }

    for (const auto& node : table) {
        if (node.status == OCCUPIED) {
            outFile << node.key << " " << node.value << std::endl;
        }
    }

    outFile.close();
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::loadFromFile(std::string filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error while opening file for reading!" << std::endl;
        return;
    }

    KeyType key;
    ValueType value;
    while (inFile >> key >> value) {
        insert(key, value);
    }

    inFile.close();
}
#endif 
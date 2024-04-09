#pragma once
#include <iostream>
#include <vector>
#include<list>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class HashTable {
    struct Pair {
        K _key;
        V _value;
        Pair* next;
        bool filled;
        Pair(K key, V value) : _key(key), _value(value), next(nullptr) {
            bool filled = true;
        };
    };
    std::vector<Pair*> _data;
    size_t _size;
    size_t hash(K key) {
        return key % _size;
    };
public:
    HashTable(size_t size) {
        if (size == 0)
            throw std::invalid_argument("Size=0");
        _size = size;
        _data.resize(size);
    };
    HashTable(size_t size, const V& max, const V& min) {
        if (size == 0)
            throw std::invalid_argument("Size=0");
        _size = size;
        _data.resize(size);
        for (int i = 0; i < size; ++i) {
            V value = rand() % (max - min + 1) + min;
            _data[i] = new Pair(i, value);
        }
    };

    HashTable(size_t size, const V& max, const V& min, size_t el_quant) {
        if (size == 0)
            throw std::invalid_argument("Size=0");
        _size = size;
        _data.resize(size);
        for (int i = 0; i < el_quant; ++i) {
            K key=rand();
            V value = rand() % (max - min + 1) + min;
            insert(key, value);
        }
    };

    HashTable(const HashTable& other) {
        _size = other.get_size();
        _data.resize(_size);
        for (size_t i = 0; i < _size; ++i) {
            Pair* current = other._data[i];
            while (current != nullptr) {
                insert(current->_key, current->_value);
                current = current->next;
            }
        }
    }
    ~HashTable() {
        for (size_t i = 0; i < _size; i++) {
            Pair* current = _data[i];
            while (current) {
                Pair* tmp = current;
                current = current->next;
                delete tmp;
            }
        }
        _size = 0;
    }
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            for (size_t i = 0; i < _size; i++) {
                Pair* current = _data[i];
                while (current != nullptr) {
                    Pair* tmp = current;
                    current = current->next;
                    delete tmp;
                }
            }
            _size = other._size;  
            _data.resize(size);
            for (size_t i = 0; i < _size; ++i) {
                Pair* current = other._data[i];
                while (current != nullptr) {
                    insert(current->key, current->value);
                    current = current->next;
                }
                ++_size;
            }

        }
        return *this;
    };


    size_t get_size() const {
        return _size;
    }
    vector<Pair*> get_data() const {
        return _data;
    }


    void print() {
        for (int i = 0; i < _size; ++i) {
            Pair* current = _data[i];
            if (current)
                std::cout << current->_key << ":";
            while (current) {
                std::cout<< current->_value<<" ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    };
    void insert( const K& key,const V& value) {
        size_t index = hash(key);
        Pair* newPair = new Pair(key, value);
        newPair->next = _data[index];
        _data[index] = newPair;
        _data[index]->filled = true;
    }
    void insert_or_assign(const K& key, const V& value) {
        size_t index = hash(key);
        Pair* current = _data[index];
        while (current) {
            if (current->_key == key) {
                current->_value = value;
                return;
            }
            current = current->next;
        }
        insert(key, value);
    };
    bool erase(const K& key) {
        size_t index = hash(key);
        Pair* current = _data[index];
        Pair* prev = nullptr;
        if (current) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    _data[index] = current->next;
                }
                delete current;    
            prev = current;
            current = current->next;
            return true;
        }
        return false;
    }

    bool contains(const V& value) const {
        for (int i = 0; i < _size; ++i) {
            Pair* current = _data[i];
            while (current) {
                if (current->_value == value)
                    return true;
                current = current->next;
            }
        }
        return false;
    };
    V* search(const K& key) {
        size_t index = hash(key);
        Pair* tmp = _data[index];
        while (tmp) {
            if (tmp->_key != key)
                tmp = tmp->next;
            return &(tmp->_value);
        }
    };
    int count(const K& key) {
        size_t index = hash(key);
        int count = 0;
        Pair* tmp = _data[index];
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        return count;
    };
};

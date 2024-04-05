#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename K, typename V>
class HashTable {
public:
    struct Pair {
        K _key;
        V _value;
        Pair* next;

        Pair(K key, V value) {
            _key = key;
            _value = value;
            next = nullptr;
        }
    };

    Pair** _pair;
    size_t _size;

    int hashFunction(K key) {
        return key % _size;
    }

public:
    HashTable(size_t size) {
        _size = size;
        _pair = new Pair * [size];
        for (size_t i = 0; i < size; ++i) {
            _pair[i] = nullptr;
        }
    }

    HashTable(size_t size, V min, V max) {
        srand(time(0));
        _size = size;
        _pair = new Pair * [size];
        for (size_t i = 0; i < size; ++i) {
            _pair[i] = new Pair(i, rand() % (max - min + 1) + min);
        }
    }

    HashTable(const HashTable& other) {
        _size = other._size;
        _pair = new Pair * [other._size];

        for (size_t i = 0; i < _size; ++i) {
            Pair* current = other._pair[i];
            Pair* newCurrent = nullptr;

            while (current != nullptr) {
                Pair* newPair = new Pair(current->_key, current->_value);
                if (newCurrent == nullptr) {
                    _pair[i] = newPair;
                    newCurrent = newPair;
                }
                else {
                    newCurrent->next = newPair;
                    newCurrent = newPair;
                }
                current = current->next;
            }
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < _size; ++i) {
            Pair* current = _pair[i];
            while (current != nullptr) {
                Pair* tmp = current;
                current = current->next;
                delete tmp;
            }
        }
        delete[] _pair;
    }

    HashTable& operator=(const HashTable& other);

    size_t get_size() const {
        return _size;
    }

    Pair** get_pair() const {
        return _pair;
    }

    void print();
    void insert(K key, V value);
    void insert_or_assign(K key, V value);
    bool erase(K key);

    bool contains(V value) const;
    V* search(K key) const;
    int count(K key) const;
};

int main() {
    HashTable<int, int> my_table= HashTable<int, int>(10, 20, 50);
    HashTable<int, int> other(my_table);
}
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "BSTree.h"
#include "/home/aandgom44/Escritorio/UNI/PRA/PR3/part1/Dict.h"
#include "/home/aandgom44/Escritorio/UNI/PRA/PR3/part1/TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>;
        }

        ~BSTreeDict(){
            delete tree;
        }

        friend std::ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
            out << *bs.tree; 
            return out;
        }

        V operator[](string key){
            return search(key);
        }

        void insert(string key, V value)override{
            TableEntry<V> *nueva_entrada = new TableEntry<V>(key, value);
            tree->insert(*nueva_entrada);
            delete nueva_entrada;
        }

        V search(string key)override{
            V aux = (tree->search(key)).value;
            return aux;
        }

        V remove(string key)override{
            V aux = search(key);
            tree->remove(key);
            return aux;
        }

        int entries()override{
            return tree->size();
        }
    
    private:
        BSTree<TableEntry<V>>* tree;

};

#endif

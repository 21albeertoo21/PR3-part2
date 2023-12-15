#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree{
	private:
		int nelem; //elementos almacenados en el árbol
		BSNode<T> *root; //Nodo raiz del árbol
		
		BSNode<T>* search(BSNode<T> *n, T e) const{
			if(n == nullptr)//árbol vacío
				throw runtime_error("Arbol vacío\n");
			else if(n->elem < e)
				return search(n->right, e);
			else if(n->elem > e)
				return search(n->left, e);
			else
				return n;
		}
		
		BSNode<T>* insert(BSNode<T> *n, T e){
			if(n == nullptr)
				return new BSNode<T>(e, nullptr, nullptr); //DUDA
			else if(n->elem == e)
				throw runtime_error("Elemento duplicado\n");
			else if(n->elem < e)
				n->right = insert(n->right, e);
			else 
				n->left = insert(n->left, e);
			
			return n;
		}
		
		void print_inorden(ostream &out, BSNode<T> *n) const{
			if(n != nullptr){
				print_inorden(out, n->left);
				out << n->elem << endl;
				print_inorden(out, n->right);
			}
		}
	
	public:
		BSTree();
		
		int size()const {
			return nelem;
		}
		
		T search(T e) const {
			return search(root, e);
		}
		
		void insert(T e){
			root = insert(root, e);
		}
		
		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
		
			out << bst.print_inorden(out, bst->root);
			return out;	
		}
};

#endif

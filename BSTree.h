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
			BSNode<T> *result;
			if(n == nullptr)
				throw runtime_error("Value not found in tree\n");
			else if(n->elem == e)
				result = n;
			else if(n->elem > e)
				result = search(n->left, e);
			else if(n->elem < e)
				result = search(n->right, e);
			
			return result;
		}
		
		BSNode<T>* insert(BSNode<T> *n, T e){
			if(n == nullptr)
				return new BSNode<T>(e);
			
			if(n->elem == e)
				throw runtime_error("Duplicated value\n");
			else if(n->elem > e)
				n->left = insert(n->left, e);
			else if(n->elem < e)
				n->right = insert(n->right, e);
			
			return n;
		}
		
		BSNode<T>* remove(BSNode<T> *n, T e){
			if(n == nullptr)
				throw runtime_error("Value not found in tree\n");
			else if(n->elem > e)
				n->left = remove(n->left, e);
			else if(n->elem < e)
				n->right = remove(n->right, e);
			else{
				if(n->right != nullptr and n->left != nullptr){
					n->elem = max(n->left);
					n->left = remove_max(n->left);
				}
				else
					n = (n->left != nullptr)? n->left: n->right;
			}
			
			return n;
		
		}
		
		T max(BSNode<T>* n) const{
			if(n == nullptr)
				throw runtime_error("Tree empty\n");
			else if(n->right != nullptr)
				return max(n->right);
			else
				return n->elem;
				
		}
		
		BSNode<T>* remove_max(BSNode<T> *n){
			if(n == nullptr)
				throw runtime_error("Tree empty\n");
			else if(n->right != nullptr)
				n->right = remove_max(n->right);
			else
				return n->left;
		
		}
		
		void print_inorden(ostream &out, BSNode<T> *n) const{
			if(n == nullptr) return;
			
			print_inorden(out, n->left);
			out << n->elem << " ";
			print_inorden(out, n->right);
		}
		
		void delete_cascade(BSNode<T>* n){
			if(n != nullptr){
				delete_cascade(n->right);
				delete_cascade(n->left);
				delete n;
			}
		
		}
	
	public:
		BSTree(){
		};
		
		~BSTree(){
			BSNode<T> *aux = root;
			delete_cascade(aux);
		}
		
		int size()const {
			return nelem;
		}
		
		void insert(T e){
			BSNode<T> *aux = root;
			aux = insert(aux, e);
			nelem++;
		}
		
		T search(T e) const {
			BSNode<T> *aux = root;
			return search(aux, e)->elem;
		}
		
		T operator[](T e) const{
			BSNode<T> *aux = root;
			aux = search(aux, e);
			T dato = aux->elem;
			return dato;
		}
		
		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
			BSNode<T> *aux = bst.root;
			bst.print_inorden(out, aux);
			out << endl;
			
			return out;
		}
		
		void remove(T e){
			BSNode<T> *aux = root;
			remove(aux, e);	
			nelem--;
		}
};

#endif

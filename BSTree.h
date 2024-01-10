#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree{
	private:
		int nelem; //elementos almacenados en el árbol
		BSNode<T> *root; //Nodo raiz del árbol
		
		BSNode<T>* search(BSNode<T> *n, T e) const{
			if(n == nullptr)
				throw runtime_error("Value not found in tree\n");
			else if(n->elem == e)
				return n;
			else if(n->elem > e)
				n = search(n->left, e);
			else if(n->elem < e)
				n = search(n->right, e);
			
			return n;
		}
		
		BSNode<T>* insert(BSNode<T> *n, T e){
			if(n == nullptr)
				return new BSNode<T>(e);
			else if(n->elem == e)
				throw runtime_error("Duplicated value\n");
			else if(n->elem > e)
				n->left = insert(n->left, e);
			else
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
				delete_cascade(n->left);
				delete_cascade(n->right);
				delete n;
			}
		}
	
	public:
		BSTree(){
			nelem = 0;
			root = nullptr;
		};
		
		~BSTree(){
			delete_cascade(root);
		}
		
		int size()const {
			return nelem;
		}
		
		void insert(T e){
			root = insert(root, e);
			nelem++;
		}
		
		T search(T e) const {
			return search(root, e)->elem;
		}
		
		T operator[](T e) const{
			return search(e);
		}
		
		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
			bst.print_inorden(out, bst.root);
			return out;
		}
		
		void remove(T e){
			remove(root, e);
			nelem--;
		}
};

#endif

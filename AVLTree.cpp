#include "AVLTree.h"
#include <stdio.h>

Node* AVLTree::getRoot(){ 
	return root;
}

void AVLTree::visit(Node* node){
	if(node == 0){
		return;
	}

    printf(" [%d] ", node->info);
}

int AVLTree::maior(int a, int b){ 
    return a > b ? a : b; 
}

void AVLTree::height(){
    printf("\n A altura da arvore eh: [%d] \n", height(root));
}

int AVLTree::height(Node* node){
    if(node == 0){
        return 0;
    }

    return 1 + maior(height(node->left), height(node->right)); 
}


void AVLTree::delete_Tree(Node* node){ 
    
    if(node == 0){
        return;
    }

    delete_Tree(node->left); 
    delete_Tree(node->right); 
    delete node;
}

void AVLTree::destruct(){
    delete_Tree(root); 
    root = 0;
    numberOfNodes = 0;
}

bool AVLTree::add(int info){
	bool h = false;
	return add(info, root, h);
}

bool AVLTree::add(int info, Node*& ptr, bool& h){

	if(ptr == 0){
		ptr = new Node(info);
		numberOfNodes++;
		h = true;
		return true;
	}

	int cmp = ptr->info - info;
	if(cmp == 0){
		return false;
	}
	
	bool ret;
	if(cmp < 0){

		ret = add(info, ptr->right, h);
		if(h){
			switch(ptr->balance){
				case -1: 
					ptr->balance = 0;
					h = false;
				break;
				case 0: 
					ptr->balance = 1;
				break;
				case 1: 
					rotationLeft(ptr);
					h = false;
			}
		}

	}else{

		ret = add(info, ptr->left, h);
		if(h){
			switch(ptr->balance){
				case 1: ptr->balance = 0;
				h = false;
				break;
			case 0: 
				ptr->balance = -1;
				break;
			case -1: 
				rotationRight(ptr);
				h = false;
			}
		}
	}
		
	return ret;
}

void AVLTree::rotationLeft(Node*& node){
	
	Node* ptr = node->right;
	/* R Esquerda */
	if(ptr->balance == 1){
		node->right = ptr->left;
		ptr->left = node;
		node->balance = 0;
		node = ptr;

	}else{  /* R D Esquerda */
		Node* ptv = ptr->left;
		ptr->left = ptv->right;
		ptv->right = ptr;
		node->right = ptv->left;
		ptv->left = node;

		if(ptv->balance == 1){
			node->balance = -1;
		}else{
			node->balance = 0;
		}

		if(ptv->balance == -1){
			ptr->balance = 1;
		}else{
			ptr->balance = 0;
		}

		node = ptv;
	}

	node->balance = 0;
}

void AVLTree::rotationRight(Node*& node){

	Node* ptr = node->left;
	/* R Direita */
	if(ptr->balance == -1) {
		node->left = ptr->right;
		ptr->right = node;
		node->balance = 0;
		node = ptr;

	}else{ /* R D Direita */

		Node* ptv = ptr->right;
		ptr->right = ptv->left;
		ptv->left = ptr;
		node->left = ptv->right;
		ptv->right = node;

		if(ptv->balance == -1){
			node->balance = 1;
		}else{
			node->balance = 0;
		}

		if(ptv->balance == 1){
			ptr->balance = -1;
		}else{
			ptr->balance = 0;
		}

		node = ptv;
	}

	node->balance = 0;
}

bool AVLTree::remove(int info){
	bool h = false;
	return remove(info, root, h);
}

bool AVLTree::remove(int info, Node*& ptr, bool& h){

	if(ptr == 0){
		return false;
	}

	int cmp = ptr->info - info;
	if(cmp == 0){

		Node* aux = ptr;

		if(ptr->left == 0 || ptr->right == 0){
			ptr = aux->right != 0 ? aux->right : aux->left;
			h = true;
			numberOfNodes--;
			delete aux;
	
		}else{
			aux = ptr->left;

			while(aux->right != 0){
				aux = aux->right;
			}

			ptr->info = aux->info;
			remove(ptr->info, ptr->left, h);

			if(h){
				switch(ptr->balance){
					case -1: 
						ptr->balance = 0;
					break;
					case 0: 
						ptr->balance = 1;
						h = false;
					break;
					case 1: 
						regularLeft(ptr, h);
				}
			}
		}
		return true;
	}

	bool ret;
	if(cmp < 0){
		ret = remove(info, ptr->right, h);

		if(h){
			switch(ptr->balance) {
				case 1: 
					ptr->balance = 0;
				break;
				case 0: 
					ptr->balance = -1;
					h = false;
				break;
				case -1: 
					regularRight(ptr, h);
			}
		}

	}else{
		ret = remove(info, ptr->left, h);

			if(h){
				switch(ptr->balance){
					case -1: 
						ptr->balance = 0;
					break;
					case 0: 
						ptr->balance = 1;
						h = false;
					break;
					case 1: 
						regularLeft(ptr, h);
				}
			}
	}
	
	return ret;
}

void AVLTree::regularLeft(Node*& ptr, bool& h){

	Node* ptrz = ptr->right;
	/* R Esquerda */
	if(ptrz->balance >= 0){
		ptr->right = ptrz->left;
		ptrz->left = ptr;

		if(ptrz->balance == 0){
			ptr->balance = 1;
			ptrz->balance = -1;
			h = false;

		}else {
			ptr->balance = 0;
			ptrz->balance = 0;
		}
		ptr = ptrz;

	}else{ /* R D Esquerda */
		Node* ptry = ptrz->left;
		ptrz->left = ptry->right;
		ptry->right = ptrz;
		ptr->right = ptry->left;
		ptry->left = ptr;

		if(ptry->balance == 1){
			ptr->balance = -1;
		}else{
			ptr->balance = 0;
		}

		if(ptry->balance == -1) {
			ptrz->balance = 1;
		}else{
			ptrz->balance = 0;
		}

		ptr = ptry;
		ptr->balance = 0;
	}
}

void AVLTree::regularRight(Node*& ptr, bool& h){

	Node* ptrz = ptr->left;
	/* R Direita */
	if(ptrz->balance <= 0){
		ptr->left = ptrz->right;
		ptrz->right = ptr;

		if(ptrz->balance == 0){
			ptr->balance = -1;
			ptrz->balance = 1;
			h = false;
		}else{
			ptr->balance = 0;
			ptrz->balance = 0;
		}
		ptr = ptrz;

	}else{ /* R D Direita */
		Node* ptry = ptrz->right;
		ptrz->right = ptry->left;
		ptry->left = ptrz;
		ptr->left = ptry->right;
		ptry->right = ptr;

		if(ptry->balance == -1){
			ptr->balance = 1;
		}else {
			ptr->balance = 0;
		}

		if(ptry->balance == 1){
			ptrz->balance = -1;
		}else{
			ptrz->balance = 0;
		}

		ptr = ptry;
		ptr->balance = 0;
	}
}
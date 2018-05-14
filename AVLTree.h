#ifndef __AVLTree_h
#define __AVLTree_h

class Node{

public:

    int info;
    int balance;
    Node* left;
    Node* right;

    Node(int info){
        this->info = info;
        left = right = 0;
        balance = 0;
    }
};

class AVLTree{


private:
    
    Node* root;
    int numberOfNodes;

    bool add(int, Node*&, bool&);
	bool remove(int, Node*&, bool&);
	void rotationLeft(Node*& );
	void rotationRight(Node*& );
	void regularLeft(Node*&, bool&);
	void regularRight(Node*&, bool&);
	void deleteTree(Node* );

	void destruct(); 
    void delete_Tree(Node*); 

public:

	AVLTree(){
		root = 0;
		numberOfNodes = 0;
	}

	~AVLTree(){
		destruct();
	}

	bool add(int );
	bool remove(int );
	bool contains(int );
	void visit(Node* );
	Node *getRoot();
	int maior(int , int );
	void height();
	int height(Node* );

	int size() const{
		return numberOfNodes;
	}

	bool isEmpty() const{
		return numberOfNodes == 0;
	}
	
};

#endif
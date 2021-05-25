#ifndef CACHE_H
#define CACHE_H

#include "main.h"
class Node 
{ 
    public:
	int key; // chinh la addr
	Elem* ele; 
    Node *left; 
    Node *right; 
    int height; 
}; 

class Cache {
		Elem** arr;
		int p;  // 
		Node* avlRoot;// avl tree
	public:
		Cache(int s) {
			arr = new Elem*[s]; 
			p = 0;
			avlRoot = NULL;
		}
		~Cache() {
			delete[] arr;
		}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
};

//------------------------------------------------------------------------------------------------------

  

int max(int a, int b); 
  

int height(Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

	Node* newNode(Elem *elem) 
	{ 
		Node* node = new Node();
		node->key = elem->addr; 
		node->ele = elem;
		node->left = NULL; 
		node->right = NULL; 
		node->height = 1; 
						
		return(node); 
	} 
	

	Node *rightRotate(Node *y) 
	{ 
		Node *x = y->left; 
		Node *T2 = x->right; 
	

		x->right = y; 
		y->left = T2; 
	
		// Update heights 
		y->height = max(height(y->left), 
						height(y->right)) + 1; 
		x->height = max(height(x->left), 
						height(x->right)) + 1; 
	
		return x; 
	} 
	

	Node *leftRotate(Node *x) 
	{ 
		Node *y = x->right; 
		Node *T2 = y->left; 
	

		y->left = x; 
		x->right = T2; 
	
		// Update heights 
		x->height = max(height(x->left), 
						height(x->right)) + 1; 
		y->height = max(height(y->left), 
						height(y->right)) + 1; 
	
	
		return y; 
	} 
	
	// Get Balance 
	int getBalance(Node *N) 
	{ 
		if (N == NULL) 
			return 0; 
		return height(N->left) - 
			height(N->right); 
	} 
	
	Node* insert(Node* node, Elem* ele) 
	{ 
		
		if (node == NULL) 
			return(newNode(ele)); 
		int key = ele->addr;
		if (key < node->key) 
			node->left = insert(node->left, ele); 
		else if (key >= node->key) //neu bang day sang phai
			node->right = insert(node->right, ele); 
		else 
			return node; 
	
		node->height = 1 + max(height(node->left), 
							height(node->right)); 
	

		int balance = getBalance(node); 
	
		// Left Left Case 
		if (balance > 1 && key < node->left->key) 
			return rightRotate(node); 
	
		// Right Right Case 
		if (balance < -1 && key > node->right->key) 
			return leftRotate(node); 
	
		// Left Right Case 
		if (balance > 1 && key > node->left->key) 
		{ 
			node->left = leftRotate(node->left); 
			return rightRotate(node); 
		} 
	
		// Right Left Case 
		if (balance < -1 && key < node->right->key) 
		{ 
			node->right = rightRotate(node->right); 
			return leftRotate(node); 
		} 
	
		return node; 
	} 
	

	Node * minValueNode(Node* node) 
	{ 
		Node* current = node; 
	
		while (current->left != NULL) 
			current = current->left; 
	
		return current; 
	} 
	

	Node* deleteNode(Node* root, int key) 
	{ 
		
		if (root == NULL) 
			return root; 
	
		if ( key < root->key ) 
			root->left = deleteNode(root->left, key); 
	
		else if( key > root->key ) 
			root->right = deleteNode(root->right, key); 
	
		else
		{ 
			//co 1 hoac ko co con
			if( (root->left == NULL) ||
				(root->right == NULL) ) 
			{ 
				Node *temp = root->left ? 
							root->left : 
							root->right; 
	
				// khong co con 
				if (temp == NULL) 
				{ 
					temp = root; 
					root = NULL; 
				} 
				else // co 1 con
				*root = *temp; 
						
				delete temp;
			} 
			else
			{ //khi co du 2 con
				Node* temp = minValueNode(root->right); 
	
				root->key = temp->key; 
	
				root->right = deleteNode(root->right, 
										temp->key); 
			} 
		} 
	// can bang lai
		if (root == NULL) 
		return root; 
	

		root->height = 1 + max(height(root->left), 
							height(root->right)); 
	

		int balance = getBalance(root); 
	
	
		// Left Left Case 
		if (balance > 1 && 
			getBalance(root->left) >= 0) 
			return rightRotate(root); 
	
		// Left Right Case 
		if (balance > 1 && 
			getBalance(root->left) < 0) 
		{ 
			root->left = leftRotate(root->left); 
			return rightRotate(root); 
		} 
	
		// Right Right Case 
		if (balance < -1 && 
			getBalance(root->right) <= 0) 
			return leftRotate(root); 
	
		// Right Left Case 
		if (balance < -1 && 
			getBalance(root->right) > 0) 
		{ 
			root->right = rightRotate(root->right); 
			return leftRotate(root); 
		} 
	
		return root; 
	} 
	
	Node* search(Node* root, int key)
	{
		// Base Cases
		if (root == NULL || root->key == key)
		return root;
		
		if (root->key < key)
		return search(root->right, key);
	
		return search(root->left, key);
	}

	void preOrderAVL(Node* root)
	{
		if(root != NULL)
		{
			root->ele->print();
			preOrderAVL(root->left);
			preOrderAVL(root->right);
		}
	}

	void inOrderAVL(Node* root)
	{
		if(root != NULL)
		{
			inOrderAVL(root->left);
			root->ele->print();
			inOrderAVL(root->right);
		}
	}

//------------------------------------------------------------------------------------------------------------


#endif
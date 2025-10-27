#include <iostream>
using namespace std;

struct Node{
	Node*left, *right;
	int data;
	Node(int d){
		data = d;
		left = right = nullptr;
	}
};

class bst{
	Node* root;
	
	public:
		bst(){
			root = nullptr;
		}
	private:
		Node* insertNode(Node* node, int val){
			if(!node){
				return new Node(val);
			}
			if(val<node->data){
				node->left = insertNode(node->left, val);
			}
			else if(val>node->data){
				node->right = insertNode(node->right, val);
			}
			return node;	
		}
	public:
		void insert(int val){
			root = insertNode(root, val);
		}
	private:
		Node* findMin(Node* node){
			while(node && node->left) node = node->left;
			return node;
		}
		
		Node* delete_Node(Node* node, int val){
			if(!node) return node;
			else if(node->data < val){
				node->left = delete_Node(node->left, val);
			}
			else if(node->data > val){
				node->right = delete_Node(node->right, val);
			}
			else{
				//node->data == val
				if (node->left == nullptr && node->right == nullptr){
					//leaf
					delete node;
					return nullptr;
				}
				if(node->left == nullptr){
					Node* temp = node->right;
					delete node;
					return temp;
				}
				if(node->right == nullptr){
					Node* temp = node->left;
					delete node;
					return temp;
				}
				//left and right are children
				Node*temp = findMin(node->right); //successor
				node->data = temp->data; //make current node's the successor's data
				node->right = delete_Node(node->right, temp->data); //delete the successor
			}
			return node;
		}
	public:
		void deleteNode(int val){
			root = delete_Node(root, val);
		}
	private:
		void preorderTransversal(Node*node){
			//root->left->right
			if(!node) return;
			cout<<node->data<<" ";
			preorderTransversal(node->left);
			preorderTransversal(node->right);
		}
		void inOrderTransversl(Node*node){
			//left->root->right
			if(!node) return;
			preorderTransversal(node->left);
			cout<<node->data<<" ";
			preorderTransversal(node->right);
		}
		void postOrderTransversal(Node*node){
			//left->right->root
			if(!node) return;
			preorderTransversal(node->left);
			preorderTransversal(node->right);
			cout<<node->data<<" ";
		}
	public:
		void preorder(){
			preorderTransversal(root);
			cout<<endl;
		}
		void inOrder(){
			inOrderTransversl(root);
			cout<<endl;
		}
		void postOrder(){
			postOrderTransversal(root);
			cout<<endl;
		}
	private:
		Node* SearchNode(Node* node, int val){
			if(node==nullptr || node->data == val) return node;
			if(val<node->data) return SearchNode(node->left, val);
			return SearchNode(node->right, val);
		}
	public:
		Node* search(int val){
			return SearchNode(root, val);
		}
};

int main(){
	
	return 0;
}
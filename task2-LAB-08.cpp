#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Combatant {
public:
    string name;
    int health;
    int attack;

    Combatant(string n = "", int h = 0, int a = 0)
        : name(n), health(h), attack(a) {}
};

class Node {
public:
    Combatant c;
    Node* left;
    Node* right;

    Node(Combatant combatant) {
        c = combatant;
        left = right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() { root = NULL; }

    Node* insert(Node* root, Combatant c) {
        if (root == NULL)
            return new Node(c);
        if (c.name < root->c.name)
            root->left = insert(root->left, c);
        else
            root->right = insert(root->right, c);
        return root;
    }

    void insert(Combatant c) {
        root = insert(root, c);
    }

    Node* findMin(Node* node) {
        while (node && node->left != NULL)
            node = node->left;
        return node;
    }

    Node* remove(Node* root, string name) {
        if (root == NULL) return root;

        if (name < root->c.name)
            root->left = remove(root->left, name);
        else if (name > root->c.name)
            root->right = remove(root->right, name);
        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = findMin(root->right);
            root->c = temp->c;
            root->right = remove(root->right, temp->c.name);
        }
        return root;
    }

    void remove(string name) {
        root = remove(root, name);
    }

    bool isEmpty() {
        return root ==nullptr;
    }

    Node* getFrontline() {
		return findMin(root);
    }
	
	private:
    void display_node(Node* node) {
    	//left root right
        if(!node) return;
		display_node(node->left);
		cout<<"name: "<<node->c.name<<"  health: "<<node->c.health<<"  attack: "<<node->c.attack<<endl;
		display_node(node->right);
    }
    public:
	
    void displayTeam() {
    	if(isEmpty()) cout<<"no Combatants left"<<endl;
        display_node(root);
        
    }
};

class BattleQuest {
private:
    BST playerTeam;
    BST enemyTeam;
    int roundNumber;

public:
    BattleQuest() {
        srand(time(0));
        initializeTeams();
        roundNumber=0;
    }

    void initializeTeams() {
    	string name;
    	for(int i=0;i<5;i++){
    		name = "hero "+ to_string(i+1);
    		Combatant C(name, 100, 25);
    		playerTeam.insert(C);
		}
		
		for(int i=0;i<5;i++){
    		name = "enemy "+to_string(i+1);
    		Combatant C(name, 100, 25);
    		enemyTeam.insert(C);
		}
    }

    void displayTeams() {
       cout<<"PLAYER TEAM: "<<endl;
       playerTeam.displayTeam();
       cout<<"ENEMY TEAM: "<<endl;
       enemyTeam.displayTeam();
    }

    void attack(Node* attacker, Node* defender, BST& defenderTeam) {
    	int randomVal = (rand()%4)+1;
    	int damage = attacker->c.attack+randomVal;
    	defender->c.health -= damage;
    	if(defender->c.health<=0) defenderTeam.remove(defender->c.name);
    }

    void start_battle() {
    	Node* attacker, *defender;
        while(!playerTeam.isEmpty() && !enemyTeam.isEmpty()){
        	roundNumber++;
        	cout<<endl<<"ROUND "<<roundNumber;
        	cout<<endl<<"Player team's turn"<<endl;
        	attacker = playerTeam.getFrontline();
        	defender = enemyTeam.getFrontline();
        	attack(attacker, defender, enemyTeam);
        	displayTeams();
        	
        	if(enemyTeam.isEmpty()) break;
        	cout<<"Enemy team's turn"<<endl;
        	attacker = enemyTeam.getFrontline();
        	defender = playerTeam.getFrontline();
        	attack(attacker, defender, playerTeam);
        	displayTeams(); 
		}
		
		if(!playerTeam.isEmpty()) cout<<"PLAYER WINS";
		else cout<<"ENENY WINS";
        
    }
};


int main() {
    BattleQuest game;
    game.start_battle(); 
    return 0;
}
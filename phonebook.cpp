#include <iostream>
#include<unordered_map>
using namespace std;


class Node{
public:
	char data;
	bool terminal;
	unordered_map<char,Node*>children;

	Node(char data){
		this->data = data;
		this->terminal = false;
	}
};

class Trie{
public:
	Node*root;
	int count;

	Trie(){
		this->root = new Node('\0');
		this->count = 0;
	}
// Insert a Contact into the Trie 
	void Addword(string str){
		Node*temp = root;

		for(int i =0; i<str.size(); i++){
			char ch = str[i];
			if(temp->children.count(ch)){
				temp = temp->children[ch];
			}
			else{
				Node*n = new Node(ch);
				temp->children[ch] = n;
				temp = n;
			}
		}
		temp->terminal = true;

	}

	 // This function simply displays all dictionary words 
     // going through current node. String 'prefix' 
     // represents string corresponding to the path from 
     // root to curNode. 
    void displayContactsUtil(Node *curNode, string prefix) 
    { 
       // Check if the string 'prefix' ends at this Node 
       // If yes then display the string found so far 
        if (curNode->terminal) 
            cout << prefix << endl; 
  
       // Find all the adjacent Nodes to the current 
       // Node and then call the function recursively 
       // This is similar to performing DFS on a graph 
        for (char i = 'a'; i <= 'z'; i++) 
        { 
            Node *nextNode = curNode->children[i]; 
            if (nextNode != NULL) 
                displayContactsUtil(nextNode, prefix + (char)i); 
        } 
    } 
  
    // Display suggestions after every character enter by 
    // the user for a given query string 'str' 
    void Autocomplete(string str) 
    { 
        Node *prevNode = root; 
        string prefix = ""; 
        int len = str.length(); 
  
        // Display the contact List for string formed 
        // after entering every character 
        int i; 
        for (i=0; i<len; i++) 
        { 
             
            prefix += (char)str[i]; 
            char lastChar = prefix[i]; 
            Node *curNode = prevNode->children[lastChar]; 
  
            // If nothing found, then break the loop as 
            // no more prefixes are going to be present. 
            if (curNode == NULL) 
            { 
                cout << "No Results Found for "<< prefix <<endl; 
                i++; 
                break; 
            } 
  
            // If present in trie then display all 
            // the contacts with given prefix. 
            cout << "Suggestions based on "<< prefix <<endl; 
            displayContactsUtil(curNode, prefix); 
            prevNode = curNode; 
        } 
  
    

        // Once search fails for a prefix, we print 
        // "Not Results Found" for all remaining 
        // characters of current query string "str". 
        for (; i<len; i++) 
        { 
            prefix += (char)str[i]; 
            cout << "No Results Found for "<< prefix << endl; 
        } 
    } 

    // search function
    bool Search(string str){
		Node*temp = root;

		for(int i =0; i<str.size(); i++){
			char ch = str[i];
			if(temp->children.count(ch)){
				temp = temp->children[ch];
			}
			else{
				return false;
			}
		}
		return temp->terminal;

	}

};


int main(){

	Trie t;
	int n;
	cin>>n;// Enter number of contacts you want to insert in your phonebook
	while(n--){
		string str;
		cin>>str;// Enter contacts.
		t.Addword(str);
	} 

	int q;
	cin>>q;// No of queries.
	while(q--){
		string str;
		cin>>str;// Enter contact that you want to search in your phonebook.
		t.Autocomplete(str); // Autocomplete.. 
		if(t.Search(str)){   // Searching..
		    cout<<"Present in Contact List!!!"<<endl;
		}
		else{
		    cout<<"Absent!!!"<<endl;
		}
    }

	return 0;
}









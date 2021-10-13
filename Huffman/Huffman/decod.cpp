//NU MERGE

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <string>
// probleme la testul 3, merge 5
using namespace std;

struct node {
	char data;
	int freq;
	node* left, * right;
	node(char data, int freq) : data{ data }, freq{ freq }{
		left = right = NULL;
	}
};

struct cmp {
	bool operator()(node* left, node* right) {
		if (left->freq > right->freq)
			return true;
		if (left->freq == right->freq)
			return left->data > right->data;
		return false;
	}
};

node* HuffmanCodeRoot(const map<char, int>&, priority_queue<node*, vector<node*>, cmp>&);
char decrypt(node*, string::iterator&);

int main(int argc, char** argv) {
	ifstream f(argv[1]);
	int n;
	f >> n;
	f.get();
	map<char, int> freq;
	for (int i = 0; i < n; i++) {
		string temp;
		getline(f, temp);
		unsigned int length = temp.size();
		freq[temp[0]] = stoi(temp.substr(2));
	}
	string encryptedmesssage;
	f >> encryptedmesssage;
	f.close();
	priority_queue<node*, vector<node*>, cmp> pq;
	node* root = HuffmanCodeRoot(freq, pq);
	ofstream g(argv[2]);
	auto it = encryptedmesssage.begin();
	while(it != encryptedmesssage.end())
		g << decrypt(root, it);
	g.close();
	
	return 0;
}

node* HuffmanCodeRoot(const map<char, int>& freq, priority_queue<node*, vector<node*>, cmp>& pq) {
	for (auto it : freq)
		pq.push(new node(it.first, it.second));
	while (pq.size() != 1) {
		node* left, * right, * newNode;
		left = pq.top();
		pq.pop();
		right = pq.top();
		pq.pop();
		newNode = new node('$', left->freq + right->freq);
		newNode->left = left;
		newNode->right = right;
		pq.push(newNode);
	}
	return pq.top();
}

char decrypt(node* root, string::iterator& it) {
	if (!root)
		return '$';
	if (root->data != '$') 
		return root->data;
	if (*it == '0')
		return decrypt(root->left, ++it);
	else
		return decrypt(root->right, ++it);
}

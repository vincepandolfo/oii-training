#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int contaOp = 0;

struct trie
{
    bool ordina;
    bool print;
    char c;
    vector<trie> sons;
    int mWord;
};

bool operator<(const trie &a, const trie&b)
{
    return a.mWord < b.mWord;
}

void addWord(string w, trie &node)
{
    if(w.empty())
    {
        node.print = true;
        return;
    }

    bool found = false;
    int i = 0;
    for(i = 0; i < (int)node.sons.size() && !found; i++)
		if(node.sons[i].c == w[0]) found = true;

    if(!found)
    {
        trie newNode;
        newNode.c = w[0];
        newNode.mWord = 0;
        newNode.print = false;
		newNode.ordina = false;
        node.sons.push_back(newNode);
    }
    else i--;

    node.sons[i].mWord = max(node.sons[i].mWord, (int)w.length());

    addWord(w.substr(1, string::npos), node.sons[i]);
}

void printSol(int &N, trie &nodo, ofstream &out)
{
    if(nodo.print)
    {
		N--;
		out << "P\n";
		contaOp++;
    }

    if(nodo.sons.empty())
		return;

    if(nodo.ordina) { nth_element(nodo.sons.begin(), nodo.sons.end()-1, nodo.sons.end()); nodo.sons.back().ordina = true; }

    int i = 0;

    while(i < nodo.sons.size())
    {
        out << nodo.sons[i].c << "\n";
        contaOp++;
        printSol(N, nodo.sons[i], out);
        if(N > 0) { out << "-\n"; contaOp++; }
        i++;
    }
}


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    string w;
    trie triet;
    triet.c = '0';
    triet.print = false;
	triet.ordina = true;
    in >> N;

    for(int i = 0; i < N; i++)
    {
        in >> w;
        addWord(w, triet);
    }

    out << "                                             \n";
    printSol(N, triet, out);

    out.seekp(ios_base::beg);

    out << contaOp;



    return 0;
}



#include<bits/stdc++.h>
using namespace std;

/*
 * 
const int N = 1e6;
const int mod = 1e9+7;
int trie[N][27], node = 0;
int createNode(char c, int k)
{
	if( c == '\0' ){
		trie[k][26] = 0;
		return 0;
	}
	else{
	if( trie[k][c - 'a'] == -1 )
		node++, trie[k][c- 'a'] = node;
	}
	return trie[k][c-'a'];
}

void dfs(int src, int &order){
	if ( trie[src][26] == 0 )
		trie[src][26] = order++;
	for( int i = 0; i < 26; ++i )
	{
		if( trie[src][i] != -1 )
			dfs(trie[src][i], order);
	}
}


bool search( string s ){
	
	int k = 0;
	for( char c: s ){
		k = trie[k][c-'a'];
		if( k == -1 ) return 0;
	}
	return trie[k][26] == 0;
}

bool startsWithPrefix(string s){
	
	int k = 0;
	for( char c: s ){
		k = trie[k][c-'a'];
		if( k == -1 ) return false; 
	}
	return true;
}


* 
*/



struct trie{
    trie* child[26] = {};
    bool isWord = false;
    int order = -1;
    trie* makeOrGetNode( char c )
    {
        if( child[c-'a'] == nullptr )
            child[c-'a'] = new trie();
        return child[c-'a'];
    }
    
    
};

class Trie {
public:
    /** Initialize your data structure here. */
    trie *root = nullptr;
    Trie() {
        root = new trie();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        trie *cur = root;
        for( char c: word )
            cur = cur->makeOrGetNode(c);
        cur->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        trie* cur = root;
        for( char c: word ){
            cur = cur->child[c-'a'];
            if( cur == nullptr ) return false;
        }
        return cur->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with 
     * the given prefix. 
     **/
    bool startsWith(string prefix) {
        trie* cur = root;
        for( char c: prefix )
        {
            cur = cur->child[c-'a'];
            if( cur == nullptr ) return false;
        }
        return true;
    }
    //Permuatauion sequence of orginal indices to get sorted 
    //order
};


int main(){

}

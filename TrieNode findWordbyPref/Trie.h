#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode*, string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
void has_prefixhidden(TrieNode* node, int& cnt_ends);
void findMinPrefixes(TrieNode*, char[], int, string&);
TrieNode* searchNodePref(struct TrieNode* root, string key);
void findWordbyPref(TrieNode* root, string& res, string& pref);


#endif

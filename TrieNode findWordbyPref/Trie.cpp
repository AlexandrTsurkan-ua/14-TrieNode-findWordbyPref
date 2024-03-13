#include <iostream>

#include "Trie.h"


using namespace std;

// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        node = node->children[index];
    }

    // �������� ��������� ���� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}



// ���������� true ���� ���� ���� � ������, ����� false 
bool search(struct TrieNode* root, string key)
{
    int index2 = key[0] - 'a';
    if (index2 < 0 || index2 > 25)
    {
        return false;

    }

    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';


        if (!node->children[index])
        {
            return false;
        }

        node = node->children[index];
    }
    if (node->isEndOfWord)
    {
        cout <<"Find word"<< endl;
        return (node != nullptr);
    }
    else
    {
        cout << "Prefix find" << endl;
        return (node != nullptr);
    }    
}





// ���������� true ���� root ����� ����, ����� false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // ���������� ����� ������
    return root;
}


void has_prefixhidden(TrieNode* node, int& cnt_ends)
{
    if (node->isEndOfWord)
    {
        cnt_ends++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            has_prefixhidden(node->children[i], cnt_ends);
        }
    }
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    if (!root)
        return;
    int cnt = 0;
    has_prefixhidden(root, cnt);
    if (cnt == 1) {
        buf[ind] = '\0';
        res += string(buf) + " ";
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)  // 100 - ����� �����
    {
        if (root->children[i]) {
            char c = i + 'a';
            buf[ind] = c;
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}






TrieNode* searchNodePref(struct TrieNode* root, string pref) // ���������� �������, ��������������� ������� ������� ��������
{
    if (!search(root, pref)) // �������� - ���� �� ������� � ������. ���� ��� - ������� ��� ��� ���, ������� �� �������
    {
        cout << "No words found!! Try again!" << endl;
        
        return nullptr;
    }
    
    int index = pref[0] - 'a';
        if (root->children[index])
        {
            return root->children[index];
        }
        else
        {
            return nullptr;
        }
}




string findWordbyPrefInner(TrieNode* node, string& res, string& pref, string& resInner) // ����������� ������� ��� ������ ���� � ��������� ������� ������� ��������
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            if (node->isEndOfWord && res.length() >= pref.length()) // ���� ����� ����� ����� � ��� ���� ����� ���������� ����� ������ ��� = ��������, �� ��������� 
                                                                   //������(���������� ����) � ��������� ����� ��� ��������� ����� �������� �����
            {
                res += ' ';
                res += resInner;
            }
            char c = i + 'a';
            res += c;
            resInner += c;
            findWordbyPrefInner(node->children[i], res, pref, resInner);
        }
    }
    return res;
}


void findWordbyPref(TrieNode* root, string& res, string& pref) // �������� ������� ������ ���� �� ��������
{
    res += pref[0];
    string resInner = res;

    struct TrieNode* node = searchNodePref(root, pref); //������� �������, ��������������� �������!! ������� �������� � ��������� ������������� ��������
                                                        // ���� ������� ������ nullptr ������ �������� ���, 
    
    if (node)
    {
        findWordbyPrefInner(node, res, pref, resInner); // ����� ����������� ������� � ��������, ��������������� �������!! ������� �������� ����� ��������
                                                        // ������� �������� � ��������� ������ �������� �������������� ������� �������
    }
    else
    {                                                  // ���� �-��� searchNodePref ������� nullptr, ������ �������� ���, �������������� ��� � ������ ������ �������,
                                                        // ������� ���������� ��������� � ������� �� �������
        res.clear();
        return;
    }
}
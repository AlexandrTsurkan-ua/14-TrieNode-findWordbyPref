#include <iostream>

#include "Trie.h"


using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
        {
            node->children[index] = getNewNode();
        }
        node = node->children[index];
    }

    // помечаем последний узел как лист, т.е. конец слова
    node->isEndOfWord = true;
}



// Возврашает true если ключ есть в дереве, иначе false 
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





// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // возвращаем новый корень
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
    for (int i = 0; i < ALPHABET_SIZE; i++)  // 100 - длина слова
    {
        if (root->children[i]) {
            char c = i + 'a';
            buf[ind] = c;
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}






TrieNode* searchNodePref(struct TrieNode* root, string pref) // возвращает вершину, соответствующую первому символу префикса
{
    if (!search(root, pref)) // проверка - есть ли префикс в дереве. Если нет - выводим что его нет, выходим из функции
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




string findWordbyPrefInner(TrieNode* node, string& res, string& pref, string& resInner) // рекурсивная функция для вывода слов в поддереве первого символа префикса
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            if (node->isEndOfWord && res.length() >= pref.length()) // если нашли конец слова и при этом длина найденного слова больше или = префиксу, то добавляем 
                                                                   //пробел(разделение слов) и найденную часть как начальную часть большего слова
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


void findWordbyPref(TrieNode* root, string& res, string& pref) // головная функция поиска слов по префиксу
{
    res += pref[0];
    string resInner = res;

    struct TrieNode* node = searchNodePref(root, pref); //находим вершину, соответствующую первому!! символу префикса с проверкой существования префикса
                                                        // если функция вернет nullptr значит префикса нет, 
    
    if (node)
    {
        findWordbyPrefInner(node, res, pref, resInner); // вызов рекурсивной функции с вершиной, соответствующей первому!! символу префикса после проверки
                                                        // наличия префикса и найденной первой вершиной соответсвующей первому символу
    }
    else
    {                                                  // если ф-ция searchNodePref вернула nullptr, значит префикса нет, соответственно нет и нужной первой вершины,
                                                        // очищаем переменную результат и выходим из функции
        res.clear();
        return;
    }
}
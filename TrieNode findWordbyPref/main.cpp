#include <iostream>
#include "Trie.h"
#include "Myfunction.h"



using namespace std;



int main()
{
    setlocale(LC_ALL, "");

    TrieNode* Node14 = getNewNode();

    string H1 = "hello";
    string H2 = "helloween";
    string H3 = "story";
    string H4 = "storynight";
    string H5 = "helloweenert";
    string H6 = "storynightert";
    insert(Node14, H1);
    insert(Node14, H2);
    insert(Node14, H3);
    insert(Node14, H4);
    insert(Node14, H5);
    insert(Node14, H6);
    string res;

  

    int ChooseSelect = 1;
    while (ChooseSelect == 1)
    {
        string pref;
        
        cout << "Введите начало слова(префикс)" << endl;
        cin >> pref;
        
        
        findWordbyPref(Node14, res, pref);

      
        if (!res.empty())
        {
            cout <<"Possible words by the entered prefix: " << res << endl;
        }
        pref.clear();
        res.clear();
        cout << "Для продолжения и попытки нового поиска слов, выберите: 1" << endl;
        cout << "Для завершения работы с программой, выберите: 0" << endl;

        ChooseSelect = chekChoose(0, 1);
    }
 
   
    return 0;
}
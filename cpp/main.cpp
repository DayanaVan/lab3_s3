#include "array.hpp"
#include "forwardlist.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "hashtabledouble.hpp"
#include "rbtree.hpp"
#include <iostream>
#include <cstring>

using namespace std;

void printHelp()
{
    cout << "Usage: ./main [FILE] [COMMAND] [ARGUMENTS]\n";
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printHelp();
        return 0;
    }

    string file(argv[1]);

    switch(argv[2][0])
    {
        case 'A'://array
        {
            Array *arr = new Array(file, false);
            if(strcmp(&argv[2][1], "ADD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                arr->add(argv[3]);
                
                arr->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->add(argv[3], stoi(indexstr));
                
                arr->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "GET") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                cout << arr->get(stoi(indexstr)) << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->remove(stoi(indexstr));
                
                arr->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "CHANGE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->change(stoi(indexstr), argv[4]);
                
                arr->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "SIZE") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << arr->getSize() << "\n";
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << arr->toString() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'F'://forward list
        {
            ForwardList *fl = new ForwardList(file, false);
            if(strcmp(&argv[2][1], "ADDTAIL") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addTail(argv[3]);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "ADDHEAD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                fl->addHead(argv[3]);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->insert(argv[3], index);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVETAIL") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeTail();
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVEHEAD") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeHead();
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVEINDEX") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "Индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->remove(index);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С головы: " << fl->toStringFromHead() << "\n";
                cout << "С хвоста " << fl->toStringFromTail() << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "Значение или номер вхождения - не число\n";
                    return 1;
                }
                fl->removeKey(argv[3], stoi(numstr));                
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "Значение или номер вхождения - не число\n";
                    return 1;
                }
                auto node = fl->find(argv[3], stoi(numstr));                
                if(node != nullptr)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'L'://list
        {
            List *fl = new List(file, false);
            if(strcmp(&argv[2][1], "ADDTAIL") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addTail(argv[3]);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "ADDHEAD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addHead(argv[3]);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->insert(argv[3], index);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVETAIL") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeTail();
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVEHEAD") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeHead();
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVEINDEX") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "Индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->remove(index);
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С головы: " << fl->toStringFromTail() << "\n";
                cout << "С хвоста " << fl->toStringFromHead() << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "номер вхождения - не число\n";
                    return 1;
                }
                fl->removeKey(argv[3], stoi(numstr));                
                
                fl->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "омер вхождения - не число\n";
                    return 1;
                }
                auto node = fl->find(argv[3], stoi(numstr));                
                if(node != nullptr)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'Q'://queue
        {
            Queue *q = new Queue(file, false);
            if(strcmp(&argv[2][1], "PUSH") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                q->push(argv[3]);
                
                q->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "POP") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                std::string a = q->pop();
                cout << a << "\n";
                
                q->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С начала: " << q->toString() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'S'://stack
        {
            Stack *s = new Stack(file, false);
            if(strcmp(&argv[2][1], "PUSH") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                s->push(argv[3]);
                
                s->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "POP") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                std::string a = s->pop();
                cout << a << "\n";
                
                s->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С конца: " << s->toString() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'T'://tree
        {
            Tree *t = new Tree(file, false);
            if(strcmp(&argv[2][1], "ADD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                t->add(stoi(keystr));
                
                t->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                t->remove(t->search(stoi(keystr)));
                
                t->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                auto node = t->search(stoi(keystr));
                if(node != t->nil)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << t->print() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'H'://hash table
        {
            HashTableDouble *ht = new HashTableDouble(file, false);
            if(strcmp(&argv[2][1], "ADD") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                string valuestr = argv[4];
                if(!isNumber(keystr) || !isNumber(valuestr))
                {
                    cout << "Ключ или значение - не число";
                    break;
                }
                ht->insert(stoi(argv[3]), stoi(argv[4]));
                
                ht->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "GET") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "ключ - не число\n";
                    return 1;
                }
                try
                {
                    cout << ht->get(stoi(keystr)) << "\n";
                } catch(...)
                {
                    cout << "не найдено";
                }
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "ключ - не число\n";
                    return 1;
                }

                ht->remove(stoi(keystr));
                
                ht->writeToFile(file);
                
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "ключ - не число\n";
                    return 1;
                }                
                if(ht->contains(stoi(keystr)))
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << ht->toString() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        default:
        {
            cout << "Неизвестная структура\n";
            return 1;
        }
    }

    return 0;
}
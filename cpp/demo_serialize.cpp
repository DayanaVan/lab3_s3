#include <iostream>
#include <string>
#include "array.hpp"
#include "forwardlist.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "hashtabledouble.hpp"
#include "bstree.hpp"

void demoArray() {
    std::cout << "\n=== ARRAY ===\n";
    Array arr;
    
    // Добавляем данные
    arr.add("first");
    arr.add("second");
    arr.add("third");
    std::cout << "Original array: " << arr.toString() << std::endl;
    
    // Текстовая сериализация
    std::string textFile = "array_text.txt";
    arr.writeToFile(textFile);
    std::cout << "Saved to text file: " << textFile << std::endl;
    
    // Бинарная сериализация
    std::string binFile = "array_bin.bin";
    arr.writeToFileBinary(binFile);
    std::cout << "Saved to binary file: " << binFile << std::endl;
    
    // Десериализация из текста
    Array arrFromText(textFile, false);
    std::cout << "Loaded from text: " << arrFromText.toString() << std::endl;
    
    // Десериализация из бинарника
    Array arrFromBin(binFile, true);
    std::cout << "Loaded from binary: " << arrFromBin.toString() << std::endl;
}

void demoForwardList() {
    std::cout << "\n=== FORWARD LIST ===\n";
    ForwardList fl;
    
    fl.addTail("one");
    fl.addTail("two");
    fl.addTail("three");
    std::cout << "Original list (head to tail): " << fl.toStringFromHead() << std::endl;
    
    std::string textFile = "flist_text.txt";
    std::string binFile = "flist_bin.bin";
    
    fl.writeToFile(textFile);
    fl.writeToFileBinary(binFile);
    
    ForwardList flFromText(textFile, false);
    ForwardList flFromBin(binFile, true);
    
    std::cout << "From text: " << flFromText.toStringFromHead() << std::endl;
    std::cout << "From binary: " << flFromBin.toStringFromHead() << std::endl;
}

void demoList() {
    std::cout << "\n=== DOUBLE LIST ===\n";
    List list;
    
    list.addTail("один");
    list.addTail("два");
    list.addTail("три");
    std::cout << "Original list (head to tail): " << list.toStringFromHead() << std::endl;
    std::cout << "Original list (tail to head): " << list.toStringFromTail() << std::endl;
    
    std::string textFile = "dlist_text.txt";
    std::string binFile = "dlist_bin.bin";
    
    list.writeToFile(textFile);
    list.writeToFileBinary(binFile);
    
    List listFromText(textFile, false);
    List listFromBin(binFile, true);
    
    std::cout << "From text (head): " << listFromText.toStringFromHead() << std::endl;
    std::cout << "From binary (head): " << listFromBin.toStringFromHead() << std::endl;
}

void demoQueue() {
    std::cout << "\n=== QUEUE ===\n";
    Queue q;
    
    q.push("first");
    q.push("second");
    q.push("third");
    std::cout << "Original queue: " << q.toString() << std::endl;
    
    std::string textFile = "queue_text.txt";
    std::string binFile = "queue_bin.bin";
    
    q.writeToFile(textFile);
    q.writeToFileBinary(binFile);
    
    Queue qFromText(textFile, false);
    Queue qFromBin(binFile, true);
    
    std::cout << "From text: " << qFromText.toString() << std::endl;
    std::cout << "From binary: " << qFromBin.toString() << std::endl;
}

void demoStack() {
    std::cout << "\n=== STACK ===\n";
    Stack s;
    
    s.push("bottom");
    s.push("middle");
    s.push("top");
    std::cout << "Original stack: " << s.toString() << std::endl;
    
    std::string textFile = "stack_text.txt";
    std::string binFile = "stack_bin.bin";
    
    s.writeToFile(textFile);
    s.writeToFileBinary(binFile);
    
    Stack sFromText(textFile, false);
    Stack sFromBin(binFile, true);
    
    std::cout << "From text: " << sFromText.toString() << std::endl;
    std::cout << "From binary: " << sFromBin.toString() << std::endl;
}

void demoHashTable() {
    std::cout << "\n=== HASH TABLE ===\n";
    HashTableDouble ht(10);
    
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);
    ht.insert(42, 420);
    std::cout << "Original hash table:\n" << ht.toString() << std::endl;
    
    std::string textFile = "hashtable_text.txt";
    std::string binFile = "hashtable_bin.bin";
    
    ht.writeToFile(textFile);
    ht.writeToFileBinary(binFile);
    
    HashTableDouble htFromText(textFile, false);
    HashTableDouble htFromBin(binFile, true);
    
    std::cout << "From text:\n" << htFromText.toString() << std::endl;
    std::cout << "From binary:\n" << htFromBin.toString() << std::endl;
}

void demoTree() {
    std::cout << "\n=== TREE ===\n";
    Tree t;
    
    t.add(50);
    t.add(30);
    t.add(70);
    t.add(20);
    t.add(40);
    std::cout << "Original tree (BFS):\n";
    std::string bfs;
    t.BFS(bfs);
    std::cout << bfs << std::endl;
    
    std::string textFile = "tree_text.txt";
    std::string binFile = "tree_bin.bin";
    
    t.writeToFile(textFile);
    t.writeToFileBinary(binFile);
    
    Tree tFromText(textFile, false);
    Tree tFromBin(binFile, true);
    
    std::cout << "From text (BFS):\n";
    tFromText.BFS(bfs);
    std::cout << bfs << std::endl;
    
    std::cout << "From binary (BFS):\n";
    tFromBin.BFS(bfs);
    std::cout << bfs << std::endl;
}

int main() {
    std::cout << "=== SERIALIZATION/DESERIALIZATION ===\n";

    demoArray();
    demoForwardList();
    demoList();
    demoQueue();
    demoStack();
    demoHashTable();
    demoTree();
    
    return 0;
}

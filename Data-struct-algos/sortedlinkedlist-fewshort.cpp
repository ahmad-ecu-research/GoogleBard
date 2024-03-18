#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
  int data;
  Node* next;
};

Node* createNode(int data) {
  Node* newNode = new Node;
  newNode->data = data;
  newNode->next = nullptr;
  return newNode;
}

bool isFileValid(string filename) {
  ifstream inputFile(filename);
  return inputFile.good();
}

bool isInteger(string str) {
  stringstream ss(str);
  int num;
  if (ss >> num) {
    return ss.eof();
  } else {
    return false;
  }
}

Node* readListFromFile(string filename) {
  if (!isFileValid(filename)) {
    cerr << "Error: File " << filename << " does not exist or is inaccessible." << endl;
    return nullptr;
  }

  ifstream inputFile(filename);
  string line;
  Node* head = nullptr;
  Node* tail = nullptr;

  while (getline(inputFile, line)) {
    if (isInteger(line)) {
      int data = stoi(line);
      Node* newNode = createNode(data);
      if (!head) {
        head = tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
    } else {
      cerr << "Invalid data format in file " << filename << endl;
      return nullptr;
    }
  }

  inputFile.close();
  return head;
}

Node* mergeLists(Node* list1, Node* list2) {
  if (!list1) {
    return list2;
  }

  if (!list2) {
    return list1;
  }

  Node* mergedList = nullptr;
  Node* mergedTail = nullptr;
  while (list1 && list2) {
    Node* newNode = nullptr;
    if (list1->data < list2->data) {
      newNode = createNode(list1->data);
      list1 = list1->next;
    } else {
      newNode = createNode(list2->data);
      list2 = list2->next;
    }

    if (!mergedList) {
      mergedList = mergedTail = newNode;
    } else {
      mergedTail->next = newNode;
      mergedTail = newNode;
    }
  }

  if (list1) {
    mergedTail->next = list1;
  } else if (list2) {
    mergedTail->next = list2;
  }

  return mergedList;
}

void writeListToFile(Node* head, string filename) {
  ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    cerr << "Error opening file " << filename << endl;
    return;
  }

  while (head) {
    outputFile << head->data << " ";
    head = head->next;
  }

  outputFile.close();
}

void cleanupMemory(Node* head) {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {
  string list1Filename, list2Filename, mergedListFilename;

  cout << "Enter the filename for list 1: ";
  cin >> list1Filename;

  cout << "Enter the filename for list 2: ";
  cin >> list2Filename;

  cout << "Enter the filename for the merged list: ";
  cin >> mergedListFilename;

  if (!isFileValid(list1Filename) || !isFileValid(list2Filename)) {
    cerr << "Error: One or more input files do not exist or are inaccessible." << endl;
    return 1;
  }

  Node* list1 = readListFromFile(list1Filename);
  Node* list2 = readListFromFile(list2Filename);

  if (!list1 || !list2) {
    cerr << "Error: Invalid data format in one or more input files." << endl;
    return 1;
  }

  Node* mergedList = mergeLists(list1, list2);

  writeListToFile(mergedList, mergedListFilename

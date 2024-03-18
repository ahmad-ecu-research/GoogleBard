#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class Node {
public:
  int data;
  unique_ptr<Node> next;

  Node(int data) : data(data), next(nullptr) {}
};

Node* ReadLinkedListFromFile(const string& filename) {
  ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    cerr << "Failed to open input file: " << filename << endl;
    exit(1);
  }

  // Create a dummy head node
  unique_ptr<Node> head(new Node(0));

  // Read the linked list from the file
  int data;
  while (inputFile >> data) {
    unique_ptr<Node> newNode(new Node(data));
    newNode->next = move(head->next);
    head->next = move(newNode);
  }

  inputFile.close();

  return head.release();
}

void WriteLinkedListToFile(const Node* head, const string& filename) {
  ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    cerr << "Failed to open output file: " << filename << endl;
    exit(1);
  }

  // Write the linked list to the file
  const Node* current = head;
  while (current != nullptr) {
    outputFile << current->data << " ";
    current = current->next.get();
  }

  outputFile.close();
}

Node* ReverseLinkedListInKGroups(Node* head, int k) {
  // Create a dummy head node
  unique_ptr<Node> dummyHead(new Node(0));
  dummyHead->next = head;

  // Initialize the previous and next nodes
  Node* previous = dummyHead.get();
  Node* next = previous->next.get();

  // Iterate over the linked list in k-groups
  while (next != nullptr) {
    // Reverse the next k nodes
    Node* reversedHead = nullptr;
    for (int i = 0; i < k && next != nullptr; i++) {
      Node* nextNode = next->next.get();
      next->next = reversedHead;
      reversedHead = next;
      next = nextNode;
    }

    // Connect the reversed nodes to the previous nodes
    previous->next = reversedHead;
    previous = reversedHead;
  }

  return dummyHead->next.release();
}

int main(int argc, char** argv) {
  // Check the number of command line arguments
  if (argc != 3) {
    cerr << "Usage: reverse_linked_list_in_k_groups <input_filename> <output_filename>" << endl;
    exit(1);
  }

  // Get the input and output filenames from the command line arguments
  string inputFilename = argv[1];
  string outputFilename = argv[2];

  // Validate the input filename
  if (inputFilename.empty()) {
    cerr << "Invalid input filename" << endl;
    exit(1);
  }

  // Read the linked list from the input file
  Node* head = ReadLinkedListFromFile(inputFilename);

  // Reverse the linked list in k-groups
  head = ReverseLinkedListInKGroups(head, 3);

  // Write the modified linked list to the output file
  WriteLinkedListToFile(head, outputFilename);

  return 0;
}

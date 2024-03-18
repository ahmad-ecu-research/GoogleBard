#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Structure for a node in a linked list
struct Node {
  int data;
  Node* next;
};

// Reads a linked list from a file
Node* ReadLinkedListFromFile(const string& filename) {
  ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    cerr << "Failed to open input file: " << filename << endl;
    exit(1);
  }

  // Create a dummy head node
  Node* head = new Node();
  head->next = NULL;

  // Read the linked list from the file
  int data;
  while (inputFile >> data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = head->next;
    head->next = newNode;
  }

  inputFile.close();

  return head;
}

// Writes a linked list to a file
void WriteLinkedListToFile(const Node* head, const string& filename) {
  ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    cerr << "Failed to open output file: " << filename << endl;
    exit(1);
  }

  // Write the linked list to the file
  Node* current = head->next;
  while (current != NULL) {
    outputFile << current->data << " ";
    current = current->next;
  }

  outputFile.close();
}

// Reverses the nodes of a linked list in k-groups
Node* ReverseLinkedListInKGroups(Node* head, int k) {
  // Create a dummy head node
  Node* dummyHead = new Node();
  dummyHead->next = head;

  // Initialize the previous and next nodes
  Node* previous = dummyHead;
  Node* next = previous->next;

  // Iterate over the linked list in k-groups
  while (next != NULL) {
    // Reverse the next k nodes
    Node* reversedHead = NULL;
    for (int i = 0; i < k && next != NULL; i++) {
      Node* nextNode = next->next;
      next->next = reversedHead;
      reversedHead = next;
      next = nextNode;
    }

    // Connect the reversed nodes to the previous nodes
    previous->next = reversedHead;
    previous = reversedHead;
  }

  return dummyHead->next;
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

  // Read the linked list from the input file
  Node* head = ReadLinkedListFromFile(inputFilename);

  // Reverse the linked list in k-groups
  head = ReverseLinkedListInKGroups(head, 3);

  // Write the modified linked list to the output file
  WriteLinkedListToFile(head, outputFilename);

  return 0;
}

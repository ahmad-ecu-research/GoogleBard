#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Wildcard pattern matching function
bool WildcardMatch(const string& text, const string& pattern) {
  // Check if the pattern is empty
  if (pattern.empty()) {
    return true;
  }

  // Check if the text is empty
  if (text.empty()) {
    return false;
  }

  // Check if the first characters of the text and pattern match
  if (text[0] != pattern[0] && pattern[0] != '*') {
    return false;
  }

  // Recursively check for a match between the rest of the text and pattern
  return WildcardMatch(text.substr(1), pattern.substr(1));
}

int main() {
  // Open the input file
  ifstream inputFile("input.txt");
  if (!inputFile.is_open()) {
    cout << "Failed to open input file: input.txt" << endl;
    return 1;
  }

  // Open the output file
  ofstream outputFile("output.txt");
  if (!outputFile.is_open()) {
    cout << "Failed to open output file: output.txt" << endl;
    return 1;
  }

  // Read the text and pattern strings from the input file
  string text, pattern;
  getline(inputFile, text);
  getline(inputFile, pattern);

  // Perform wildcard matching
  bool matchFound = WildcardMatch(text, pattern);

  // Write the result to the output file
  outputFile << matchFound << endl;

  // Close the input and output files
  inputFile.close();
  outputFile.close();

  return 0;
}

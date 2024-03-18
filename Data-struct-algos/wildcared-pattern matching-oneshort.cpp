#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

// Regular expression to match allowed characters in the input and output filenames
regex allowedFilenameCharsRegex("^[a-zA-Z0-9-_.]*$");

// Validate the input and output filenames
bool ValidateFilenames(const string& inputFilename, const string& outputFilename) {
  return regex_match(inputFilename, allowedFilenameCharsRegex) && regex_match(outputFilename, allowedFilenameCharsRegex);
}

// Open the input and output files
ifstream OpenInputFile(const string& inputFilename) {
  ifstream inputFile(inputFilename);
  if (!inputFile.is_open()) {
    cout << "Failed to open input file: " << inputFilename << endl;
    exit(1);
  }
  return inputFile;
}

ofstream OpenOutputFile(const string& outputFilename) {
  ofstream outputFile(outputFilename);
  if (!outputFile.is_open()) {
    cout << "Failed to open output file: " << outputFilename << endl;
    exit(1);
  }
  return outputFile;
}

// Perform wildcard matching
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

int main(int argc, char** argv) {
  // Check the number of command line arguments
  if (argc != 3) {
    cout << "Usage: wildcard_matching <input_filename> <output_filename>" << endl;
    exit(1);
  }

  // Get the input and output filenames from the command line arguments
  string inputFilename = argv[1];
  string outputFilename = argv[2];

  // Validate the input and output filenames
  if (!ValidateFilenames(inputFilename, outputFilename)) {
    cout << "Invalid input or output filename." << endl;
    exit(1);
  }

  // Open the input and output files
  ifstream inputFile = OpenInputFile(inputFilename);
  ofstream outputFile = OpenOutputFile(outputFilename);

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

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <fnmatch.h>

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
    cerr << "Failed to open input file: " << inputFilename << endl;
    exit(1);
  }
  return inputFile;
}

ofstream OpenOutputFile(const string& outputFilename) {
  ofstream outputFile(outputFilename);
  if (!outputFile.is_open()) {
    cerr << "Failed to open output file: " << inputFilename << endl;
    exit(1);
  }
  return outputFile;
}

// Perform wildcard matching
vector<string> WildcardMatch(ifstream& inputFile, const string& pattern) {
  vector<string> matchingRecords;
  string line;
  while (getline(inputFile, line)) {
    if (fnmatch(pattern.c_str(), line.c_str(), FNM_PATHNAME) == 0) {
      matchingRecords.push_back(line);
    }
  }
  return matchingRecords;
}

int main(int argc, char** argv) {
  // Check the number of command line arguments
  if (argc != 3) {
    cerr << "Usage: wildcard_matching <input_filename> <output_filename>" << endl;
    exit(1);
  }

  // Get the input and output filenames from the command line arguments
  string inputFilename = argv[1];
  string outputFilename = argv[2];

  // Validate the input and output filenames
  if (!ValidateFilenames(inputFilename, outputFilename)) {
    cerr << "Invalid input or output filename." << endl;
    exit(1);
  }

  // Open the input and output files
  ifstream inputFile = OpenInputFile(inputFilename);
  ofstream outputFile = OpenOutputFile(outputFilename);

  // Perform wildcard matching
  vector<string> matchingRecords = WildcardMatch(inputFile, "*.*");

  // Write the matching records to the output file
  for (const string& record : matchingRecords) {
    outputFile << record << endl;
  }

  // Close the input and output files
  inputFile.close();
  outputFile.close();

  return 0;
}

#include <iostream>
#include <string>
#include <vector>

// Database connection library
#include <mysql/mysql.h>

using namespace std;

// Connect to the database
MYSQL* ConnectToDatabase() {
  MYSQL* mysql = mysql_init(NULL);
  if (mysql == NULL) {
    cout << "Failed to initialize MySQL" << endl;
    return NULL;
  }

  // Connect to the database server
  if (mysql_real_connect(mysql, "localhost", "root", "", "my_database", 0, NULL, 0) == NULL) {
    cout << "Failed to connect to the database server: " << mysql_error(mysql) << endl;
    mysql_close(mysql);
    return NULL;
  }

  return mysql;
}

// Perform a search in the database using the provided pattern
vector<string> SearchDatabase(MYSQL* mysql, const string& pattern) {
  // Create a SQL query to search the database
  string query = "SELECT * FROM my_table WHERE name LIKE '%" + pattern + "%'";

  // Execute the query and get the results
  MYSQL_RES* result = mysql_query(mysql, query.c_str());
  if (result == NULL) {
    cout << "Failed to execute query: " << mysql_error(mysql) << endl;
    return vector<string>();
  }

  // Get the number of rows returned by the query
  unsigned long numRows = mysql_num_rows(result);

  // Iterate over the results and add them to a vector
  vector<string> matchingRecords;
  for (unsigned long i = 0; i < numRows; i++) {
    MYSQL_ROW row = mysql_fetch_row(result);
    matchingRecords.push_back(row[0]);
  }

  // Close the result set
  mysql_free_result(result);

  return matchingRecords;
}

// Display the matching records to the user
void DisplayMatchingRecords(const vector<string>& matchingRecords) {
  if (matchingRecords.empty()) {
    cout << "No records found." << endl;
  } else {
    cout << "Matching records:" << endl;
    for (const string& record : matchingRecords) {
      cout << record << endl;
    }
  }
}

// Main function
int main() {
  // Connect to the database
  MYSQL* mysql = ConnectToDatabase();
  if (mysql == NULL) {
    return 1;
  }

  // Get the wildcard pattern from the user
  cout << "Enter a wildcard pattern: ";
  string pattern;
  cin >> pattern;

  // Perform a search in the database using the provided pattern
  vector<string> matchingRecords = SearchDatabase(mysql, pattern);

  // Display the matching records to the user
  DisplayMatchingRecords(matchingRecords);

  // Close the database connection
  mysql_close(mysql);

  return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>

// Establish Connection 
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

conn = mysql_init(NULL);
if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
  std::cerr << "Failed to connect to database: " << mysql_error(conn) << std::endl;
  exit(1);
}


// Read email data from input file:

std::ifstream inputFile("input.txt");
if (!inputFile.is_open()) {
  std::cerr << "Failed to open input file" << std::endl;
  exit(1);
}

std::string email;
while (std::getline(inputFile, email)) {
  // Process each email line
}

inputFile.close();


// Execute SQL query to delete duplicates:

std::string query = "DELETE FROM Emails e1 USING Emails e2 ON e1.Id > e2.Id AND e1.Email = e2.Email;";

if (mysql_query(conn, query.c_str())) {
  std::cerr << "Failed to execute query: " << mysql_error(conn) << std::endl;
  exit(1);
}

// Write updated email data to output file:

std::ofstream outputFile("output.txt");
if (!outputFile.is_open()) {
  std::cerr << "Failed to open output file" << std::endl;
  exit(1);
}

std::string query = "SELECT * FROM Emails";
if (mysql_query(conn, query.c_str())) {
  std::cerr << "Failed to execute query: " << mysql_error(conn) << std::endl;
  exit(1);
}

res = mysql_store_result(conn);
if (!res) {
  std::cerr << "Failed to retrieve results: " << mysql_error(conn) << std::endl;
  exit(1);
}

while ((row = mysql_fetch_row(res))) {
  // Write each row of email data to output file
}

mysql_free_result(res);
outputFile.close()

Close database connection:

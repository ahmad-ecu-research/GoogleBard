#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>
using namespace std;
// Establish connection
MYSQL *conn;
MYSQL_STMT *stmt;
MYSQL_BIND bind[2];

conn = mysql_init(NULL);
if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
  std::cerr << "Failed to connect to database: " << mysql_error(conn) << std::endl;
  exit(1);
}

// Prepare SQL query
std::string query = "INSERT INTO Emails (Id, Email) VALUES (NULL, ?);";
if (mysql_stmt_prepare(conn, query.c_str(), &stmt)) {
  std::cerr << "Failed to prepare statement: " << mysql_error(conn) << std::endl;
  exit(1);
}

// Bind parameters
MYSQL_FIELD *field;
unsigned int num_fields = mysql_stmt_field_count(stmt);

for (unsigned int i = 0; i < num_fields; ++i) {
  field = mysql_stmt_fetch_field(stmt);
  switch (field->type) {
    case MYSQL_TYPE_NULL:
      bind[i].buffer_type = MYSQL_TYPE_NULL;
      bind[i].buffer = NULL;
      bind[i].length = 0;
      break;
    case MYSQL_TYPE_BLOB:
    case MYSQL_TYPE_VAR_STRING:
    case MYSQL_TYPE_STRING:
      bind[i].buffer_type = MYSQL_TYPE_STRING;
      bind[i].buffer = new char[field->max_length + 1];
      bind[i].length = field->max_length;
      break;
    default:
      std::cerr << "Unsupported data type: " << field->type << std::endl;
      exit(1);
  }
}

mysql_stmt_bind_param(stmt, bind);

// Validate and sanitize user input
std::ifstream inputFile("input.txt");
if (!inputFile.is_open()) {
  std::cerr << "Failed to open input file" << std::endl;
  exit(1);
}

std::string email;
while (std::getline(inputFile, email)) {
  // Validate email format
  if (!validateEmail(email)) {
    std::cerr << "Invalid email format: " << email << std::endl;
    continue;
  }

  // securiy conex Sanitize email input
  email = sanitizeEmail(email);

  // Insert email into the 'Emails' table
  bind[1].buffer = (char *)email.c_str();
  bind[1].length = email.length();

  if (mysql_stmt_execute(stmt)) {
    std::cerr << "Failed to execute prepared statement: " << mysql_error(conn) << std::endl;
    exit(1);
  }
}

mysql_stmt_close(stmt);
inputFile.close();

mysql_close(conn);

return 0;

// Function to validate email format
bool validateEmail(const std::string& email) {
  // Regular expression pattern for email validation
  const std::regex emailRegex(R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:\.[a-zA-Z0-9-]+)*$)");
  return std::regex_match(email, emailRegex);
}

// Function to sanitize email input
std::string sanitizeEmail(std::string& email) {
  // Remove leading and trailing whitespace
  email.trim();

  // Convert email to lowercase
  std::transform(email.begin(), email.end(), email.begin(), ::tolower);

  return email;
}

#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>

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

// Read email data from input file
std::ifstream inputFile("input.txt");
if (!inputFile.is_open()) {
    std::cerr << "Failed to open input file" << std::endl;
    exit(1);
}

std::string email;
while (std::getline(inputFile, email)) {
    // Process each email line
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

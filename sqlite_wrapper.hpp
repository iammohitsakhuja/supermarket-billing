/**
 * A wrapper class for sqlite3 library
 * that contains code for connecting to a database
 * and executing SQL queries on it.
 *
 * Author: Mohit Sakhuja
 */

#ifndef SQLITE_WRAPPER_HPP
#define SQLITE_WRAPPER_HPP

#include <sqlite3.h>

class Database
{
    private:
        int connection_status;
        static int callback(void *unused, int col_count, char **col_data, char **col_name);
        static int callback_max_order_id(void *unused, int col_count, char **col_data, char **col_name);
        static int callback_add_items_to_order(void *unused, int col_count, char **col_data, char **col_name);

    public:
        // sqlite database object
        sqlite3 *db;
        char *errmsg;

        // open a connection with the database
        Database(char const *db_name);

        // gets connection status, true if established
        bool get_conn_status(void);

        // execute SQL commands
        void execute(const char *command, ...) __attribute__((format(__printf__, 2, 3)));

        // close connection
        ~Database(void);
};

extern Database db_order;
extern Database db_items;

#endif
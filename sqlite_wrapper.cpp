/**
 * Contains functions for a wrapper class for sqlite3 library
 * that contains code for connecting to a database
 * and executing SQL queries on it.
 *
 * Author: Mohit Sakhuja
 */

#include "sqlite_wrapper.hpp"
#include "helpers.hpp"
#include <cstdio>
#include <cstring>

// open a connection to the given database
Database::Database(const char *db_name)
{
    connection_status = sqlite3_open(db_name, &db);
}

// returns true is database is currently open
bool Database::get_conn_status(void)
{
    return connection_status == SQLITE_OK;
}

// Execute a command on the database
void Database::execute(const char *command, ...)
{
    char *formatted_cmd = new char[strlen(command) + 100];

    // Format the given command
    va_list ap;
    va_start(ap, command);
    vsprintf(formatted_cmd, command, ap);

    int return_code;

    // Check if command is for getting the max order id
    if (strcasestr(formatted_cmd, "max(order_id)") != NULL)
    {
        return_code = sqlite3_exec(db, formatted_cmd, callback_max_order_id, NULL, &errmsg);
    }
    // Else check if it is for selecting all items
    else if (!strcasecmp(formatted_cmd, "select * from items;"))
    {
        return_code = sqlite3_exec(db, formatted_cmd, callback_add_items_to_order, NULL, &errmsg);
    }
    // Else check if it is an update, insert or a delete command
    else if ((strcasestr(formatted_cmd, "insert") != NULL) ||
             (strcasestr(formatted_cmd, "update") != NULL) ||
             (strcasestr(formatted_cmd, "delete") != NULL))
    {
        return_code = sqlite3_exec(db, formatted_cmd, NULL, NULL, &errmsg);
    }
    // Else just run the given command
    else
    {
        return_code = sqlite3_exec(db, formatted_cmd, callback, NULL, &errmsg);
    }

    // Cleanup
    delete[] formatted_cmd;
    va_end(ap);

    if (return_code != SQLITE_OK)
    {
        throw SQLITE_ERROR;
    }
}

// Generic callback function that prints any rows returned to it
int Database::callback(void *unused, int col_count, char **col_data, char **col_name)
{
    static int records = 0;
    if (col_count == 0)
    {
        return 1;
    }

    records++;
    printf("Row: %i\n", records);
    for (int i = 0; i < col_count; i++)
    {
        printf("%s = %s\n", col_name[i], col_data[i]);
    }
    printf("\n");

    return 0;
}

// Get the last order's id
int Database::callback_max_order_id(void *unused, int col_count, char **col_data, char **col_name)
{
    // Increment the last id and assign that to the new order
    order.id = atoi(col_data[0]) + 1;
    return 0;
}

// Adds an items to order
int Database::callback_add_items_to_order(void *unused, int col_count, char **col_data, char **col_name)
{
    // Interpret data from columns
    int id = atoi(col_data[0]);
    string name = col_data[1];
    float cost = atof(col_data[2]);
    int max_quantity = atoi(col_data[3]);

    // Create an item from the data
    Item item = Item(id, name, cost, 0, max_quantity);

    // Push an item into the order
    order.items.push_back(item);

    // success
    return 0;
}

// Close the connection to the database
Database::~Database(void)
{
    if (get_conn_status())
    {
        sqlite3_close(db);
    }

    if (errmsg != NULL)
    {
        sqlite3_free(errmsg);
    }
}

Database db_order = Database("supermarket.db");
Database db_items = Database("supermarket.db");

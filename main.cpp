/** A supermarket billing system
 * that takes the order of a customer and prints the bill.
 *
 * Author: Mohit Sakhuja
 */

#include "helpers.hpp"
#include "sqlite_wrapper.hpp"

using namespace std;

int main(void)
{
    greet();

    get_customer_name();

    // Get last order id
    try
    {
        db_order.execute("SELECT MAX(order_id) FROM orders;");
    }
    catch (int error)
    {
        cerr << "Error code: " << error << endl;
        cerr << "Error getting last order id." << endl;
        cerr << "Error: " << db_order.errmsg << endl;
        return 1;
    }

    // Read items from the database and add them to the order
    try
    {
        db_items.execute("SELECT * FROM items;");
    }
    catch (int error)
    {
        cerr << "Error code: " << error << endl;
        cerr << "Error adding items to the order." << endl;
        cerr << "Error: " << db_items.errmsg << endl;
        return 1;
    }

    order.show_menu();

    int choice;
    cin >> choice;

    // while (true)
    // {
    //     switch (choice)
    //     {
    //         case 0 ... 7:
    //             // Change the quantity for an item/Add an item
    //             order.change_quantity(choice);
    //             break;

    //         case 10:
    //             // View cart
    //             order.view_cart();
    //             break;

    //         case 20:
    //             // Produce bill
    //             char option;
    //             cout << "Are you sure you don't want to buy anything else? (y/n) ";
    //             cin >> option;

    //             if (option == 'y')
    //             {
    //                 order.produce_bill();
    //                 return 0;
    //             }
    //             break;

    //         case 500:
    //             // Quit
    //             return 0;

    //         default:
    //             // Invalid option
    //             invalid_option();
    //             break;
    //     }

    //     order.show_menu();
    //     cin >> choice;
    // }

    // success
    return 0;
}
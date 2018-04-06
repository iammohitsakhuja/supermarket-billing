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
        db_order.execute("SELECT %s FROM %s;", "MAX(order_id)", "orders");
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
        db_items.execute("SELECT %s FROM %s;", "*", "items");
    }
    catch (int error)
    {
        cerr << "Error code: " << error << endl;
        cerr << "Error adding items to the order." << endl;
        cerr << "Error: " << db_items.errmsg << endl;
        return 1;
    }

    // Get the ID of the last item
    int last_item_id = order.items[order.items.size() - 1].id;

    order.show_menu();

    int choice;
    cin >> choice;

    while (true)
    {
        switch (choice)
        {
            // View cart
            case VIEW_CART:
                order.view_cart();
                break;

            // Produce bill
            case CHECKOUT:
                char option;
                cout << "Are you sure you don't want to buy anything else? (y/n) ";
                cin >> option;

                if (option == 'y')
                {
                    order.produce_bill();
                    return 0;
                }
                break;

            // Quit
            case QUIT:
                // quit();
                return 0;

            default:
                if (choice >= 1 && choice <= last_item_id)
                {
                    // Change the quantity for an item/Add an item
                    order.change_quantity(choice);
                }
                else
                {
                    // Invalid option
                    invalid_option();
                }
                break;
        }

        order.show_menu();
        cin >> choice;
    }

    // success
    return 0;
}
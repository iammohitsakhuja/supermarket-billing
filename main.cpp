/** A supermarket billing system
 * that takes the order of a customer and prints the bill.
 *
 * Author: Mohit Sakhuja
 */

#include "helpers.hpp"

using namespace std;

int main(void)
{
    // hard coded items
    Item *hc_items = new Item[8] {
        Item(0, "Biscuits", 20),
        Item(1, "Chips", 25),
        Item(2, "Pulses", 190, 0, 4),
        Item(3, "Detergents", 95, 0, 8),
        Item(4, "Cream", 350, 0, 4),
        Item(5, "Oil", 225),
        Item(6, "Soap", 45),
        Item(7, "Bedsheet", 1100, 0, 6)
    };

    // hard coded order
    Order order = Order(123, "Mohit Sakhuja");
    for (int i = 0; i < 8; i++)
    {
        order.add_item(hc_items[i]);
    }

    // housekeeping for items
    housekeeping(hc_items);

    int choice;

    greet();
    order.show_menu();
    cin >> choice;

    while (true)
    {
        switch (choice)
        {
            case 0 ... 7:
                // Change the quantity for an item/Add an item
                order.change_quantity(choice);
                break;

            case 10:
                // View cart
                order.view_cart();
                break;

            case 20:
                // Produce bill
                char option;
                cout << "Are you sure you don't want to buy anything else? (y/n) ";
                cin >> option;

                if (option == 'y')
                {
                    order.produce_bill();
                    return 0;
                }
                break;

            case 500:
                // Quit
                return 0;

            default:
                // Invalid option
                invalid_option();
                break;
        }

        order.show_menu();
        cin >> choice;
    }

    // success
    return 0;
}
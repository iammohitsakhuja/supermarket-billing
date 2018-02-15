/** A supermarket billing system
 * that takes the order of a customer and prints the bill,
 * maintains the inventory,
 * and the income for each day.
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

    while (true)
    {
        order.show_menu();
        cin >> choice;

        if (get_cart_size(order) > 0)
        {
            switch (choice)
            {
                case 0 ... 7:
                    order.change_quantity(choice);
                    break;

                case -1:
                    // TODO: Produce bill
                    order.produce_bill();
                    exit(EXIT_SUCCESS);
                    break;

                case -2:
                    // TODO: Abandon and Quit
                    // Implement ask and quit function here
                    cout << "Are you sure you want to quit? (y/n)\n";
                    cin >> choice;
                    if (choice == 'y')
                    {
                        cout << "Okay, quitting...";
                        exit(EXIT_FAILURE);
                    }
                    break;

                default:
                    // TODO: Show error
                    cout << "You've entered a wrong choice.\n"
                         << "Please enter a right one!";
                    break;
            }
        }
        else
        {
            // TODO: Implement logic here
            switch (choice)
            {
                case 0 ... 7:
                    order.change_quantity(choice);
                    break;

                case -2:
                    // TODO: Abandon and Quit
                    // Implement ask and quit function here
                    cout << "Are you sure you want to quit? (y/n)\n";
                    cin >> choice;
                    if (choice == 'y')
                    {
                        cout << "Okay, quitting...";
                        exit(EXIT_FAILURE);
                    }
                    break;

                default:
                    // TODO: Show error
                    cout << "You've entered a wrong choice.\n"
                         << "Please enter a right one!";
                    break;
            }
        }
    }

    // success
    return 0;
}
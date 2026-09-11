#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;

//this is the main function for rental management
void mainRentalOrAnalytics(acoomendation_listing_searching& loggedInStudent)
{
    string choice;

    do
    {
        cout << "\n===== Rental & Property Info =====\n";
        cout << "1. Rental Management\n";
        cout << "2. Property Insights & Statistics\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1")
        {
           applyForRental(loggedInStudent);
        }
        else if (choice == "2")
        {
            propertyInsightsMenu();
        }
        else if (choice == "3")
        {
            cout << "Returning to main menu...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != "3");
}
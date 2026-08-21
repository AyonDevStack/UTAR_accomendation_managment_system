#include <bits/stdc++.h>
#include "accomedation.h"

using namespace std;

int main()
{
    cout << R"(
     Welcome to UTAR Accommodation Management System
   ===================================================

     1. Accommodation Listing & Searching
     2. Communication for Management
     3. Rental Management
)";

    string choice;

    cout << "Enter your option: ";
    cin >> choice;

    if (choice == "1")
    {
        accommodationListingAndSearching();
    }
    

    return 0;
}
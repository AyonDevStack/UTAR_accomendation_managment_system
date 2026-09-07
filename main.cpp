#include <bits/stdc++.h>
#include "accomedation.h"

using namespace std;

int main()
{
    cout << R"(
     Welcome to UTAR Accommodation Management System
   ===================================================

     1. Accommodation Listing & Searching
     2. Communication with Owner / Students
     3. Rental Management & Analytics
)";

    string choice;

    cout << "Enter your option: ";
    cin >> choice;

    if (choice == "1")
    {
        accommodationListingAndSearching();
    }
    else if(choice == "2")
    {
        
        communication_appoitment();
    }
    else if(choice == "3"){
             rentalAndAnalyticsEntry();

    }

    else{
        cout << " Invalid choice ";
    }

    return 0;
}
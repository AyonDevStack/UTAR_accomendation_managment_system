#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;

void owner_main_enquire()
{
    vector<owner_details> owners = loadOwners();
    owner_details ownerLogin;
    bool loginSuccess = OwnerLogin(owners, ownerLogin);

    if (!loginSuccess)
    {
        return;
    }

    string owner_choice_enq;

    do
    {
        cout << R"(
    
    1. View Enquiries About My Properties
    2. Reply to an Enquiry
    3. Back
    )";

        cout << "Enter your choice : ";
        cin >> owner_choice_enq;

        if (owner_choice_enq == "1")
        {
            // viewEnquiriesForOwner(ownerLogin);

        }
        else if (owner_choice_enq == "2")
        {
            // replyToEnquiry(ownerLogin);
            
        }
        else if (owner_choice_enq == "3")
        {
            cout << "Returning...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (owner_choice_enq != "3");
}
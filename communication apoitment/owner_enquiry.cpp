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
            viewEnquiriesForOwner(ownerLogin);
        }
        else if (owner_choice_enq == "2")
        {
            replyToEnquiry(ownerLogin);   
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



//this part is the view enquires about his land
//start
void viewEnquiriesForOwner(owner_details& ownerLogin)
{
    vector<Enquiry> enquiries = loadEnquiries();
    bool foundAny = false;

    for (Enquiry& e : enquiries)
    {
        if (e.ownerUserName == ownerLogin.OwnerUserName)
        {
            foundAny = true;
            cout << "-----------------------------\n";
            cout << "Enquiry ID   : " << e.enquiryID << "\n";
            cout << "Property ID  : " << e.propertyID << "\n";
            cout << "From Student : " << e.studentUserName << "\n";
            cout << "Message      : " << e.message << "\n";

            if (e.isReplied)
                cout << "Your Reply   : " << e.reply << "\n";
            else
                cout << "Status       : Not replied yet\n";
        }
    }

    if (!foundAny)
    {
        cout << "No enquiries about your properties yet.\n";
    }

    cout << "-----------------------------\n";
}

//end







//this is part is for Onwer reaply to student
//start
void replyToEnquiry(owner_details& ownerLogin)
{
    vector<Enquiry> enquiries = loadEnquiries();

    string targetID;
    cout << "Enter Enquiry ID to reply to: ";
    cin >> targetID;

    bool found = false;

    for (Enquiry& e : enquiries)
    {
        if (e.enquiryID == targetID && e.ownerUserName == ownerLogin.OwnerUserName)
        {
            found = true;

            cout << "Student's Message: " << e.message << "\n";
            cout << "Enter your reply: ";
            cin.ignore();
            getline(cin, e.reply);

            e.isReplied = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Enquiry ID not found, or it doesn't belong to your properties.\n";
        return;
    }

    saveEnquiries(enquiries);
    cout << "Reply sent successfully!\n";
}

//end

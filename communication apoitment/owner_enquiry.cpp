#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;


void owner_main_enquire()
{
    vector<owner_details> owners = loadOwners();
    owner_details ownerLogin;

    if (!OwnerLogin(owners, ownerLogin)) {
        cout << "Login failed.\n";
        return;
    }

    string choice;
    do {
        cout << R"(
        --- Owner Enquiry Menu ---
        1. View enquiries for my properties
        2. Reply to an enquiry
        3. Back
        )";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            viewEnquiriesForOwner(ownerLogin);
        } else if (choice == "2") {
            replyToEnquiry(ownerLogin);
        } else if (choice == "3") {
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != "3");
}


void viewEnquiriesForOwner(owner_details& ownerLogin)
{
    vector<Enquiry> enquiries = loadEnquiries();
    bool found = false;

    for (auto& e : enquiries) {
        if (e.ownerUserName == ownerLogin.OwnerUserName) {
            found = true;
            cout << "----------------------\n";
            cout << "Enquiry ID   : " << e.enquiryID << "\n";
            cout << "Property ID  : " << e.propertyID << "\n";
            cout << "From Student : " << e.studentUserName << "\n";
            cout << "Message      : " << e.message << "\n";
            cout << "Replied      : " << (e.isReplied ? "Yes" : "No") << "\n";
            if (e.isReplied) {
                cout << "Reply        : " << e.reply << "\n";
            }
        }
    }

    if (!found) {
        cout << "No enquiries found for your properties.\n";
    }
}


void replyToEnquiry(owner_details& ownerLogin)
{
    vector<Enquiry> enquiries = loadEnquiries();
    string targetID;

    cout << "Enter Enquiry ID to reply to: ";
    cin >> targetID;

    bool found = false;
    for (auto& e : enquiries) {
        if (e.enquiryID == targetID && e.ownerUserName == ownerLogin.OwnerUserName) {
            found = true;
            cin.ignore();
            cout << "Enter your reply: ";
            getline(cin, e.reply);
            e.isReplied = true;
            break;
        }
    }

    if (found) {
        saveEnquiries(enquiries);
        cout << "Reply saved.\n";
    } else {
        cout << "Enquiry not found or not yours to reply to.\n";
    }
}
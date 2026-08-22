#ifndef ACCOMEDATION_H
#define ACCOMEDATION_H

#include <bits/stdc++.h>

using namespace std;



// Student Structure

struct acoomendation_listing_searching
{
    string name;
    string email;
    string phoneNumber;
    string userNname;
    string password;
};


// Owner Details structure

struct owner_details
{
    string name;
    string email;
    string OwnerphoneNumber;
    string owner_address;
    string OwnerUserName;
    string OwnerPassWord;


};

struct Property
{
    string propertyID;
    string ownerUsername;
    string homeName;
    string room;
    string roomType;
    string address;
    string price;
    string description;
};

// Accommodation Section

void accommodationListingAndSearching();


// Student Section

void studentMenu();
void student_registration();
bool StudentLogin(
    vector<acoomendation_listing_searching>& students,
    acoomendation_listing_searching& loggedInStudent);
void updateProfile();
void searchProperty();
void shortlistHouse(const string& studentUsername);






// Owner Section

// Owner Section

void owner_main();
void owner_registration();
bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin);
void owner_view_profile(owner_details& ownerLogin);
void updateOwnerProfile();
void addProperty(const string& ownerUsername);
void updateProperty(const string& ownerUsername);
void deleteProperty(const string& ownerUsername);
void viewMyProperties(const string& ownerUsername);
bool propertyIDExists(const string& propertyID);


#endif
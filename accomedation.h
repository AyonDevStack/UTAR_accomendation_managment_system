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



// Accommodation Section

void accommodationListingAndSearching();


// Student Section

void studentMenu();

void student_registration();

bool StudentLogin(
    vector<acoomendation_listing_searching>& students,
    acoomendation_listing_searching& loggedInStudent);

void updateProfile();

// Owner Section

void owner_main();
void owner_registration();
bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin);

#endif
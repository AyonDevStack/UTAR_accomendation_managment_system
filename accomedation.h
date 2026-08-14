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

#endif
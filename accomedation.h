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
    double distanceFromUTAR;   // in km, e.g. 2.5
};


// this is belong to the communication part.

   struct Enquiry
{
    string enquiryID;         // changed from int → string, consistent with Property.propertyID
    string studentUserName;
    string ownerUserName;
    string propertyID;
    string message;
    string reply;
    bool isReplied;            
};


// Rental management Area

struct RentalApplication {
    string applicationID;
    string studentUserName;
    string ownerUserName;
    string propertyID;
    string requestedStartDate;
    string status;       // "Pending", "Approved", "Rejected"
};

struct RentalRecord {
    string rentalID;
    string studentUserName;
    string ownerUserName;
    string propertyID;
    string startDate;
    string endDate;
    double monthlyRent;
    bool isActive;
    bool isPaid;
};






// Accommodation Section

void accommodationListingAndSearching();

//communication part
void communication_appoitment();
vector<acoomendation_listing_searching> loadStudents();


// rental and analysis part
void mainRentalOrAnalytics(acoomendation_listing_searching& loggedInStudent);



// communication Student Quary:
void studentEnquiryMenu();
void sendEnquiry(acoomendation_listing_searching& loggedInStudent);
void viewMyEnquiries(acoomendation_listing_searching& loggedInStudent);
vector<Property> loadProperties();
vector<Enquiry> loadEnquiries();                         
void saveEnquiries(vector<Enquiry>& enquiries); 



//communication Qwnwe Quary
void owner_main_enquire();
vector<owner_details> loadOwners();
void viewEnquiriesForOwner(owner_details& ownerLogin);
void replyToEnquiry(owner_details& ownerLogin);





// Student Section accomendation

void studentMenu();
void student_registration();
bool StudentLogin(
    vector<acoomendation_listing_searching>& students,
    acoomendation_listing_searching& loggedInStudent);
void updateProfile();
void searchProperty();
void shortlistHouse(const string& studentUsername);
void viewMyShortlist(const string& studentUsername);







// Owner Section

void owner_main();
void owner_registration();
bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin);
void owner_view_profile(owner_details& ownerLogin);
void updateOwnerProfile(const string& username);
void addProperty(const string& ownerUsername);
void updateProperty(const string& ownerUsername);
void deleteProperty(const string& ownerUsername);
void viewMyProperties(const string& ownerUsername);
bool propertyIDExists(const string& propertyID);




//Rental and Management & Analysis are

//rental_management.cpp

void mainRentalOrAnalytics(acoomendation_listing_searching& loggedInStudent);
void mainRentalOrAnalyticsOwner(owner_details& loggedInOwner);
//void rentalManagementMenu(acoomendation_listing_searching& loggedInStudent);
void viewApplicationsForOwner(owner_details& ownerLogin);
void rentalAndAnalyticsEntry();
vector<RentalApplication> loadApplications();
void saveApplications(vector<RentalApplication>& applications);
void applyForRental(acoomendation_listing_searching& loggedInStudent);


//Rental and Management & Analysis are

//analytics part
void showTotalListings();
void showAveragePrice();
void showPropertyTypeBreakdown();
void showDistanceStats();
void showShortlistStats();
void propertyInsightsMenu();





#endif
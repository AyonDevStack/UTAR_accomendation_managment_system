#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;


//it is help to save the data

//start
void saveApplications(vector<RentalApplication>& applications)
{
    system("mkdir \"rental management\\data\" 2> nul");

    ofstream appFile("rental management/data/rental_applications.txt");

    for (RentalApplication& a : applications)
    {
        appFile << "Application ID : " << a.applicationID << "\n";
        appFile << "Student Username : " << a.studentUserName << "\n";
        appFile << "Owner Username : " << a.ownerUserName << "\n";
        appFile << "Property ID : " << a.propertyID << "\n";
        appFile << "Requested Start Date : " << a.requestedStartDate << "\n";
        appFile << "Status : " << a.status << "\n";
        appFile << "----------------------\n";
    }

    appFile.close();
}

//end







//this is for application form,
vector<RentalApplication> loadApplications()
{
    vector<RentalApplication> applications;
    ifstream appFile("rental management/data/rental_applications.txt");

    if (!appFile.is_open())
    {
        return applications;
    }

    string line;
    RentalApplication current;
    bool hasData = false;

    while (getline(appFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData)
            {
                applications.push_back(current);
            }
            current = RentalApplication();
            hasData = false;
        }
        else if (line.find("Application ID : ") == 0)
        {
            string label = "Application ID : ";
            current.applicationID = (line.length() > label.length()) ? line.substr(label.length()) : "";
            hasData = true;
        }
        else if (line.find("Student Username : ") == 0)
        {
            string label = "Student Username : ";
            current.studentUserName = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Owner Username : ") == 0)
        {
            string label = "Owner Username : ";
            current.ownerUserName = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Property ID : ") == 0)
        {
            string label = "Property ID : ";
            current.propertyID = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Requested Start Date : ") == 0)
        {
            string label = "Requested Start Date : ";
            current.requestedStartDate = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Status : ") == 0)
        {
            string label = "Status : ";
            current.status = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
    }

    if (hasData)
    {
        applications.push_back(current);
    }

    appFile.close();
    return applications;
}



void viewApplicationsForOwner(owner_details& ownerLogin)
{
    vector<RentalApplication> applications = loadApplications();
    bool found = false;

    for (RentalApplication& a : applications)
    {
        if (a.ownerUserName == ownerLogin.OwnerUserName)
        {
            found = true;
            cout << "----------------------\n";
            cout << "Application ID : " << a.applicationID << "\n";
            cout << "Property ID    : " << a.propertyID << "\n";
            cout << "Student        : " << a.studentUserName << "\n";
            cout << "Start Date     : " << a.requestedStartDate << "\n";
            cout << "Status         : " << a.status << "\n";
        }
    }

    if (!found)
    {
        cout << "No rental applications found for your properties.\n";
    }
}




//this is the main function,,allows a logged-in student to apply for a property.

//start
void applyForRental(acoomendation_listing_searching& loggedInStudent)
{
    // Step 1: load properties to validate ID and find the owner
    vector<Property> properties = loadProperties();

    string propertyID;
    cout << "Enter Property ID you want to apply for: ";
    cin >> propertyID;

    // Step 2: find the property and its owner
    bool found = false;
    string ownerUsername;

    for (Property& p : properties)
    {
        if (p.propertyID == propertyID)
        {
            found = true;
            ownerUsername = p.ownerUsername;
            break;
        }
    }

    if (!found)
    {
        cout << "Property ID not found.\n";
        return;
    }

    // Step 3: get requested start date
    cin.ignore();
    string startDate;
    cout << "Enter requested start date (e.g. 2026-09-01): ";
    getline(cin, startDate);

    // Step 4: load existing applications, generate new ID
    vector<RentalApplication> applications = loadApplications();

    int newIDNum = applications.empty() ? 1 : stoi(applications.back().applicationID) + 1;
    string newApplicationID = to_string(newIDNum);

    // Step 5: build the new application
    RentalApplication newApp;
    newApp.applicationID = newApplicationID;
    newApp.studentUserName = loggedInStudent.userNname;
    newApp.ownerUserName = ownerUsername;
    newApp.propertyID = propertyID;
    newApp.requestedStartDate = startDate;
    newApp.status = "Pending";

    // Step 6: save
    applications.push_back(newApp);
    saveApplications(applications);

    cout << "Rental application submitted successfully! Status: Pending\n";
}
//end
void mainRentalOrAnalyticsOwner(owner_details& loggedInOwner)
{
    string choice;

    do
    {
        cout << "\n===== Rental & Property Info (Owner) =====\n";
        cout << "1. View Rental Applications for My Properties\n";
        cout << "2. Property Insights & Statistics\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1")
        {
               viewApplicationsForOwner(loggedInOwner);

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

void rentalAndAnalyticsEntry()
{
    string userType;
    cout << "\n1. Student\n2. Owner\nWho are you: ";
    cin >> userType;

    if (userType == "1")
    {
        vector<acoomendation_listing_searching> students = loadStudents();
        acoomendation_listing_searching loggedInStudent;
        bool loginSuccess = StudentLogin(students, loggedInStudent);

        if (!loginSuccess) return;

        mainRentalOrAnalytics(loggedInStudent);
    }
    else if (userType == "2")
    {
        vector<owner_details> owners = loadOwners();
        owner_details loggedInOwner;
        bool loginSuccess = OwnerLogin(owners, loggedInOwner);

        if (!loginSuccess) return;

        mainRentalOrAnalyticsOwner(loggedInOwner);
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}
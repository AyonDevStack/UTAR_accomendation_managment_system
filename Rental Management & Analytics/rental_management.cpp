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
//start
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
            current.applicationID = line.substr(18);
            hasData = true;
        }
        else if (line.find("Student Username : ") == 0)
        {
            current.studentUserName = line.substr(19);
        }
        else if (line.find("Owner Username : ") == 0)
        {
            current.ownerUserName = line.substr(18);
        }
        else if (line.find("Property ID : ") == 0)
        {
            current.propertyID = line.substr(14);
        }
        else if (line.find("Requested Start Date : ") == 0)
        {
            current.requestedStartDate = line.substr(24);
        }
        else if (line.find("Status : ") == 0)
        {
            current.status = line.substr(9);
        }
    }

    if (hasData)
    {
        applications.push_back(current);
    }

    appFile.close();
    return applications;
}

//end








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

void rentalAndAnalyticsEntry()
{
    vector<acoomendation_listing_searching> students = loadStudents();
    acoomendation_listing_searching loggedInStudent;
    bool loginSuccess = StudentLogin(students, loggedInStudent);

    if (!loginSuccess)
    {
        return;
    }

    mainRentalOrAnalytics(loggedInStudent);
}
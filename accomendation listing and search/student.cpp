#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
#include<cstdlib>
using namespace std;

// student.cpp

bool checkName(string name)
{
    if(name.empty())
    {
        return false;
    }

    for(char n : name)
    {
        if(!isalpha(n) && n != ' ')
            return false;
    }

    return true;
}


void student_registration()
{   
    acoomendation_listing_searching s;

     cout << " Enter your name : " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, s.name);

    if(!checkName(s.name))
    {
        cout << "please put the valid name" << endl;
        return;
    }

    cout << " Enter your email : " << endl;
    cin >> s.email;

    cout << "Enter you User Name : " << endl;
    cin >> s.userNname;

    cout << "Enter your Password : " << endl;
    cin >> s.password;

    bool validPhoneNumber;

    do
    {
        cout << "Enter your Phone Number: ";
        cin >> s.phoneNumber;

        validPhoneNumber = true;

        for (char digit : s.phoneNumber)
        {
            if (!isdigit(digit))
            {
                validPhoneNumber = false;
                break;
            }
        }

        if (!validPhoneNumber)
        {
            cout << "Invalid phone number. Please enter numbers only." << endl;
        }

    } while (!validPhoneNumber);

    system("mkdir \"accomendation listing and search\\data\" 2> nul");

    ofstream studentFile("accomendation listing and search/data/student.txt", ios::out | ios::app);

    if (!studentFile.is_open())
    {
        cout << "ERROR: Could not open data/student.txt for writing. "
             << "Registration was NOT saved." << endl;
        return;
    }

    studentFile << "Name : " << s.name << endl;
    studentFile << "Email : " << s.email << endl;
    studentFile << "User name : " << s.userNname << endl;
    studentFile << "PassWord : " << s.password << endl;
    studentFile << "Phone Number : " << s.phoneNumber << endl;
    studentFile << "----------------------" << endl;

    studentFile.close();

    cout << "Your details added Sucessfully" << endl;
}


// student Login part
bool StudentLogin(
    vector<acoomendation_listing_searching>& students,
    acoomendation_listing_searching& loggedInStudent)
{
    string inputUserName;
    string inputPassword;

    cout << "Please Enter you user name and Password :" << endl;

    cout << "Enter your username: " << endl;
    cin >> inputUserName;

    cout << "Enter your password: " <<endl;
    cin >> inputPassword;

    for (acoomendation_listing_searching& student : students)
    {
        if (student.userNname == inputUserName &&
            student.password == inputPassword)
        {
            loggedInStudent = student;
            cout << "\nLogin successful!" << endl;
            return true;
        }
    }

    cout << "\nInvalid username or password." << endl;
    return false;
}


// Load all students
vector<acoomendation_listing_searching> loadStudents()
{
    vector<acoomendation_listing_searching> students;
    ifstream studentFile("accomendation listing and search/data/student.txt");

    if (!studentFile.is_open())
    {
        return students;
    }

    string line;
    acoomendation_listing_searching current;
    bool hasData = false;

    while (getline(studentFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData)
            {
                students.push_back(current);
            }
            current = acoomendation_listing_searching();
            hasData = false;
        }
        else if (line.find("Name : ") == 0)
        {
            current.name = line.substr(7);
            hasData = true;
        }
        else if (line.find("Email : ") == 0)
        {
            current.email = line.substr(8);
        }
        else if (line.find("User name : ") == 0)
        {
            current.userNname = line.substr(12);
        }
        else if (line.find("PassWord : ") == 0)
        {
            current.password = line.substr(11);
        }
        else if (line.find("Phone Number : ") == 0)
        {
            current.phoneNumber = line.substr(15);
        }
    }

    studentFile.close();
    return students;
}


void ProfileView( acoomendation_listing_searching& loggedInStudent)
{
    cout << "Register Student Profile " << endl;
    cout << "Name : " << loggedInStudent.name <<endl;
    cout << "Phone Number : " << loggedInStudent.phoneNumber << endl;
    cout << "Email : " << loggedInStudent.email << endl;
    cout << " User Name : " << loggedInStudent.userNname << endl;
    cout << "-------------------------------\n";
}


void updateProfile()
{
    string username;
    int choice;

    string newName;
    string newEmail;
    string newPhone;
    string newPassword;

    cout << "\n========== Update Profile ==========" << endl;
    cout << "Enter your username: " <<endl;
    cin >> username;

    cout << "\n1. Update Name" << endl;
    cout << "2. Update Email" << endl;
    cout << "3. Update Phone Number" << endl;
    cout << "4. Update Password" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter new name: ";
        cin >> newName;
    }
    else if (choice == 2)
    {
        cout << "Enter new email: ";
        cin >> newEmail;
    }
    else if (choice == 3)
    {
        cout << "Enter new phone number: ";
        cin >> newPhone;
    }
    else if (choice == 4)
    {
        cout << "Enter new password: ";
        cin >> newPassword;
    }
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream studentFile("accomendation listing and search/data/student.txt");

    if (!studentFile.is_open())
    {
        cout << "ERROR: student.txt not found. Nothing to update." << endl;
        return;
    }

    ofstream tempFile("accomendation listing and search/data/temp.txt");

    string line;
    bool updated = false;
    vector<string> block;

    while (getline(studentFile, line))
    {
        if (line == "----------------------")
        {
            bool isTargetStudent = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "User name : " + username)
                {
                    isTargetStudent = true;
                    break;
                }
            }

            if (isTargetStudent)
            {
                for (string& blockLine : block)
                {
                    if (choice == 1 && blockLine.find("Name : ") == 0)
                    {
                        blockLine = "Name : " + newName;
                        updated = true;
                    }
                    else if (choice == 2 && blockLine.find("Email : ") == 0)
                    {
                        blockLine = "Email : " + newEmail;
                        updated = true;
                    }
                    else if (choice == 3 && blockLine.find("Phone Number : ") == 0)
                    {
                        blockLine = "Phone Number : " + newPhone;
                        updated = true;
                    }
                    else if (choice == 4 && blockLine.find("PassWord : ") == 0)
                    {
                        blockLine = "PassWord : " + newPassword;
                        updated = true;
                    }
                }
            }

            for (const string& blockLine : block)
            {
                tempFile << blockLine << endl;
            }
            tempFile << "----------------------" << endl;

            block.clear();
        }
        else
        {
            block.push_back(line);
        }
    }

    studentFile.close();
    tempFile.close();

    remove("accomendation listing and search/data/student.txt");
    rename("accomendation listing and search/data/temp.txt", "accomendation listing and search/data/student.txt");

    if (updated)
    {
        cout << "\nProfile updated successfully!" << endl;
    }
    else
    {
        cout << "\nStudent username not found." << endl;
    }
}


// ===================== Search Property =====================
void searchProperty()
{
    string keyword;

    cout << "\n========== Search Property ==========" << endl;
    cout << "Enter keyword (matches Home Name, Room Type, or Address): ";
    cin.ignore();
    getline(cin, keyword);

    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        cout << "ERROR: property.txt not found." << endl;
        return;
    }

    string line;
    vector<string> block;
    bool foundAny = false;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isMatch = false;

            for (const string& blockLine : block)
            {
                bool isSearchableField =
                    blockLine.find("Home Name : ") == 0 ||
                    blockLine.find("Room Type : ") == 0 ||
                    blockLine.find("Address : ") == 0;

                if (isSearchableField && blockLine.find(keyword) != string::npos)
                {
                    isMatch = true;
                    break;
                }
            }

            if (isMatch)
            {
                for (const string& blockLine : block)
                {
                    cout << blockLine << endl;
                }
                cout << "----------------------" << endl;
                foundAny = true;
            }

            block.clear();
        }
        else
        {
            block.push_back(line);
        }
    }

    propertyFile.close();

    if (!foundAny)
    {
        cout << "No properties matched your search." << endl;
    }
}


void shortlistHouse(const string& studentUsername)
{
    string propertyID;

    cout << "\n========== Shortlist a House ==========" << endl;
    cout << "Enter the Property ID to shortlist: ";
    cin >> propertyID;

    if (!propertyIDExists(propertyID))
    {
        cout << "That Property ID doesn't exist. Please check and try again." << endl;
        return;
    }

    system("mkdir \"accomendation listing and search\\data\" 2> nul");

    ofstream shortlistFile("accomendation listing and search/data/shortlist.txt", ios::app);

    if (!shortlistFile.is_open())
    {
        cout << "ERROR: Could not open shortlist.txt to save your shortlist." << endl;
        return;
    }

    shortlistFile << "Student Username : " << studentUsername << endl;
    shortlistFile << "Property ID : " << propertyID << endl;
    shortlistFile << "----------------------" << endl;

    shortlistFile.close();

    cout << "\nProperty shortlisted successfully!" << endl;
}

//start of the shortlisted view

void viewMyShortlist(const string& studentUsername)
{
    ifstream shortlistFile("accomendation listing and search/data/shortlist.txt");

    if (!shortlistFile.is_open())
    {
        cout << "No shortlist data found yet.\n";
        return;
    }

    string line;
    vector<string> block;
    bool foundAny = false;

    cout << "\n========== My Shortlisted Properties ==========\n";

    while (getline(shortlistFile, line))
    {
        if (line == "----------------------")
        {
            bool isMine = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Student Username : " + studentUsername)
                {
                    isMine = true;
                    break;
                }
            }

            if (isMine)
            {
                for (const string& blockLine : block) cout << blockLine << endl;
                cout << "----------------------\n";
                foundAny = true;
            }

            block.clear();
        }
        else
        {
            block.push_back(line);
        }
    }

    shortlistFile.close();

    if (!foundAny)
    {
        cout << "You haven't shortlisted any properties yet.\n";
    }
}

//end of the view shortlisted

void studentMenu()
{
    static vector<acoomendation_listing_searching> students;
    static acoomendation_listing_searching loggedInStudent;
    string choice;

    do
        {
            cout << "#########################" << endl;
            cout << "       Student Menu" << endl;
            cout << "########################" << endl;

            cout << "1. Student Registration" << endl;
    cout << "2. Student Login" << endl;
    cout << "3. View Profile" << endl;
    cout << "4. Update Profile" << endl;
    cout << "5. Search Property" << endl;
    cout << "6. Shortlist House" << endl;
    cout << "7. View My Shortlist" << endl;
    cout << "8. Rental & Property Info" << endl;
    cout << "9. Back to Main Menu" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == "1") { student_registration(); }
    else if (choice == "2") { students = loadStudents(); StudentLogin(students, loggedInStudent); }
    else if(choice == "3") { ProfileView(loggedInStudent); }
    else if(choice == "4") { updateProfile(); }
    else if(choice == "5") { searchProperty(); }
    else if(choice == "6") { shortlistHouse(loggedInStudent.userNname); }
    else if(choice == "7") { viewMyShortlist(loggedInStudent.userNname); }
    else if(choice == "8") { mainRentalOrAnalytics(loggedInStudent); }
    else if(choice == "9") { cout << "Returning to main menu...\n"; }
    else { cout << "Invalid choice." << endl; }

    } while (choice != "9");
}
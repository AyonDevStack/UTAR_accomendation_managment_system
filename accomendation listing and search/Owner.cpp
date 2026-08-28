#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
#include<cstdlib>   //system() to create the "data" folder
using namespace std;

// student.cpp


bool checkName(string name)
{

    if(name.empty())
    {
        return false;
    }

    for(char n :  name){

        if(!isalpha(n) && n !=' ')
            return false;

    }


    return true;
}


void student_registration()
{   

    // vector<acoomendation_listing_searching>students;
    acoomendation_listing_searching s;

    cout << " Enter your name : " << endl;
    cin >> s.name;

    // BUG FIX #1: previously, if the name was invalid, we only printed a
    // warning but kept going and saved the bad data anyway.
    // Now we actually stop registration when the name is invalid.
    if(!checkName(s.name))
    {
        cout << "please put the valid name" << endl;
        return;   // stop here instead of continuing to save
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

    // Now we actually check whether the file opened successfully.
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

    // Only print success AFTER we've actually confirmed the write happened.
    cout << "Your details added Scuessfully" << endl;
}




// student Loging part
// start --------

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


    // Check username and password
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

//student Loging part End --------

//load data of login start
// ===================== Helper: load all students from file into a vector =====================
vector<acoomendation_listing_searching> loadStudents()
{
    vector<acoomendation_listing_searching> students;
    ifstream studentFile("accomendation listing and search/data/student.txt");

    if (!studentFile.is_open())
    {
        return students; // empty — no students registered yet
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

//load data of student end 





// view profile section start

void ProfileView( acoomendation_listing_searching& loggedInStudent)
{


    cout << "Register Student Profile " << endl;

    cout << "Name : " << loggedInStudent.name <<endl;
    cout << "Phone Number : " << loggedInStudent.phoneNumber << endl;
    cout << "Email : " << loggedInStudent.email << endl;
    cout << " User Name : " << loggedInStudent.userNname << endl;

    cout << "-------------------------------\n";


}
// view profile end sections






// update profile start section :

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


    // Get the new information
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


    // Open the old file for reading
    ifstream studentFile("accomendation listing and search/data/student.txt");

    if (!studentFile.is_open())
    {
        cout << "ERROR: student.txt not found. Nothing to update." << endl;
        return;
    }

    // Create a temporary file for the updated data
    ofstream tempFile("accomendation listing and search/data/temp.txt");

    string line;
    bool updated = false;

 
    vector<string> block;

    while (getline(studentFile, line))
    {
        if (line == "----------------------")
        {
            // We've collected one full student record — check if it's the one we want
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

            // Write this student's block (updated or not) into the temp file
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


    // Replace the old file with the updated file
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
// Update section end section :



//search property start : 
void searchProperty()
{
    string keyword;

    cout << "\n========== Search Property ==========" << endl;
    cout << "Enter keyword (matches Home Name, Room Type, or Address): ";
    cin.ignore();
    getline(cin, keyword);

<<<<<<< HEAD
    cout << "Enter Home Name: ";
    getline(cin, homeName);

    cout << "Enter Room (e.g. Room 4B): ";
    getline(cin, room);

    cout << "Enter Room Type (e.g. Single Room / Master Room / Shared Room): ";
    getline(cin, roomType);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Price (e.g. RM 200): ";
    getline(cin, price);

    cout << "Enter Description: ";
    getline(cin, description);

    ofstream propertyFile("accomendation listing and search/data/property.txt", ios::app);

    if (!propertyFile.is_open())
    {
        cout << "ERROR: Could not open property.txt to add new property." << endl;
        return;
    }

    propertyFile << "Property ID : " << propertyID << endl;
    propertyFile << "Owner Username : " << ownerUsername << endl;
    propertyFile << "Home Name : " << homeName << endl;
    propertyFile << "Room : " << room << endl;
    propertyFile << "Room Type : " << roomType << endl;
    propertyFile << "Address : " << address << endl;
    propertyFile << "Price : " << price << endl;
    propertyFile << "Description : " << description << endl;
    propertyFile << "----------------------" << endl;

    propertyFile.close();

    cout << "\nProperty added successfully!" << endl;
}









vector<Property> loadProperties()
{
    vector<Property> properties;
    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        return properties;
    }

    string line;
    Property current;
    bool hasData = false;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData)
            {
                properties.push_back(current);
            }
            current = Property();
            hasData = false;
        }
        else if (line.find("Property ID : ") == 0)
        {
            current.propertyID = line.substr(14);
            hasData = true;
        }
        else if (line.find("Owner Username : ") == 0)
        {
            current.ownerUsername = line.substr(18);
        }
        else if (line.find("Home Name : ") == 0)
        {
            current.homeName = line.substr(12);
        }
        else if (line.find("Room : ") == 0)
        {
            current.room = line.substr(7);
        }
        else if (line.find("Room Type : ") == 0)
        {
            current.roomType = line.substr(12);
        }
        else if (line.find("Address : ") == 0)
        {
            current.address = line.substr(10);
        }
        else if (line.find("Price : ") == 0)
        {
            current.price = line.substr(8);
        }
        else if (line.find("Description : ") == 0)
        {
            current.description = line.substr(14);
        }
    }

    if (hasData)
    {
        properties.push_back(current);
    }

    propertyFile.close();
    return properties;
}







// ===================== Update Property =====================
void updateProperty(const string& ownerUsername)
{
    string propertyID;
    int choice;

    string newHomeName;
    string newRoom;
    string newRoomType;
    string newAddress;
    string newPrice;
    string newDescription;

    cout << "\n========== Update Property ==========" << endl;
    cout << "Enter the Property ID to update: ";
    cin >> propertyID;

    cout << "\n1. Update Home Name" << endl;
    cout << "2. Update Room" << endl;
    cout << "3. Update Room Type" << endl;
    cout << "4. Update Address" << endl;
    cout << "5. Update Price" << endl;
    cout << "6. Update Description" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        cout << "Enter new home name: ";
        getline(cin, newHomeName);
    }
    else if (choice == 2)
    {
        cout << "Enter new room: ";
        getline(cin, newRoom);
    }
    else if (choice == 3)
    {
        cout << "Enter new room type: ";
        getline(cin, newRoomType);
    }
    else if (choice == 4)
    {
        cout << "Enter new address: ";
        getline(cin, newAddress);
    }
    else if (choice == 5)
    {
        cout << "Enter new price (e.g. RM 250): ";
        getline(cin, newPrice);
    }
    else if (choice == 6)
    {
        cout << "Enter new description: ";
        getline(cin, newDescription);
    }
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        cout << "ERROR: property.txt not found. Nothing to update." << endl;
        return;
    }

    ofstream tempFile("accomendation listing and search/data/temp_property.txt");

    string line;
    bool updated = false;
    vector<string> block;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isTargetProperty = false;
            bool isMyProperty = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Property ID : " + propertyID)
                    isTargetProperty = true;

                if (blockLine == "Owner Username : " + ownerUsername)
                    isMyProperty = true;
            }

            if (isTargetProperty && isMyProperty)
            {
                for (string& blockLine : block)
                {
                    if (choice == 1 && blockLine.find("Home Name : ") == 0)
                    {
                        blockLine = "Home Name : " + newHomeName;
                        updated = true;
                    }
                    else if (choice == 2 && blockLine.find("Room : ") == 0)
                    {
                        blockLine = "Room : " + newRoom;
                        updated = true;
                    }
                    else if (choice == 3 && blockLine.find("Room Type : ") == 0)
                    {
                        blockLine = "Room Type : " + newRoomType;
                        updated = true;
                    }
                    else if (choice == 4 && blockLine.find("Address : ") == 0)
                    {
                        blockLine = "Address : " + newAddress;
                        updated = true;
                    }
                    else if (choice == 5 && blockLine.find("Price : ") == 0)
                    {
                        blockLine = "Price : " + newPrice;
                        updated = true;
                    }
                    else if (choice == 6 && blockLine.find("Description : ") == 0)
                    {
                        blockLine = "Description : " + newDescription;
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

    propertyFile.close();
    tempFile.close();

    remove("accomendation listing and search/data/property.txt");
    rename("accomendation listing and search/data/temp_property.txt", "accomendation listing and search/data/property.txt");

    if (updated)
        cout << "\nProperty updated successfully!" << endl;
    else
        cout << "\nProperty not found, or it doesn't belong to you." << endl;
}


// ===================== Delete Property =====================
void deleteProperty(const string& ownerUsername)
{
    string propertyID;

    cout << "\n========== Delete Property ==========" << endl;
    cout << "Enter the Property ID to delete: ";
    cin >> propertyID;

    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        cout << "ERROR: property.txt not found. Nothing to delete." << endl;
        return;
    }

    ofstream tempFile("accomendation listing and search/data/temp_property.txt");

    string line;
    bool deleted = false;
    vector<string> block;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isTargetProperty = false;
            bool isMyProperty = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Property ID : " + propertyID)
                    isTargetProperty = true;

                if (blockLine == "Owner Username : " + ownerUsername)
                    isMyProperty = true;
            }

            if (isTargetProperty && isMyProperty)
            {
                deleted = true; // skip writing this block = deletes it
            }
            else
            {
                for (const string& blockLine : block)
                {
                    tempFile << blockLine << endl;
                }
                tempFile << "----------------------" << endl;
            }

            block.clear();
        }
        else
        {
            block.push_back(line);
        }
    }

    propertyFile.close();
    tempFile.close();

    remove("accomendation listing and search/data/property.txt");
    rename("accomendation listing and search/data/temp_property.txt", "accomendation listing and search/data/property.txt");

    if (deleted)
        cout << "\nProperty deleted successfully!" << endl;
    else
        cout << "\nProperty not found, or it doesn't belong to you." << endl;
}


// ===================== View My Properties =====================
void viewMyProperties(const string& ownerUsername)
{
=======
>>>>>>> 683b24953a4afca3309ca019cfa61d48ab034089
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


//search property end






//shortlisted house function start :

void shortlistHouse(const string& studentUsername)
{
    string propertyID;

    cout << "\n========== Shortlist a House ==========" << endl;
    cout << "Enter the Property ID to shortlist: ";
    cin >> propertyID;

    // Step 1: confirm this Property ID actually exists in property.txt
    if (!propertyIDExists(propertyID))
    {
        cout << "That Property ID doesn't exist. Please check and try again." << endl;
        return;
    }

    // Step 2: save this student's shortlist entry
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

//shortlisted hoise function end : 














// student start with menu

void studentMenu()
{
    string choice;

    // Shared state so Login -> View/Update can use the same student list.
    // (Empty for now until a "load from file" function is added — see note above.)
    static vector<acoomendation_listing_searching> students;
    static acoomendation_listing_searching loggedInStudent;

    cout << "#########################" << endl;
    cout << "       Student Menu" << endl;
    cout << "########################" << endl;

    cout << "1. Student Registration" << endl;
    cout << "2. Student Login" << endl;
    cout << "3. View Profile" << endl;
    cout << "4. Update Profile" << endl;
    cout << "5. Search Property" << endl;
    cout << "6. Shortlist House" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == "1")
    {
        student_registration();
    }
    else if (choice == "2")
    {
        students = loadStudents();          // FIXED: load real data before checking login
        StudentLogin(students, loggedInStudent); 
       
    }

    else if(choice == "3")
    {
        
        ProfileView(loggedInStudent);
    }

    else if(choice == "4")
    {
        updateProfile();
    }

    else if(choice == "5")
    {
        searchProperty();
    }

    else if(choice == "6")
    {
       void shortlistHouse(const string& studentUsername);

    }
    else
    {
        cout << "Invalid choice." << endl;
    }

}
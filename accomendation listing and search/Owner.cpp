#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
#include<cstdlib>
using namespace std;

// ===================== Owner Registration =====================
void owner_registration()
{
    owner_details o;

     cout << "Enter your name: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, o.name);
    
    cout << "Enter your email: " << endl;
    cin >> o.email;

    cout << "Enter your phone number: " << endl;
    cin >> o.OwnerphoneNumber;

    cin.ignore();
    cout << "Enter your address: " << endl;
    getline(cin, o.owner_address);

    cout << "Enter your username: " << endl;
    cin >> o.OwnerUserName;

    cout << "Enter your password: " << endl;
    cin >> o.OwnerPassWord;

    system("mkdir \"accomendation listing and search\\data\" 2> nul");

    ofstream ownerFile("accomendation listing and search/data/owner.txt", ios::out | ios::app);

    if (!ownerFile.is_open())
    {
        cout << "ERROR: Could not open owner.txt for writing. Registration was NOT saved." << endl;
        return;
    }

    ownerFile << "Name : " << o.name << endl;
    ownerFile << "Email : " << o.email << endl;
    ownerFile << "Phone Number : " << o.OwnerphoneNumber << endl;
    ownerFile << "Address : " << o.owner_address << endl;
    ownerFile << "User name : " << o.OwnerUserName << endl;
    ownerFile << "PassWord : " << o.OwnerPassWord << endl;
    ownerFile << "----------------------" << endl;

    ownerFile.close();

    cout << "Your details added successfully!" << endl;
}


// ===================== Load Owners =====================
vector<owner_details> loadOwners()
{
    vector<owner_details> owners;
    ifstream ownerFile("accomendation listing and search/data/owner.txt");

    if (!ownerFile.is_open())
    {
        return owners;
    }

    string line;
    owner_details current;
    bool hasData = false;

    while (getline(ownerFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData)
            {
                owners.push_back(current);
            }
            current = owner_details();
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
        else if (line.find("Phone Number : ") == 0)
        {
            current.OwnerphoneNumber = line.substr(15);
        }
        else if (line.find("Address : ") == 0)
        {
            current.owner_address = line.substr(10);
        }
        else if (line.find("User name : ") == 0)
        {
            current.OwnerUserName = line.substr(12);
        }
        else if (line.find("PassWord : ") == 0)
        {
            current.OwnerPassWord = line.substr(11);
        }
    }

    if (hasData)
    {
        owners.push_back(current);
    }

    ownerFile.close();
    return owners;
}


// ===================== Owner Login =====================
bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin)
{
    string inputUserName;
    string inputPassword;

    cout << "Enter your username: " << endl;
    cin >> inputUserName;

    cout << "Enter your password: " << endl;
    cin >> inputPassword;

    for (owner_details& owner : owners)
    {
        if (owner.OwnerUserName == inputUserName &&
            owner.OwnerPassWord == inputPassword)
        {
            ownerLogin = owner;
            cout << "\nLogin successful!" << endl;
            return true;
        }
    }

    cout << "\nInvalid username or password." << endl;
    return false;
}


// ===================== View Profile =====================
void owner_view_profile(owner_details& ownerLogin)
{
    cout << "\n===== Owner Profile =====\n";
    cout << "Name : " << ownerLogin.name << endl;
    cout << "Email : " << ownerLogin.email << endl;
    cout << "Phone Number : " << ownerLogin.OwnerphoneNumber << endl;
    cout << "Address : " << ownerLogin.owner_address << endl;
    cout << "Username : " << ownerLogin.OwnerUserName << endl;
    cout << "-------------------------------\n";
}


// ===================== Update Owner Profile =====================
void updateOwnerProfile(const string& username)
{
    int choice;
    string newName, newEmail, newPhone, newAddress, newPassword;

    cout << "\n1. Update Name\n2. Update Email\n3. Update Phone\n4. Update Address\n5. Update Password\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) { cout << "Enter new name: "; getline(cin, newName); }
    else if (choice == 2) { cout << "Enter new email: "; getline(cin, newEmail); }
    else if (choice == 3) { cout << "Enter new phone: "; getline(cin, newPhone); }
    else if (choice == 4) { cout << "Enter new address: "; getline(cin, newAddress); }
    else if (choice == 5) { cout << "Enter new password: "; getline(cin, newPassword); }
    else { cout << "Invalid choice." << endl; return; }

    ifstream ownerFile("accomendation listing and search/data/owner.txt");

    if (!ownerFile.is_open())
    {
        cout << "ERROR: owner.txt not found." << endl;
        return;
    }

    ofstream tempFile("accomendation listing and search/data/temp_owner.txt");

    string line;
    bool updated = false;
    vector<string> block;

    while (getline(ownerFile, line))
    {
        if (line == "----------------------")
        {
            bool isTarget = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "User name : " + username)
                {
                    isTarget = true;
                    break;
                }
            }

            if (isTarget)
            {
                for (string& blockLine : block)
                {
                    if (choice == 1 && blockLine.find("Name : ") == 0) { blockLine = "Name : " + newName; updated = true; }
                    else if (choice == 2 && blockLine.find("Email : ") == 0) { blockLine = "Email : " + newEmail; updated = true; }
                    else if (choice == 3 && blockLine.find("Phone Number : ") == 0) { blockLine = "Phone Number : " + newPhone; updated = true; }
                    else if (choice == 4 && blockLine.find("Address : ") == 0) { blockLine = "Address : " + newAddress; updated = true; }
                    else if (choice == 5 && blockLine.find("PassWord : ") == 0) { blockLine = "PassWord : " + newPassword; updated = true; }
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

    ownerFile.close();
    tempFile.close();

    remove("accomendation listing and search/data/owner.txt");
    rename("accomendation listing and search/datatemp_owner.txt", "accomendation listing and search/data/owner.txt");

    if (updated)
        cout << "\nProfile updated successfully!" << endl;
    else
        cout << "\nOwner username not found." << endl;
}


// ===================== Add Property =====================
void addProperty(const string& ownerUsername)
{
    string propertyID, homeName, room, roomType, address, price, description;
    double distanceFromUTAR;

    cout << "\n========== Add Property ==========" << endl;
    cout << "Enter Property ID: ";
    cin.ignore();
    getline(cin, propertyID);
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
    cout << "Enter estimated distance from UTAR (in km, e.g. 2.5): ";
    cin >> distanceFromUTAR;

    system("mkdir \"accomendation listing and search\\data\" 2> nul");
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
    propertyFile << "Distance From UTAR : " << distanceFromUTAR << " km" << endl;
    propertyFile << "----------------------" << endl;
    propertyFile.close();

    cout << "\nProperty added successfully!" << endl;
}


// ===================== Load Properties =====================
vector<Property> loadProperties()
{
    vector<Property> properties;
    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
        return properties;

    string line;
    Property current;
    bool hasData = false;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData) properties.push_back(current);
            current = Property();
            hasData = false;
        }
        else if (line.find("Property ID : ") == 0)
        {
            string label = "Property ID : ";
            current.propertyID = (line.length() > label.length()) ? line.substr(label.length()) : "";
            hasData = true;
        }
        else if (line.find("Owner Username : ") == 0)
        {
            string label = "Owner Username : ";
            current.ownerUsername = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Home Name : ") == 0)
        {
            string label = "Home Name : ";
            current.homeName = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Room : ") == 0)
        {
            string label = "Room : ";
            current.room = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Room Type : ") == 0)
        {
            string label = "Room Type : ";
            current.roomType = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Address : ") == 0)
        {
            string label = "Address : ";
            current.address = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Price : ") == 0)
        {
            string label = "Price : ";
            current.price = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Description : ") == 0)
        {
            string label = "Description : ";
            current.description = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Distance From UTAR : ") == 0)
        {
            string label = "Distance From UTAR : ";
            current.distanceFromUTAR = (line.length() > label.length()) ? stod(line.substr(label.length())) : 0.0;
        }
    }

    if (hasData) properties.push_back(current);

    propertyFile.close();
    return properties;
}


// ===================== Update Property =====================
void updateProperty(const string& ownerUsername)
{
    string propertyID;
    int choice;
    string newHomeName, newRoom, newRoomType, newAddress, newPrice, newDescription;

    cout << "\n========== Update Property ==========" << endl;
    cout << "Enter the Property ID to update: ";
    cin >> propertyID;

    cout << "\n1. Update Home Name\n2. Update Room\n3. Update Room Type\n4. Update Address\n5. Update Price\n6. Update Description\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) { cout << "Enter new home name: "; getline(cin, newHomeName); }
    else if (choice == 2) { cout << "Enter new room: "; getline(cin, newRoom); }
    else if (choice == 3) { cout << "Enter new room type: "; getline(cin, newRoomType); }
    else if (choice == 4) { cout << "Enter new address: "; getline(cin, newAddress); }
    else if (choice == 5) { cout << "Enter new price (e.g. RM 250): "; getline(cin, newPrice); }
    else if (choice == 6) { cout << "Enter new description: "; getline(cin, newDescription); }
    else { cout << "Invalid choice." << endl; return; }

    ifstream propertyFile("accomendation listing and search/data/property.txt");
    if (!propertyFile.is_open()) { cout << "ERROR: property.txt not found." << endl; return; }

    ofstream tempFile("accomendation listing and search/data/temp_property.txt");
    string line;
    bool updated = false;
    vector<string> block;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isTargetProperty = false, isMyProperty = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Property ID : " + propertyID) isTargetProperty = true;
                if (blockLine == "Owner Username : " + ownerUsername) isMyProperty = true;
            }

            if (isTargetProperty && isMyProperty)
            {
                for (string& blockLine : block)
                {
                    if (choice == 1 && blockLine.find("Home Name : ") == 0) { blockLine = "Home Name : " + newHomeName; updated = true; }
                    else if (choice == 2 && blockLine.find("Room : ") == 0) { blockLine = "Room : " + newRoom; updated = true; }
                    else if (choice == 3 && blockLine.find("Room Type : ") == 0) { blockLine = "Room Type : " + newRoomType; updated = true; }
                    else if (choice == 4 && blockLine.find("Address : ") == 0) { blockLine = "Address : " + newAddress; updated = true; }
                    else if (choice == 5 && blockLine.find("Price : ") == 0) { blockLine = "Price : " + newPrice; updated = true; }
                    else if (choice == 6 && blockLine.find("Description : ") == 0) { blockLine = "Description : " + newDescription; updated = true; }
                }
            }

            for (const string& blockLine : block) tempFile << blockLine << endl;
            tempFile << "----------------------" << endl;
            block.clear();
        }
        else block.push_back(line);
    }

    propertyFile.close();
    tempFile.close();

    if (remove("accomendation listing and search/data/property.txt") != 0)
    {
        cout << "ERROR: Could not delete old property.txt.\n";
        return;
    }

    if (rename("accomendation listing and search/data/temp_property.txt", "accomendation listing and search/data/property.txt") != 0)
    {
        cout << "ERROR: Could not rename temp_property.txt to property.txt.\n";
        return;
    }

    if (updated) cout << "\nProperty updated successfully!" << endl;
    else cout << "\nProperty not found, or it doesn't belong to you." << endl;
}
// ===================== Delete Property =====================
void deleteProperty(const string& ownerUsername)
{
    string propertyID;
    cout << "\n========== Delete Property ==========" << endl;
    cout << "Enter the Property ID to delete: ";
    cin >> propertyID;

    ifstream propertyFile("accomendation listing and search/data/property.txt");
    if (!propertyFile.is_open()) { cout << "ERROR: property.txt not found." << endl; return; }

    ofstream tempFile("accomendation listing and search/data/temp_property.txt");
    string line;
    bool deleted = false;
    vector<string> block;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isTargetProperty = false, isMyProperty = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Property ID : " + propertyID) isTargetProperty = true;
                if (blockLine == "Owner Username : " + ownerUsername) isMyProperty = true;
            }

            if (isTargetProperty && isMyProperty) deleted = true;
            else
            {
                for (const string& blockLine : block) tempFile << blockLine << endl;
                tempFile << "----------------------" << endl;
            }

            block.clear();
        }
        else block.push_back(line);
    }

    propertyFile.close();
    tempFile.close();
    remove("accomendation listing and search/data/property.txt");
    rename("accomendation listing and search/data/temp_property.txt", "accomendation listing and search/data/property.txt");

    if (deleted) cout << "\nProperty deleted successfully!" << endl;
    else cout << "\nProperty not found, or it doesn't belong to you." << endl;
}


// ===================== View My Properties =====================
void viewMyProperties(const string& ownerUsername)
{
    ifstream propertyFile("accomendation listing and search/data/property.txt");
    if (!propertyFile.is_open()) { cout << "ERROR: property.txt not found." << endl; return; }

    string line;
    vector<string> block;
    bool foundAny = false;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isMyProperty = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Owner Username : " + ownerUsername) { isMyProperty = true; break; }
            }

            if (isMyProperty)
            {
                for (const string& blockLine : block) cout << blockLine << endl;
                cout << "----------------------" << endl;
                foundAny = true;
            }

            block.clear();
        }
        else block.push_back(line);
    }

    propertyFile.close();

    if (!foundAny) cout << "You have no properties listed yet." << endl;
}


// ===================== Check if a Property ID exists =====================
bool propertyIDExists(const string& propertyID)
{
    vector<Property> properties = loadProperties();

    for (Property& p : properties)
    {
        if (p.propertyID == propertyID)
        {
            return true;
        }
    }

    return false;
}


// ===================== Owner Main Menu =====================
void owner_main()
{
    string choice;

    static vector<owner_details> owners;
    static owner_details ownerLogin;

    cout << "#########################" << endl;
    cout << "       Owner Menu" << endl;
    cout << "#########################" << endl;

    cout << "1. Owner Registration" << endl;
    cout << "2. Owner Login" << endl;
    cout << "3. View Profile" << endl;
    cout << "4. Update Profile" << endl;
    cout << "5. Add Property" << endl;
    cout << "6. Update Property" << endl;
    cout << "7. Delete Property" << endl;
    cout << "8. View My Properties" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == "1")
    {
        owner_registration();
    }
    else if (choice == "2")
    {
        owners = loadOwners();
        OwnerLogin(owners, ownerLogin);
    }
    else if (choice == "3")
    {
        owner_view_profile(ownerLogin);
    }
    else if (choice == "4")
    {
        updateOwnerProfile(ownerLogin.OwnerUserName);
    }
    else if (choice == "5")
    {
        addProperty(ownerLogin.OwnerUserName);
    }
    else if (choice == "6")
    {
        updateProperty(ownerLogin.OwnerUserName);
    }
    else if (choice == "7")
    {
        deleteProperty(ownerLogin.OwnerUserName);
    }
    else if (choice == "8")
    {
        viewMyProperties(ownerLogin.OwnerUserName);
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}
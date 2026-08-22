#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
#include<cstdlib>   //system() to create the "data" folder
using namespace std;




// ===================== Helper: validate name =====================
bool is_owner_name(string name)
{
    if (name.empty())
    {
        return false;
    }

    for (char own : name)
    {
        if (!isalpha(own) && own != ' ')
        {
            return false;
        }
    }

    return true;
}


// ===================== Helper: check if a Property ID already exists =====================
bool propertyIDExists(const string& propertyID)
{
    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        return false; // no file yet = no properties yet = no duplicate possible
    }

    string line;

    while (getline(propertyFile, line))
    {
        if (line == "Property ID : " + propertyID)
        {
            propertyFile.close();
            return true;
        }
    }

    propertyFile.close();
    return false;
}


// ===================== Helper: load all owners from file into a vector =====================
vector<owner_details> loadOwners()
{
    vector<owner_details> owners;
    ifstream ownerFile("accomendation listing and search/data/owner.txt");

    if (!ownerFile.is_open())
    {
        return owners; // empty — no owners registered yet
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
        else if (line.find("User Name : ") == 0)
        {
            current.OwnerUserName = line.substr(12);
        }
        else if (line.find("Password : ") == 0)
        {
            current.OwnerPassWord = line.substr(11);
        }
    }

    ownerFile.close();
    return owners;
}


// ===================== Owner Registration =====================
void owner_registration()
{
    owner_details owner;

    // Validate name — keep asking until valid (fixed: this used to not loop)
    bool validName;
    do
    {
        cout << "Enter your Name : ";
        cin >> owner.name;

        validName = is_owner_name(owner.name);

        if (!validName)
        {
            cout << "Please enter a valid name (letters and spaces only)." << endl;
        }

    } while (!validName);


    cout << "Enter your Email : " << endl;
    cin >> owner.email;


    // Validate phone number — digits only
    bool validOwnerPhoneNmbr;

    do
    {
        cout << "Enter the Your Phone Number : " << endl;
        cin >> owner.OwnerphoneNumber;

        validOwnerPhoneNmbr = true;

        for (char digit : owner.OwnerphoneNumber)
        {
            if (!isdigit(digit))
            {
                validOwnerPhoneNmbr = false;
                break;
            }
        }

        if (!validOwnerPhoneNmbr)
        {
            cout << "Please Enter the number only" << endl;
        }

    } while (!validOwnerPhoneNmbr);


    // Address (can contain spaces, so use getline)
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline/buffer
    cout << "Enter your Address : " << endl;
    getline(cin, owner.owner_address);


    // Username and password
    cout << "Enter the User Name : " << endl;
    cin >> owner.OwnerUserName;

    cout << "Enter your Strong Password : " << endl;
    cin >> owner.OwnerPassWord;


    // Create data folder if it doesn't exist
    system("mkdir \"accomendation listing and search\\data\" 2> nul");

    // FIXED: filename now matches what updateOwnerProfile() reads ("owner.txt")
    ofstream OwnerFile("accomendation listing and search/data/owner.txt", ios::out | ios::app);

    if (!OwnerFile.is_open())
    {
        cout << "Error: Could not open file to save data!" << endl;
        return;
    }

    // FIXED: labels now match exactly what updateOwnerProfile() searches for
    OwnerFile << "Name : " << owner.name << endl;
    OwnerFile << "Email : " << owner.email << endl;
    OwnerFile << "Phone Number : " << owner.OwnerphoneNumber << endl;
    OwnerFile << "Address : " << owner.owner_address << endl;       // removed leading space
    OwnerFile << "User Name : " << owner.OwnerUserName << endl;     // capital N to match update check
    OwnerFile << "Password : " << owner.OwnerPassWord << endl;      // matches update check now

    // FIXED: separator now matches exactly what updateOwnerProfile() checks for (22 dashes)
    OwnerFile << "----------------------" << endl;
    OwnerFile.close();

    cout << "Your Data Successfully added " << endl;
}


// ===================== Owner Login =====================
bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin)
{
    cout << "Enter your User Name : " << endl;
    string OwnerloginName;
    cin >> OwnerloginName;

    cout << "Enter your Password : " << endl;
    string OwnerloginPassword;
    cin >> OwnerloginPassword;

    for (owner_details& owner : owners)
    {
        if (owner.OwnerUserName == OwnerloginName && owner.OwnerPassWord == OwnerloginPassword)
        {
            ownerLogin = owner;
            cout << "You login successful\n";
            return true;
        }
    }

    cout << "\nInvalid username or password." << endl;
    return false;
}


// ===================== View Profile =====================
void owner_view_profile(owner_details& ownerLogin)
{
    cout << "\n===== Registered Profile (Owner) =====" << endl;
    cout << "Name : " << ownerLogin.name << endl;
    cout << "Email : " << ownerLogin.email << endl;
    cout << "Phone Number : " << ownerLogin.OwnerphoneNumber << endl;
    cout << "Address : " << ownerLogin.owner_address << endl;
    cout << "User Name : " << ownerLogin.OwnerUserName << endl;
}


// ===================== Update Owner Profile =====================
void updateOwnerProfile(const string& username)
{
    int choice;

    string newName;
    string newEmail;
    string newPhone;
    string newPassword;
    string newAddress;

    cout << "\n========== Update Profile ==========" << endl;

    cout << "\n1. Update Name" << endl;
    cout << "2. Update Email" << endl;
    cout << "3. Update Phone Number" << endl;
    cout << "4. Update Password" << endl;
    cout << "5. Update Address" << endl;

    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // clear leftover newline so getline() works correctly below

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
    else if (choice == 5)
    {
        cout << "Enter new address: ";
        getline(cin, newAddress);
    }
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream ownerFile("accomendation listing and search/data/owner.txt");

    if (!ownerFile.is_open())
    {
        cout << "ERROR: owner.txt not found. Nothing to update." << endl;
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
            bool isTargetOwner = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "User Name : " + username)   // FIXED: capital N
                {
                    isTargetOwner = true;
                    break;
                }
            }

            if (isTargetOwner)
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
                    else if (choice == 4 && blockLine.find("Password : ") == 0)   // FIXED: matches registration label
                    {
                        blockLine = "Password : " + newPassword;
                        updated = true;
                    }
                    else if (choice == 5 && blockLine.find("Address : ") == 0)
                    {
                        blockLine = "Address : " + newAddress;
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

    ownerFile.close();
    tempFile.close();

    remove("accomendation listing and search/data/owner.txt");
    rename("accomendation listing and search/data/temp_owner.txt", "accomendation listing and search/data/owner.txt");

    if (updated)
    {
        cout << "\nProfile updated successfully!" << endl;
    }
    else
    {
        cout << "\nOwner username not found." << endl;
    }
}


// ===================== Add Property =====================
void addProperty(const string& ownerUsername)
{
    string propertyID;
    string homeName;
    string room;
    string roomType;
    string address;
    string price;
    string description;

    cout << "\n========== Add New Property ==========" << endl;

    do
    {
        cout << "Enter Property ID (e.g. P004): ";
        cin >> propertyID;

        if (propertyIDExists(propertyID))
        {
            cout << "That Property ID is already taken. Please choose a different one.\n" << endl;
        }

    } while (propertyIDExists(propertyID));

    cin.ignore();

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
    ifstream propertyFile("accomendation listing and search/data/property.txt");

    if (!propertyFile.is_open())
    {
        cout << "ERROR: property.txt not found." << endl;
        return;
    }

    string line;
    vector<string> block;
    bool foundAny = false;

    cout << "\n========== My Properties ==========" << endl;

    while (getline(propertyFile, line))
    {
        if (line == "----------------------")
        {
            bool isOwnedByMe = false;

            for (const string& blockLine : block)
            {
                if (blockLine == "Owner Username : " + ownerUsername)
                {
                    isOwnedByMe = true;
                    break;
                }
            }

            if (isOwnedByMe)
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
        cout << "You have no properties listed yet." << endl;
    }
}


// ===================== Owner Main Menu =====================
void owner_main()
{
    owner_details loggedInOwner;
    bool isLoggedIn = false;

    while (true)
    {
        cout << "==============================" << endl;
        cout << "       Owner Menu" << endl;
        cout << "==============================" << endl;

        cout << "1. Owner Registration" << endl;
        cout << "2. Owner Login" << endl;
        cout << "3. View Profile" << endl;
        cout << "4. Update Profile" << endl;
        cout << "5. Add Property" << endl;
        cout << "6. Update Property" << endl;
        cout << "7. Delete Property" << endl;
        cout << "8. View My Properties" << endl;
        cout << "9. Back to Main Menu" << endl;

        string choice;
        cout << "Enter your choice : ";
        cin >> choice;

            if (choice == "1")
            {
                owner_registration();
            }
            else if (choice == "2")
            {
                vector<owner_details> owners = loadOwners();
                isLoggedIn = OwnerLogin(owners, loggedInOwner);
            }
            else if (choice == "3")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    owner_view_profile(loggedInOwner);
                }
            }
            else if (choice == "4")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    updateOwnerProfile(loggedInOwner.OwnerUserName);
                }
            }
            else if (choice == "5")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    addProperty(loggedInOwner.OwnerUserName);
                }
            }
            else if (choice == "6")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    updateProperty(loggedInOwner.OwnerUserName);
                }
            }
            else if (choice == "7")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    deleteProperty(loggedInOwner.OwnerUserName);
                }
            }
            else if (choice == "8")
            {
                if (!isLoggedIn)
                {
                    cout << "Please login first (option 2)." << endl;
                }
                else
                {
                    viewMyProperties(loggedInOwner.OwnerUserName);
                }
            }
            else if (choice == "9")
            {
                break; // exits the while loop, returns to whatever called owner_main()
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            } 
    }
}
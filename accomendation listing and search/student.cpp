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


    //    students.push_back(s);


    //  ================================================================
    //  BUG FIX #2 (this is the real cause of "file not saving"):
    //  ofstream does NOT create missing folders. If "data/" doesn't
    //  exist next to the running executable, the file open silently
    //  fails, and the old code never checked for that — it just
    //  printed "Your details added Successfully" regardless.
    //  ================================================================

    // Make sure the "data" folder exists before we try to write into it.
    // NOTE: std::filesystem is broken on MinGW 8.1.0 (a known compiler bug),
    // so we use a plain system() call instead — works everywhere, no
    // special headers needed.
    // Folder now lives INSIDE "accomendation listing and search/data"
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

    cout << "Please Enter you user name and Password :";

    cout << "Enter your username: ";
    cin >> inputUserName;

    cout << "Enter your password: ";
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

    cout << "Enter your username: ";
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

    // ================================================================
    // BUG FIX: the old code checked line-by-line top to bottom and only
    // realized "this is the right student" once it hit the "User name : "
    // line. But in the file, "User name :" comes AFTER "Email :" —
    // so by the time the right student was recognized, the Email line
    // (and Name line) had already been copied past unchanged.
    //
    // Fix: read each student's FULL record (5 lines) into a block first,
    // check if that block belongs to the target username, THEN decide
    // which line inside the block to update. This works regardless of
    // what order the fields appear in.
    // ================================================================

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


// ============================================================
// NOTE on the two functions above (StudentLogin, ProfileView):
// Both take a vector<acoomendation_listing_searching>& students
// (or a loggedInStudent reference) as a parameter, but nothing
// in this program currently loads data/student.txt back into
// such a vector. So even after this fix, Login/View/Update
// won't have real data to work with until you add a function
// that reads data/student.txt into a vector at startup.
// That's a separate feature gap from today's bug, flagging it
// so it doesn't surprise you later.
// ============================================================


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
        // BUG FIX #3: "bool StudentLogin();" was a DECLARATION, not a call.
        // It compiled but did nothing. Now we actually call the function.
        StudentLogin(students, loggedInStudent);
    }

    else if(choice == "3")
    {
        // BUG FIX #4: same problem — "void ProfileView();" declared,
        // never called. Fixed to an actual call with the right argument.
        ProfileView(loggedInStudent);
    }

    else if(choice == "4")
    {
        // BUG FIX #5: same problem — now actually calls updateProfile().
        updateProfile();
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

}
#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
using namespace std;

// student.cpp

   struct acoomendation_listing_searching
    {
        string name;
        string email;
        int phoneNumber;
        string userNname;
        string password;

    };


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
  
    vector<acoomendation_listing_searching>students;
    acoomendation_listing_searching s;

    cout << " Enter your name : " << endl;
    cin >> s.name;

    if(checkName(s.name))
    {
        cout << "please put the valid name"<< endl;
    }


    cout << " Enter your email : " << endl;
    cin >> s.email;
    

    cout << "Enter you User Name : " << endl;
    cin >> s.userNname;

    cout << "Enter your Password : " << endl;
    cin >> s.password;


    cout << "Enter your Phone Number : " << endl;
    cin >> s.phoneNumber;

    if (isdigit(s.phoneNumber))
    {
        cout << " it is not valid input"<<endl;
    }

   students.push_back(s);
  
   cout << "Your details added Scuessfully ";



 //    file handle system to store the data
   
   ofstream studentFile("data/student.tx" , ios::out | ios::app);


   studentFile << "Name : " << s.name << endl;
   studentFile << "Email : " << s.email << endl;
   studentFile << "User name : " << s.userNname << endl;
   studentFile << "PassWord : " << s.password << endl;
   studentFile << "Phone Number : " << s.phoneNumber << endl;

   studentFile << "----------------------" << endl;
   
   studentFile.close();
   
    
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
    ifstream studentFile("data/student.txt");

    // Create a temporary file for the updated data
    ofstream tempFile("data/temp.txt");

    string line;

    bool correctStudent = false;
    bool updated = false;


    // Read the file line by line
    while (getline(studentFile, line))
    {
        // Check if this is the student's username
        if (line == "User name : " + username)
        {
            correctStudent = true;
        }


        // Change only the selected information
        if (correctStudent && choice == 1)
        {
            if (line.find("Name : ") == 0)
            {
                line = "Name : " + newName;
                updated = true;
            }
        }
        else if (correctStudent && choice == 2)
        {
            if (line.find("Email : ") == 0)
            {
                line = "Email : " + newEmail;
                updated = true;
            }
        }
        else if (correctStudent && choice == 3)
        {
            if (line.find("Phone Number : ") == 0)
            {
                line = "Phone Number : " + newPhone;
                updated = true;
            }
        }
        else if (correctStudent && choice == 4)
        {
            if (line.find("Password : ") == 0)
            {
                line = "Password : " + newPassword;
                updated = true;
            }
        }


        // Write the line into the temporary file
        tempFile << line << endl;


        // When we reach the end of this student's record,
        // stop searching for this student.
        if (line == "----------------------")
        {
            correctStudent = false;
        }
    }


    studentFile.close();
    tempFile.close();


    // Replace the old file with the updated file
    remove("data/student.txt");
    rename("data/temp.txt", "data/student.txt");


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





void studentMenu()
{
    string choice;

    cout << "==============================" << endl;
    cout << "       Student Menu" << endl;
    cout << "==============================" << endl;

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
        bool StudentLogin();
    }

    else if(choice == "3")
    {
        void ProfileView();
    }

    else if(choice == "4")
    {
        void updateProfile();

    }





}




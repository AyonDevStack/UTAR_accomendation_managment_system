    #include <bits/stdc++.h>
    #include "accomedation.h"

    using namespace std;

    void studentEnquiryMenu()
    {
        vector<acoomendation_listing_searching> students = loadStudents();
        acoomendation_listing_searching loggedInStudent;
        bool loginSuccess = StudentLogin(students, loggedInStudent);

        if (!loginSuccess)
        {
            return;
        }

        cout << "\nWelcome, " << loggedInStudent.name << "!\n";

        string choice_stu_enq;

        do
        {
            cout << R"(
            ===== Student Enquiry Menu =====
            1. Send Enquiry to Owner
            2. View My Enquiries
            3. Back
            )";

            cout << "Enter Your Choice : ";
            cin >> choice_stu_enq;

            if (choice_stu_enq == "1")
            {

                sendEnquiry(loggedInStudent);

            }
            else if (choice_stu_enq == "2")
            {

                viewMyEnquiries(loggedInStudent);
            }
            else if (choice_stu_enq == "3")
            {

                cout << "Returning...\n";

            }
            else
            {
                cout << "Invalid choice.\n";

            }

        } while (choice_stu_enq != "3");
    }

   vector<Enquiry> loadEnquiries()
{
    vector<Enquiry> enquiries;
    ifstream enquiryFile("communication apoitment/data/communication.txt");

    if (!enquiryFile.is_open())
    {
        return enquiries;
    }

    string line;
    Enquiry current;
    bool hasData = false;

    while (getline(enquiryFile, line))
    {
        if (line == "----------------------")
        {
            if (hasData)
            {
                enquiries.push_back(current);
            }
            current = Enquiry();
            hasData = false;
        }
        else if (line.find("Enquiry ID : ") == 0)
        {
            string label = "Enquiry ID : ";
            current.enquiryID = (line.length() > label.length()) ? line.substr(label.length()) : "";
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
        else if (line.find("Message : ") == 0)
        {
            string label = "Message : ";
            current.message = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Reply : ") == 0)
        {
            string label = "Reply : ";
            current.reply = (line.length() > label.length()) ? line.substr(label.length()) : "";
        }
        else if (line.find("Is Replied : ") == 0)
        {
            string label = "Is Replied : ";
            current.isReplied = (line.length() > label.length()) ? (line.substr(label.length()) == "1") : false;
        }
    }

    if (hasData)
    {
        enquiries.push_back(current);
    }

    enquiryFile.close();
    return enquiries;
}

    void saveEnquiries(vector<Enquiry>& enquiries)
    {
        system("mkdir \"communication apoitment\\data\" 2> nul");

        ofstream enquiryFile("communication apoitment/data/communication.txt");

        for (Enquiry& e : enquiries)
        {
            enquiryFile << "Enquiry ID : " << e.enquiryID << "\n";
            enquiryFile << "Student Username : " << e.studentUserName << "\n";
            enquiryFile << "Owner Username : " << e.ownerUserName << "\n";
            enquiryFile << "Property ID : " << e.propertyID << "\n";
            enquiryFile << "Message : " << e.message << "\n";
            enquiryFile << "Reply : " << e.reply << "\n";
            enquiryFile << "Is Replied : " << (e.isReplied ? "1" : "0") << "\n";
            enquiryFile << "----------------------\n";
        }

        enquiryFile.close();
    }







    //send the enquires parts start

    void sendEnquiry(acoomendation_listing_searching& loggedInStudent)
    {
        // Step 1: load existing properties so we can look up the owner
        vector<Property> properties = loadProperties();   // assumes this already exists from your property module

        string propertyID;
        cout << "Enter Property ID you want to enquire about: ";
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

        // Step 3: get the message
        cin.ignore();   // clear leftover newline before getline
        string message;
        cout << "Enter your message: ";
        getline(cin, message);

        // Step 4: load existing enquiries, generate new ID
        vector<Enquiry> enquiries = loadEnquiries();

        int newIDNum = enquiries.empty() ? 1 : stoi(enquiries.back().enquiryID) + 1;
        string newEnquiryID = to_string(newIDNum);

        // Step 5: build the new enquiry
        Enquiry newEnquiry;
        newEnquiry.enquiryID = newEnquiryID;
        newEnquiry.studentUserName = loggedInStudent.userNname;
        newEnquiry.ownerUserName = ownerUsername;
        newEnquiry.propertyID = propertyID;
        newEnquiry.message = message;
        newEnquiry.reply = "";
        newEnquiry.isReplied = false;

        // Step 6: save
        enquiries.push_back(newEnquiry);
        saveEnquiries(enquiries);

        cout << "Enquiry sent successfully!\n";
    }
    // send the enquires part end


    void viewMyEnquiries(acoomendation_listing_searching& loggedInStudent)
    {
        vector<Enquiry> enquiries = loadEnquiries();
        bool foundAny = false;

        cout << "\n===== My Enquiries =====\n";

        for (Enquiry& e : enquiries)
        {
            if (e.studentUserName == loggedInStudent.userNname)
            {
                foundAny = true;
                cout << "-----------------------------\n";
                cout << "Enquiry ID   : " << e.enquiryID << "\n";
                cout << "Property ID  : " << e.propertyID << "\n";
                cout << "Owner        : " << e.ownerUserName << "\n";
                cout << "Message      : " << e.message << "\n";
                if (e.isReplied)
                    cout << "Reply        : " << e.reply << "\n";
                else
                    cout << "Reply        : (No reply yet)\n";
            }
        }

        if (!foundAny)
        {
            cout << "You have not sent any enquiries yet.\n";
        }

        cout << "-----------------------------\n";
    }
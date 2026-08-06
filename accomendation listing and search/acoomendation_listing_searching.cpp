#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;


   struct acoomendation_listing_searching
    {
        string name;
        string email;
        string phoneNumber;
        string userNname;
        string password;

    };
    




void student_registration()
{
  
    vector<acoomendation_listing_searching>students;
    acoomendation_listing_searching s;

    cout << " Enter your name : " << endl;
    cin >> s.name;


    cout << " Enter your email : " << endl;
    cin >> s.email;
    

    cout << "Enter you User Name : " << endl;
    cin >> s.userNname;


    cout << "Enter your Phone Number : " << endl;
    cin >> s.phoneNumber;

}





// main student list to what to do : 

void accommodationListingAndSearching(){


  cout << R"(
  
  
  
    ==============================
        Accommodation Listing
    ==============================

        1. Student Registration
        2. Student Login
        3. View Profile
        4. Update Profile
        5. Add Property
        6. Update Property
        7. Search Property
        8. Shortlist House
        9. Back to Main Menu
  
  )";

  string choice ;


  if ( choice == "1")
  {

    student_registration();

  }





        


}



int accomendation_main()
{
    accommodationListingAndSearching();


    return 0;
}
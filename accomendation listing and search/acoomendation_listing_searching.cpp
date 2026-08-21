#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;


// accommodationListingAndSearching.cpp

// part Start:   main student list to what to do : 

void accommodationListingAndSearching(){ 


  cout << R"(
  
  
  
    ==============================
        Accommodation Listing
    ==============================

         Choice Who you are : 

            1. Student
            2. Property Manager / Owner
            3. Back to Main Menu
                
  )";

    cout << "Enter your choice: ";
      string choice ;
    cin >> choice;

    if ( choice == "1")
  {

    studentMenu();

  }
  
  else if(choice == "2")
  {
    
    owner_main();
     
  }




        


}
// part End:   main student list to what to do : 



int accomendation_main()
{
    accommodationListingAndSearching();


    return 0;
}
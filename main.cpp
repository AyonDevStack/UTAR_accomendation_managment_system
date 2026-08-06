#include<bits/stdc++.h>
#include "accomedation.h"

using namespace std;


void accommodationListingAndSearching();



int main()
{
 cout << R"(
 
 
         Welcome to UTAR Accommodation Management System
       ===================================================
         *** Select the Number as an option ***
 
         1. Accommodation Listing & Searching 
         2. Communication for Management
         3. Rental Management 

 
 )";

  
   string choice;
   cout << "Enter you option : " ;

   cin >> choice;


   if(choice == "1")
   {

    accommodationListingAndSearching(); 
   
   
   
   }



   return 0;
}
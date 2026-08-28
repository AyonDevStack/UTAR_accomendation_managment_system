#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;





void communication_appoitment()
{


  cout << R"(
  
         ######### Please do Login ######### 
           
           1. Student 
           2. Property Manager / Owner
           3. Back to Main Menu
  
  
  )";


     string commu_choice;
     cout << "Enter your Choice : " ;
     cin >> commu_choice;

     if(commu_choice == "1")
     {
          studentEnquiryMenu();

     }
     else if(commu_choice == "2")
     {
          owner_main_enquire();

     }
     else if(commu_choice == "3"){
           return; 
     }               
    else
    {
        cout << "Invalid choice.\n";
    }


}


int main_communnication()
{

void communication_appoitment();

}
#include<bits/stdc++.h>
#include "accomedation.h"
#include<fstream>
#include<cstdlib>   //system() to create the "data" folder
using namespace std;


// owener.cpp



// create the function to check the function is working or not//
bool is_owner_name(string name)
{

     if(name.empty())
     {
        return false;
     }
     
      for(char own : name)
      {
            if(!isalpha(own) && own !=' ')
            {
                   return false;
            }


      }


       return true;

}


// owner registration function : start//

void owner_registration()
{

    owner_details owner;

    cout << "Enter your Name : " ; 
    cin >> owner.name;

    if( !is_owner_name(owner.name))
    {
           cout << "Please enter the valid name" << endl;
         
    }
    
  
    // asked for email :
    cout << "Enter your Email : " << endl;
    cin >> owner.email;



    // asked for phone number : 
      
    bool validOwnerPhoneNmbr;

    do{
        
       cout << "Enter the Your Phone Number : " << endl;
       cin >> owner.OwnerphoneNumber;

       validOwnerPhoneNmbr = true;
        
  
       for(char digit : owner.OwnerphoneNumber)
       {
  
         if(!isdigit(digit)){
    
            validOwnerPhoneNmbr=false;
            break;
       }


       }


          if(!validOwnerPhoneNmbr)
          {
              cout << "Please Enter the number only" << endl;
          }
    




    } while (!validOwnerPhoneNmbr);


    
    
    // asking for the creating the addrees:
     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline/buffer
    cout << "Enter your Address : " << endl;
    getline(cin, owner.owner_address);

    
    // asking for create username and password;

    cout << "Enter the User Name : " << endl;
    cin >>owner.OwnerUserName;

    cout << "Enter your Strong Password : " << endl;
    cin >>owner.OwnerPassWord;


    // this is the system command that create the Data folder 

    system("mkdir \"accomendation listing and search\\data\" 2> nul");
    ofstream OwnerFile("accomendation listing and search/data/Owner_file.txt", ios::out | ios::app);

        if (!OwnerFile.is_open())
        {
            cout << "Error: Could not open file to save data!" << endl;
            return;
        }

    OwnerFile << "Name : " << owner.name << endl;
    OwnerFile << "Email : " << owner.email << endl;
    OwnerFile << "Phone Number : " << owner.OwnerphoneNumber << endl;
    OwnerFile << " Address : " << owner.owner_address << endl;
    OwnerFile << "User Name : " << owner.OwnerUserName << endl;
    OwnerFile << "Password : " << owner.OwnerPassWord << endl;
   
    OwnerFile << "-----------------------------------" << endl;
    OwnerFile.close();

    cout << "Your Data Sucessfully added " << endl;


}

// owner registration function : End//




// owner Login start 



bool OwnerLogin(vector<owner_details>& owners, owner_details& ownerLogin)
{
    cout << "Add your User Name : " << endl;
    string OwnerloginName;
    cin >> OwnerloginName;

    cout << "Add you password Name : " << endl;
    string OwnerloginPassword;
    cin >> OwnerloginPassword;

    for (owner_details &owner : owners)
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


// owner login end 


void owner_view_profile(owner_details& ownerLogin)
{

      cout << "Register Profile as a Owener : " << endl;

      cout << " Name : " << ownerLogin.name << endl;
      cout << "Email : " << ownerLogin.email << endl;
      cout << "Phone Number : " << ownerLogin.OwnerphoneNumber << endl;
      cout << "Address : " << ownerLogin.owner_address << endl;
      cout << "User Name : " << ownerLogin.OwnerUserName << endl;



}





void owner_main(){



    cout << "==============================" << endl;
    cout << "       Student Menu" << endl;
    cout << "==============================" << endl;

        cout << "1. Owner Registration" << endl;
        cout << "2. Owner Login" << endl;
        cout << "3. View Profile" << endl;
        cout << "4. Update Profile" << endl;
        cout << "5. Add Property" << endl;
        cout << "6. Update Property" << endl;
        cout << "7. Delete Property" << endl;
        cout << "8. View My Properties" << endl;
        cout << "9. View the Appoitment " << endl;

    
        string choice;

        cout << "Enter your choice : " ;
        cin >> choice;


        if(choice == "1")
        {

            owner_registration();
        }

        else if(choice == "2")
        {
            bool OwnerLogin();       
         
        }





}
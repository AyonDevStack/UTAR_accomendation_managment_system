#include<bits/stdc++.h>
#include "accomedation.h"
using namespace std;


void showTotalListings()
{
    vector<Property> properties = loadProperties();
    cout << "\n===== Total Listings =====\n";
    cout << "Total number of properties listed: " << properties.size() << "\n";
}


void showAveragePrice()
{
    vector<Property> properties = loadProperties();

    if (properties.empty())
    {
        cout << "\nNo properties available to calculate average price.\n";
        return;
    }

    double total = 0;

    for (Property& p : properties)
    {
        total += stod(p.price);   // stod reads the leading number, stops at "RM"
    }

    double average = total / properties.size();

    cout << "\n===== Average Rental Price =====\n";
    cout << "Average price across " << properties.size() << " listing(s): RM " << average << "\n";
}


void showPropertyTypeBreakdown()
{
    vector<Property> properties = loadProperties();

    if (properties.empty())
    {
        cout << "\nNo properties available.\n";
        return;
    }

    map<string, int> typeCount;

    for (Property& p : properties)
    {
        typeCount[p.roomType]++;
    }

    cout << "\n===== Property Type Breakdown =====\n";
    for (auto& pair : typeCount)
    {
        cout << pair.first << " : " << pair.second << " listing(s)\n";
    }
}

void showDistanceStats()
{
    vector<Property> properties = loadProperties();

    if (properties.empty())
    {
        cout << "\nNo properties available.\n";
        return;
    }

    double totalDistance = 0;
    double closest = properties[0].distanceFromUTAR;
    double farthest = properties[0].distanceFromUTAR;

    for (Property& p : properties)
    {
        totalDistance += p.distanceFromUTAR;

        if (p.distanceFromUTAR < closest)
            closest = p.distanceFromUTAR;

        if (p.distanceFromUTAR > farthest)
            farthest = p.distanceFromUTAR;
    }

    double average = totalDistance / properties.size();

    cout << "\n===== Distance from UTAR =====\n";
    cout << "Average distance : " << average << " km\n";
    cout << "Closest property  : " << closest << " km\n";
    cout << "Farthest property : " << farthest << " km\n";
}

void showShortlistStats()
{
    ifstream shortlistFile("accomendation listing and search/data/shortlist.txt");

    if (!shortlistFile.is_open())
    {
        cout << "\nNo shortlist data found yet.\n";
        return;
    }

    string line;
    map<string, int> propertyShortlistCount;
    int totalShortlists = 0;
    string currentPropertyID;

    while (getline(shortlistFile, line))
    {
        if (line.find("Property ID : ") == 0)
        {
            currentPropertyID = line.substr(14);
            propertyShortlistCount[currentPropertyID]++;
            totalShortlists++;
        }
    }

    shortlistFile.close();

    cout << "\n===== Shortlisted Student Statistics =====\n";
    cout << "Total shortlist entries: " << totalShortlists << "\n";

    for (auto& pair : propertyShortlistCount)
    {
        cout << "Property " << pair.first << " shortlisted by " << pair.second << " student(s)\n";
    }
}


void propertyInsightsMenu()
{
    string choice;

    do
    {
        cout << "\n===== Property Insights & Statistics =====\n";
        cout << "1. Total Listings\n";
        cout << "2. Average Rental Price\n";
        cout << "3. Property Type Breakdown\n";
        cout << "4. Distance from UTAR\n";
        cout << "5. Shortlisted Student Statistics\n";
        cout << "6. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") showTotalListings();
        else if (choice == "2") showAveragePrice();
        else if (choice == "3") showPropertyTypeBreakdown();
        else if (choice == "4") showDistanceStats();
        else if (choice == "5") showShortlistStats();
        else if (choice == "6") cout << "Returning...\n";
        else cout << "Invalid choice.\n";

    } while (choice != "6");
}
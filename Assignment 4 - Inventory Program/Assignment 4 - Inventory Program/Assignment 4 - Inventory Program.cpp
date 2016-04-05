// Assignment 4 - Inventory Program.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// Declare 'tm' structure 'my_time' and use it to set constant intervals for the current year, month, and date.
// This will be used later in the 'add_record' function for input validation. 
 /*
 const int curyear = 16;
 const int curmon = 04;
 const int curday = 05;*/
// The following code allows the compiler to utilize current date & time without specifying integers, but it 
// requires the user to set the SDL Checks option to "No". I've included some lines of code to use in lieu of
// the time/date variables above this paragraph. Simply comment out the next 5 lines of code and uncomment the
// three lines of code before this set of notes if you don't wish to do that. 
 time_t t = time(NULL);
 tm* timePtr = localtime(&t);
 const int curyear = ((timePtr->tm_year)%100);
 const int curmon = ((timePtr->tm_mon)+1);
 const int curday = timePtr->tm_mday;

 const int description_size = 32;

struct inventory_bin
{
	char Description[description_size]; // Item Description
	int quant; // Quantity in inventory
	double Whlslcost; // Wholesale Cost
	double Retprice; // Retail Price
	int date_added_year; // Year added to inventory.
	int date_added_month; // Month added to inventory.
	int date_added_day; // Day added to inventory.

};

void add_record(fstream &);
void display_record(fstream &);
void mod_record(fstream &);



int main()
{
	char Again = 'y';
	fstream inventoryfile;
	int user_choice;
	
	do{
		// Query user to see what they would like to do. 
		cout << curyear << endl;
		cout << curmon << endl;
		cout << curday << endl;
		cout << "Good morning, human meatbag. Please select a choice from the following menu.\n1. Add an inventory record.\n2. Display an inventory record.\n3. Modify an inventory record.\n4. Quit the program.\n";
		cout << "Please enter your selection:  ";
		cin >> user_choice;
		// Input validation. User cannot input a value less than 1 or greater than 4. 
		while(user_choice < 1 || user_choice > 4)
		{
			cout << "ERROR! INPUT INVALID!\nPlease select from the valid menu options by entering a number between 1 and 4.\n\n>>>>>>> ";
			cin >> user_choice;
		}

		// Use 'switch' function to have the program respond to the separate cases of user_choice values.
		switch(user_choice)
		{
		// Call the add_record function if the user selects option 1.
		case 1:
			add_record(inventoryfile);
			break;
		// Call the display_record function if the user selects option 2.
		case 2:
			display_record(inventoryfile);
			break;
		// Call the mod_record function if the user selects option 3.
		case 3:
			mod_record(inventoryfile);
			break;
		// Set 'Again' equal to 'n' if the user decides to quit the program. 
		case 4:
			Again = 'n';
			break;
		}



		// Query the user to see if they would like to repeat the program. 
		cout << "\n\nWell, that was fun.\nWould you like to run the program again? (enter 'y' for 'yes' and any other input for 'no')\n\n>>>>>>   ";
		cin >> Again;
		// Clear the console if they wish to repeat the program. 
		if (tolower(Again) == 'y')
			system("cls");
		// Close the while loop.

	}while(toupper(Again)=='Y');

	return 0;
}

void add_record(fstream &inventoryfile)
{
	// Declare 'inventory_bin' called "record".
	inventory_bin record;
	// Open the data structure in read, write, and binary mode.
	inventoryfile.open("inventory.dat", ios::out | ios::app | ios::binary);
	// Set the program to indicate if the record failed to open. 
	if(inventoryfile.fail())
	{
		cout << "Error opening file.\nExiting...\n\n";
		exit(EXIT_FAILURE);
	}
	// Clear the CIN object.
	cin.get();
	// Indicate that the user is about to enter data.
	cout << "Enter the following inventory data when prompted.\n";
	// Query the user for a Description. 
	cout << "Description (No more than 32 characters, please.):  ";
	// Take the input of the cin object and apply it to "Description".
	cin.getline(record.Description, 32);
	// Request the quantity.
	cout << "\nPlease enter the quantity.\nQuantity:  ";
	// Take the quantity input. 
	cin >> record.quant;
	while(record.quant <0)
	{
		cout << "\nI'm sorry. You must enter a value of 0 or greater.\nQuantity:  ";
		cin >> record.quant;
	}
	// Take wholesale cost.
	cout << "\nPlease enter the wholesale cost of the item.\nWholesale Cost:  ";
	cin >> record.Whlslcost;
	while(record.Whlslcost <0)
	{
		cout << "\nI'm sorry. You must enter a value of 0 or greater.\nWholesale Cost:  ";
		cin >> record.Whlslcost;
	}
	// Get the retail price.
	cout << "\nPlease enter the retail price of the item.\nRetail Price:  ";
	cin >> record.Retprice;
	while(record.Retprice < 0)
	{
		cout << "\nI'm sorry. You must enter a value of 0 or greater.\nRetail Price:  ";
		cin >> record.Retprice;
	}
	// Get the year added to inventory.
	cout << "\nPlease enter the 2-digit year that the item is being added to inventory.\nYear:  ";
	cin >> record.date_added_year;
	while(record.date_added_year > curyear){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT YEAR!\nPlease enter the 2-digit year that the item is being added to inventory.\nYear: ";
		cin >> record.date_added_year;
	}
	// Get the month added.
	cout << "\nPlease enter the 2-digit month that the item is being added to inventory.\nMonth:  ";
	cin >> record.date_added_month;
	while(record.date_added_month > curmon){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT MONTH!\nPlease enter the 2-digit month that the item is being added to inventory.\nMonth: ";
		cin >> record.date_added_month;
	}
	// Get the day of the month added to inventory.
	cout << "\nPlease enter the 2-digit day of the month that the item is being added to inventory.\nDay:  ";
	cin >> record.date_added_day;
	while(record.date_added_day > curday){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT DAY!\nPlease enter the 2-digit month that the item is being added to inventory.\nDay: ";
		cin >> record.date_added_day;
	}	
	// Write the record to the save file. 
	inventoryfile.write(reinterpret_cast<char *>(&record), sizeof(record));

	// Account for an error in writing the file. 
	if(inventoryfile.fail())
		cout << "\nError: Failed writing to the file.\n\n";
	else
		cout << "\nSuccess: Record written to the file.\n\n";

	// Close the file. 
	inventoryfile.close();
}

void display_record(fstream &inventoryfile)
{
	inventory_bin record;

	// Declare variable to store the record number.
	long recnum;

	// Open the file.
	inventoryfile.open("inventory.dat", ios::in | ios::binary);

	// Exit if an error occurs.
	if(inventoryfile.fail())
	{
		cout << "ERROR: File could not be opened.\n";
		exit(EXIT_FAILURE);
	}
	
	// Get the record number.
	cout << "\nEnter the record number you wish to view. \n\nRecord #:  ";
	cin >> recnum;

	// Look up the record.
	inventoryfile.seekg(recnum * sizeof(record), ios::beg);
	if (inventoryfile.fail())
	{
		cout << "\nERROR: Record could not be located.\n";
		inventoryfile.close();
		return;
	}

	// Read the record.
	inventoryfile.read(reinterpret_cast<char *>(&record), sizeof(record));
	inventoryfile.close();

	// Display the data in the record.
	cout << "\nDescription: " << record.Description << endl;
	cout << "Quantity: " << record.quant << endl;
	cout << "Wholesale cost: " << record.Whlslcost << endl;
	cout << "Retail price: " << record.Retprice << endl;
	cout << "Date added: " << record.date_added_month << "-" << record.date_added_day << "-" << record.date_added_year << endl;
	cout << "Press any key to continue... ";
    cin.get();
}

void mod_record(fstream &inventoryfile)
{
	inventory_bin record;

	// Declare variable to store the record number.
	long recnum;

	// Open the file.
	inventoryfile.open("inventory.dat", ios::in | ios::out | ios::binary);

	// Exit if an error occurs.
	if(inventoryfile.fail())
	{
		cout << "ERROR: File could not be opened.\n";
		exit(EXIT_FAILURE);
	}
	
	// Get the record number.
	cout << "\nEnter the record number you wish to view. \n\nRecord #:  ";
	cin >> recnum;

	// Look up the record.
	inventoryfile.seekg(recnum * sizeof(record), ios::beg);
	if (inventoryfile.fail())
	{
		cout << "\nERROR: Record could not be located.\n";
		inventoryfile.close();
		return;
	}

	// Read the record.
	inventoryfile.read(reinterpret_cast<char *>(&record), sizeof(record));

	// Display the data in the record.
	cout << "\nDescription: " << record.Description << endl;
	cout << "Quantity: " << record.quant << endl;
	cout << "Wholesale cost: " << record.Whlslcost << endl;
	cout << "Retail price: " << record.Retprice << endl;
	cout << "Date added: " << record.date_added_month << "-" << record.date_added_day << "-" << record.date_added_year << endl;
	cout << "Press any key to continue... ";
    cin.get();
	// Indicate that the user is about to enter data.
	cout << "Enter the following inventory data when prompted.\n";
	// Query the user for a Description. 
	cout << "Description (No more than 32 characters, please.):  ";
	// Take the input of the cin object and apply it to "Description".
	cin.getline(record.Description, 32);
	// Request the quantity.
	cout << "\nPlease enter the quantity.\nQuantity:  ";
	// Take the quantity input. 
	cin >> record.quant;
	while(record.quant <0)
	{
		cout << "\nI'm sorry. You must enter a value of 0 or greater.\nQuantity:  ";
		cin >> record.quant;
	}
	// Take wholesale cost.
	cout << "\nPlease enter the wholesale cost of the item.\nWholesale Cost:  ";
	cin >> record.Whlslcost;
	while(record.Whlslcost <0)
	{
		cout << "\nI'm sorry. You must enter a value of 0 or greater.\nWholesale Cost:  ";
		cin >> record.Whlslcost;
	}
	// Get the year added to inventory.
	cout << "\nPlease enter the 2-digit year that the item is being added to inventory.\nYear:  ";
	cin >> record.date_added_year;
	while(record.date_added_year > curyear){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT YEAR!\nPlease enter the 2-digit year that the item is being added to inventory.\nYear: ";
		cin >> record.date_added_year;
	}
	// Get the month added.
	cout << "\nPlease enter the 2-digit month that the item is being added to inventory.\nMonth:  ";
	cin >> record.date_added_month;
	while(record.date_added_month > curmon){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT MONTH!\nPlease enter the 2-digit month that the item is being added to inventory.\nMonth: ";
		cin >> record.date_added_month;
	}
	// Get the day of the month added to inventory.
	cout << "\nPlease enter the 2-digit day of the month that the item is being added to inventory.\nDay:  ";
	cin >> record.date_added_day;
	while(record.date_added_day > curday){
		cout << "ERROR! CANNOT BE LATER THAN CURRENT DAY!\nPlease enter the 2-digit month that the item is being added to inventory.\nDay: ";
		cin >> record.date_added_day;
	}	
	
	// Seek the original record position.
	inventoryfile.seekp(recnum * sizeof(record), ios::beg);
	
	// Write the record to the save file. 
	inventoryfile.write(reinterpret_cast<char *>(&record), sizeof(record));

	// Account for an error in writing the file. 
	if(inventoryfile.fail())
		cout << "\nError: Failed writing to the file.\n\n";
	else
		cout << "\nSuccess: Record written to the file.\n\n";

	// Close the file. 
	inventoryfile.close();

	cout << "Press any key to continue... ";
    cin.get();
}
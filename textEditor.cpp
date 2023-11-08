/***********************************************************
 * COP 4530
 * Fatemah Elsewaky - U29797564
 * Noreen Abdelmaksoud - U14450950
 * March 10, 2023
 * 
 * This is the cpp file for the TextEditor. It contains 
 * the main function that runs the program
 * 
 * ********************************************************/
#include "textEditor.hpp"
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>

//main fuction 
int main() {
  cout<<"Welcome to our Text Editor! ;) "<< endl;
  cout<<"We have two types of editors:\n";
  cout << "1) Simple Text Editor:\n\na) add text to the document\nb) print the document\nc) undo your last action" << endl;
  cout << "\n\n2) Advanced Text Editor:\n\na) add text to the document\nb) print the document\nc) undo your last action\nd) redo your last action" << endl;
  
  cout << "\n\nChoose a text editor by typing 1 or 2: " << endl;

  //Input validation for the selection of an editor
  string choice;
  bool valid_input = false;
  while(!valid_input){
    cin >> choice;
    if (choice == "1" || choice == "2") {
      valid_input = true;
    }
    else{
      cout << "Invalid choice. Please enter 1 or 2: ";
    }
  }

  //converting choice to an integr to create the if-else statements
  int choices = stoi(choice);

  //Simple text editor
  if(choices == 1){
    
    SimpleTextEditor editor;
    
    cout << "Enter '1' to add text to the document" << endl;
    cout << "Enter '2' to print the document" << endl;
    cout << "Enter '3' to undo your last action" << endl;
    cout << "Enter '0' to quit the text editor" << endl;
    
    //Input validation
    string menu;
    bool valid_menu = false;
    int num;
    while (!valid_menu) {
        cout << "Choose an action: ";
        cin >> menu;

        if (menu.length() == 1 && menu[0] >= '0' && menu[0] <= '3') {
          num = menu[0] - '0'; //converting menu to an integer in order to create the switch cases
          valid_menu = true;
        }
        else {
          valid_menu = false;
          cout << "Invalid input. Enter a number between 0 and 3: " << endl;
          continue;
        }

        //switch cases to implement the functions based on the user's input
        switch (num) {
        case 1:
            editor.addText();
            break;
        case 2:
            editor.printDoc();
            break;
        case 3:
            editor.undo();
            cout << "Updated ";
            editor.printDoc();
            break;
        case 0:
            cout << "bye :)";
            return 0;
        default:
            valid_menu = false;
            cout << "Invalid input. Enter a number between 0 and 3: " << endl;
            continue;
        }

        cout<<"Would you like to do something else today?"<<endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choose 1 or 2: " << endl;

        //Input validation
        string choice;
        bool valid_input = false;
        while(!valid_input){
          cin >> choice;
          if (choice == "1" || choice == "2") {
            valid_input = true;
          }
          else{
            cout << "Invalid choice. Please enter 1 or 2: ";
          }
        }

        int continue_choice = stoi(choice);

        if(continue_choice == 1){
          cout<<"Would you like to see our menu again?"<<endl;
          cout << "1. Yes" << endl;
          cout << "2. No" << endl;
          cout << "Choose 1 or 2: " << endl;
          
          //Input validation
          string choice;
          bool valid_input = false;
          while(!valid_input){
            cin >> choice;
            if (choice == "1" || choice == "2") {
              valid_input = true;
            }
            else{
              cout << "Invalid choice. Please enter 1 or 2: ";
            }
          }
            
          int menue_choice = stoi(choice);
          if(menue_choice == 1){
            cout << "Enter '1' to add text to the document" << endl;
            cout << "Enter '2' to print the document" << endl;
            cout << "Enter '3' to undo your last action" << endl;
            cout << "Enter '0' to quit the text editor" << endl;
            valid_menu=false;
            continue;
          }
          else{
            valid_menu=false;
            continue;
          }

        }

        else{
          cout << "Thank you for using our text editor! Have a great day!";
          valid_menu = true;
          break; 
        }
    }

  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Advance Text Editor
  else if (choices == 2){


    AdvancedTextEditor editor;
    
    cout << "Enter '1' to add text to the document" << endl;
    cout << "Enter '2' to print the document" << endl;
    cout << "Enter '3' to undo your last action" << endl;
    cout << "Enter '4' to redo your last" << endl;
    cout << "Enter '0' to quit the text editor" << endl;
    
    //Input validation
    string menu;
    bool valid_menu = false;
    int num;
    while (!valid_menu) {
        cout << "Choose an action: ";
        cin >> menu;

        if (menu.length() == 1 && menu[0] >= '0' && menu[0] <= '4') {
          num = menu[0] - '0';
          valid_menu = true;
        }
        else {
          valid_menu = false;
          cout << "Invalid input. Enter a number between 0 and 4: " << endl;
          continue;
        }

      //switch cases to implement the different functions 
        switch (num) {
        case 1:
            editor.addText();
            break;
        case 2:
            editor.printDoc();
            break;
        case 3:
            editor.undo();
            cout << "Updated ";
            editor.printDoc();
            break;
        case 4:
            editor.redo();
            cout << "Updated ";
            editor.printDoc();
            break; 
        case 0:
            cout << "bye :)";
            return 0;
        default:
            valid_menu = false;
            cout << "Invalid input. Enter a number between 0 and 4: " << endl;
            continue;
        }

        cout<<"Would you like to do something else today?"<<endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Choose 1 or 2: " << endl;
        
        //Input validation
        string choice;
        bool valid_input = false;
        while(!valid_input){
        cin >> choice;
        if (choice == "1" || choice == "2") {
            valid_input = true;
        }
        else{
            cout << "Invalid choice. Please enter 1 or 2: ";
        }
        }
        int continue_choice = stoi(choice);

        if(continue_choice == 1){
            cout<<"Would you like to see our menu again?"<<endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Choose 1 or 2: " << endl;
            string choice;
            bool valid_input = false;
            while(!valid_input){
                cin >> choice;
                if (choice == "1" || choice == "2") {
                valid_input = true;
                }
                else{
                cout << "Invalid choice. Please enter 1 or 2: ";
                }
            }
            int menue_choice = stoi(choice);
            if(menue_choice == 1){
                cout << "Enter '1' to add text to the document" << endl;
                cout << "Enter '2' to print the document" << endl;
                cout << "Enter '3' to undo your last action" << endl;
                cout << "Enter '4' to redo your last" << endl;
                cout << "Enter '0' to quit the text editor" << endl;
                //to continue the loop
                valid_menu=false;
                continue; 
            }
            else{
                //to break the loop
                valid_menu=false;
                continue;
            }
        }
        else{
            cout << "Thank you for using our text editor! Have a great day!";
            //to break the loop
            valid_menu = true;
            break; 
        }
    }
   
  }
  
  return 0;
}



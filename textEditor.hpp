/*********************************************************************************************
 * COP 4530
 * Fatemah Elsewaky - U29797564
 * Noreen Abdelmaksoud - U14450950
 * March 10, 2023
 * 
 * This is the header file (textEditor.hpp). This file contains the code for the template 
 * classes Node, Linked list, and Stack , The Parent class (TextEditor), and the two 
 * child classes (SimpleTextEditor and AdvancedTextEditor)
 * 
 * *******************************************************************************************/
#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>

using namespace std;

template <typename T>                                                   // Template for our classes "T"                                        
class LinkedList;                                                       //class decleration

// Node class for the linked list
template<typename T>
class Node {
    private:
      T data;
      Node<T> * next;                                                  // next used for traversing through the singly linked list                  
    public:
      Node(){};                                       
      Node( T d, Node *n) {
        data = d;
        next = n;
      }
  //creating a friend class "LinkedList" to make sure it can access the public & private members of the Node class
  friend class LinkedList<T>; 

};

//singly linkedlist class
template<typename T>                                                  //Template for LinkedList class
class LinkedList {
    private:
        Node<T>* head;
    public:
        //constructor 
        LinkedList() {
          head = new Node<T>;
          head = nullptr;
        }
        //destructor         
        ~LinkedList(){
          while(!empty()){
          removeFront();
          }
        }
        //check if the list is empty
        bool empty() const{
            return head == NULL;
        }
        //remove the first elem in the list and return that removed element 
        T removeFront(){
          //if the list is empty
          if (head == nullptr) {
            cout<<"List is empty";
            exit(1);
          }

          T elem = head->data;
          Node <T> * oldNode = head;
          head = oldNode -> next;
          delete oldNode;
          return elem;                                                 //return the removed element 
        }

        // Deep copy constructor

        /*****************************************************************************************************************
         * This function is a copy constructor for the LinkedList class. It creates a new instance of LinkedList 
         * by copying the contents of another LinkedList passed as a parameter. If the other LinkedList is empty 
         * (its head is a null pointer), then the new LinkedList will also be empty. Otherwise, the new LinkedList 
         * will have the same elements in the same order as the initial LinkedList. The function achieves this by creating 
         * new nodes for each element in the initial LinkedList and copying their values into the new nodes.
         * ***************************************************************************************************************/
        LinkedList(const LinkedList<T>& other) {
            if (other.head == nullptr) {
              head = nullptr;
            } 
            else {
              head = new Node<T>;
              head->data = other.head->data;
              Node<T>* current = head;
              Node<T>* otherCurrent = other.head->next;
              while (otherCurrent != nullptr) {
                current->next = new Node<T>;
                current = current->next;
                current->data = otherCurrent->data;
                otherCurrent = otherCurrent->next;
              }
              current->next = nullptr;  
            }
        }
        /**********************************************************************************************************************
         * This function assigns the contents of another LinkedList to the current LinkedList. If the other LinkedList 
         * is the same as the current one, it returns the current LinkedList. Otherwise, it creates a temporary LinkedList, 
         * swaps the heads of the current and temporary LinkedLists, and returns the current LinkedList.
         * ********************************************************************************************************************/
        LinkedList& operator=(const LinkedList<T>& other) {
          if (this == &other) {
            return *this;
          }
          LinkedList<T> temp(other);
          swap(head, temp.head);
          return *this;
        } 

        // Insert a node at the beginning of the linked list
        void addFront(T elem) {
            Node<T>* newNode = new Node<T>;
            newNode->data = elem;
            newNode->next = head;
            head = newNode;
        }
        
        // Return the data of the first node in the linked list
        T first() {
            if (head == nullptr) {
                throw out_of_range("List is empty");
            }
            return head->data;
        }

        // Insert a node at the end of the linked list
        void addBack(T elem) {
            Node<T>* newNode = new Node<T>;
            newNode->data = elem;
            newNode->next = nullptr;
            //if list is empty
            if (head == nullptr) {
                head = newNode;
            } 
            else {
                Node<T>* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }

        // Print all elements in the linked list
        void print() {
            Node<T>* current = head;
            if (current == NULL) {
              cout << "list is empty";
              return;
            }
            while (current != nullptr) {
                cout << current->data;
                current = current->next;
                if (current != nullptr) {
                    cout << " ";
                }
            }
            return; 
        }
        //delete all elements in the list
        void clear() {
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            }
            head = nullptr;                                             // set head to null after deleting all nodes
        }


};

//stack class
//calls on the the functions of the linkedlist class
template<typename T>
class Stack {
    private:
        LinkedList<T>* doc;
    public:
        // Constructor
        Stack() {
            doc = new LinkedList<T>();
        }

        // Destructor
        ~Stack() {
            delete doc;
            doc = nullptr;
        }

        // Push an element onto the stack
        void push(T elem) {
            doc->addFront(elem);
        }

        // Pop the top element off the stack and return it
        T pop() {
            return doc->removeFront();
        }

        // Return the top element of the stack without removing it
        T top() {
            return doc->first();
        }

        // Check if the stack is empty
        bool empty() {
            return doc->empty();
        }

        // Clear the stack
        void clear() {
            delete doc;
            doc = new LinkedList<T>();
        }
};

//parent class 
class TextEditor{
  protected:
  
    LinkedList<string> document;                                        //object of the linkedlist class that updates the document
    Stack<LinkedList<string> > undoStack;                               //stack object the keep track of the action to be undone
    Stack<LinkedList<string> > redoStack;                               //stack object the keep track of the action to be redone

  public:
    //virtual functions to use in both child classes
    virtual void addText() = 0;
    virtual void printDoc() = 0;
    virtual void undo() = 0;
    
};

//first child class
class SimpleTextEditor : public TextEditor{
  public:
    void addText() override{
      cout << "Enter text to add to the document: ";
      string text;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      getline(cin, text);
      document.addBack(text);                                              // Modify the document with the user's input
      undoStack.push(document);

      
      bool valid_menu = false;

      while(!valid_menu){
        
        bool valid_input = false;
        string ans;
        cout << "Enter 'y' to keep adding text to the document and 'q' to exit the add option: ";
        while(!valid_input){
          cin >> ans;
          if (ans == "y" || ans == "q") {
            valid_input = true;
          }
          else{
            cout << "Invalid choice. Please enter 'y' or 'q': ";
          }
        }
        if(ans == "y"){
          cout << "Enter text to add to the document: ";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          getline(cin, text);
          document.addBack(text);                                              // Modify the document with the user's input
          undoStack.push(document);                                            // Push the current state onto the undo stack
          continue;
        }
        else{
          valid_menu = true;
          break; 
        }     
      }
    }

    void printDoc()override{
      // Print the updated document
      cout << "Document: ";
      document.print();
      cout << endl;
    }

    void undo() override {
      if (!undoStack.empty()) {
        undoStack.pop();                                               // Pop the current state off the undo stack

        // Update the document with the previous state, or clear it if the undo stack is empty
        if (!undoStack.empty()) {
          document = undoStack.top();
        }
        else {
          document.clear();
        }
      } 
      else {
        cout << "Cannot undo - stack is empty" << endl;
      }
    }
    
};
//second child class
class AdvancedTextEditor : public TextEditor{
  public:
    void addText()override{
      cout << "Enter text to add to the document: ";
      string text;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      getline(cin, text);
      document.addBack(text);                                              // Modify the document with the user's input
      undoStack.push(document);
      redoStack.clear();

      
      bool valid_menu = false;

      while(!valid_menu){
        
        bool valid_input = false;
        string ans;
        cout << "Enter 'y' to keep adding text to the document and 'q' to exit the add option: ";
        while(!valid_input){
          cin >> ans;
          if (ans == "y" || ans == "q") {
            valid_input = true;
          }
          else{
            cout << "Invalid choice. Please enter 'y' or 'q': ";
          }
        }
        if(ans == "y"){
          cout << "Enter text to add to the document: ";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          getline(cin, text);
          document.addBack(text);                                              // Modify the document with the user's input
          undoStack.push(document);                                            // Push the current state onto the undo stack
           redoStack.clear();
          continue;
        }
        else{
          valid_menu = true;
          break; 
        }     
      }
      
    }

    void printDoc()override{
      // Print the updated document
      cout << "Document: ";
      document.print();
      cout << endl;
    }

    void undo() override {
      if (!undoStack.empty()) {
        redoStack.push(undoStack.top());                                     // Pop the current state off the undo stack and push it onto the redo stack
        undoStack.pop();

        // Update the document with the previous state
        if (!undoStack.empty()) {
          document = undoStack.top();
        } else {
          document.clear();
        }
      } 
      else {
        cout << "Cannot undo - stack is empty" << endl;
      }
    }

    void redo()  {
      if (!redoStack.empty()) {
        undoStack.push(redoStack.top());                                    // Pop the current state off the redo stack and push it onto the undo stack
        redoStack.pop();
        document = undoStack.top();                                         // Update the document with the next state

      } else {
        cout << "Cannot redo - stack is empty" << endl;
      }
     
  }    
};

#endif
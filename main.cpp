/** @file main.cpp
 @brief In this file a user can create a list of user input values and then input values at chosen indexes. The program then sorts, modifies and merges this list with another pre-defined list.
 @author Connor Hennen
 @date November 15, 2016
 */

#include "NodeListIterator.hpp"

/*@function main
 The main function will create a list of user input values, displays them, and then allow the user to insert values at chosen indexes. It displays this new list, its maximum, and its size. Then it removes every second value from the new list, displays that update, sorts it from least to greatest, then from greatest to least, and then merges it with another list, displaying the list after each modification.
*/

int main()
{
    // initialize user input list
    List userList;
    
    // initialize user input
    int input;
    
    std::cout << "Please input a set of non-negative numbers for a List (Enter -1 when you are finished): " << std::endl;
    
    //push back nodes into list with user input values user inputs -1
    while((std::cin >> input)&&!(input == -1))
    {
        if(input < -1)
        {
            std::cout << "Please input -1 or a non-negative number:" << std::endl;
        }
        else userList.push_back(input);
    }
    
    std::cout << "Your list is: " << std::endl;
    userList.print();
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    // create a bool that will be true until user inputs -1
    bool moreInput = true;
    while(moreInput == true)
    {
        std::cout << "Select an index for insertion (Enter -1 when you are finished): ";
        int indexInput;
        std::cin >> indexInput;
        
        if (indexInput > -1)
        {
            std::cout << "Select a value for insertion: ";
            int inputValue;
            std::cin >> inputValue;
            
            // create iterator that will iterator until it's pointing at the correct chosen index
            Iterator listIterator = userList.begin();
            for(int i = 0; i < indexInput; ++i) ++listIterator;
            // insert value at chosen index
            userList.insert(listIterator, inputValue);
        }
        // if user inputs -1 the loop will end
        else if (indexInput == -1)
            moreInput = false;
        else
            std::cout << "Must input -1 or a non-negative number." << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "The augmented List is: " << std::endl;
    userList.print();
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "The maximum of the List is: " << maximum(userList) << std::endl;
    std::cout << "The size of the List is: " << userList.get_size() << std::endl;
    
    std::cout << "When we remove every second value from this list we are left with" << std::endl;
    //remove every second value from the list
    downsize(userList);
    userList.print();
    std::cout << std::endl;
    
    std::cout << "When we sort this downsized list we obtain" << std::endl;
    
    // sort downsized list
    sort(userList);
    // print sorted downsized list
    userList.print();

    std::cout << std::endl;
    
    std::cout << "And this sorted list in reverse order is" << std::endl;
    
    //reverse the order of the sorted downsized list
    userList.reverse();
    // print sorted downsized list in reverse order
    userList.print();
    
    std::cout << std::endl;
    
    // create list that will be merged with user defined list
    List mergerList;
    mergerList.push_back(2);
    mergerList.push_back(3);
    mergerList.push_back(5);
    mergerList.push_back(7);
    mergerList.push_back(11);
    
    std::cout << "If we merge this list with the list (2,3,5,7,11) we obtain" << std::endl;
    
    // merges list with user reverse sorted downsized list
    userList.merge(mergerList);
    userList.print();
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    return 0;
}

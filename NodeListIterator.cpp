/** @file NodeListIterator.cpp
 @brief Implements Node, List, and Iterator classes
 @author Connor Hennen
 @date November 15, 2016
 */

#include "NodeListIterator.hpp"

// --------------------------------- Node class implementation ---------------------------------

// Default constructor for node. Previous and next are set to nullptr and data is set to 0
Node::Node():next(nullptr), previous(nullptr), data(0){}

/*Constructor for node with one parameter
 @param input is the value to set the private member variable data to
 */
Node::Node(int input):data(input), next(nullptr), previous(nullptr){}

// ------------------Iterator class implementation---------------------------------

// Default constructor for Iterator class. Sets current node equal to nullptr.
Iterator::Iterator()
{
    current = nullptr;
}

/* Constructor for Iterator class.
 
 @param newNode is a node pointer to the node Iterator will point at
 
 */
Iterator::Iterator(Node* newNode)
{
    current = newNode;
}

// Overloaded prefix operator++
Iterator& Iterator::operator++()
{
    current = current->next;
    return *this;
}

// Overloaded postfix operator++
Iterator Iterator::operator++(int unused)
{
    Iterator clone = current;
    ++(*this);
    return clone;
}

// Overloaded prefix operator--
Iterator& Iterator::operator--()
{
    current = current->previous;
    return *this;
}

// Overloaded postfix operator--
Iterator Iterator::operator--(int unused)
{
    Iterator clone = current;
    --(*this);
    return clone;
}

// Overloaded deference operator
int Iterator::operator*() const
{
	// return value stored by the node pointed to by iterator
    return current->data; 
}

// Overloaded == operator
bool operator==(const Iterator& a , const Iterator& b)
{
	// if both iterators are pointing the same node, return true
	if (a.current == b.current)
	{
		return true;
	}
	// otherwise return false
	else
	{
		return false;
	}
}

// Overloaded != operator
bool operator!=(const Iterator& a, const Iterator& b)
{
    return !(a == b);
}


// --------------------------------- List class implementation ---------------------------------

// Default constructor for List class. First and last private members are set to nullptr and size is set to 0
List::List()
{
    first = nullptr;
    last = nullptr;
    
    size = 0;
}

// List class destructor. Iterates through and deletes each node
List::~List()
{
    Node* current = first;
    
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

/* Begin function 
 @returns iterator pointing to the first node of list
 */
Iterator List::begin()
{
    Iterator begin;
    begin.current = first;
    begin.container = this;
    return begin;
}

/* End function
 @returns iterator pointing to default node after last node of list
 */
Iterator List::end()
{
    Iterator end;
    end.current = nullptr;
    end.container = this;
    
    return end;
}

/* push_back function 
 @brief Appends node to the end of the list
 
 @param value integer value to be appended to the list
 */
void List::push_back(int value)
{
    Node* new_node = new Node(value);
    
    if (last == nullptr)
    {
        first = new_node;
        last = new_node;
    }
    else
    {
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
    
    ++size;
}

/* push_front function
 @brief Appends node to the beginning of the list
 
 @param value integer value to be appended to beginning of the list
 */
void List::push_front(int input)
{
    Node* new_node = new Node(input);
    
    if(first == nullptr)
    {
        first = new_node;
        last = new_node;
    }
    else 
    {
        new_node->next = first;
        first->previous = new_node;
        first = new_node;
    }
    
    ++size;
}

/* Insert functon
 @brief inserts node with input value at position before the node pointed to by input iterator
 
 @param IteratorPosition is the Iterator pointing to the position after the position where the new node is to be inserted
 @param value is the value of the new node to be input into the list
 
 @return Iterator pointing to newly inserted node
 */
Iterator List::insert(Iterator IteratorPosition, int value)
{
    if (IteratorPosition.current == nullptr)
    {
        push_back(value);
        return end();
    }
    
    // Node at insert position
    Node* moveAfter = IteratorPosition.current;
    // Node before insert position
    Node* nodeBefore = moveAfter->previous;
    
    // Create new node to be inserted
    Node* newNode = new Node(value);
    
    // make new node's previous node the node before the node at insert position
    newNode->previous = nodeBefore;
    // makes new node's next node the node after the node at insert position
    newNode->next = moveAfter;
    moveAfter->previous = newNode;
    
    // if insert position is the position of first node of list, the new node is now the first node
    if (nodeBefore == nullptr)
    {
        first = newNode;
    }
    // if insert position is not the position of first node of list, next of node before node at insert position is set to newly inserted node
    else
    {
        nodeBefore->next = newNode;
    }
    
    // create iterator pointing to the new node
    Iterator Iterator_newNode = newNode;
    Iterator_newNode.container = this;
    
    ++size;
    return Iterator_newNode;
}

/* Erase function
 @brief erases the node at the position pointed to by input iterator.
 
 @param position Iterator pointing to the node to be erased
 
 @return Iterator pointing to the node before the erased node
 */
Iterator List::erase(Iterator position)
{
    // assert that the iterator is pointing to an actual node
    assert(position.current != nullptr);
    
    // node to be deleted
    Node* erasedNode = position.current;
    // node before node to be deleted
    Node* nodeBefore = erasedNode->previous;
    // node after node to be deleted
    Node* nodeAfter = erasedNode->next;
    
    // if the node to be removed is the first node, set first to the node after the first node
    if(erasedNode == nodeBefore)
    {
        first = nodeAfter;
    }
    // otherwise set next of node before the deleted node to the node after node to be deleted
    else
        nodeBefore->next = nodeAfter;
    
    // if the node to be removed is the last node, set first to the node before it
    if(erasedNode == last)
    {
        last = nodeBefore;
    }
    // otherwise, set previous of node after to the node before the node to be removed
    else
    {
        nodeAfter->previous = nodeBefore;
    }
    
    delete erasedNode;
    
    --size;
    
    // initialize iterator that will point to the node before the node to be removed
    Iterator output;
    output.current = nodeAfter;
    output.container = this;
    
    return output;
}

// Reverse function. Reverses the ordering of the nodes in the List
void List::reverse()
{
    // create iterator pointing to the first node
    Iterator nodeCrawler = begin();
    
    // if the list is empty or has a single node, it can't be reversed
    if((nodeCrawler.current == nullptr)||(size == 1))
    {
        return;
    }
    
	else
	{
		// loop through the list
		while (nodeCrawler != end())
		{
			//exchange previous and next of each node
			Node* tempNodeValueHolder = nodeCrawler.current->previous;
			nodeCrawler.current->previous = nodeCrawler.current->next;
			nodeCrawler.current->next = tempNodeValueHolder;

			--nodeCrawler;
		}

		// exchange the first and last of list
		Node* tempNodeValueHolder = first;
		first = last;
		last = tempNodeValueHolder;
	}
}

// Swap function. Swaps two lists
void List::swap(List& other)
{
    // switch last nodes
    Node* tempNodeValueHolder = other.last;
    other.last = last;
    last = tempNodeValueHolder;
    
    // switch first nodes
    tempNodeValueHolder = other.first;
    other.first = first;
    first = tempNodeValueHolder;
    
    // switch sizes
    unsigned int tempIntValueHolder = other.size;
    other.size = size;
    size = tempIntValueHolder;
}

/* get_size function
 @returns an unsigned int value of the number of nodes in the list
 */
unsigned int List::get_size() const
{
    return size;
}

// downsize function. Removes every other node from the list
void downsize(List& names)
{
    // if the list is empty it can't be downsized
    if (names.first == nullptr)
    {
        return;
    }
    
	else
	{
		// Node before node to be deleted
		Node* trailingNode = names.first;
		// Node to be deleted
		Node* erasedNode = names.first->next;

		// Iterate until the end of the list or unless one the Node pointers is pointing to a nullptr
		while (trailingNode != nullptr && !(erasedNode == nullptr))
		{
			// set next of trailing node to next of forward node
			trailingNode->next = erasedNode->next;

			if (erasedNode == names.last)
			{
				names.last = trailingNode;
			}
			else
			{
				(erasedNode->next)->previous = trailingNode;
			}

			delete erasedNode;

			// update trailingNode and erasedNode pointers
			trailingNode = trailingNode->next;
			if (trailingNode != nullptr)
			{
				erasedNode = trailingNode->next;
			}
		}

		// correct for changes in size
		if (names.size % 2 == 0)
		{
			names.size = names.size / 2;
		}
		else
		{
			names.size = (names.size / 2) + 1;
		}
	}
}

/* maximum function
 @returns an unsigned int value equal to the maximum value stored by nodes of the list
 */
unsigned int maximum(List& input)
{
    // create iterator pointing to the end of the list
    Iterator ListEnding = input.end();
    // create iterator pointing to the beginning of the list
    Iterator ListBeginning = input.begin();
    
    // at first, let max value be equal to the int value stored in first node
    int maxValue = *ListBeginning;
    
    // iterate until the end of the list and update maximum value along the way
    while(ListBeginning != ListEnding)
    {
        if (*ListBeginning > maxValue)
        {
            maxValue = *ListBeginning;
        }
            ++ListBeginning;
    }
    return maxValue; // return max value
}

/* merge function. Merges two lists into function invoking list
 @param a reference to the List that is to be merged into the list that called the function
 */
void List::merge(List& a)
{
    // if the invoking list is bigger:
    if (this->get_size() > a.get_size())
    {
        Iterator ListBeginning = begin();
        Iterator aListBeginning = a.begin();
        
        ++ListBeginning;
        
        while(aListBeginning != a.end())
        {
            insert(ListBeginning, *aListBeginning);
            ++ListBeginning;
            ++aListBeginning;
        }
    }
    
    //if the invoking list is smaller:
    else
    {
        Iterator ListBeginning = begin();
        Iterator aListBeginning = a.begin();
        
        ++ListBeginning;
        
        while(ListBeginning != end())
        {
            insert(ListBeginning, *aListBeginning);
            ++ListBeginning;
            ++aListBeginning;
        }
        
        while(aListBeginning != a.end())
        {
            push_back(*aListBeginning);
            ++aListBeginning;
        }
    }
}

/* Sort function. Sorts nodes of list in increasing order of their value using selection sort
 
 */
void sort(List& name)
{
    // An empty list or a list with a single value cannot be sorted
    if (name.size == 0 || name.size == 1)
    {
        return;
    }
    
	else
	{
		Iterator a = name.begin();

		while (a != name.end())
		{
			Iterator b = a.current->next;

			while (b != name.end())
			{
				// if there comes a node with a smaller value than the node being pointed to be the a iterator, exchange their values
				if (*b < *a)
				{
					int tempNodeValueStorage = a.current->data;
					a.current->data = b.current->data;
					b.current->data = tempNodeValueStorage;
				}
				++b;
			}
			++a;
		}
	}
}

// print function for list class
void List::print()
{
    if (first == nullptr)
    {
        std::cout << "()";
    }
    
	else
	{
		std::cout << "(";
		for (Iterator i = begin(); i.current != last; ++i)
		{
			std::cout << *i << ",";
		}
		std::cout << last->data << ")";
	}
}

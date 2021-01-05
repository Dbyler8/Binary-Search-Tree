#include <iostream>
#include<fstream>
#include<cstdlib>

#ifndef BINARYTREE_H
#define BINARYTREE_H
using namespace std;

typedef struct tree* tree_ptr;




struct node
{
	tree_ptr data; //Stored data value
	node* next; //Pointer to next data node
};

class Stack
{
public:
	Stack() { maxnum = 10; count = 0; node new_node; top = &new_node; top->next = &new_node; }; //Default constructor
	Stack(int maxquantity) { maxnum = maxquantity;count = 0; top->next = top; }; //Another Constructor
	~Stack(); //Destructor
	void operator =(const Stack& source) { top = source.top; count = source.count; maxnum = source.maxnum; };
	bool isEmpty(); //Returns true is empty
	bool isFull(); //Returns true if full
	void push(const tree_ptr& new_data); //Places a new value at the top of the stack
	void pop(); //Pops the top value off and removes 
	void print(); // Prints stack and uses pop to remove the stack
	tree_ptr top_value();
private:
	int count; //Counts number of times in stack
	int maxnum; //Max number of items
	node* top; //Pointer to storage node

};
//#endif 



Stack::~Stack()
{
	while (!isEmpty()) // Runs until stack is empty
	{
		node* newptr;
		newptr = top;
		top = top->next;
		delete newptr;
		count--;
	}
};

bool Stack::isEmpty()
{
	if (count == 0)
		return true; //Stack is empty
	else
		return false; //Stack is full
};
bool Stack::isFull()
{
	if (count == maxnum)
		return true;//Stack is full
	else
		return false;//Stack is empty
};
void Stack::push(const tree_ptr& new_data)
{
	if (isFull())
		cout << "This stack is full " << endl;
	else
	{
		node* old = top; // Creates old ptr from which to get top->next value
		top = new node();  // Assigns a new address to top
		if (count == 0) // if its the first number first number
		{
			top->data = new_data; //Data assigned goes to data spot
			top->next = NULL; //Last value so, next is NULL
			count++; //Increment count to keep track of values
		}
		else
		{
			top->next = old; //next data is equal to top or old, so that the next value is placed on the new 
			top->data = new_data; //new data is now placed as the data in the new top. 
			count++;
		}
	}
};

void Stack::pop()
{
	if (isEmpty());
	else
	{
		node* tmp;
		tmp = top;
		top = top->next;
		count--;
		delete tmp;
	}
};

void Stack::print()
{
	while (count != 0)
	{

		cout << top->data;
		pop();
		count--;
	}
};
tree_ptr Stack::top_value()
{
	return top->data;
}


#endif
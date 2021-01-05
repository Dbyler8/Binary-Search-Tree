#include "BinaryTree.h"
struct tree
{
	int data;
	int count; //count determines the number of duplicates of the value that was inserted
	tree_ptr left_child;
	tree_ptr right_child;
};

void insert_func(tree*& root, int data, ofstream&  out_f);
void delete_func(tree*& root, int data, ofstream&  out_f);
void print(tree*& root, ofstream&  out_f);
//void insertion(int tree);

int main()
{
	tree* root = NULL;
	char operation; int value;
	ifstream in_file; //This section opens the input file where the values are stored
	in_file.open("BinaryTree.DAT");
	if (in_file.fail()) //Check for open failure
	{
		cout << "File opening failed. \n";

		exit(0); // if we couldn't open the file to read from we exit
	}
	ofstream out_file;//This section opens or creates an output file to place our results
	out_file.open("BinaryTree.txt");
	if (out_file.fail())// Check for file failure
	{
		cout << "File opening failed. \n";

		exit(0); // if we couldn't open the file to read from we exit
	}
	
	while (!in_file.eof()) // While the input file still has more values to process
	{
		in_file >> operation; // First value of every line is a letter. Either I or D
		if (operation == 'I') //IF I we insert
		{
			in_file >> value; // The value we are inserting
			insert_func(root, value, out_file); //Calling the insert function
			operation = 'X';
		}
		if (operation == 'D')//The same except deletion
		{
			in_file >> value;
			delete_func(root, value, out_file);
			operation = 'X'; //Had some issues with the last number repeating its command, thus the x
		}
			
	}

	print(root, out_file); //Prints the numbers after all of the insertion and deletion. 
	
	out_file.close();//Closing the files
	in_file.close();
	system("pause");
	return 0;
}

void insert_func(tree*& root, int data, ofstream&  out)
{
	//insert new nodes into the tree. If the new node value has already been placed, merely increment the count value of the node containing the value. 
	//The first value inserted into the tree will become the root node
	tree* temp; // Temp is a pointer that uses root to orient itself, and then traverses the tree as necessary to find the right location for the inserted node.
	temp = root;
	bool insert = 0; //Whether the node has been inserted or not.
	if (temp == NULL)
	{
		tree* datanode = new tree(); //Data node is the new node being inserted into the tree
		datanode->data = data;
		datanode->left_child = NULL;
		datanode->right_child = NULL;
		datanode->count = 1; 
		root = datanode; //Since this is the first node, the program makes this the root node.
		cout << data << " inserted in the tree as the root node" << endl; //ALL THROUGHOUT, RESULTS ARE DISPLAYED TO CONSOLE AND TO OUTPUT FILE
		out << data << " inserted in the tree as the root node" << endl;

	}
	else
	{
		while (insert == 0) // I use insert as a boolean to communicate when the data has succesfully been placed in the tree
		{
			if (data < temp->data)
			{
				if (temp->left_child == NULL) //IF there is no node here than, we create a new one in this spot, else the program traverses to the next left-child node
				{
					tree* datanode = new tree();//Data node is the new node being inserted into the tree
					datanode->data = data;
					datanode->left_child = NULL;
					datanode->right_child = NULL;
					datanode->count = 1;
					temp->left_child = datanode;
					insert = 1;
					cout << data << " inserted in the tree as a left child, parent node is: " << temp->data << endl;
					out << data << " inserted in the tree as a left child, parent node is: " << temp->data << endl;
				}
				else temp = temp->left_child;
			}
			else if (data > temp->data)
			{
				if (temp->right_child == NULL)
				{ 
					tree* datanode = new tree(); //Data node is the new node being inserted into the tree
					datanode->data = data;
					datanode->left_child = NULL;
					datanode->right_child = NULL;
					datanode->count = 1;
					temp->right_child = datanode; //Temp is the root node on the first pass. Afterwords it could be just about anywhere. Any internal node
					insert = 1;
					cout << data << " inserted in the tree as a right child, parent node is: " << temp->data << endl;
					out << data << " inserted in the tree as a right child, parent node is: " << temp->data << endl;
				}
				else temp = temp->right_child;
			}
			else if (data == temp->data) //The value meant to be inserted is already in the tree
			{
				cout << data << " has already been inserted in the tree. Count incremented" << endl;
				out << data << " has already been inserted in the tree. Count incremented" << endl;
				temp->count++;
				insert = 1;
			}
		}
	}
}


void delete_func(tree*& root, int data, ofstream& out)
{
	int found = 0; // This variable tells the program whether the data value has been found in the tree
	bool selector = true; //This determines whether to select the left or right subtree for the re-organization of the tree. Switches with each use
	tree *q, *temp = root, *parent = root; //Temp will contain the node that the value is located in, and parent tells which node is that node's parent.
	int del = 0; //This variable informs the while loop in the bottom section about whether to keep recyling through the list. This ensures that when nodes get re-arranged, they wer properly deleted
	if (root == NULL)// if tree is empty
	{
		cout << "Deletion Error: No values in tree" << endl;
		out << "Deletion Error: No values in tree" << endl;
	}
	else
	{
		while (found == 0) // This while loop cycles through the tree until it finds a value equal to the search term or the item cannot be found. Found = 0 indicates the program is still searching. 
		{
			parent = temp;
			if (data < temp->data)
			{
				if (temp->left_child == NULL)
				{
					found = 2; //This codifies that the value was not found
				}
				else
				{
					temp = temp->left_child;
				}
			}
			if (data > temp->data)
			{
				if (temp->right_child == NULL)
					found = 2;
				else
				{
					temp = temp->right_child;
				}
			}

			if (data == temp->data)
			{
				found = 1; //Indicates the value has been found
			}
		}
	}
	if (found == 2) //Value not found;
	{
		cout << data << " not found in the tree" << endl;
		out << data << " not found in the tree" << endl;
	}
	if (found == 1)//The value has been found and the temp node pointer contains that value
	{
			if (temp->count != 1) //If the value has been inserted more than once, we de-increment rather than delete the node. 
			{
				temp->count--;
				cout << data << " count deincremented " << endl;
				out << data << " count deincremented " << endl;
				
			}
			else // The program deletes the node as requested and re-routes the nodes that connected to the deleted node to one that remains. 
			{
				while (temp->right_child != NULL || temp->left_child != NULL) //While the child nodes are not null, run through this loop. Note: the temp
				{
					if (temp->right_child == NULL && temp->left_child != NULL) // If the node doesn't have a right child, but does have a left child
					{
						parent = temp; //Parent node values are set before moving temp down to left child
						temp->count = temp->left_child->count;
						temp->data = temp->left_child->data;
						temp = temp->left_child;// Reseting temp equal to another node will place that value as the node to be deleted in the next run of the while loop
					}
					else if (temp->right_child != NULL && temp->left_child == NULL)// If the node doesn't have a left child, but does have a right child
					
					{
						
						parent = temp; //Parent node values are set before moving temp down to right child
						temp->count = temp->right_child->count;
						temp->data = temp->right_child->data;
						temp = temp->right_child;
						// Reseting temp equal to another node will place that value as the node to be deleted in the next run of the while loop
					}
					else if (temp->right_child != NULL && temp->left_child != NULL)
					{
						//Alternately select to move either largest node of the left subtree or the smallest of the right. This ensures the integrity of the tree by having the most middle number as the head of this subtree. Either option should be ok to use

						if (selector) //Selected to look for largest node on the left side to replace the temp node
						{
							q = temp->left_child;
							while (q->right_child != NULL) //Looks for largest sub node on the leftside
							{
								parent = q;
								q = q->right_child;
							}

							temp->count = q->count;
							temp->data = q->data;
							temp = q;// Reseting temp equal to another node will place that value as the node to be deleted in the next run of the while loop
							selector = false;
						}
						else // Else selected to look for smallest node on the right side to replace the temp node
						{
							q = temp->right_child;
							while (q->left_child != NULL) //Looks for smallest sub node on the right side
							{
								parent = q;
								q = q->left_child;
							}
								
							temp->count = q->count;
							temp->data = q->data;
							temp = q; // Reseting temp equal to another node will place that value as the node to be deleted in the next run of the while loop
							selector = true;
						}
					}
				}	
				//End of while loop. Both child nodes should be empty and the leaf node can be deleted without issue 

				if (temp->right_child == NULL && temp->left_child == NULL) //Checks to ensure that node is a leaf node
				{
					cout << data << " deleted from the tree" << endl; //Indicates deleted node
					out << data << " deleted from the tree" << endl;

					if (parent->data > temp->data) //If this is true, then temp will be located in the left child pointer of the parent
					{
						parent->left_child = NULL; //Set pointer to Null, breaking the connection with the tree

					}
					else //Else, then temp will be located in the right child pointer of the parent
					{
						parent->right_child = NULL; //Set pointer to Null

					}
					if (root == temp)
						root = NULL;
					delete temp; //Delete temp and free up the memory used here

				}
			}
			
		
	}
}

void print(tree*& root, ofstream& out)
{
	cout << "Displaying the tree" << endl << "Inorder Traversal:" << endl;
	cout << "Value" << "\t" << "Count" << endl;
	out << "Displaying the tree" << endl << "Inorder Traversal:" << endl;
	out << "Value" << "\t" << "Count" << endl;
	//Inorder traversal, so displays Left nodes first, then Parent, and finally right Right nodes. This creates an output where the numbers are consistently increasing. 
	Stack nodes; // A stack of nodes
	tree* temp = root;

	while (temp != NULL || !nodes.isEmpty()) //Continues while there are nodes left to count
	{
		while (temp != NULL) // Finds the left most child if the current node is not NULL
		{
			nodes.push(temp); //Pushes the node onto the stack 
			temp = temp->left_child;//Keeps moving left
		}
		temp = nodes.top_value(); //Assigns the value of the most recently pushed node (In practical terms, the leftmost node that has not been pushed yet)
		nodes.pop();
		cout << temp->data << "\t" << temp->count << endl;
		out << temp->data << "\t" << temp->count << endl;
		temp = temp->right_child; //Resets the while loop from the right child as temp node. Is set to NULL if there is no right child in which case the parent node would be the top value.
	}
}








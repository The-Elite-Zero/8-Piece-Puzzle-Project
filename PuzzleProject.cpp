// The following program will solve an 8-Piece Puzzle based on randomly
// generated or pre-generated states. It will use 3 different search
// algorithms: Breadth-First, Depth-First, and A* w/ Out of Place Tile
// Heuristic. 
//
// Name: 
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

// Global Variables
const string goalState = "123456780";	// Solution
string solutionState = "783415602";		// A Working State
string initialState = "123456780";		// Variable for use within Menu()
int counter = 0;						// Counter for node count

// Map / Map Iterator
map <string, int> visited_states;
map <string, int>::iterator it = visited_states.begin();

// Object "node"
struct node
{
	string currentState;	// Holds currentState of this node
	int depth = 0;			// Depth of node in tree
	int heuristic = 0;		// How many nodes are out of place

	// Operator Function for Priority-Queue
	bool operator< (const node& other) const
	{
		return heuristic > other.heuristic;
	}
};

// Functions
void Swap0and1(node&);		// Swap Function Prototypes (12)
void Swap0and3(node&);
void Swap1and2(node&);
void Swap1and4(node&);
void Swap2and5(node&);
void Swap3and4(node&);
void Swap4and5(node&);
void Swap4and7(node&);
void Swap5and8(node&);
void Swap6and3(node&);
void Swap6and7(node&);
void Swap7and8(node&);

void randomGenerator();				// Random State Generator
int Check_Goal(node);				// Check for Goal State
void Check_Map(node&);				// Map Check Function
void Expand(node, vector<node>&);	// Expand function
void BFS(node);						// Breadth-First Search Algorithm
void DFS(node);						// Depth-First Search Algorithm
void ASS(node);						// A* w/ Out of Place Algorithm
void Menu();						// Menu Function
void timer(long, long);				// Timer Function (Run Time)
void Heuristic_Calc(node&);			// Calculate Heuristic
void All_Searches(node);			// Runs all Searches
int getInvCount(int);				// Inversion Count
bool isSolvable(string);			// Solvability Check

void displayPuzzle(string PUZZLE);	// Puzzle Output (Formatted Matrix)

// 1-2-3	0-1-2	Logic Layouts for Matrices
// 4-5-6	3-4-5
// 7-8-0	6-7-8

// Goal State [1,2,3,4,5,6,7,8,0]

//-----------------------------------------------------------------------------

int main()	// Main Function
{
	Menu(); // Menu called for input from User

	system("pause"); // Windows Only Pause

	// cin.ignore(); // Universal Pause
	// cin.get();
	// cout << "Press 'Enter' to continue..." << endl;

	return 0; // Success
}

//-----------------------------------------------------------------------------

void Menu() // Outputs Menu for Functionality
{
	int option = NULL;

	cout << " AI Project" << endl;				 
	cout << "------------" << endl << endl;

	cout << "1. Generate Initial State" << endl;
	cout << "2. Breadth-First Search" << endl;
	cout << "3. Depth-First Search" << endl;
	cout << "4. A* Search w/ Out of Place Tiles" << endl;
	cout << "88. Run all Searches" << endl;
	cout << "\n0. Exit Program" << endl;

	cout << "\n\n**Note: If you do not choose to generate an initial state ";
	cout << "\nbefore a search, a working state will be chosen for you.**";
	cout << endl << endl;
	cout << ">> ";
	cin >> option;

	if (cin.fail()) option = 99; // Fail safe for non-numeric inputs

	switch (option)
	{
	case 1: 
		initialState = goalState;
		randomGenerator();	// Shuffles Goal State

		cout << "\nYour Initial Start State is: " << initialState << endl;
		cout << endl;
		displayPuzzle(initialState); // Output initialState Matrix
		cout << "\nPress 'Enter' to return to the menu" << endl;
		cin.ignore();
		cin.get();
		system("cls");
		Menu();
		break;

	case 2:
		if (initialState == "123456780") // Check for unchosen state
		{
			cout << "\nA state was chosen for you." << endl;
			randomGenerator();
			cout << "Your Initial Start State is: " << initialState << endl;

			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			BFS(initialNode); // Send in initialNode 

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}
		else
		{
			cout << "\nYour Initial Start State is: " << initialState;
			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			BFS(initialNode); // Send in initialNode

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}

	case 3:
		if (initialState == "123456780") // Check for unchosen state
		{
			cout << "\nA state was chosen for you." << endl;
			randomGenerator();
			cout << "Your Initial Start State is: " << initialState;

			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			DFS(initialNode); // Send in initialNode

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}
		else
		{
			cout << "\nYour Initial Start State is: " << initialState;
			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			DFS(initialNode); // Send in initialNode

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}

	case 4:
		if (initialState == "123456780") // Check for unchosen state
		{
			cout << "\nA state was chosen for you." << endl;
			randomGenerator();
			cout << "Your Initial Start State is: " << initialState << endl;

			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			ASS(initialNode); // Send in initialNode

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}
		else
		{
			cout << "\nYour Initial Start State is: " << initialState;
			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			ASS(initialNode); // Send in initialNode

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}

	case 88:
		if (initialState == "123456780") // Check for unchosen state
		{
			cout << "\nA state was chosen for you." << endl;
			randomGenerator();
			cout << "Your Initial Start State is: " << initialState << endl;

			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			All_Searches(initialNode);	// Runs all Searches

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}
		else
		{
			cout << "\nYour Initial Start State is: " << initialState;
			cout << endl << endl;
			displayPuzzle(initialState); // Output Matrix

			node initialNode;
			initialNode.currentState = initialState;
			All_Searches(initialNode);	// Runs all Searches

			cout << "Press 'Enter' to return to the menu" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			Menu();
			break;
		}

	case 0:
		cout << "\nExiting the Program..." << endl;
		system("exit"); // Windows Only Pause and Exit
		break;

	default: cout << "\nInput is not valid. Please try again\n\n";
		system("pause");
		cout << endl;
		cin.clear();
		cin.ignore();
		cin.get();
		system("cls"); // Windows Only Clear Screen
		Menu();
		break;

	}//End Switch

}//End void Menu()

//-----------------------------------------------------------------------------

void randomGenerator()	// Generates Random States
{
	// Shuffling string substrings like arrays to generate random
	// states to use within the search algorithms. No numbers will
	// repeat within the substring arrays and they will be different
	// every time as it is randomly seeded based on the clock.

	srand(time(NULL)); // Seed rand to clock time

	for (int i = 8; i > 0; i--) // Shuffle prevents repeats
	{
		int r = rand() % i;

		int temp = initialState[i]; // Swap i and r
		initialState[i] = initialState[r];
		initialState[r] = temp;
	}

	isSolvable(initialState); // Check for Solvability

}//end RandomGenerator

int getInvCount(int arr[])	// Counts Inversions
{
	int inv_count = 0;
	for (int i = 0; i < 9 - 1; i++)
		for (int j = i + 1; j < 9; j++)
			// Value 0 is used for empty space
			if (arr[j] && arr[i] && arr[i] > arr[j])
				inv_count++;
	return inv_count;

}//end getInvCount

bool isSolvable(string puzzle)	// Checks Solvability
{
	int puzzleArray[3][3]; // Multidimensional array
	int n = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			puzzleArray[i][j] = puzzle[n];
			n++;
		}

	// Count inversions in given 8 puzzle
	int invCount = getInvCount((int *)puzzleArray);

	// return true if inversion count is even.
	if (invCount % 2 == 0)
	{
		return true;
	}
	else randomGenerator();	// Search for a Solvable State

}//end isSolvable

//-----------------------------------------------------------------------------

int Check_Goal(node puzzle)	// Checks Node for Goal State
{
	// Goal State = "123456780"

	if (puzzle.currentState == goalState)
	{
		cout << "Goal State Found after <"<< counter << "> nodes" << endl;
		return 0; // Goal State Found
	}
	else
	{
		return 1; // Goal State Not Found
	}
}// end void Check_Goal

//-----------------------------------------------------------------------------

void Check_Map(node& puzzle) // Checks Map for Node
{
	// map <string, int> visited_states;

	// Checks map for node and inserts if
	// node doesn't exist in map

	it = visited_states.begin();
	it = visited_states.find(puzzle.currentState);

	// If iterator goes to end, add node, else clear string

	if (it == visited_states.end()) // If not within map
	{
		counter++;					// Increment counter & add node
		visited_states.insert(pair<string, int>(puzzle.currentState, counter));
	}
	else
	{
		puzzle.currentState.clear();	// Empty node of string
		puzzle.depth = 0;
		puzzle.heuristic = 0;

	}
	
}// end void checkMap

//-----------------------------------------------------------------------------

void Expand(node puzzle, vector <node>& container)	// Expands nodes
{
	// 1-2-3	0-1-2	Logic Layouts for Matrices
	// 4-5-6	3-4-5
	// 7-8-0	6-7-8

	int position = NULL;
	puzzle.depth++;			// Expansion Increases Depth
	node temp = puzzle;		// Temporarily hold parent node

	for (int i = 0; i < 9; i++)
	{
		// Find '0' within character substring
		if (puzzle.currentState[i] == '0') position = i;
	}

	switch (position) // Based on '0' position, swaps called
	{
	case 0: 
		Swap0and1(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap0and3(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 1: 
		Swap0and1(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap1and2(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap1and4(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 2:
		Swap2and5(puzzle);
		Check_Map(puzzle);					// Check Map / Insert

		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap1and2(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 3:
		Swap0and3(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap3and4(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap6and3(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 4:
		Swap3and4(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap1and4(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap4and5(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap4and7(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 5:
		Swap2and5(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap4and5(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap5and8(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 6:
		Swap6and3(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap6and7(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 7:
		Swap6and7(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap4and7(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap7and8(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	case 8:
		Swap7and8(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		puzzle = temp;						// Reset puzzle
		Swap5and8(puzzle);
		Check_Map(puzzle);					// Check Map / Insert
		
		if (!puzzle.currentState.empty())	// If node was not within map
		{
			container.push_back(puzzle);	// Push node onto queue
		}

		break;

	}// end Swap Switch

}//end void Expand

//-----------------------------------------------------------------------------

void BFS(node puzzle)	// Breadth-First Search
{
	cout << "Searching for Breadth-First Solution..." << endl << endl;

	clock_t t1, t2;				// Timer Start 
	t1 = clock();

	int check = 0;				// Double Check for solution
	counter = 0;

	queue <node> BFSFringe;		// Containers
	vector <node> container;
	node temp;				

	Check_Map(puzzle);			// Check / Input Map
	BFSFringe.push(puzzle);		// Push 1st Node to Queue

	while (!BFSFringe.empty())	// Loop for Expansions
	{
		temp = BFSFringe.front();	// Copy node at front of queue
		BFSFringe.pop();			// Pop node from queue

		if (Check_Goal(temp) == 0)	// Check Goal for return
		{
			// Goal found returns 0
			cout << "Goal Found at <" << temp.depth << "> Depth." << endl;
			cout << "Breadth-First Search Complete!" << endl;
			check++;
			goto endBFS;
		}
		else
		{
			// Goal not found returns 1
			container.clear();
			Expand(temp, container);	// Expand for next node

			for (int i = 0; i < container.size(); i++)	// Transfer
			{				
				BFSFringe.push(container[i]);
			}

		}
	}

	if (BFSFringe.empty())	// Empty Queue
	{
		if (check == 0)		// Solution never found
		{
			cout << "Queue Empty! No Solution!" << endl;
		}
	}

	endBFS:					// Branch if goal found

	visited_states.clear();	// Clear Map after search ends

	t2 = clock();			// Timer End

	timer(t1, t2);			// Run Time Calculator

}//end BFS

//-----------------------------------------------------------------------------

void DFS(node puzzle)	// Depth-First Search
{
	cout << "Searching for Depth-First Solution..." << endl << endl;

	clock_t t1, t2;				// Timer Start 
	t1 = clock();

	int check = 0;				// Double Check for solution
	counter = 0;

	stack <node> DFSFringe;		// Containers
	vector <node> container;
	node temp;

	Check_Map(puzzle);			// Initial Node
	DFSFringe.push(puzzle);		

	while (!DFSFringe.empty())	// Loop for Expansions
	{
		temp = DFSFringe.top();	// Copy node at top of stack
		DFSFringe.pop();		// Pop node from stack

		if (Check_Goal(temp) == 0)	// Check Goal for return
		{
			// Goal found returns 0
			cout << "Goal Found at <" << temp.depth << "> Depth." << endl;
			cout << "Depth-First Search Complete!" << endl;
			check++;
			goto endDFS;
		}
		else
		{
			// Goal not found returns 1
			container.clear();
			Expand(temp, container);					// Expand for next node

			for (int i = 0; i < container.size(); i++)	// Transfer
			{
				DFSFringe.push(container[i]);
			}

		}
	}

	if (DFSFringe.empty())	// Empty Queue
	{
		if (check == 0)		// Solution never found
		{
			cout << "Stack Empty! No Solution!" << endl;
		}
	}

	endDFS:					// Branch if goal found

	visited_states.clear();	// Clear Map after search ends

	t2 = clock();			// Timer End

	timer(t1, t2);			// Run Time Calculator

}//end DFS

//-----------------------------------------------------------------------------

void ASS(node puzzle)	// A* Search w/ Heuristic
{
	// This search algorithm will use cost based on
	// out of place tiles (Heuristic).

	cout << "Searching for A* w/ Heuristic Solution..." << endl << endl;

	clock_t t1, t2;				// Timer Start 
	t1 = clock();

	int check = 0;				// Double Check for solution
	counter = 0;
	priority_queue <node> ASSFringe;

	vector <node> container;	// Temporary container
	node temp;

	Heuristic_Calc(puzzle);			// Initial Node
	Check_Map(puzzle);
	ASSFringe.push(puzzle);

	while (!ASSFringe.empty())		// Loop for Expansions
	{
		temp = ASSFringe.top();		// Copy node at front of queue
		ASSFringe.pop();			// Pop node from queue

		if (Check_Goal(temp) == 0)	// Check Goal for return
		{
			// Goal found returns 0
			cout << "Goal Found at <" << temp.depth << "> Depth." << endl;
			cout << "A* Search Complete!" << endl;
			check++;
			goto endASS;
		}
		else
		{
			// Goal not found returns 1
			container.clear();
			Expand(temp, container);					// Expand for next node

			for (int i = 0; i < container.size(); i++)	// Transfer
			{
				container[i].heuristic = 0;
				Heuristic_Calc(container[i]);
				ASSFringe.push(container[i]);
			}
		}
	}

	if (ASSFringe.empty())	// Empty Queue
	{
		if (check == 0)		// Solution never found
		{
			cout << "Priority_Queue Empty! No Solution!" << endl;
		}
	}

	endASS:					// Branch if goal found

	visited_states.clear();	// Clear Map after search ends

	t2 = clock();			// Timer End

	timer(t1, t2);			// Run Time Calculator

}

//-----------------------------------------------------------------------------

void All_Searches(node puzzle)
{
	// Run all Searches 10x and Time them all
	// Average them and compare the searches
	// Explain the differences

	clock_t t1, t2;				// Timer Start 
	t1 = clock();

	BFS(puzzle);
	DFS(puzzle);
	ASS(puzzle);

	t2 = clock();			// Timer End

	cout << "\nRuntime for All Searches" << endl << endl;

	timer(t1, t2);			// Run Time Calculator

}

//-----------------------------------------------------------------------------

void Swap0and1(node& puzzle) // Swap pos 1 and 2
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[0];
	puzzle.currentState[0] = puzzle.currentState[1];
	puzzle.currentState[1] = temp;

	//cout << "After swapping 1 and 2" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap0and3(node& puzzle) // Swap pos 1 and 4
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[0];
	puzzle.currentState[0] = puzzle.currentState[3];
	puzzle.currentState[3] = temp;

	//cout << "After swapping 1 and 4" << endl << endl;
	//displayPuzzle(puzzle.currentState);
}

void Swap1and2(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[1];
	puzzle.currentState[1] = puzzle.currentState[2];
	puzzle.currentState[2] = temp;

	//cout << "After swapping 2 and 3" << endl << endl;
	//displayPuzzle(puzzle.currentState);
}

void Swap1and4(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[1];
	puzzle.currentState[1] = puzzle.currentState[4];
	puzzle.currentState[4] = temp;

	//cout << "After swapping 2 and 5" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap2and5(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[2];
	puzzle.currentState[2] = puzzle.currentState[5];
	puzzle.currentState[5] = temp;

	//cout << "After swapping 3 and 6" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap3and4(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[3];
	puzzle.currentState[3] = puzzle.currentState[4];
	puzzle.currentState[4] = temp;

	//cout << "After swapping 4 and 5" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap4and5(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[4];
	puzzle.currentState[4] = puzzle.currentState[5];
	puzzle.currentState[5] = temp;

	//cout << "After swapping 5 and 6" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap4and7(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[4];
	puzzle.currentState[4] = puzzle.currentState[7];
	puzzle.currentState[7] = temp;

	//cout << "After swapping 5 and 8" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap5and8(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[5];
	puzzle.currentState[5] = puzzle.currentState[8];
	puzzle.currentState[8] = temp;

	//cout << "After swapping 6 and 9" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap6and3(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[6];
	puzzle.currentState[6] = puzzle.currentState[3];
	puzzle.currentState[3] = temp;

	//cout << "After swapping 7 and 4" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap6and7(node& puzzle)
{
	// 0-1-2	Layout for Matrix
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[6];
	puzzle.currentState[6] = puzzle.currentState[7];
	puzzle.currentState[7] = temp;

	//cout << "After swapping 7 and 8" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

void Swap7and8(node& puzzle)
{
	// 0-1-2	Layout for Matrix as substring positions
	// 3-4-5
	// 6-7-8

	int temp = 0;

	temp = puzzle.currentState[7];
	puzzle.currentState[7] = puzzle.currentState[8];
	puzzle.currentState[8] = temp;

	//cout << "After swapping 8 and 0" << endl << endl;
	//displayPuzzle(puzzle.currentState);

}

//-----------------------------------------------------------------------------

void Heuristic_Calc(node& puzzle)	// Calculate Heuristic
{
	// This function calculates the heuristic based on 
	// Out-of-Place tiles by comparing the current node
	// to the Goal State and adding accordingly.

	for (int i = 0; i < 9; i++)
	{
		if (puzzle.currentState[i] == goalState[i])
		{
			continue;	// Compare to Goal
		}
		else
		{
			puzzle.heuristic++;	// Cost Increase
		}
	}
	
}//end void Heuristic_Calc

void displayPuzzle(string puzzle)	// Displays Puzzle as Matrix
{
	// 0-1-2	Layout for Matrix as substring positions
	// 3-4-5
	// 6-7-8

	cout <<" "<<puzzle[0]<<" - "<<puzzle[1]<<" - "<<puzzle[2]<<endl;
	cout <<" |"<<"   |"<<"   |"<< endl;
	cout <<" "<<puzzle[3]<<" - "<<puzzle[4]<<" - "<<puzzle[5]<<endl;
	cout << " |" << "   |" << "   |" << endl;
	cout <<" "<<puzzle[6]<<" - "<<puzzle[7]<<" - "<<puzzle[8]<<endl<<endl;

}// end void displayPuzzle()

void timer(long t1, long t2)	// Calculates Time
{
	// Calculates time based on clock ticks
	// and converts them to seconds using
	// CLOCK_PER_SEC algorithm which is
	// basically dividing based on 1000
	// ticks

	int hours = 0, mins = 0;
	float seconds = 0;

	float diff((float)t2 - (float)t1);
	
	hours = mins / 60;
	mins = seconds / 60;
	seconds = diff / CLOCKS_PER_SEC;

	cout << "Time: " << hours << ":" << mins << ":" << seconds << endl << endl;
	
}

//-----------------------------------------------------------------------------

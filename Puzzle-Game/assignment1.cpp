/*
CS 2336 PROJECT - 1
WORD FINDER
DONE BY : SARVESH.K.RAMIYA
*/

//Including all required Header Files
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cctype>
using namespace std;

//Enumeration of Directions
enum direction { LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };

//Max number of rows and columns in Puzzle Array
const int MAX = 50;

//Structure to Store Details of the Puzzle
struct wordGame
{
	int version;
	int numberRows;
	int numberColumns;
	char puzzle[MAX][MAX];
};

//Structure to Store details of the word to be found
struct wordFind
{
	string word;
	bool found;
	int row;
	int column;
	direction where;
	int foundCount;
};

//Function Prototype of function to find the word.
void findWord(wordGame &game, wordFind &theFind);

//Function Prototype of function to read the puzzle.
bool readPuzzle(wordGame &game, string inputFileName);

//Function Prototype of function to display the puzzle.
void displayPuzzle(wordGame &game);

//Driver Function main()
int main()
{
	string puzzle_file;				//Variable to store Puzzle file name
	string word_file;				//Variable to store Word file name
	wordGame game;					//Object of WordGame with details of the game.
	string key;						//Temporary variable to store the word to be found.
	wordFind temp;					//Temporary Object of WordFind structure to store details of the word
	cin >> puzzle_file;				//Inputting Puzzle file name
	bool file_open = readPuzzle(game, puzzle_file); // Calling readPuzzle
	if (file_open)					// Checking if file is open.
	{
		cout << "The puzzle from file \"" << puzzle_file << "\"" << endl;
		displayPuzzle(game);		// Calling displayPuzzle()
	}
	else
	{
		cout << "The puzzle file \"" << puzzle_file << "\" could not be opened or is invalid" << endl;
		return 0;
	}
	cin >> word_file;				//Inputting Word File name
	fstream words(word_file);		//Opening ostream
	file_open = (words.is_open());	//Checking if file is open
	if (file_open)
	{
		while (!(words.eof()))		//Inputting words till end of file
		{
			words >> key;			//Inputting word from file
			for (int i = 0; i < key.length(); i++)
			{
				key[i]=toupper(key[i]);	//Converting Word to Upper Case (BONUS)
			}
			if (temp.word != key)	//Making sure no consecutive words repeat.
			{
				temp.word = key;
			}
			else
			{
				break;
			}
			findWord(game, temp);	//Calling findWord Function.
			if (temp.foundCount == 1) //If word was found once
			{
				//Displaying message based on direction
				if (temp.where == 0)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "right" << endl;
				}
				if (temp.where == 1)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "left" << endl;
				}
				if (temp.where == 2)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "down" << endl;
				}
				if (temp.where == 3)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "up" << endl;
				}
				if (temp.where == 4)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "right/down" << endl;
				}
				if (temp.where == 5)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "right/up" << endl;
				}
				if (temp.where == 6)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "left/down" << endl;
				}
				if (temp.where == 7)
				{
					cout << "The word " << temp.word << " was found at (" << temp.row + 1 << ", " << temp.column + 1 << ") - " << "left/up" << endl;
				}
			}
			else if (temp.foundCount == 0) // If word was not found
			{
				cout << "The word " << temp.word << " was not found" << endl;
			}
			else if (temp.foundCount > 1) // If word was found more than once
			{
				cout << "The word " << temp.word << " was found " << temp.foundCount << " times" << endl;
			}
		}
	}
	else
	{
		cout << "The puzzle file \"" << word_file << "\" could not be opened or is invalid" << endl;
		return 0;
	}
	words.close();	//Closing words file 
	return 0;
}

//Function to Read Puzzle
bool readPuzzle(wordGame &game, string inputFileName)
{
	game.version = 2;  // Setting game version to 2 (bonus Completed)
	ifstream puzzleFile(inputFileName); //Opening input stream
	if (puzzleFile.is_open())
	{
		puzzleFile >> game.numberRows;		//Reading number of rows
		if (game.numberRows <= 0 || game.numberRows >50)
		{
			return false;					//If invalid row number
		}
		puzzleFile >> game.numberColumns;	//Reading number of columns
		if (game.numberColumns <= 0 || game.numberColumns >50)
		{
			return false;					//If invalid column number
		}
		for (int i = 0; i < game.numberRows; i++)	//Inputting Puzzle into 2D array
		{
			for (int j = 0; j < game.numberColumns; j++)
			{
				if ((j<game.numberColumns && i< game.numberRows) && (puzzleFile.eof()))
				{
					return false; 			//If not enough characters or rows or columns return false
				}
				puzzleFile >> game.puzzle[i][j];
				game.puzzle[i][j]=toupper(game.puzzle[i][j]); // Converting to Upper Case (Bonus)
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	puzzleFile.close();
}

//Function to Display Puzzle
void displayPuzzle(wordGame &game)
{
	//Displaying Puzzle
	for (int i = 0; i < game.numberRows; i++)
	{
		for (int j = 0; j < game.numberColumns; j++)
		{
			cout << game.puzzle[i][j];
		}
		cout << endl;
	}
}

/*
//Function to Find the word in the Puzzle 
Strategy: Traverse through the puzzle. If the first letter of the word is found then check in different different directions
		  if there are enough characters for the word to be present.If there are enough characters then check each letter in sequence
		  and see if it is the same as that in the word. If the complete word was found then store the details of the word.
*/		  
void findWord(wordGame &game, wordFind &theFind)
{
	int flag = 0;					//Variable to check if word is found
	theFind.row = 0;				//Row where the Variable is found
	theFind.column = 0;				//Column where the Variable is found
	theFind.foundCount = 0;			//Number of times the word is found
	theFind.found = 0;				//Variable to store true if word is found
	int textLen = static_cast<int>(theFind.word.length()); // cast the length() return value to an int
	//Traversing the Puzzle
	for (int i = 0; i < game.numberRows; i++)
	{
		for (int j = 0; j < game.numberColumns; j++)
		{
			if (game.puzzle[i][j] == theFind.word[0]) //If the first letter of word is found
			{
				//Checking Left to Right first
				//Checking if the number of characters to the right is more than the length
				if (((j + textLen) - 1) < game.numberColumns) 
				{
					for (int k = j + 1, l = 1; (k < game.numberColumns) && (l < textLen); k++, l++) //Traversing the rest 
					{
						if (!(game.puzzle[i][k] == theFind.word[l]))  //If the letter next doesnt match that in the word
						{
							flag = 0;								  //Word was not found
							break;									  //Break	
						}
						else
						{
							if (l == textLen - 1)					  //If complete word is found	
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)									  //If word was found	
					{
						if (theFind.foundCount == 0)				  //Storing the detaild of where and how the word was found
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = LEFT_RIGHT;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Right to Left 
				//Checking if the number of characters to the left is more than the length
				if (((j - textLen) + 1) >= 0)
				{
					for (int k = j - 1, l = 1; (k >= 0) && (l < textLen); k--, l++) //Traversing the rest
					{
						if (!(game.puzzle[i][k] == theFind.word[l]))	//If the letter doesnt match that in the word
						{
							flag = 0;									//Word was not found
							break;										//Break
						}
						else
						{
							if (l == textLen - 1)						//IF complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)										//If word was found
					{
						if (theFind.foundCount == 0)					//Storing details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = RIGHT_LEFT;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Down 
				//Checking if the number of characters below is more than the length
				if (((i + textLen) - 1) < game.numberRows)
				{
					for (int k = i + 1, l = 1; (k < game.numberRows) && (l < textLen); k++, l++) // Traversing the rest
					{
						if (!(game.puzzle[k][j] == theFind.word[l])) //If the letter doesnt match that of the word
						{
							flag = 0;								 //Word was not found	
							break;									 //Break
						}
						else
						{
							if (l == textLen - 1)					//If complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)									//If word was found
					{
						if (theFind.foundCount == 0)				//Storing details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = DOWN;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking up
				//Checking if the number of characters up is more than the length
				if ((i - textLen) + 1 >= 0)
				{
					for (int k = i - 1, l = 1; (k >= 0) && (l < textLen); k--, l++) //Traversing the rest
					{
						if (!(game.puzzle[k][j] == theFind.word[l])) //If the letter doesnt match that in the word
						{
							flag = 0;								 //Word was not found
							break;									 //Break
						}
						else
						{
							if (l == textLen - 1)					 //If Complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)									 //If word was found
					{
						if (theFind.foundCount == 0)				 //Storing the details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = UP;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Right and Down
				//Checking if the number of characters to the right and down is more than the length
				if (((j + textLen) - 1) < game.numberColumns && ((i + textLen) - 1) < game.numberRows)
				{
					//Traversing the rest
					for (int k = j + 1, r = i + 1, l = 1; (k < game.numberColumns && r < game.numberRows) && (l < textLen); k++, r++, l++)
					{
						if (!(game.puzzle[r][k] == theFind.word[l]))	//If the letter doesnt match that in the word
						{
							flag = 0;									//Word was not found
							break;										//Break
						}
						else
						{
							if (l == textLen - 1)						//If Complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)										//If word was Found
					{
						if (theFind.foundCount == 0)					//Storing the details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = RIGHT_DOWN;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Right and Up
				//Checking if the number of characters to the right and up is more than the length
				if ((((j + textLen) - 1) < game.numberColumns) && ((i - textLen) + 1 >= 0))
				{
					//Traversing the rest
					for (int k = j + 1, r = i - 1, l = 1; (k < game.numberColumns && r >= 0) && (l < textLen); k++, r--, l++)
					{
						if (!(game.puzzle[r][k] == theFind.word[l]))	//If the letter doesnt match that in the word
						{
							flag = 0;									//Word was not found
							break;										//Break
						}
						else
						{
							if (l == textLen - 1)						//If complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)										//If word was found
					{
						if (theFind.foundCount == 0)					//Storing the details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = RIGHT_UP;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Left and down
				//Checking if the number of characters to the left and down is more than the length
				if (((j - textLen) + 1 >= 0) && (((i + textLen) - 1) <= game.numberRows))
				{
					//Traversing the rest
					for (int k = j - 1, r = i + 1, l = 1; (k >= 0 && r <= game.numberRows) && (l < textLen); k--, r++, l++)
					{
						if (!(game.puzzle[r][k] == theFind.word[l])) //If the letter does not match that in the word
						{
							flag = 0;								 //Word was not Found
							break;									 //Break
						}
						else
						{
							if (l == textLen - 1)					 //If complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)									 //If word was found
					{
						if (theFind.foundCount == 0)				 //Storing the details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = LEFT_DOWN;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
				flag = 0;
				//Checking Left and up
				//Checking if the number of characters to left and up is more than the length
				if (((j - textLen) + 1 >= 0) && ((i - textLen) + 1 >= 0))
				{
					//Traversing the rest
					for (int k = j - 1, r = i - 1, l = 1; (k >= 0 && r >= 0) && (l < textLen); k--, r--, l++)
					{
						if (!(game.puzzle[r][k] == theFind.word[l]))	//If the letter doesnt match that in the word
						{
							flag = 0;									//Word was not found
							break;										//Break
						}
						else
						{
							if (l == textLen - 1)						//If complete word was found
							{
								flag = 1;
							}
						}
					}
					if (flag == 1)										//If the word was found
					{
						if (theFind.foundCount == 0)					//Storing the details of the word
						{
							theFind.found = true;
							theFind.row = i;
							theFind.column = j;
							theFind.where = LEFT_UP;
							theFind.foundCount = theFind.foundCount + 1;
						}
						else
						{
							theFind.foundCount = theFind.foundCount + 1;
						}
					}
				}
			}
		}
	}
}

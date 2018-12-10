/***********************************************************************
* Program:
*    Project 12, Sudoku Project
*    Brother Honeycutt, CS124
* Author:
*    Joshua Pearson
* Summary:
*    Creates a quick sudoku board and allows some interaction.
*    
*    
*
*    Estimated:  6.0 hrs
*    Actual:     9.4 hrs
*      Figuring out how to display the stuff.
************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

#define ROWS 9
#define COLS 9

void getSaveFilename(string & filename); 
bool writeFile(string & filename, int board[][COLS]); 
void editSelectedArea(int board[][COLS]); 
void getFilename(string & filename); 
bool readFile(string & filename, int board[][COLS]); 
void display(int board[][COLS]); 
void showPossible(int board[][COLS]);
void getValues(int r, int c, int board[][COLS], int possilbe[]); 
void interact(); 
void interact(int board[][COLS]); 
void getCoordinates(string & coords); 
bool isValid(int r, int c, string & coords, int board[][COLS]); 


/**********************************************************************
 * Starts program and calls all functions.
 ***********************************************************************/
int main() {
  string filename;
  int board[ROWS][COLS];

  getFilename(filename);
  readFile(filename, board);
  interact(board);
  getSaveFilename(filename);
  if (writeFile(filename, board))
  {
    cout << "Board written successfully" << endl;
  }
}

/**********************************************************************
 * prompts for filename
 ***********************************************************************/
void getFilename(string & filename)
{
  cout << "Where is your board located? ";
  cin >> filename;
  cin.ignore();
}

/**********************************************************************
 * iterates file and stores in arrays
 ***********************************************************************/
bool readFile(string & filename, int board[][COLS])
{
  ifstream fin(filename.c_str());
  
  if (fin.fail())
  {
    return false;
  }
  else
  {
    for (int r = 0; r < ROWS; r++)
    {
      for (int c = 0; c < COLS; c++)
      {
        fin >> board[r][c];
      }
    }
    return true;
  }
  fin.close();
}

/**********************************************************************
 * interact
 * prompts the user for the game option desired and performs the 
 * corresponding tasks.
 ***********************************************************************/
void interact(int board[][COLS])
{
  char option;
  interact();
  cout << endl;
  display(board);
  do
  {
    cout << "\n> ";
    cin >> option;
    switch (option)
    {
      case '?':
        interact();
        cout << endl;
        break;
      case 'D':
      case 'd':
        display(board);
        break;
      case 'E':
      case 'e':
        editSelectedArea(board);
        break;
      case 'S':
      case 's':
        showPossible(board);
        break;
      case 'Q':
      case 'q':
        break;
      default:
        cout << "ERROR: Invalid command\n";
        break;
    }
  } while (toupper(option) != 'Q');
}

/**********************************************************************
 * display possbilities
 ***********************************************************************/
void interact()
{
  cout << "Options:" << endl;
  cout << "   ?  Show these instructions" << endl;
  cout << "   D  Display the board" << endl;
  cout << "   E  Edit one square" << endl;
  cout << "   S  Show the possible values for a square" << endl;
  cout << "   Q  Save and Quit" << endl;
}

/**********************************************************************
 * asks for file location.
 ***********************************************************************/
void getSaveFilename(string & filename)
{
  cout << "What file would you like to write your board to: ";
  cin >> filename;
  cin.ignore();
}

/**********************************************************************
 * saves the game board data to a file
 ***********************************************************************/
bool writeFile(string & filename, int board[][COLS])
{
  ofstream fout(filename.c_str());
      
      if (fout.fail())
        return false;
        
      for (int r = 0; r < ROWS; r++)
      {
        for (int c = 0; c < COLS; c++)
        {
          fout << board[r][c];
          if (c < COLS -1)
            fout << " ";
        }
        if (r < ROWS - 1)
          fout << endl;
      }
      fout.close();
  return true;
}

/**********************************************************************
 * edit selected area.
 ***********************************************************************/
void editSelectedArea(int board[][COLS])
{
  string coords;
  int c;
  int r;
  getCoordinates(coords);
  c = toupper(coords[0]) - 'A';
  r = (int)coords[1] - '1';
  coords[0] = toupper(coords[0]);
  if (isValid(r, c, coords, board))
  {
    cout << "What is the value at '" << coords[0]
         << coords[1] << "': ";
    cin >> board[r][c];
  }
}

/**********************************************************************
 * prompt for coordinates from user
 ***********************************************************************/
void getCoordinates(string & coords)
{
  cout << "What are the coordinates of the square: ";
  cin >> coords[0];
  cin >> coords[1];
}

/**********************************************************************
 * checks if coords are valid
 ***********************************************************************/
bool isValid(int r, int c, string & coords, int board[][COLS])
{

  if (board[r][c] != 0)
  {
    cout << "ERROR: Square '" << coords[0] << coords[1]
         << "' is filled" << endl;
    return false;
  }
  return true;
}

/**********************************************************************
 * display possible values
 ***********************************************************************/
void showPossible(int board[][COLS])
{
  string coords;
  getCoordinates(coords);
  int c = toupper(coords[0]) - 'A';
  int r = (int)coords[1] - '1';
  
  int possible[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  getValues(r, c, board, possible);
  coords[0] = toupper(coords[0]);
  cout << "The possible values for " << coords[0] << coords[1]
       << " is/are: " << possible;
  for (int i = 0; i < 9; i++)
  {
    if (possible[i] != 0)
      cout << possible[i];
  }
  cout << endl;
}


/**********************************************************************
 * get values.
 ***********************************************************************/
void getValues(int r, int c, int board[][COLS], int possible[])
{
  
}

/**********************************************************************
 * display
 * prints the game board with the loaded data from the given file
 ***********************************************************************/
void display(int board[][COLS])
{
  cout << "   A B C D E F G H I\n";
  for (int r = 0; r < ROWS; r++)
  {
    cout << setw(3) << left << r + 1;
    for (int c = 0; c < COLS; c++)
    {
      if ((c + 1) % 3 == 0 && (c + 1) % 9 != 0)
      {
        if (board[r][c] == 0)
        {
          cout << " |";
        }
        else {
          cout << board[r][c] << "|";
        }

      }
      else if ((c + 1) % 9 == 0)
      {
        if (board[r][c] == 0)
        {
          cout << " \n";
        }
        else {
          cout << board[r][c] << "\n";
        }
      }
      else
      {
        if (board[r][c] == 0)
        {
          cout << "  ";
        }
        else {
          cout << board[r][c] << " ";
        }
      }
    }
    if ((r + 1) % 3 == 0 && (r + 1) % 9 != 0)
    {
      cout << "   -----+-----+-----\n";
    }
  }
}

#ifndef SOLITAIRE_H
#define SOLITAIRE_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
// ENGLISH board shape has 33 holes
// DIAMOND board tepe has 41 holes
// We do not support FRENCH board
enum BOARDSHAPE {NONE, ENGLISH, FRENCH, DIAMOND};
const int ENGLISHSIZE = 7; // used to create a 7x7 matrix
const int DIAMONDSIZE = 9; // used to create a 9x9 matrix
const int NUMENGLISHMARBLES = 32; // total number of marbles used on an english board
const int NUMDIAMONDMARBLES = 40; // total number of marbles used on a diamond board

class Solitaire{
public:
    friend class Grader; //friends so they can use Solitaires priv vars
    friend class Tester;
    Solitaire(); // creates an empty object
    Solitaire(BOARDSHAPE board); // creates the specific board, allocates mem
    Solitaire(const Solitaire & rhs);
    ~Solitaire();
    void clear(); // clears memory and reinitializes all members
    bool newBoard(); // reinitializes the game with the same board shape
    void changeBoard(BOARDSHAPE board); // creates a new board
    bool play(pair<int,int> origin, pair<int,int> destination);// makes a move
    int reportNumMarbles(); // for debugging purposes
    void printBoard();
    void getCoords(string input, char coords[10]); 
    void print();
    bool gameNotOver(); //game over function

    private:
    int m_numRows;
    int m_numColumns;
    char ** m_board;     // the 2d structure to store game 
    BOARDSHAPE m_shape; // the board shape (either english or diamond)
    int m_numMarbles;   // current number of marbles
    
    void englishBoard();    
    void diamondBoard();

    //check to see if an adjacent position has a 'O'
    bool adjacent(pair<int,int> origin, pair<int,int> destination); 

   

   
    

   
};
#endif
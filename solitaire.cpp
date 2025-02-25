#include "solitaire.h"

Solitaire::Solitaire(){
    m_shape = NONE; 
    m_board = nullptr;
    m_numColumns = 0;
    m_numRows = 0;
    m_numMarbles = 0;    
} 
Solitaire::Solitaire(BOARDSHAPE board){
    m_shape = board;

    switch(m_shape){
        case ENGLISH:
            m_numColumns = ENGLISHSIZE;
            m_numRows = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            englishBoard();
            break;
        case DIAMOND:
            m_numColumns = DIAMONDSIZE;
            m_numRows = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            diamondBoard();
            break;
        case FRENCH:
            m_board = nullptr;
            m_numColumns = 0;
            m_numRows = 0;
            m_numMarbles = 0;
            break;
        case NONE:
            m_board = nullptr;
            m_numColumns = 0;
            m_numRows = 0;
            m_numMarbles = 0;
            break;
    }
    
}
Solitaire::Solitaire(const Solitaire & rhs){
    m_numColumns = rhs.m_numColumns;
    m_numRows = rhs.m_numRows;
    m_shape = rhs.m_shape;
    m_numMarbles = rhs.m_numMarbles;
    m_board = rhs.m_board;

    if(rhs.m_board != nullptr){
        m_board = new char*[m_numRows];
        for(int i = 0; i < m_numRows; i++){
            m_board[i] = new char[m_numColumns];
            for(int j = 0; j < m_numColumns; j++){
                m_board[i][j] = rhs.m_board[i][j];
            }
        }
    }

    
}

Solitaire::~Solitaire(){
    clear();
}

void Solitaire::clear(){
    for(int i = 0; i < m_numRows; i++){
        delete[] m_board[i];
    }
    delete[] m_board;
    m_board = nullptr;
    m_numColumns = 0;
    m_numRows = 0;
    m_numMarbles = 0;

}

bool Solitaire::play(pair<int,int> origin, pair<int,int> destination){

    //checks if inputs are in range     
    if((origin.first < m_numColumns && origin.second < m_numColumns && 
    destination.first < m_numColumns && destination.second < m_numColumns) &&
    //prevents landing on or choosing space not on board or empty space
    (m_board[origin.first][origin.second] != ' ' &&
     m_board[destination.first][destination.second] != ' ' &&
     m_board[origin.first][origin.second] != 'X') && 
    //inputs are not the same space
    (m_board[origin.first][origin.second] !=
     m_board[destination.first][destination.second]) &&
    //jumps are only orthogonal 
    (origin.first == destination.first ||
     origin.second == destination.second) &&
    //cannot jump next to origin place
    (destination.first != origin.first + 1 &&     
     destination.second != origin.second + 1 && 
     destination.first != origin.first - 1 &&
     destination.second != origin.second - 1) &&
    //cannot jump more than 2 places
    (abs(origin.first-destination.first) == 2 ||
     abs(origin.second-destination.second) == 2) &&
    //cannot jump over empty space 
    (adjacent(origin, destination))

    ){
    
        //logic for replacing space jumped over with empty space (X)
        if(origin.first - destination.first == 2){
            m_board[origin.first - 1][origin.second] = 'X';

        }else if(origin.first - destination.first == -2){
            m_board[origin.first + 1][origin.second] = 'X';   

        }else if(origin.second - destination.second == 2){
            m_board[origin.first][origin.second - 1] = 'X';

        }else if(origin.second - destination.second == -2){
            m_board[origin.first][origin.second + 1] = 'X';
        }

        m_board[destination.first][destination.second] = 'O';
        m_board[origin.first][origin.second] = 'X';       
        m_numMarbles--;
        return true;

    }else{
        return false;
   }
    
}

void Solitaire::changeBoard(BOARDSHAPE board){

    if(m_board != nullptr){
        for(int i = 0; i < m_numRows; i++){
            delete[] m_board[i];
        }
        delete[] m_board;
        m_board = nullptr;
    }

    m_shape = board;

    switch(m_shape){
        case ENGLISH:
            m_numColumns = ENGLISHSIZE;
            m_numRows = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            englishBoard();
            break;
        case DIAMOND:
            m_numColumns = DIAMONDSIZE;
            m_numRows = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            diamondBoard();
            break;
        case FRENCH:
            m_board = nullptr;
            m_numColumns = 0;
            m_numRows = 0;
            m_numMarbles = 0;
            break;
        case NONE:
            m_board = nullptr;
            m_numColumns = 0;
            m_numRows = 0;
            m_numMarbles = 0;
            break;
    }
}

bool Solitaire::newBoard(){

    if(m_shape == NONE){
        return false;
    }

    if(m_board != nullptr){
        for(int i = 0; i < m_numRows; i++){
            delete[] m_board[i];
        }
        delete[] m_board;
        m_board = nullptr;
    }
    
    switch(m_shape){
        case ENGLISH:
            m_numColumns = ENGLISHSIZE;
            m_numRows = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            englishBoard();
            break;
        case DIAMOND:
            m_numColumns = DIAMONDSIZE;
            m_numRows = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            diamondBoard();
            break;
        default:
            return false;
    }
        
       
    return true;

    
}

int Solitaire::reportNumMarbles(){
    // this is to facilitate debugging 
    cout << "You have " << m_numMarbles << " marbles to remove!" << endl;
    return m_numMarbles;
}

void Solitaire::printBoard(){
    cout << "    ";

    for(int i = 1; i < m_numColumns + 1; i++){
        cout << i << " ";
    }
    cout << endl;
    cout << endl;

    for(int i = 0; i < m_numRows; i++){
        cout << i+1 << "   ";
        for(int j = 0; j < m_numColumns; j++){
            cout << m_board[i][j] << " ";
        }
        cout << endl;
    }
}

void Solitaire::englishBoard(){
    m_numMarbles = 32;
    m_board = new char*[m_numRows];        //allocate mem
    for(int i = 0; i < m_numRows; i++){
        m_board[i] = new char[m_numColumns];
    } 

    for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){
            m_board[i][j] = 'O';
        }
    }
    m_board[3][3] = 'X'; m_board[0][0] = ' '; m_board[0][1] = ' '; 
    m_board[1][0] = ' '; m_board[1][1] = ' '; m_board[0][5] = ' '; 
    m_board[0][6] = ' '; m_board[1][5] = ' '; m_board[1][6] = ' '; 
    m_board[5][0] = ' '; m_board[6][0] = ' '; m_board[5][1] = ' '; 
    m_board[6][1] = ' '; m_board[5][5] = ' '; m_board[5][6] = ' '; 
    m_board[6][5] = ' '; m_board[6][6] = ' '; 
    
}

void Solitaire::diamondBoard(){
    m_numMarbles = 40;
    m_board = new char*[m_numRows];        //allocate mem
    for(int i = 0; i < m_numRows; i++){
        m_board[i] = new char[m_numColumns];
    } 

    for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){
            m_board[i][j] = 'O';
        }
    }

    m_board[4][4] = 'X';

    for(int i = 0; i <= 3; i++){
        m_board[i][0] = ' ';
    }
    for(int i = 0; i <= 3; i++){
        m_board[0][i] = ' ';
    }
    m_board[1][1] = ' ';  m_board[2][1] = ' ';  m_board[1][2] = ' '; 

    for(int i = 5; i < 8; i++){
        m_board[0][i] = ' ';
    }
    for(int i = 0; i < 4; i++){
        m_board[i][8] = ' ';
    }
    m_board[1][6] = ' ';  m_board[1][7] = ' ';  m_board[2][7] = ' ';

    for(int i = 5; i < 8; i++){
        m_board[i][0] = ' ';
    }
    for(int i = 0; i < 4; i++){
        m_board[8][i] = ' ';
    }
    m_board[7][1] = ' ';  m_board[6][1] = ' ';  m_board[7][2] = ' ';

    for(int i = 5; i <= 8; i++){
        m_board[8][i] = ' ';
    }
    for(int i = 5; i < 8; i++){
        m_board[i][8] = ' ';
    }
    m_board[7][7] = ' ';  m_board[7][6] = ' ';  m_board[6][7] = ' ';

}   

bool Solitaire::adjacent(pair<int,int> origin, pair<int,int> destination){
    //if adjacent has 'O' then return true (valid jump)
    //check horizontally 
    if(origin.first == destination.first){
        int x = max(origin.second, destination.second);
        if(m_board[origin.first][x-1] == 'O'){
            return true;
        }else{
            return false;
        }
    }
    //check vertically 
    if(origin.second == destination.second){
        int y = max(origin.first, destination.first);
        if(m_board[y-1][origin.second] == 'O'){
            return true;
        }else{
            return false;
        }
    }

}

void Solitaire::getCoords(string input, char coords[10]){
    //if digit is found in input, store it in coords array
    int index = 0;
    for(int i = 0; i < input.length(); i++){
        if(isdigit(input[i])){
            coords[index] = input[i];
            index++;
        }
    }
}

void Solitaire::print(){
    cout << m_board[3][4] << endl;
}

bool Solitaire::gameNotOver(){
    //iterate through board and check if a 'O' has an adjacent 'O'
    //if so, return true (game is not over)
    //else return false (game is over) 
    for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){

            if(m_board[i][j] == 'O'){
                if(m_board[i][j+1] == 'O'){
                    return true;
                }
                if(m_board[i][j-1] == 'O'){
                    return true;
                }
                if(m_board[i+1][j] == 'O'){
                    return true;
                }
                if(m_board[i-1][j] == 'O'){
                    return true;
                }
            }
        }
    }

    return false;
}
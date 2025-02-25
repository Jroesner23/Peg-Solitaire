#include "solitaire.h"
class Tester{
    public:
        bool testCopyConstructorNormal(const Solitaire& solitaire);
        bool isValid(const Solitaire& solitaire, 
        pair<int,int> origin, pair<int,int> destination);
        bool testErrorCopy(const Solitaire& solitaire);
        bool testEnglishConstructor();
        bool testDiamondConstructor();
        bool testInvalidConstructor(const Solitaire& solitaire);
        bool testNewBoard(const Solitaire& solitaire);
        bool testEmptyNewBoard(const Solitaire& solitaire);
        bool testChangeBoard(const Solitaire& solitaire);

};

int main(){
    Solitaire peg;
    int choice;
    string input;
    char coords[10];

    cout << "Choose a board shape: " << endl;
    cout << "1. English" << endl;
    cout << "2. Diamond" << endl;

    while(true){ 
        cout << "-> ";
        cin >> choice;
        if(choice == 1){
            peg.changeBoard(ENGLISH);
            break;
        }else if(choice == 2){
            peg.changeBoard(DIAMOND);
            break;
        }else{
            cout << "Invalid choice" << endl;
        }
    }

    peg.printBoard();
    
    while(peg.gameNotOver()){
        cout << "Type q to quit. Enter coordinates: ";
        cin >> input;
        if(input == "q"){
            break;
        }
        else{
            peg.getCoords(input, coords);
        }
        int origin1 = coords[0] - '1';
        int origin2 = coords[1] - '1';
        int dest1 = coords[2] - '1';
        int dest2 = coords[3] - '1';
        if(!(peg.play(pair<int,int>(origin1,origin2), pair<int,int>(dest1,dest2)))){
            cout << "Invalid move" << endl;
        }else{
            peg.printBoard();
            peg.reportNumMarbles();
        }
    }

    cout << "Congradulations. You won!" << endl;

 
    return 0;
}


bool Tester::testCopyConstructorNormal(const Solitaire& solitaire){
    
    Solitaire copy(solitaire);
    if (solitaire.m_numColumns == copy.m_numColumns && 
        solitaire.m_numRows == copy.m_numRows &&
        solitaire.m_shape == copy.m_shape &&
        solitaire.m_numMarbles == copy.m_numMarbles && 
        solitaire.m_board != copy.m_board){
        for (int i=0;i<solitaire.m_numRows;i++){
            for (int j=0;j<solitaire.m_numColumns;j++)
            {
                if ((solitaire.m_board[i][j] != copy.m_board[i][j]) ||   //check the value
                    (solitaire.m_board[i] == copy.m_board[i])){          //check the ith pointer
                    return false;
                }
            }
        }
        return true;// everything is correct
    }
    else return false;//everthing else
}

bool Tester::testErrorCopy(const Solitaire& solitaire){
    Solitaire copy(solitaire);
    if(copy.m_board == nullptr){
        return true;
    }else{
        return false;
    }

}

bool Tester::isValid(const Solitaire& solitaire, 
pair<int,int> origin, pair<int,int> destination){
  
    if((origin.first < solitaire.m_numColumns && origin.second < solitaire.m_numColumns && 
    destination.first < solitaire.m_numColumns && destination.second < solitaire.m_numColumns) &&
    //prevents landing on or choosing space not on board or empty space
    (solitaire.m_board[origin.first][origin.second] != 0 &&
     solitaire.m_board[destination.first][destination.second] != 0 &&
     solitaire.m_board[origin.first][origin.second] != 1) && 
    //inputs are not the same space
    (solitaire.m_board[origin.first][origin.second] !=
     solitaire.m_board[destination.first][destination.second]) &&
    //jumps are only orthogonal 
    (solitaire.m_board[origin.first] == solitaire.m_board[destination.first] ||
     solitaire.m_board[origin.second] == solitaire.m_board[destination.second]) &&
    //cannot jump over empty space
    (destination.first != origin.first + 1 &&     
     destination.second != origin.second + 1 && 
     destination.first != origin.first - 1 &&
     destination.second != origin.second - 1) &&
    //cannot jump more than 2 places
    (abs(origin.first-destination.first) == 2 ||
     abs(origin.second-destination.second) == 2)
    
    ){

        return true;
    }else{

        return false;
   }
    


}

    bool Tester::testEnglishConstructor(){
        Solitaire solitaire(ENGLISH); 
        if(solitaire.m_shape == ENGLISH && 
        solitaire.m_numColumns == ENGLISHSIZE &&
        solitaire.m_numRows == ENGLISHSIZE &&
        solitaire.m_numMarbles == NUMENGLISHMARBLES &&
        solitaire.m_board != nullptr ){

            return true;
        }else{
            return false;
        }

}

bool Tester::testDiamondConstructor(){
        Solitaire solitaire(DIAMOND);
        if(solitaire.m_shape == DIAMOND && 
        solitaire.m_numColumns == DIAMONDSIZE &&
        solitaire.m_numRows == DIAMONDSIZE &&
        solitaire.m_numMarbles == NUMDIAMONDMARBLES &&
        solitaire.m_board != nullptr ){

            return true;
        }else{
            return false;
        }

}

bool Tester::testInvalidConstructor(const Solitaire& solitaire){
    if(solitaire.m_shape == 0 && 
        solitaire.m_numColumns == 0 &&
        solitaire.m_numRows == 0 &&
        solitaire.m_numMarbles == 0 &&
        solitaire.m_board == nullptr ){

        return true;
    }else{
        return false;
    }

}
bool Tester::testNewBoard(const Solitaire& solitaire){
    
    switch(solitaire.m_shape){
        case ENGLISH:
            if((solitaire.m_numColumns == ENGLISHSIZE) &&
            (solitaire.m_numRows == ENGLISHSIZE) &&
            (solitaire.m_numMarbles == NUMENGLISHMARBLES)){
                return true;
            }
            break;
        case DIAMOND:
            if((solitaire.m_numColumns == DIAMONDSIZE) &&
            (solitaire.m_numRows == DIAMONDSIZE) &&
            (solitaire.m_numMarbles == NUMDIAMONDMARBLES)){
                return true;
            }
            break;
        
    }

    return false;
    
}

bool Tester::testEmptyNewBoard(const Solitaire& solitaire){
    switch(solitaire.m_shape){
         case FRENCH:
            if(solitaire.m_board == nullptr){
                return true;
            }
            break;
        case NONE:
            if(solitaire.m_board == nullptr){
                return true;
            }

    }

    return false;

}

bool Tester::testChangeBoard(const Solitaire& solitaire){
    switch(solitaire.m_shape){
        case ENGLISH:
            if((solitaire.m_numColumns == ENGLISHSIZE) &&
            (solitaire.m_numRows == ENGLISHSIZE) &&
            (solitaire.m_numMarbles == NUMENGLISHMARBLES)){
                return true;
            }
            break;
        case DIAMOND:
            if((solitaire.m_numColumns == DIAMONDSIZE) &&
            (solitaire.m_numRows == DIAMONDSIZE) &&
            (solitaire.m_numMarbles == NUMDIAMONDMARBLES)){
                return true;
            }
            break;
        
    }

    return false;

}


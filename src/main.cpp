#include <iostream>
#include <string>
#include <array>
 
using namespace std;

class Grid{
    public:
    std::array<std::array<char, 3> , 3> grid;

    Grid(){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                grid[i][j] = 'O';
            }
        }

    };

    void printGrid(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                std::cout << grid[i][j] << " ";
            }
        std::cout << endl;
        }
    };

    bool checkHorizontal(char player){
        for(int i = 0; i < 3; i++){
            return checkHorizontalAux(player, i, 0);
        }
        
    }
    /**
     * Recursive call to check 
     * 
     */
    bool checkHorizontalAux(char player, int row, int column){
        // Base case : All the grids in the same row are the same
        if(column == 2){
            return true;
        }
        // Recursive case : Calls checkHorizontalAux on the next column
        else{
            if(grid[row][column] == player){
                return checkHorizontalAux(player, row, column+1);
            }
            else{
                return false;
            }
            
        }
    }

    bool checkVertical(char player){
        for(int i = 0; i < 3; i++){
            return checkVerticalAux(player, 0, i);
        }
        
    }

    bool checkVerticalAux(char player, int row, int column){
        // Base case : All the grids in the same row are the same
        if(row == 2){
            return true;
        }
        // Recursive case : Calls checkHorizontalAux on the next column
        else{
            if(grid[row][column] == player){
                return checkVerticalAux(player, row+1, column);
            }
            else{
                return false;
            }
            
        }
    }


};

int main(){

    Grid grid;
    grid.printGrid();
    grid.grid[0][0] = 'X';
    grid.grid[1][0] = 'X';
    grid.grid[2][0] = 'X';
    grid.printGrid();
    // if(grid.checkVertical('X')){
    //     std::cout <<"True" << endl;
    // }
    std::cout << std::boolalpha << grid.checkHorizontal('X');

}



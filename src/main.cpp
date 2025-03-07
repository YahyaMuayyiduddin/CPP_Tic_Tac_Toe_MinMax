#include <iostream>
#include <string>
#include <array>
 
using namespace std;

class Grid{
    public:
    std::array<std::array<char, 3> , 3> grid;
    int rows;
    int column;

    Grid(){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                grid[i][j] = 'O';
            }
        }
        rows = 3;
        column = 3;

    };

    void printGrid(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                std::cout << grid[i][j] << " ";
            }
        std::cout << endl;
        }
    };

    bool checkHorizontal(char player, int row, int column){
        int sum = 0;
        sum += countHorizontal(player, row, column + 1, 1);
        sum += countHorizontal(player, row, column - 1, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    /**
     * Recursive call to count how many matching tokens in the same row
     * 
     */
    int countHorizontal(char player, int row, int column, int step){
        if(column > 2||grid[row][column] != player ){
            return 0;
        }else{
            return 1 + countHorizontal(player,row, column + step, step);
        }
    };


    bool checkVertical(char player, int row, int column){
        int sum = 0;
        sum += countVertical(player, row+1, column, 1);
        sum += countVertical(player, row -1, column, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    /**
     * Recursive call to count how many matching tokens in the same column
     * 
     */
    int countVertical(char player, int row, int column, int step){
        if(column > 2||grid[row][column] != player ){
            return 0;
        }else{
            return 1 + countVertical(player,row + step, column, step);
        }
    };


    void playToken(char player, int row, int columns){
        if(grid[row][columns] != 'O' || row >= rows ||  columns >= column){
            std::cout << "Invalid placement" << endl;
        }else{
            grid[row][columns] = player;
        }
       
    }
    bool checkDiagonalL(char player, int row, int column){
        int sum = 0;
        sum += countDiagonalL(player, row+1, column+1, 1);
        sum += countDiagonalL(player, row -1, column-1, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    int countDiagonalL(char player, int row, int column, int step){
        if(column > 2||grid[row][column] != player ){
            return 0;
        }else{
            return 1 + countDiagonalL(player,row + step, column + step, step);
        }
    };
    bool checkDiagonalR(char player, int row, int column){
        int sum = 0;
        sum += countDiagonalR(player, row+1, column-1, 1);
        sum += countDiagonalR(player, row -1, column+1, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    int countDiagonalR(char player, int row, int column, int step){
        if(column > 2||grid[row][column] != player ){
            return 0;
        }else{
            return 1 + countDiagonalR(player,row + step, column - step, step);
        }
    };


};

class Game{
    public:
    Grid grid;
    std::array<char,2> players;
    char currentPlayer;
    int currentIdx;

    Game(){
        currentIdx = 0;
        players = getPlayers();
        currentPlayer = players[currentIdx];
    };
    
    void playGame(){
        bool winner = false;
        grid.printGrid();
        while(!winner){
            int row;
            int column;
            std::array<int,2> inputs = askInput();
            row = inputs[0] - '0';
            column = inputs[1] - '0';
            grid.playToken(currentPlayer,row,column);
            grid.printGrid();
            if(grid.checkHorizontal(currentPlayer, row, column) || grid.checkVertical(currentPlayer, row, column) 
            || grid.checkDiagonalL(currentPlayer,row,column)||grid.checkDiagonalR(currentPlayer, row,column)){
                winner = true;
            }
            nextPlayer();


        }
        std::cout << "You win" << endl;

    };

    std::array<int,2> askInput(){
        std::array<int,2> inputs;
        string input;
        
        
        std::cout << "Which row and column would you like to place your token? (format it as: 01) ";
        cin >> input;
        inputs[0] = input[0];
        inputs[1] = input[1];
        return inputs;
        

    };

    void nextPlayer(){
        currentIdx = (currentIdx+1)%2;
        currentPlayer = players[currentIdx];
    }

    std::array<char,2> getPlayers(){
        std::array<char,2> players;
        for(int i = 0; i < 2; i++){
            std::cout<< "Player " + std::to_string(i) +  " pick your letter "; 
            std::cin >> players[i];
        }
        return players;
    }

};


    



int main(){

    // Grid grid;
    // grid.grid[0][0] = 'X';
    // grid.grid[1][1] = 'X';
    // grid.grid[2][2] = 'X';
    // grid.printGrid();
    // std::cout << std::boolalpha << grid.checkDiagonalL('X',2,2);

    
    // char string[6] = "Yahya";
    // char* ptr = string;
    // std::cout << *ptr;


    Game game;
    // std::cout << game.askInput()[0];
    game.playGame();


}



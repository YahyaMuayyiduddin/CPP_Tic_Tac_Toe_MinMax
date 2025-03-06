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
     * Recursive call to check 
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
     * Recursive call to check 
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
            
            std::array<int,2> inputs = askInput();
            grid.playToken(currentPlayer,(int)inputs[0],(int)inputs[1]);
            grid.printGrid();
            if(grid.checkHorizontal(currentPlayer, (int)inputs[0],(int)inputs[1]) || grid.checkVertical(currentPlayer, (int)inputs[0],(int)inputs[1])){
                winner = true;
            }
            nextPlayer();


        }
        std::cout << "You win" << endl;

    };

    std::array<int,2> askInput(){
        std::array<int,2> inputs;
        
        std::cout << "Which row would you like to place your token?";
        cin >> inputs[0];
        std::cout << endl;
        std::cout << "Which column would you like to place your token? ";
        cin >> inputs[1];
        std::cout << endl;
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

    Game game;
    game.playGame();


}



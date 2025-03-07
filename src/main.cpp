#include <iostream>
#include <string>
#include <array>
 
using namespace std;
/**
 * 
 * Definition of a grid class
 * 
 */

 class Grid{
    public:
    std::array<std::array<char, 3> , 3> internalGrid;
    int rows;
    int column;
    int emptySpaces;

    Grid(){
        //Initialises an empty grid
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                internalGrid[i][j] = 'O';
                emptySpaces--;
            }
        }
        rows = 3;
        column = 3;

    };

    /**
     * 
     * Prints the grid
     * 
     */
    void printGrid(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                std::cout << internalGrid[i][j] << " ";
            }
        std::cout << endl;
        }
    };

    /**
     * 
     * Check if there is a horizontal 3 in a row based on the specified tile
     * @param player The player letter
     * @param row the row of the tile
     * @param column the column of the tile
     * 
     * @return 'true' if there is a 3 in a row, false otherwise
     */
    bool checkHorizontal(char player, int row, int column){
        int sum = 0;
        // Checks and counts how many matching tokens to the right of the tile
        sum += countHorizontal(player, row, column + 1, 1);
        // Checks and counts how many matching tokens to the left of the tile
        sum += countHorizontal(player, row, column - 1, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    /**
     * Recursive call to count how many matching tokens in the same row, given a direction
     * @param player The specified player letter
     * @param row The row of the tile called on
     * @param column The column of the tile called on
     * @param step The direction to check horizontally
     * 
     * @return How many matching tiles
     * 
     */
    int countHorizontal(char player, int row, int column, int step){
        if(column > 2||internalGrid[row][column] != player ){
            return 0;
        }else{
            return 1 + countHorizontal(player,row, column + step, step);
        }
    };

    /**
     * 
     * Check if there is a vertical 3 in a row based on the specified tile
     * @param player The player letter
     * @param row the row of the tile
     * @param column the column of the tile
     * 
     * @return 'true' if there is a 3 in a row, false otherwise
     */
    bool checkVertical(char player, int row, int column){
        int sum = 0;
        // Checks and counts how many matching tokens below the tile
        sum += countVertical(player, row+1, column, 1);
        // Checks and counts how many matching tokens above the tile
        sum += countVertical(player, row -1, column, -1);
        if(sum + 1 >= 3){
            return true;
        }
        return false;
        
    };
    /**
     * Recursive call to count how many matching tokens in the same row, given a direction
     * @param player The specified player letter
     * @param row The row of the tile called on
     * @param column The column of the tile called on
     * @param step The direction to check vertically
     * 
     * @return How many matching tiles
     * 
     */
    int countVertical(char player, int row, int column, int step){
        if(column > 2||internalGrid[row][column] != player ){
            return 0;
        }else{
            return 1 + countVertical(player,row + step, column, step);
        }
    };

    /**
     * 
     * Tries and plays the token and places it on the tile
     * 
     * @param player The player lettert
     * @param row The row to put the token in
     * @param column the column to put the token in
     * 
     */
    void playToken(char player, int row, int columns){
        if(internalGrid[row][columns] != 'O' || row >= rows ||  columns >= column){
            std::cout << "Invalid placement" << endl;
        }else{
            internalGrid[row][columns] = player;
            emptySpaces--;
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
        if(column > 2||internalGrid[row][column] != player ){
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
        if(column > 2||internalGrid[row][column] != player ){
            return 0;
        }else{
            return 1 + countDiagonalR(player,row + step, column - step, step);
        }
    };

    /**
     * 
     * Check if there is a 3 in a row from a given tile
     * 
     * @param player The player letter
     * @param row The row of the tile to check
     * @param column The column of the tile to check
     * @return 'true' if there is a 3 in a row, 'false' otherwise
     * 
     */
    bool checkWin(char player,int row, int column){
        return checkDiagonalL(player, row, column) || checkDiagonalR(player,row,column) || checkVertical(player, row, column) || checkHorizontal(player,row,column);
    }
    /**
     * 
     * Gets the number of empty spaces on a grid
     * 
     * @return number of empty spaces on the grid
     * 
     */
    int getEmptySpaces(){
        return emptySpaces;
    };

        
    



};

class Game{
    public:
    Grid grid;
    std::array<char,2> players;
    char currentPlayer;
    int currentIdx;
    char PC = 'X';

    Game(){
        // currentIdx = 0;
        // players = getPlayers();
        // currentPlayer = players[currentIdx];
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

    std::array<std::array<char, 3>,3>& getGrid(){
        return grid.internalGrid;
        
    }

    std::vector<std::array<int, 2>> getPositions(Grid gridCheck){

        std::vector<std::array<int, 2>> positions;
        for(int i = 0; i < gridCheck.internalGrid.size(); i++ ){
            for(int j = 0; j < gridCheck.internalGrid[i].size(); j++ ){
                if(gridCheck.internalGrid[i][j] == 'O'){
                    std::array<int,2> pos; 
                    pos[0] = i;
                    pos[1] = j;
                    positions.push_back(pos);


                }
                
            }
        }
        
        return positions;
    
    }

    int findMin(std::vector<int>& lst ){
        int currMin = std::numeric_limits<int>::max();
        for(int i = 0; i < lst.size(); i++){
            if(lst[i] < currMin){
                currMin = lst[i];
            }
        }
        return currMin;
    }

    int findMax(std::vector<int>& lst ){
        int currMax = std::numeric_limits<int>::min();
        for(int i = 0; i < lst.size(); i++){
            if(lst[i] > currMax){
                currMax = lst[i];
            }
        }
        return currMax;
    }

    std::array<int,2> findBestPlay(char player){
        int currIdx = 0;
        int currMax = std::numeric_limits<int>::min();
        std::vector<std::array<int,2>> positions = getPositions(grid);
        std::vector<int> scores;
        for(int i = 0; i < positions.size(); i++){
            
            scores.push_back(minMax(PC,positions[i][0], positions[i][1], grid));

            }

        for(int i = 0; i < scores.size(); i++){
            

            if (scores[i] == 1){
                return positions[i];
                
            }else{
                if(scores[i] > currMax){
                    currMax = scores[i];
                    currIdx = i;
                }
            }
            
        }
        return positions[currIdx];

    }

    int minMax(int index, int row, int column, Grid checkGrid){
        // std::vector<int> scores;
        if(checkGrid.checkWin(players[index], row, column) && players[index] == PC ){
            return +1;
        }else if(checkGrid.checkWin(players[index],row,column) && players[index] != PC){
            return -1;
        }else if(grid.getEmptySpaces() == 0){
            return 0;
        }
        else{
            std::vector<std::array<int, 2>> positions = getPositions(checkGrid);
            std::vector<int> validPos;
            int finalScore = 0;
            for(int i = 0; i < positions.size(); i++){
                checkGrid.playToken(players[index], positions[i][0], positions[i][1]);
                validPos.push_back(minMax((index+1)%2, positions[i][0], positions[i][1], checkGrid));
                checkGrid.internalGrid[positions[i][0]][positions[i][1]] = 'O';
            }
            for(int i = 0; i < validPos.size(); i++){
                if(players[index] == PC){
                    finalScore = findMax(validPos);
                }else{
                    finalScore = findMin(validPos);
                }

                }

                return finalScore;
                
            }
            
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
    game.grid.internalGrid[0][0] = 'P';
    game.grid.internalGrid[0][1] = 'X';
    game.grid.internalGrid[0][2] = 'P';
    game.grid.internalGrid[1][0] = 'P';
    game.grid.internalGrid[1][1] = 'X';
    game.grid.internalGrid[1][2] = 'X';
    game.grid.internalGrid[2][2] = 'X';
    game.grid.printGrid();
    std::array<int,2> bestPos = game.findBestPlay('X');
    std::cout << bestPos[0] << bestPos[1] << endl;
    game.grid.playToken('X',bestPos[0],bestPos[1]);
    game.grid.printGrid();



    // game.playGame();
    // game.getGrid()[0][1] = 'X';
    // std::vector<std::array<int, 2>> positions = game.getPositions();

    // for(int i = 0; i < positions.size();i++){
    //     std::cout << positions[i][0] << positions[i][1] <<endl;
    // }
    
    // std::cout << game.askInput()[0];
    // game.playGame();


}



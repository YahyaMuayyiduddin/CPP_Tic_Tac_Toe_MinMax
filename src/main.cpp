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
    int emptySpaces=0;

    Grid(){
        //Initialises an empty grid
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                internalGrid[i][j] = 'O';
                emptySpaces++;
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
        std::cout << endl;
        std::cout << "          Columns " << endl;
        std::cout << "         0   1   2" << endl;
        std::cout << "      ------------" << endl;
        for(int i = 0; i < 3; i++){
            if(i==1){
                std::cout << "Rows ";
                std::cout << "|"<<i<< "| ";
            }else{
                std::cout <<"     |"<< i<< "| ";
            }
            
            for(int j = 0; j < 3; j++){
                std::cout<< internalGrid[i][j] << "   ";
            }
         std::cout << "     | | "<<endl;
         std::cout << "     | | "<<endl;
        }
        std::cout << endl;
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
        if(column < 0 || column > 2||internalGrid[row][column] != player ){
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
        // std::cout << row <<endl;
        if(row < 0||row > 2||internalGrid[row][column] != player ){
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
    bool playToken(char player, int row, int columns){
        if(internalGrid[row][columns] != 'O' || row >= rows ||  columns >= column){
            std::cout << "Invalid placement" << endl;
            return false;
        }else{
            internalGrid[row][columns] = player ; //change later
            emptySpaces--;
            return true;
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
        if(column > 2||column < 0 || row > 2 || row < 0|| internalGrid[row][column] != player ){
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
        if(column > 2||column < 0 || row > 2 || row < 0|| internalGrid[row][column] != player ){
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
    std::array<char,2> players = {'P','X'};
    char currentPlayer;
    int currentIdx;
    char PC = 'X';

    Game(){
        currentIdx = 0;
        // players[1] = PC;
        // players[0] = 'P';
        // players = getPlayers();
        currentPlayer = players[currentIdx];
    };
    
    void playGame(){
        bool winner = false;
        std::cout <<endl<< "You are playing as player P. Your marks will be represented as capital P"<< endl <<"The PC will play against you, and X will represen its mark"<<endl;
        grid.printGrid();
        int row;
        int column;
        while(!winner){
            std::cout<<grid.emptySpaces <<endl;
            if(grid.emptySpaces==0){
                break;
            }
            std::cout << "Player "<< currentPlayer << " is playing" << endl;
            if(currentPlayer == PC){
                std::array<int,2> pos = findBestPlay(PC);
                row = pos[0];
                column = pos[1];
                grid.playToken(currentPlayer,row,column);

            }else{
            bool validPlay = false;
            while(!validPlay){
                std::array<int,2> inputs = askInput();
                row = inputs[0] - '0';
                column = inputs[1] - '0';
                validPlay = grid.playToken(currentPlayer,row,column);
            }
           

            }
            
            grid.printGrid();
            if(grid.checkHorizontal(currentPlayer, row, column) || grid.checkVertical(currentPlayer, row, column) 
            || grid.checkDiagonalL(currentPlayer,row,column)||grid.checkDiagonalR(currentPlayer, row,column)){
                winner = true;
                break;
            }
            
            nextPlayer();


        }
        if(grid.emptySpaces==0){
            std::cout<< "Draw!"<<endl;
        }
        else{
            std::cout << "Player " <<players[currentIdx]<< " wins!" << endl;

        }
    
        

   
        

    };

    std::array<int,2> askInput(){
        std::array<int,2> inputs;
        string input;
        bool validInput = false;
        while(!validInput){
        std::cout << "Which row and column would you like to place your token? (format it as: 01) "<<endl;
        cin >> input;
        if(input.size() > 2){
            std::cout << "Input should only be 2 digits" << endl;
        }else{
            inputs[0] = input[0];
        inputs[1] = input[1];
        validInput = true;
        }
        

        }
        
        
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

    /**
     * 
     * Method to pick the best move to play next
     * 
     * @param player The pc player letter
     * @return a 2 dimensional array containing the position coordinate of the best next move
     */
    std::array<int,2> findBestPlay(char player){
        int currIdx = 0;
        int currMax = std::numeric_limits<int>::min();
        //Gets available positions/empty positions on the grid
        std::vector<std::array<int,2>> positions = getPositions(grid);
        std::vector<int> scores;
        //Iterates through empty positions
        for(int i = 0; i < positions.size(); i++){
            //Places a token on the position
            grid.playToken(PC, positions[i][0],positions[i][1]);
            //Calls minMax to calculate the score of this branch, and pushes the score to scores
            scores.push_back(minMax((currentIdx+1)%2,positions[i][0], positions[i][1], grid));
            //Resets the grid to its original state before the recursive call
            grid.internalGrid[positions[i][0]][positions[i][1]] = 'O';
            grid.emptySpaces++;
            }
        //Finds the highest score, and sets the current iteration idex to be returned
        for(int i = 0; i < scores.size(); i++){
            // std::cout << scores[i]  << ' ' << positions[i][0] << positions[i][1] << endl;
                if(scores[i] > currMax){
                    currMax = scores[i];
                    currIdx = i;
                }
        }
        return positions[currIdx];

    }
    /**
     * 
     * Recursive implementation of the Mini-Max algorithm to find the next position to play.
     * PC player is considered the max player, and human player is the min player
     * @param index The player index in the recursive call/The player currently 'playing' in the simulation
     * @param row The row of the tile the token will be placed on for this branch
     * @param column The column of the tile the token will be placed on for this branch
     * @param checkGrid The copy of the grid to simulate/recurse on
     * 
     * @return The highest || lowest score based on the player in the recursive call
     * 
     */
    int minMax(int index, int row, int column, Grid checkGrid){
        //Base cases
        //If the tree ends with a PC player winning, return a score of 1
        if(checkGrid.checkWin(checkGrid.internalGrid[row][column], row, column) && checkGrid.internalGrid[row][column] == PC ){
            return +1;
        //If the tree ends with a Human player winning, return a score of -1
        }else if(checkGrid.checkWin(checkGrid.internalGrid[row][column],row,column) && checkGrid.internalGrid[row][column] != PC){
            return -1;
        //Tree ends in a draw, return 0
        }else if(grid.getEmptySpaces() == 0){
            return 0;
        }
        else{
            std::vector<int> scores;
            // Gets all available positions/ all empty positions
            std::vector<std::array<int, 2>> positions = getPositions(checkGrid);
            std::vector<int> validPos;
            int finalScore = 0;
            // Iterates through all available empty positions
            for(int i = 0; i < positions.size(); i++){
                // Puts the players token in the position on the copied grid
                checkGrid.playToken(players[index], positions[i][0], positions[i][1]);
                // Recursively calls minMax on the copied grid that was update, the next player, and the current positon
                // in the iteration. Then appends the score
                validPos.push_back(minMax((index+1)%2, positions[i][0], positions[i][1], checkGrid));
                checkGrid.internalGrid[positions[i][0]][positions[i][1]] = 'O';
            }
            // Picks score based on which player is in the recursive call
            for(int i = 0; i < validPos.size(); i++){
                if(players[index] == PC){
                    // Picks the highest score if the player in the recursive call is the PC
                    finalScore = findMax(validPos);
                }else{
                    // Picks the lowest score if the player in the recursive call is the human player
                    finalScore = findMin(validPos);
                }
                }
                return finalScore;
                
            }
            
        }
    

    };


    
int main(){

    
    Game game;
    game.playGame();
    // game.grid.internalGrid[0][0] = 'P';
    // game.grid.internalGrid[0][1] = 'X';
    // game.grid.internalGrid[0][2] = 'P';
    // game.grid.internalGrid[1][0] = 'P';
    // game.grid.internalGrid[1][1] = 'X';
    // game.grid.internalGrid[1][2] = 'X';
    // game.grid.internalGrid[2][2] = 'X';
    // game.grid.printGrid();
    // game.findBestPlay('X');

  

}



#include <iostream>
#include <array>
#include <cmath>
#include <vector>

using namespace std;

//here we create global variables that we will use for our bitmask

vector<int> rowMask(16,0);
vector<int> colMask(16,0);
vector<int> boxMask(16,0);
vector<pair<int,int>> emptyCells;


int getBoxIndex(int row, int col, int n) {
    int mod = sqrt(n); 
    return (row / mod) * mod + (col / mod);
}


//we are mapping our values to the bitmask here. I used geeksforgeeks to help me understand this
//basically we are trying to see what bits are already 'on' in our bitmask 
//so if we  say rowMask[2] = 0000001000100000  5 and 9 are on
//and then we do 1<<12 = 0001000000000000 this is bit 12 and we will then add this to our bitmask 
//then we do the or operation rowMask[2] |= (1 << 12)
//and we do binary addition to fill our mask that will look like this
//0001001000100000 
void setValues(vector<vector<int>>& grid){
    int n = grid.size();
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j]){
                rowMask[i] |= 1 << grid[i][j];
                colMask[j] |= 1 << grid[i][j];
                boxMask[getBoxIndex(i,j,n)] |= 1 << grid[i][j];
            }
        }
    }
}
    

//I also used geeksforgeeks to help me with this function here we are checking to see if a number is safe to place but it is a little different to how I did it for the 9x9 submission
//So what we do it initially say int bit = (1 << num); which checks to see if the current bit we are checking is 0
//then in our return statement we are checking if the bit is 'on' or 'off' 
//if we get back a number that is not 0 we know the number is used and it is not safe and the inverse applies for numbers that are 0
bool isSafe(vector<vector<int>>& grid, int row, int col,int num){

    int n = grid.size();
    int bit = (1 << num);
    int box = getBoxIndex(row,col,n);

    return !(rowMask[row]&bit) && !(colMask[col]&bit) && !(boxMask[box] & bit);
}


//After testing my algorithm with bitmasks it was much faster than without it but thought I could get it even faster to first see which cells are empty and only check those instead of going through the whole grid using MRV
void findEmptyCells(vector<vector<int>>& grid){
    int n = grid.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 0){
                emptyCells.push_back({i,j});
            }
        }
    }
}

//Basically this function is our MRV (minmum remaining values) function
//this finds the empty cells with the smallest count of valid numbers that can be placed
//so basically what we do is pick a cell that has the least number of options for numbers that could be placed and work our way up so that its easier to fill out the board with correct options 
//I modified this function so that it does not need to loop through the whole grid but rather it only checks the empty cells instead of calling findBestCell for every possible value
pair<int,int> findBestCell(vector<vector<int>>&grid){

    int n = grid.size();
    int bestRow = -1;
    int bestCol = -1;
    int best = n + 1;

    //modified this loop to only search the empty cells instead of the whole grid so there are less checks required. This made it much faster. 
    for(auto[i,j] : emptyCells){ 
            if(grid[i][j] == 0){
                
                int box = getBoxIndex(i,j,n);
                int blocked = rowMask[i] | colMask[j] | boxMask[box];
                int choose = 0;

                for(int num = 1; num <= n; num++){
                    if(!(blocked & (1 << num))){
                        choose++;
                    }
                }

                if(choose < best){
                    best = choose;
                    bestRow = i;
                    bestCol = j;

                    if(choose == 0) return {bestRow,bestCol};
                }
            }
    }

    return {bestRow,bestCol};
}

//Here we are updating our backtracking algorithm to use our bitmask to go through every possbility I also used geeksforgeeks to help me with this
//This function tries to assign values to all empty cells in our grid using our bitmask it works the same as the usual backtracking algorithm but uses our bitmask to fill out the board which is much more memory efficient
bool backTracking(vector<vector<int>>&grid){
    int n = grid.size();

    //since we using pair to find best cell easier to use auto variable. Just figured this out today and super useful !! 
    auto [row,col] = findBestCell(grid); 

    if(row == -1){
        return true;
    }

    for(int num = 1; num <=n; num++){
        if(isSafe(grid, row, col ,num)){
            grid[row][col] = num;

            int currBit = (1 << num);
            int box = getBoxIndex(row,col,n);

            //add bit to current cell and mark as used
            rowMask[row] |= currBit;
            colMask[col] |= currBit;
            boxMask[box] |= currBit;

            //check possibilities
            if(backTracking(grid)){
                return true;
            }

            grid[row][col] = 0;

            //flip bits and find another number that works
            rowMask[row] &= ~currBit;
            colMask[col] &= ~currBit;
            boxMask[box] &= ~currBit;
        }

    }

    return false;
}


void readInput(vector<vector<int>>& grid) {

    vector<int> numbers;

    string value;

    while (cin >> value) {
        int num;

        if(value[0] == 'A') num = 10;
        else if(value[0] == 'B') num = 11; 
        else if(value[0] == 'C') num = 12;
        else if(value[0] == 'D') num = 13;
        else if(value[0] == 'E')num = 14;
        else if(value[0] == 'F') num = 15;
        else if(value[0] == 'G') num = 16;
        else if(value[0] == 'H') num = 17;
        else if(value[0] == 'I') num = 18;
        else if(value[0] == 'J') num = 19;
        else if(value[0] == 'K') num = 20;
        else if(value[0] == 'L') num = 21;
        else if(value[0] == 'M') num = 22;
        else if(value[0] == 'N') num = 23;
        else if(value[0] == 'O') num = 24;
        else if(value[0] == 'P') num = 25;  
        
        else{ 
            num = stoi(value); 
        }

        numbers.push_back(num);
    }

    int numItems = numbers.size();
    int n = sqrt(numItems);

    grid.resize(n, vector<int>(n));

    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = numbers[idx++];
        }
    }
}

void printGrid(vector<vector<int>>& grid) {

    int n = grid.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if(grid[i][j] == 10) cout << 'A';
            else if(grid[i][j] == 11) cout << 'B';
            else if(grid[i][j] == 12) cout << 'C';
            else if(grid[i][j] == 13) cout << 'D';
            else if(grid[i][j] == 14) cout << 'E';
            else if(grid[i][j] == 15) cout << 'F';
            else if(grid[i][j] == 16) cout << 'G';
            else if(grid[i][j] == 17) cout << 'H';
            else if(grid[i][j] == 18) cout << 'I';
            else if(grid[i][j] == 19) cout << 'J';
            else if(grid[i][j] == 20) cout << 'K';
            else if(grid[i][j] == 21) cout << 'L';
            else if(grid[i][j] == 22) cout << 'M';
            else if(grid[i][j] == 23) cout << 'N';
            else if(grid[i][j] == 24) cout << 'O';
            else if(grid[i][j] == 25) cout << 'P';

            else{
                cout << grid[i][j];

            }


            if (j < n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid;
    readInput(grid);
    setValues(grid);  
    findEmptyCells(grid); 

    if(backTracking(grid)){
        printGrid(grid);
    } else {
        cout << "No Solution" << endl;
    }
}

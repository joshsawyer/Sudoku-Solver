#include <iostream>
#include <array>
#include <cmath>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& grid, int row, int col,int num){

    int n = grid.size();

    for(int i = 0; i < n; i++){
        if (grid[row][i] == num){
            return false;
        }
    }

    for(int i = 0; i < n; i++){
        if(grid[i][col] == num){
            return false;
        }
    }

    int mod = round(sqrt(n));

    int currRow = row - row%mod;
    int currCol = col - col%mod;

    for(int i = 0; i < mod; i++){
        for(int j = 0; j < mod; j++){
            if(grid[currRow + i][currCol + j] == num){
                return false;
            }
        }
    }

    return true;
}

pair<int,int> findBestCell(vector<vector<int>>&grid){

    int n = grid.size();
    int bestRow = -1;
    int bestCol = -1;
    int best = 17;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 0){
                int choose = 0;

                for(int k = 1; k <= n; k++){
                    if(isSafe(grid,i,j,k)){
                        choose++;
                    }
                }

                if(choose < best){
                    best = choose;

                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    return {bestRow,bestCol};
}

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

            if(backTracking(grid)){
                return true;
            }

            grid[row][col] = 0;
        }

    }

    return false;
}


void readInput(vector<vector<int>>& grid) {

    vector<int> numbers;

    string value;

    while (cin >> value) {
        int num;

        if(value[0] == 'A'){
            num = 10;
        }
        else if(value[0] == 'B'){
            num = 11;
        } 
        else if(value[0] == 'C'){
            num = 12;
        }
        else if(value[0] == 'D'){
            num = 13;
        }
        else if(value[0] == 'E'){
            num = 14;
        }
        else if(value[0] == 'F'){
            num = 15;
        }
        else if(value[0] == 'G'){
            num = 16;
        }   
        
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

            if(grid[i][j] == 10){
                cout << 'A';
            }
            else if(grid[i][j] == 11){
                cout << 'B';
            }
            else if(grid[i][j] == 12){
                cout << 'C';
            }
            else if(grid[i][j] == 13){
                cout << 'D';
            }
            else if(grid[i][j] == 14){
                cout << 'E';
            }
            else if(grid[i][j] == 15){
                cout << 'F';
            }
            else if(grid[i][j] == 16){
                cout << 'G';
            }
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

    if(backTracking(grid)){
        printGrid(grid);
    } else {
        cout << "No Solution" << endl;
    }

    readInput(grid);

    if(backTracking(grid)){
        printGrid(grid);
    } else {
        cout << "No Solution" << endl;
    }
}



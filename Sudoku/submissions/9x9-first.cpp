#include <iostream>
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

    int mod = sqrt(n);

    int currRow = row - row%mod;
    int currCol = col - col%mod;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(grid[currRow + i][currCol + j] == num){
                return false;
            }
        }
    }

    return true;


}

bool backTracking(vector<vector<int>>&grid){
    int col = -1;
    int row = -1;

    int n = grid.size();

    bool empty = true;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 0){
                row = i;
                col = j;

                empty = false;
                break;

            }

        }
        if(!empty){
            break;
        }
    }

    if(empty){
        return true;
    }

    //int num = 1;

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

    int value;
    while (cin >> value) {
        numbers.push_back(value);
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
            cout << grid[i][j];

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

    if(backTracking(grid)){
        printGrid(grid);
    } else {
        cout << "No Solution" << endl;
    }
}



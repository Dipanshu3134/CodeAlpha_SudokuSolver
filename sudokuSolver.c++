#include <iostream>
#include <vector>
using namespace std;

void printSudoku(const int arr[9][9]) {
    cout << "-------------------------" << endl;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
}

bool canPlace(const int arr[9][9], int row, int col, int num) {
    if (arr[row][col] != 0) return false;

    int gridX = (col / 3) * 3;
    int gridY = (row / 3) * 3;

    for (int i = 0; i < 9; i++) {
        if (arr[row][i] == num || arr[i][col] == num || arr[gridY + i / 3][gridX + i % 3] == num) {
            return false;
        }
    }
    return true;
}

void findNextEmpty(const int arr[9][9], int row, int col, int &nextRow, int &nextCol) {
    int indexNext = 9 * 9 + 1;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
        if (arr[i / 9][i % 9] == 0) {
            indexNext = i;
            break;
        }
    }
    nextRow = indexNext / 9;
    nextCol = indexNext % 9;
}

void copyArray(const int source[9][9], int dest[9][9]) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            dest[y][x] = source[y][x];
        }
    }
}

vector<int> findPlaceableNumbers(const int arr[9][9], int row, int col) {
    vector<int> placeables;
    for (int num = 1; num <= 9; num++) {
        if (canPlace(arr, row, col, num)) {
            placeables.push_back(num);
        }
    }
    return placeables;
}

bool solveSudoku(int arr[9][9], int row, int col) {
    if (row > 8) return true;

    if (arr[row][col] != 0) {
        int nextRow, nextCol;
        findNextEmpty(arr, row, col, nextRow, nextCol);
        return solveSudoku(arr, nextRow, nextCol);
    }

    vector<int> placeables = findPlaceableNumbers(arr, row, col);
    if (placeables.empty()) return false;

    for (int num : placeables) {
        int arrCopy[9][9];
        copyArray(arr, arrCopy);
        arrCopy[row][col] = num;

        int nextRow = row, nextCol = col;
        findNextEmpty(arrCopy, row, col, nextRow, nextCol);

        if (solveSudoku(arrCopy, nextRow, nextCol)) {
            copyArray(arrCopy, arr);
            return true;
        }
    }
    return false;
}

int main() {
    int board1[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int board2[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}
    };

    if (solveSudoku(board1, 0, 0)) {
        cout << "Successfully solved board 1!" << endl;
    } else {
        cout << "Failed to solve board 1." << endl;
    }
    printSudoku(board1);

    if (solveSudoku(board2, 0, 0)) {
        cout << "Successfully solved board 2!" << endl;
    } else {
        cout << "Failed to solve board 2." << endl;
    }
    printSudoku(board2);

    return 0;
}

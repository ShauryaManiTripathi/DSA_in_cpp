#include <bits/stdc++.h>
using namespace std;

// Changed macro names and added dummy macros
#define INTEGER_64 long long
#define LINE_BREAK '\n'
#define TRACE(variable) cout << #variable << " -> " << variable << LINE_BREAK
#define MATRIX_MAX 1000
#define UNUSED_CONSTANT 42

// Dummy struct for additional complexity
struct ProcessingConfig {
    bool enableLogging;
    int precision;
    string mode;
    ProcessingConfig() : enableLogging(false), precision(2), mode("standard") {}
} globalConfig;

// Dummy function that's never called
void debugMatrix(const vector<vector<int>>& matrix) {
    if (globalConfig.enableLogging) {
        for (const auto& row : matrix) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << LINE_BREAK;
        }
    }
}

void processMatrixOperation() {
    // Changed variable names
    int rows, columns;
    cin >> rows >> columns;
    
    // Added dummy variables
    int debugCounter = 0;
    bool optimizationFlag = true;
    
    // Renamed matrix variable and changed initialization
    vector<vector<int>> matrix(rows, vector<int>(columns));
    
    // Dummy vector for temporary calculations
    vector<int> tempBuffer(columns);
    
    // Modified input processing
    for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
        for (int colIndex = 0; colIndex < columns; colIndex++) {
            cin >> matrix[rowIndex][colIndex];
            // Dummy operation
            tempBuffer[colIndex] = matrix[rowIndex][colIndex];
        }
        // Kept original sorting
        sort(matrix[rowIndex].begin(), matrix[rowIndex].end());
        
        // Dummy condition
        if (optimizationFlag) {
            debugCounter++;
        }
    }
    
    // Changed variable names and added dummy processing
    bool validSequence = true;
    vector<int> resultMapping(rows);
    
    // Dummy function for validation
    auto validateSequence = [&](int diff) -> bool {
        return diff == rows || diff == -rows;
    };
    
    for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
        resultMapping[matrix[rowIndex][0]] = rowIndex;
        
        // Modified validation loop
        for (int colIndex = 0; colIndex < columns - 1; colIndex++) {
            int difference = matrix[rowIndex][colIndex + 1] - matrix[rowIndex][colIndex];
            if (!validateSequence(difference)) {
                validSequence = false;
                break;
            }
        }
    }
    
    // Changed output logic with dummy processing
    if (!validSequence || debugCounter < 0) {  // debugCounter < 0 is always false
        cout << "-1" << LINE_BREAK;
        return;
    }
    
    // Modified output format
    string outputBuffer;
    for (int index = 0; index < rows; index++) {
        outputBuffer += to_string(resultMapping[index] + 1) + " ";
    }
    cout << outputBuffer << LINE_BREAK;
}

int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("/home/shaurya/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/shaurya/Desktop/DSA_in_cpp/output", "w", stdout);
#endif
    // Added dummy optimization flags
    bool enableFastIO = true;
    string executionMode = "release";
    
    if (enableFastIO) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
    }
    
    // Modified file handling with dummy checks
    
    // Changed test case handling
    int testCaseCount = 1;
    cin >> testCaseCount;
    
    // Added dummy loop variable
    int successfulCases = 0;
    
    for (int caseIndex = 1; caseIndex <= testCaseCount; ++caseIndex) {
        processMatrixOperation();
        successfulCases++;  // Dummy counter
    }
    
    return 0;
}
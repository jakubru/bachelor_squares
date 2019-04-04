// Example program
#include <cstdlib>
#include <cstdio>

int count = 0;

bool canBeTransversal(char **square, char** result, int n, int k, int val){
    if(val == k%n){
        return false;
    }
    else{
        for(int i = 0; i < k; i++){
            char tmp = result[i/n][i%n];
            if(tmp == val){
                if(square[i/n][i%n] == square[k/n][k%n]){
                    return false;
                }
            }
        }
    }
    return true;
}


void checkTransversalsRec(char **square, char** result, int n, int k){
    if(k == n*n){
        return;
    }
    else{
        for(int i = 0; i < n; i++){
            if(canBeTransversal(square,result, n, k, i)){
                result[k/n][k%n] = i;
                return checkTransversalsRec(square,result, n, k + 1);
            }
        }
    }
}

char** checkTransversals(char** square, int n){
    char** result = new char*[n];
    for(int i = 0; i < n; i++){
        result[i] = new char[n];
    }
    for(int i = 0; i < n; i++){
        result[0][i] = i;
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n; j++){
            result[i][j] = -1;
        }
    }
    checkTransversalsRec(square, result, n, n);
    return result;
}


bool canExtendToLatinSquare(int n, char** square, int k, int val){
    int column = k%n;
    int row = k/n;
    for(int i = 0; i < column; i++){
        if(square[row][i] == val){
            return false;
        }
    }
    for (int j = 0; j < row; j++){
        if(square[j][column] == val){
            return false;
        }
    }
    return true;
    
    
}

void printLatinSquare(char** square, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void generateReducedLatinSquaresRec(int k, char** square, int n){
    int size = n*n;
    if(k == size){
        printLatinSquare(checkTransversals(square, n), n);
        count++;
    }
    else{
        if(k%n){
            for(int i = 0; i < n; i++){
                if(canExtendToLatinSquare(n, square,k,i)){
                    square[k/n][k%n] = i;
                    generateReducedLatinSquaresRec(k+1, square,n);
                }
            }
        }
        else{
            generateReducedLatinSquaresRec(k+1, square,n);
        }
    }
}

void generateReducedLatinSquares(int n){
    char** square = new char*[n];
    for (int i = 0; i < n; i++)
        square[i] = new char[n];
    
    for (int i = 0; i < n; i++){
        square[0][i] = i;
        square[i][0] = i;
    }
    generateReducedLatinSquaresRec(n + 1, square, n);
    for (int i = 0; i < n; i++)
        delete [] square[i];
    delete [] square;
}




int main()
{
    generateReducedLatinSquares(6);
}

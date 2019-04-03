// Example program
#include <cstdlib>
#include <cstdio>

int count = 0;
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
    /*char** square = new char*[4];
    for (int i = 0; i < 4; i++)
        square[i] = new char[4];
    
    for (int i = 0; i < 4; i++){
        square[0][i] = i;
        square[i][0] = i;
    }
    
    printLatinSquare(square, 4);
    
    printf("%d\n",canExtendToLatinSquare(4, square, 6, 3));
    
    */
    generateReducedLatinSquares(7);
    printf("%d ", count);
}

// Example program
#include <cstdlib>
#include <cstdio>

int count = 0;

void printLatinSquare(char **square, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

bool canBeTransversal(char **square, char** result, int n, int k, int val){
    for(int i = 0; i < k/n; i++){
        if(result[i][k%n] == val){
            return false;
        }
    }
    //jeśli poprzedni element w wierszu należy do tego transwersala, to nie może
    for(int i = 0; i < k%n; i++){
        if(result[k/n][i] == val){
            return false;
        }
    }
    //jeśli na transwersalu leży już element o takiej samej wartości, to nie może
    for(int i = 0; i < k; i++){
        if(result[i/n][i%n] == val){
            if(square[i/n][i%n] == square[k/n][k%n]){
                return false;
            }
        }
    }
    return true;
}


void checkTransversalsRec(char **square, char** result, int n, int k, bool& found){
    if(k == n*n){
        found = true;
    }
    else{
        for(int i = 0; i < n; i++){
            if(canBeTransversal(square,result, n, k, i) && !found){
                //printLatinSquare(result, n);
                result[k/n][k%n] = i;
                checkTransversalsRec(square,result, n, k + 1, found);
            }
        }
    }
}

bool checkTransversals(char** square, int n){
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
    bool found = false;
    checkTransversalsRec(square, result, n, n, found);
    return found;
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


void generateReducedLatinSquaresRec(int k, char** square, int n){
    int size = n*n;
    if(k == size){
        if(checkTransversals(square, n)){
            printLatinSquare(square, n);
        };
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

void generatePermutations(){
    
}


int main()
{
/*
    char **table = new char*[5];
    for(int i = 0; i <5; i++){
        table[i] = new char[5];
    }
    table[0][0]=0;
    table[0][1]=1;
    table[0][2]=2;
    table[0][3]=3;
    table[0][4]=4;
    table[1][0]=1;
    table[1][1]=2;
    table[1][2]=3;
    table[1][3]=4;
    table[1][4]=0;
    table[2][0]=2;
    table[2][1]=3;
    table[2][2]=4;
    table[2][3]=0;
    table[2][4]=1;
    table[3][0]=3;
    table[3][1]=4;
    table[3][2]=0;
    table[3][3]=1;
    table[3][4]=2;
    table[4][0]=4;
    table[4][1]=0;
    table[4][2]=1;
    table[4][3]=2;
    table[4][4]=3;
*/
    //printLatinSquare(table, 5);
    generateReducedLatinSquares(7);
    //checkTransversals(table, 5);
}

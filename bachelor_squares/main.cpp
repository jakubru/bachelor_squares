// Example program
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>

int count = 0;

typedef std::vector<std::vector<char>> LatinSquare;


LatinSquare toLatinSquare(char** square, int n){
    LatinSquare latinSquare;
    for(int i = 0; i < n;i++){
        latinSquare.push_back(std::vector<char>());
        for(int j = 0; j < n; j++){
            latinSquare[i].push_back(square[i][j]);
        }
    }
    return latinSquare;
}

void printLatinSquare(char **square, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void permute(char *a, int i, int n, char** perms, int &k)
{
    int j;
    if (i == n){
        for(int j = 0; j <= n; j++){
            perms[k][j] = a[j];
        }
        k = k+1;
    }
    else
    {
        for (j = i; j <= n; j++)
        {
            swap((a + i), (a + j));
            permute(a, i + 1, n, perms, k);
            swap((a+i), (a + j));
        }
    }
}



bool canBeTransversal(char **square, char** result, int n, int k, int val){
    //jeśli leży w kolumnie, w której już jes jakiś element k%n transwersala to nie bierzemy do transwersala
    for(int i = 0; i < k/n; i++){
        if(result[i][k%n] == val){
            return false;
        }
    }
    //jeśli poprzedni element w wierszu należy do tego transwersala, to nie bierzemy do transwersala
    for(int i = 0; i < k%n; i++){
        if(result[k/n][i] == val){
            return false;
        }
    }
    //jeśli na transwersalu leży już element o takiej samej wartości, to nie bierzemy do transwersala
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
            if(canBeTransversal(square,result, n, k, i) && !found){//jeśli nadal może być transwersalem, lub w poprzednim wywołaniu rekurencji jeszcze nie znaleźliśmy pełnego rozkładu to szuka nadal
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


void generateReducedLatinSquaresRec(int k, char** square, int n, std::list<LatinSquare> list){
    int size = n*n;
    if(k == size){
        if(checkTransversals(square, n)){
            list.push_back(toLatinSquare(square, n));
        };
    }
    else{
        if(k%n){
            for(int i = 0; i < n; i++){
                if(canExtendToLatinSquare(n, square,k,i)){
                    square[k/n][k%n] = i;
                    generateReducedLatinSquaresRec(k+1, square,n, list);
                }
            }
        }
        else{
            generateReducedLatinSquaresRec(k+1, square,n, list);
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
    std::list<LatinSquare> list;
    generateReducedLatinSquaresRec(n + 1, square, n, list);
    for (int i = 0; i < n; i++)
        delete [] square[i];
    delete [] square;
}

char** generatePermutations(int n){
    int fact = factorial(n);
    char **perms = new char*[factorial(n)];
    for(int i = 0; i < fact; i++){
        perms[i] = new char[n];
    }
    char *a = new char[n];
    for(int i = 0; i < n; i++){
        a[i] = i;
    }
    int k = 0;
    permute(a, 0 , n-1, perms, k);
    free(a);
    return perms;
}

void permuteRows(char* perm, LatinSquare square){

}

void permuteColumns(char* perm, LatinSquare square){
    
}

void permuteElements(char* perm, LatinSquare square){
    
}

bool compareSquares(LatinSquare square1, LatinSquare square2){
    return true;
}



int main()
{
    
}

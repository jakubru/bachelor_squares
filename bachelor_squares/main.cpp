// Example program
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

typedef std::vector<std::vector<char>> LatinSquare;
typedef void (*swap)(LatinSquare&, int, int);


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

void printLatinSquare(LatinSquare square, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
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


void generateReducedLatinSquaresRec(int k, char** square, int n, std::list<LatinSquare>* list){
    int size = n*n;
    if(k == size){
        if(checkTransversals(square, n)){
            list->push_back(toLatinSquare(square, n));
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

std::list<LatinSquare> generateReducedLatinSquares(int n){
    char** square = new char*[n];
    for (int i = 0; i < n; i++)
        square[i] = new char[n];
    
    for (int i = 0; i < n; i++){
        square[0][i] = i;
        square[i][0] = i;
    }
    std::list<LatinSquare> list;
    generateReducedLatinSquaresRec(n + 1, square, n, &list);
    for (int i = 0; i < n; i++)
        delete [] square[i];
    delete [] square;
    return list;
}


bool compareSquares(LatinSquare square1, LatinSquare square2){
    return true;
}

void swapColumn(LatinSquare &square, int i, int j){
    for (auto &v : square)
        std::swap(v[i], v[j]);
}

void swapRow(LatinSquare& square, int i, int j){
    std::iter_swap(square.begin() + i, square.begin() + j);
}

void swapElements(LatinSquare& square,  int i, int j){
    for(int k = 0; k < square.size(); k++){
        int a = 0;
        int b = 0;
        for(int l = 0; l != square[k].size(); l++){
            if(i == square[k][l]){
                a = l;
            }
            if(square[k][l] == j){
                b = l;
            }
        }
        std::swap(square[k][a], square[k][b]);
    }
}

void permute(char* permutation, LatinSquare& square, swap swap){
    int i = 0;
    int start = i;
    do{
        swap(square,i, permutation[i]);
        i = permutation[i];
        printLatinSquare(square, square.size());
    }
    while(permutation[i] != start);
}

void computeIsotopyClasses(std::list<LatinSquare>* list, int n){
    char* permutation = new char[n];
    for (std::list<LatinSquare>::iterator it=list->begin(); it != list->end(); ++it){
        for(int i = 0; i < n; i++){
            permutation[i] = i;
        }
        while(std::next_permutation(permutation, permutation + n)){
            permute(permutation, *it, swapRow);
            permute(permutation, *it, swapColumn);
            permute(permutation, *it, swapElements);

        }
    }
    delete [] permutation;
}



int main()
{
    std::list<LatinSquare> list= generateReducedLatinSquares(5);
    /*for (std::list<LatinSquare>::iterator it=list.begin(); it != list.end(); ++it){
        swapElements((*it), 3, 2);
        printLatinSquare(*it, 5);
    }*/
    LatinSquare square = *list.begin();
    char permutation[5] = {1,2,3,4,0};
    permute(permutation,square, swapRow);
    //computeIsotopyClasses(nullptr, 5);
    
}

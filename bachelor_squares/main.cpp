#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <cstring>

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

bool canBeTransversal(char **square, char** result, int n, int k, int val){
    //jeśli leży w kolumnie, w której już jest jakiś element tego transwersala to nie bierzemy do transwersala
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
        found = true;// potrzebujemy znaleźć tylko pierwsze rozbicie na transwersale, dalsze szukanie nie jest konieczne
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
    for(int i = 0; i < column; i++){//sprawdzam dla dodanej wartości czy zgadza się wierszu
        if(square[row][i] == val){
            return false;
        }
    }
    for (int j = 0; j < row; j++){//sprawdzam dla dodanej wartości czy zgadza się kolumnie
        if(square[j][column] == val){
            return false;
        }
    }
    return true;
    
    
}


void generateReducedLatinSquaresRec(int k, char** square, int n, std::list<LatinSquare>& list, int &count){
    int size = n*n;
    if(k == size){
        count = count+1;
        if(!checkTransversals(square, n)){
            list.push_back(toLatinSquare(square, n));
        };
    }
    else{
        if(k%n){
            for(int i = 0; i < n; i++){
                if(canExtendToLatinSquare(n, square,k,i)){
                    square[k/n][k%n] = i; //dodaję do następnej komórki macierzy wartość od 0 do n - 1 wtedy,gdy nadal jest szansa, że będzie to kwadrat łaciński
                    generateReducedLatinSquaresRec(k+1, square,n, list, count);
                }
            }
        }
        else{
            generateReducedLatinSquaresRec(k+1, square,n, list,count);//jeśli k%n = 0 to jesteśmy w pierwszej kolumnie i wartość w komórce jest ustalona
        }
    }
}

std::list<LatinSquare> generateReducedLatinSquares(int n, int &count){
    char** square = new char*[n];
    for (int i = 0; i < n; i++)
        square[i] = new char[n];
    
    for (int i = 0; i < n; i++){
        square[0][i] = i;
        square[i][0] = i;
    }
    std::list<LatinSquare> list;
    generateReducedLatinSquaresRec(n + 1, square, n, list, count);
    for (int i = 0; i < n; i++)
        delete [] square[i];
    delete [] square;
    return list;
}

bool compareSquares(LatinSquare &square1, LatinSquare &square2){
    for(int i = 0; i < square2.size(); i++){
        char* a = &square1[i][0];
        char* b = &square2[i][0];
        if(memcmp(a, b, square2.size())){//porównanie bloków pamięci
            return false;
        }
    }
    return true;
}

void swapColumn(LatinSquare &square, int i, int j){
    for (auto &v : square)
        std::swap(v[i], v[j]);
}

void swapRow(LatinSquare& square, int i, int j){
    std::iter_swap(square.begin() + i, square.begin() + j);
}


void renameVector(std::vector<char>& vector, std::vector<char> permutation){
    std::vector <char> tmp(vector.size());
    for(int i = 0; i < vector.size(); i++){
        tmp[i] = permutation[vector[i]];
    }
    for(int i = 0; i < vector.size(); i++){
        vector[i] = tmp[i];
    }
}

void renameElements(LatinSquare& square, std::vector<char> permutation){
    for(int i = 0; i < square.size(); i++){
        renameVector(square[i], permutation);
    }
}


void reversePermutation(std::vector<char> permutation, std::vector<char> &reverse){
    for(int i = 0; i < permutation.size(); i++){
        reverse[permutation[i]] = i;
    }
}

void swapInVector(std::vector<char> &vector, int i, int j){
    std::swap(vector[i], vector[j]);
}

//metoda szablonowa permutująca zadany ciąg
template<typename T>
void permute(std::vector<char> permutation, std::vector<T>& square, void (*swap)(std::vector<T>&, int, int)){
    int wasPermuted = 0;//nie używam do markowania tablicy bool, tylko pojedynczej zmiennej
    int end = (1 << square.size()) - 1;
    char i = 0;
    while(wasPermuted < end){
        char start = i;
        do{
            swap(square,i, permutation[i]);
            wasPermuted = wasPermuted | (1 << permutation[i]);
            i = permutation[i];
        }
        while(permutation[i] != start);
        wasPermuted = wasPermuted | (1 << start);
        i = 0;
        while(wasPermuted & 1 << i){
            i++;
        };
    }
}

void getFirstColumn(LatinSquare &square, std::vector<char> &column){
    for(int i = 0; i < square.size(); i++){
        column[i] = square[i][0];
    }
}

void computeIsotopyClasses(std::list<LatinSquare>& list, int n){
    std::vector<char> permutation(n);
    std::vector<char> permutation2(n);
    for (std::list<LatinSquare>::iterator it=list.begin(); it != list.end(); ++it){
        std::iota(permutation.begin(), permutation.end(),0);
        std::vector<char> reverse(n);
        while(std::next_permutation(permutation.begin(), permutation.end())){
            LatinSquare square(*it);
            permute(permutation, square, swapColumn);
            for(int i = 0; i < n; i++){
                LatinSquare square2(square);
                getFirstColumn(square2, permutation2);
                std::vector<char> permutation3(square[i]);
                reversePermutation(permutation2, reverse);
                permute(permutation3,reverse,swapInVector);
                permute(reverse, square2, swapRow);
                reversePermutation(permutation3, reverse);
                renameElements(square2, reverse);
                if(!compareSquares(square2, *it)){
                    std::list<LatinSquare>::iterator it2=list.begin();
                    while(it2 != list.end() && !compareSquares(square2, *it2)){
                        it2++;
                    }
                    if(it2 != list.end())
                        list.erase(it2);
                }
            }
        }
    }
}

int main()
{
    for(int i = 2; i < 7; i++){
        printf("n: %d\n", i);
        int count = 0;
        std::list<LatinSquare> list = generateReducedLatinSquares(i, count);
        printf("Liczba wszystkich zredukowanych: %d\n", count );
        printf("Liczba wszystkich zredukowanych bachelor: %d\n", list.size() );
        computeIsotopyClasses(list, i);
        printf("Liczba wszystkich zredukowanych wzajemnie nieizotopijnych bachelor: %d\n", list.size());
    }
}

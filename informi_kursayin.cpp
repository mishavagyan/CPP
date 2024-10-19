#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

void makeFile(int*);
void getMat(int mat[][50], int);
void printMatColored(int mat[][50], int, int minI[200], int minJ[200], int);
void makeMinFile(int, int mat[][50], int, int minI[200], int minJ[200]);
void printMinFile(int, int mat[][50], int, int minI[200], int minJ[200]);

int main() {
    int mat[50][50], n, i, j, k, z, f, o, q = 0, min, minI[200], minJ[200];
    makeFile(&n);
    getMat(mat, n);

    i = 0;
    for (j = 0; j < n + n - 1; j++) {
        if (j >= n) q++;
        k = q;
        z = j - q;
        min = mat[k][z];
        minI[i] = k;
        minJ[i] = z;
        f = k;
        o = z;

        while (z >= q) {
            if (mat[k][z] < min) {
                min = mat[k][z];
                minI[i] = k;
                minJ[i] = z;
            }
            k++;
            z--;
        }
        i++;

        // Handle additional minimums on the same diagonal
        while (o >= q) {
            if (mat[f][o] == min && minI[i-1] != f && minJ[i-1] != o) {
                minI[i] = f;
                minJ[i] = o;
                i++;
            }
            f++;
            o--;
        }
    }
    printMatColored(mat, n, minI, minJ, i);
    makeMinFile(i, mat, n, minI, minJ);
    printMinFile(i, mat, n, minI, minJ);

    return 0;
}

void makeFile(int *n) {
    cout << "Enter n = ";
    cin >> *n;

    ofstream fptr("matrix.txt");
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            int c = rand() % 100;
            fptr << c << " ";
        }
        fptr << endl;
    }
    fptr.close();
}

void getMat(int mat[][50], int n) {
    ifstream fptr("matrix.txt");
    if (fptr.is_open()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fptr >> mat[i][j];
            }
        }
        fptr.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

void printMatColored(int mat[][50], int n, int minI[200], int minJ[200], int count) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool isMin = false;
            for (int k = 0; k < count; k++) {
                if (i == minI[k] && j == minJ[k]) {
                    isMin = true;
                    break;
                }
            }
            if (isMin) {
                printf("\033[1;36m%3d\033[0m", mat[i][j]);
            } else {
                printf("%3d", mat[i][j]);
            }
        }
        cout << endl;
    }
}

void makeMinFile(int count, int mat[][50], int n, int minI[200], int minJ[200]) {
    ofstream fptr("minsFile.txt");
    for (int i = 0; i < count; i++) {
        fptr << mat[minI[i]][minJ[i]] << " " << minI[i] << " " << minJ[i] << endl;
    }
    fptr.close();
}

void printMinFile(int count, int mat[][50], int n, int minI[200], int minJ[200]) {
    cout << endl;
    ifstream fptr("minsFile.txt");
    if (fptr.is_open()) {
        for (int i = 0; i < count; i++) {
            int a, b, c;
            fptr >> a >> b >> c;
            cout << a << " " << b << " " << c << endl;
        }
        fptr.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

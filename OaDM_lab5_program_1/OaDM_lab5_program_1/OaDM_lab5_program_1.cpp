#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void dodo(int** table, int** score, int n, int m, int** u)
{
    /* for (int i = 0; i < n; i++)
     {
         for (int j = 0; j < m; j++)
             cout << setw(11) << setprecision(4) << table[i][j];
         cout << endl;
     }
     */
    for (int z = m - 2; z > 0; z--)
    {
        for (int i = 0; i < n; i++)
        {
            double ok = table[n - 1][z] + score[i][z + 1];
            int k = 0;
            score[i][z] = ok;
            for (int j = 0; j < n - i; j++)
                if (table[n - 1 - j][z] + score[i + j][z + 1] < ok)
                {
                    ok = table[n - 1 - j][z] + score[i + j][z + 1];
                    score[i][z] = ok;
                    k = j;
                    u[i][z] = k;
                }
            cout << " for state x" << z << " = " << setw(4) << i * 50 << " 000 , max profit = " << setw(8) << ok << " 000  it is for investing in company number " << z << " u = " << k * 50000 << "    ";
            cout << endl;
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        score[i][0] = score[i][1] + table[n - 1 - i][0];
        cout << "from x0 = 0 through x1 = " << i << ", max profit = " << score[i][0] << " 000 , for investing in company number 0 u = " << i * 50000 << endl;
        u[i][0] = i;
    }
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            cout << setw(7) << u[i][j];
        }
        cout << endl;
    }
    int path[5];
    cout << "        ";
    for (int i = 0; i < m; i++)
    {
        cout << setw(7) << "x" << i + 1;
    }
    cout << endl;
    for (int y = 0; y < n; y++)
    {
        int ui = 0;
        path[0] = u[y][0];
        cout << "path " << y + 1 << " -> " << setw(8) << path[0] * 50000;
        for (int i = 1; i < m; i++)
        {
            path[i] = u[path[i - 1]][i] + path[i - 1];
            int p = 0;
            for (int g = 0; g < i; g++)
                p += path[g];
            cout << setw(8) << (path[i]) * 50000;
        }
        cout << "   profit = " << score[y][0] * -1000 << endl;
    }
}

int main()
{
    int n = 7, m = 5;
    int** u;
    int** array;
    array = new int* [n];
    int table[7][5] = { {0,0,0,0,0},{10,15,40,20,10},{20,20,40,25,10},{25,30,40,30,30},{26,35,45,35,35},{40,35,45,40,50},{45,35,45,45,55} };
    u = new int* [n];
    for (int i = 0; i < n; i++)
        u[i] = new int[m];
    for (int i = 0; i < n; i++)
        array[i] = new int[m];
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
        {
            array[n - 1 - i][j] = int(table[i][j] * -1);
            u[i][j] = 0;
        }

    int** score;
    score = new int* [n];
    for (int i = 0; i < n; i++)
        score[i] = new int[m];

    for (int i = 0; i < n; i++)
    {
        score[i][4] = array[i][4];
        // << score[i][4]<<"    ";
        u[i][4] = n - i - 1;
        cout << " for state x4 = " << setw(4) << i * 50 << " 000 , max profit = " << setw(8) << array[i][4] << " 000  it is for investing in company number 5 u = " << u[i][4] * 50000 << "    " << endl;
        u[i][4] = n - i - 1;
    }
    cout << endl;
    dodo(array, score, n, m, u);
    double on = score[0][1];
    int l;
    for (l = 0; l < n - 1; l++)
    {
        if (score[l][1] > score[l + 1][1])
            on = score[l + 1][1];
    }
    cout << "\n\nmaximum profit equals = " << on * -1000 << " for path number " << n - l << endl;
    for (int i = 0; i < n; i++)
    {
        delete[] array[i];
        delete[] score[i];
    }
    delete[] array;
    delete[] score;


}

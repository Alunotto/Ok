#include <iostream>
#include <iomanip>

using namespace std;

void printmat(double** tab, int n, int m, string* znaczki, int* arryyy) //this function is for visual purposes only it just prints the tableu
{
    for (int i = -1; i < n; i++)
    {
        for (int j = -1; j < m; j++)
            if (i >= 0 && j >= 0)
                cout << setw(11) << setprecision(4) << tab[i][j];
            else if (i < 0 && j >= 0)
            {
                if (m == 6 && j == 5)
                    cout << setw(11) << znaczki[7];
                else
                    cout << setw(11) << znaczki[j];
            }
        if (i >= 0)
            cout << "    " << znaczki[arryyy[i]];
        cout << endl;
    }
    cout << endl;
}
int minel(double* tab, int nje)       // this function finds minimum element in a given row and returns number of this column
{
    int witch = 1;
    for (int i = 1; i < (nje - 2); i++)
        if (tab[i] > tab[witch])
            witch = i;
    return witch;
}
int pivotel(double** tab, int n, int m, int pivotcol)   //this function returns number of element chosen in pivot column after ratio test
{
    int witch = 1;
    for (int i = 1; i < n - 1; i++)
    {
        if (tab[witch][pivotcol] < 0)
            witch++;
        if ((tab[i + 1][m - 1] / tab[i + 1][pivotcol]) < (tab[witch][m - 1] / tab[witch][pivotcol]) && tab[i + 1][pivotcol] > 0)
            witch = i + 1;
    }
    if (tab[witch][pivotcol] < 0)
        cout << "tarapaty" << endl;
    return witch;
}
void pivoting(double** tab, int n, int m, int pivotrow, int pivotcol)    //this function makes pivot element = 1 and sets other elements
{                                                                        //in pivot column to zero with usage of ero
    double help = tab[pivotrow][pivotcol];
    if (tab[pivotrow][pivotcol] != 1)
    {
        for (int i = 0; i < m; i++)
            if (i != pivotcol)
                tab[pivotrow][i] = tab[pivotrow][i] / tab[pivotrow][pivotcol];
        tab[pivotrow][pivotcol] = tab[pivotrow][pivotcol] / tab[pivotrow][pivotcol];
    }
    for (int i = 0; i < n; i++)
    {
        if (i != pivotrow)
        {
            help = tab[i][pivotcol];
            for (int f = 0; f < m; f++)
            {
                tab[i][f] -= help * tab[pivotrow][f];
                if (tab[i][f] > -0.000001 && tab[i][f] < 0.000001)
                    tab[i][f] = 0;
            }

        }
    }
}

void dodo(double** array, int n, int m, string* znaczki, int* arryyy, int cntarryyy, int* arr, int cntarr, int* fun, int cntfun)
{                               //this is function responsible for controling whole process of simplex method
                                //it prints tableu after each step and with usage of if statements and loops 
                                //assures that every step would be done as many times as required which means that program should also work for higher dimensions problems

    int max = 0;
    int pivotcol = 0, pivotrow = 0;
    printmat(array, n, m, znaczki, arryyy);
    for (int i = 0; i < cntarr; i++)                //at first we need to make all a equal to 0 in z row
    {
        if (array[0][arr[i]] != 0)
        {
            max = array[i + 1][arr[i]] / array[0][arr[i]];
            for (int j = 0; j < m; j++)
                array[0][j] -= array[i + 1][j] * max;
        }
        printmat(array, n, m, znaczki, arryyy);
    }
    for (int i = 0; i < n - 1; i++)         //if after previous procedure there are still some left none zero values for all a in z row
    {                                       //then it means that program done sth wrong
        if (array[0][arr[i]] != 0)
            cout << "wow problems" << endl;
    }
    bool chaka = 0;
    while (true)                            //here program searches for pivot element using functions and then use pivoting function
    {
        chaka = 1;
        for (int i = 1; i < (m - 1); i++)
        {
            if (array[0][i] > 0)
                chaka = 0;
        }
        if (chaka == 1)
            break;
        pivotcol = minel(array[0], m);
        pivotrow = pivotel(array, n, m, pivotcol);
        pivoting(array, n, m, pivotrow, pivotcol);
        arryyy[pivotrow] = pivotcol;
        printmat(array, n, m, znaczki, arryyy);
    }
    double** newarray;                  //after this process program is ready to drop columns with a variables and creates new array with reduced number of columns
    newarray = new double* [n];
    for (int i = 0; i < n; i++)
        newarray[i] = new double[m - cntarr];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m - cntarr; j++)
            array[i][j] = array[i][j];

    int cnt = 0;
    bool cani = 1;
    for (int i = 0; i < n; i++)              //here program writes data from our previous tableu to new one with reduced number of columns
    {
        cnt = 0;
        for (int u = 0; u < m; u++)
        {
            cani = 1;
            for (int y = 0; y < cntarr; y++)
                if (u == arr[y])
                    cani = 0;
            if (cani == 1)
            {
                newarray[i][cnt] = array[i][u];
                cnt++;
            }
        }
    }
    printmat(newarray, n, m - cntarr, znaczki, arryyy);
    for (int i = 0; i < cntfun; i++)         //here programs write according values ffrom our function to z row
    {
        newarray[0][i + 1] = fun[i];
        newarray[0][i + 1] = fun[i];
    }
    double helpy = 0;
    int j;
    printmat(newarray, n, m - cntarr, znaczki, arryyy);
    for (int i = 1; i < m - 1; i++)         //and in this loop program will make all basic variables in z row = 0 by using ero
    {
        cani = 0;
        j = 1;
        for (; j < cntarryyy; j++)
            if (arryyy[j] == i)
            {
                cani = 1;
                break;
            }
        if (newarray[0][i] < 0 && cani == 1)
        {    
            helpy = newarray[0][i];
            for (int h = 0; h < m - cntarr; h++)
                newarray[0][h] -= newarray[j][h] * helpy;
            printmat(newarray, n, m - cntarr, znaczki, arryyy);
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << "max when: " << znaczki[arryyy[i]] << " = " << newarray[i][m - cntarr - 1] << endl;
    }
}

int main()
{
    int n = 3;
    int m = 8;

    double x1 = 0;
    double x2 = 0;

    string* znaczki;
    znaczki = new string[m];
    string getznaczki[8] = { "z","x1", "x2", "s1", "s2", "a1", "a2", "rs" };            //creating array with signs for visual purposes only 
    for (int i = 0; i < m; i++)
        znaczki[i] = getznaczki[i];

    double** array;
    array = new double* [n];
    for (int i = 0; i < n; i++)                     //creating our tableu
        array[i] = new double[m];
    double getarray[3][8] = { {1,0,0,0,0,-1,-1,0},{0,-1,6,1,0,1,0,12},{0,5,2,0,1,0,1,68} };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            array[i][j] = getarray[i][j];

    int* arryyy;
    arryyy = new int[n];                        //denoting basic variables
    int getarryyy[3] = { 0,5,6 };
    for (int i = 0; i < n; i++)
        arryyy[i] = getarryyy[i];

    int* arr;
    arr = new int[n - 1];
    int getarr[2] = { 5,6 };
    for (int i = 0; i < n - 1; i++)                 // denoting places of a
        arr[i] = getarr[i];

    int fun[2] = { -1,-2 };
    cout << "minimize: -1x1 - 2x2, constraints :  -x1 +6x2 >= 12,   5x1 + 2x2 >= 60,    x1, x2 >= 0" << endl<<endl;
    dodo(array, n, m, znaczki, arryyy, 3, arr, 2, fun, 2);      //proceding with simplex method

    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "minimize: -5x1 - 4x2, constraints :  4x1 + 2x2 <= 32,   2x1 + 3x2 <= 24,    x1, x2 >= 0" << endl<<endl;
    double getarrayy[3][8] = { {1,0,0,0,0,-1,-1,0},{0,4,2,1,0,1,0,32},{0,2,3,0,1,0,1,24} };         //tableu for second example
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            array[i][j] = getarrayy[i][j];
    int funn[2] = { -5,-4 };
    dodo(array, n, m, znaczki, arryyy, 3, arr, 2, funn, 2);
    delete[] arr;
    delete[] arryyy;
    delete[] znaczki;
    for (int i = 0; i < n; i++)                   
        delete[] array[i];
    delete[] array;

    return 0;
}
#include <iostream>     
#include <fstream>     
#include <string>       
#include <windows.h>    

using namespace std;    

int main()
{
    int length = 0, length2, counter = 0, i, counter2 = 0, counter3 = 0;                                                                                                          
    int* position;           
    char* check;          
    bool av = 1;          
    char bin;             
    fstream dictionary;     
    string word;          
    for (;;)              
    {
        if (av == 0)      
            break;
        system("cls");     
        cout << "Please select what would you like to do next and enter according number" << endl;
        cout << "1. Search for anagrams in given dictionary" << endl;
        cout << "2. Add new words to the dictionary" << endl;
        cout << "Other char. Exit app" << endl;
        cin >> bin;                     
        switch (int(bin))               
        {
        case 49:                      
            length = 0;
            counter2 = 0;               
            cout << "Please enter any word: ";
            cin >> word;             
            cout << "Your anagrams:" << endl;
            for (int n = 0;; n++)       
                if (word[n] != '\0')
                    length++;
                else
                    break;
            position = new int[length];        
            check = new char[length];         
            dictionary.open("Dictionary.txt", ios::in);    
            if (!dictionary)                               
                cout << "oops" << endl;
            while (!dictionary.eof())          
            {
                av = 1;
                i = 0;
                counter = 0;
                counter3 = 0;
                length2 = 0;                    
                for (int y = 0; y < length; y++)   
                    position[y] = 0;
                dictionary >> noskipws >> bin;      
                while (!dictionary.eof() && int(bin) != 10 && bin != '\n' && int(bin) != 32)    
                {
                    if (i < length)                  
                        check[i] = bin;            
                    dictionary >> noskipws >> bin;  
                    i++;
                    if (i == (length + 1))          
                    {
                        while (int(bin) != 10 && bin != '\n' && !dictionary.eof())  
                        {
                            dictionary >> noskipws >> bin;
                            av = 0;
                        }
                        break;
                    }
                }
                if (i == length)                  
                {
                    for (int g = 0; g < length; g++)    
                    {
                        for (int j = 0; j < length; j++)
                        {
                            if (word[g] == check[j] && position[j] != 887) 
                            {
                                counter++;
                                position[j] = 887;
                                break;
                            }
                        }
                    }
                    if (counter == length)   
                    {
                        for (int nb = 0; nb < length; nb++)
                            if (word[nb] == check[nb])
                                counter3++;
                        if (counter3 == length)
                            av = 0;
                        if (av == 1)
                        {
                            for (int y = 0; y < length; y++)
                                cout << check[y];
                            cout << endl;
                            counter2++;
                        }

                    }
                }
            }
            dictionary.close();        
            cout << "Total number of anagrams: " << counter2 << endl;
            delete[] position;
            delete[] check;           
            cout << "Please enter some char to continue" << endl;
            cin >> bin;                 
            av = 1;                    
            break;
        case 50:
            dictionary.open("Dictionary.txt", ios::app);    
            cout << "Please enter word You want to add to dictionary (if you want to add many words just separate them with spaces) " << endl;
            cin >> word;        
            getline(cin, word);  
            for (i = 0; word[i] != '\0'; i++)
                if (word[i] == ' ')
                    word[i] = '\n';         
            dictionary << noskipws << word;   
            dictionary.close();             
            break;
        default:
            cout << "Goodbye" << endl;
            av = 0;                        
            break;
        }
    }
}

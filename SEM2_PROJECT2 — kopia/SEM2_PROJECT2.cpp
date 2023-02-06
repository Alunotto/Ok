#include <iostream>
#include <fstream>          //to use files
#include <math.h>           //to use pow() function
#include <string>           //to acquire strings with spaces between words
#include <windows.h>        //to use some domestic functions

using namespace std;

class car
{
public:
    char bn[50];            //car brand
    char issues[50];        //what issues car has
    char pricee[50];        //how much it costs to rent this car
    int price = 0;          //as above but as number
};

class user
{
public:
    char name[50];          //name of the user
};

class operation : public user, car
{
public:
    char name[50];          //name of the user who is currently renting car/or has rented car as the last person
    char carbn[50];         //name of the car whgich he is renting
    bool rented;            // 1 if the car is rented and 0 if car is available
    char rentedc;           // as above but char
};

class superglue
{
public:
    int cars = 0;           // number of cars and operations in database
    int users = 0;          //number of users in database
};

int howmany(fstream& a,int b)       //calculating how many cars or anything is in the file with special denoted data
{                                   //first argument is file second is how many lines should be counted as one 
    int counter = 0;        
    int thatmany = 0;
    char bin;
    for (; !a.eof();)
    {
        a >> bin;
        if (bin == ';')
            if (counter == b)
            {
                thatmany++;
                counter = 0;
            }
            else
                counter++;
    }
    return thatmany;
}

int main()
{
    char bin{};
    char choice;
    string name;
    bool av = 0,av2 = 1,av3 = 1,av4=0;
    class superglue master;
    fstream fcars;          // There are 3 files: with users, with cars and with operations 
    fstream fusers;
    fstream foperations;
    for (;av3==1;)
    {
        av2 = 1;        
        system("cls");              //main menu
        cout << "Please select what would you like to do next and enter according number" << endl;
        cout << "(1)Edit car database" << endl;
        cout << "(2)Edit user database" << endl;
        cout << "(3)Edit operations database" << endl;
        cout << "(4)take a look into databases" << endl;
        cout << "(5)Exit app" << endl;
        cin >> choice;
        switch ((int)choice)                
        {
        case 49:
            av2 = 1;
            for (;av2==1;)
            {
                av4 = 1;
                fcars.open("Cars.txt", ios::in);
                master.cars = howmany(fcars, 2);        //calculating how many cars is database
                fcars.close();
                fcars.open("Cars.txt", ios::in);
                car* ocars = new car[master.cars];      //creating that many objects
                for (; !fcars.eof();)                   //filling this objects with data
                {
                    for (int i = 0; i < master.cars && !fcars.eof(); i++)
                    {
                        int n;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].bn[n] = bin;
                            fcars >> noskipws >> bin;
                        }
                        ocars[i].bn[n] = '\0';
                        fcars >> bin;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].issues[n] = bin;
                            fcars >> noskipws >> bin;
                        }
                        ocars[i].issues[n] = '\0';
                        fcars >> bin;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].pricee[n] = bin;
                            fcars >> bin;
                        }
                        ocars[i].pricee[n] = '\0';
                        for (int m = 0; m < n; m++)
                        {
                            ocars[i].price += (((int)ocars[i].pricee[m]) - 48) * pow(10.0, (n - m - 1));
                        }
                        fcars >> noskipws >> bin;
                        fcars >> noskipws >> bin;
                    }
                    for (; !fcars.eof();)
                        fcars >> noskipws >> bin;
                }
                foperations.open("Operations.txt",ios::in);
                operation* ooperations = new operation[master.cars];        //the same situation for operations (ratio of number of cars and operations is constant) 
                for (; !foperations.eof();)                                 //(there is one operation for every car      
                {
                    for (int i = 0; i < master.cars && !foperations.eof(); i++)
                    {
                        int n;
                        foperations >> bin;
                        if (foperations.eof())
                            break;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].carbn[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].carbn[n] = '\0';
                        foperations >> noskipws >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].name[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].name[n] = '\0';
                        foperations >> noskipws >> bin;
                        foperations >> noskipws >> bin;
                        ooperations[i].rentedc = bin;
                        ooperations[i].rented = (int(bin) - 48);
                        foperations >> noskipws >> bin;
                    }
                    for (; !foperations.eof();)
                        foperations >> noskipws >> bin;
                }
                foperations.close();
                fcars.close();
                system("cls");          //submenu
                cout << "Please select what would you like to do next and enter according number" << endl;
                cout << "(1)Edit car info" << endl;
                cout << "(2)Add another car" << endl;
                cout << "(3)Delete car" << endl;
                cout << "(4)Exit this menu" << endl;
                cin >> choice;
                switch ((int)choice)
                {
                case 49:
                    system("cls");
                    cout << "Please enter brand of the car which data You want to edit" << endl;
                    cin >> name;
                    int i;
                    for (i = 0; i < master.cars; i++)       //checking if given car exists
                    {
                        if ((string)ocars[i].bn == name)
                        {
                            av = 1;
                            break;
                        }
                    }
                    if (av != 1)
                    {
                        cout << "Car not found" << endl;
                        cout << "Enter some character to continue" << endl;
                        cin >> choice;
                    }
                    else
                    {
                        for (; av2 == 1;)
                        {
                            av2 = 1;            //if car exist then there is subsubmenu
                            system("cls");
                            cout << "Please select what would you like to change" << endl;
                            cout << "(1)Brand name" << endl;
                            cout << "(2)Issues with car" << endl;
                            cout << "(3)Car rent price" << endl;
                            cout << "(4)I am done(save changes)" << endl;
                            cin >> choice;
                            switch ((int)choice)
                            {
                            case 49:
                                cout << "Please enter new car brand name" << endl;
                                cin.ignore();
                                getline(cin, name);
                                int h;
                                for (h = 0; name[h] != '\0'; h++)           //changing already existing name 
                                    ocars[i].bn[h] = name[h];
                                ocars[i].bn[h] = '\0';
                                for (h = 0; name[h] != '\0'; h++)           //as above but this time in operation database
                                    ooperations[i].carbn[h] = name[h];
                                ooperations[i].carbn[h] = '\0';
                                break;
                            case 50:
                                cout << "Please enter what issues car has now" << endl;
                                cin.ignore();
                                getline(cin, name);
                                for (h = 0; name[h] != '\0'; h++)           //changing issues with car
                                        ocars[i].issues[h] = name[h];
                                
                                ocars[i].issues[h] = '\0';
                                break;
                            case 51:
                                cout << "Please enter new price for renting" << endl;
                                cin >> name;
                                for (h = 0; name[h] != '\0'; h++)           //changing price for rent
                                    ocars[i].pricee[h] = name[h];
                                ocars[i].pricee[h] = '\0';
                                break;
                            case 52:
                                fcars.close();
                                fcars.open("Cars.txt", ios::out | ios::trunc);          //clearing file
                                fcars.close();
                                fcars.open("Cars.txt", ios::app);                       //filling file with new data from object
                                for (int i = 0; i < master.cars; i++)
                                {
                                    fcars << noskipws << (string)ocars[i].bn << ';' << '\n';
                                    fcars << noskipws << (string)ocars[i].issues << ';' << '\n';
                                    fcars << noskipws << (string)ocars[i].pricee << ';' << '\n' << '\n';
                                }
                                fcars.close();
                                foperations.open("Operations.txt", ios::out | ios::trunc);  //clearing file
                                foperations.close();
                                foperations.open("Operations.txt", ios::app);       
                                for (int n = 0; n < master.cars; n++)                       //filling file with new data from object
                                {
                                        foperations << noskipws << (string)ooperations[n].carbn << ';' << '\n';
                                        foperations << noskipws << (string)ooperations[n].name << ';' << '\n';
                                        foperations << noskipws << ooperations[n].rentedc << ';' << '\n' << '\n';
                                    
                                }
                                foperations.close();
                                av2 = 0;
                                break;
                            default:
                                cout << "Enter proper number" << endl;        //info for wrong character
                                Sleep(5000);
                                break;
                            }
                        }
                        av2 = 1;
                    }
                    delete ocars;                               //deleting already existing objects to create them again when returning to submenu with new data
                    delete ooperations;
                    break;
                case 50:
                    system("cls");
                    fcars.close();
                    foperations.close();
                    fcars.open("Cars.txt", ios::app);
                    foperations.open("Operations.txt", ios::app);               //adding new car to car database
                    cout << "Please enter brand name of car you want to add" << endl;
                    cin.ignore();
                    getline(cin, name);
                    fcars << noskipws << name << ';' << '\n';
                    foperations << noskipws << name << ';' << '\n' << "none" << ';' << '\n' << '0' << ';' << '\n' << '\n';  //adding new car to operation database
                    cout << "\nPlease enter what issues does this car have" << endl;
                    cin.sync();
                    getline(cin, name);
                    fcars << noskipws << name << ';' << '\n';
                    cout << "\nPlease enter how much will it cost to rent this car" << endl;
                    cin >> name;
                    fcars << noskipws << name << ';' << '\n';
                    fcars.close();
                    foperations.close();
                    delete ocars;                //deleting already existing objects to create them again when returning to submenu with new data (this time this step was necessary not only because of program structure)
                    delete ooperations;
                    break;
                case 51:
                    system("cls");
                    cout << "Please enter brand of the car which data You want to delete" << endl;
                    cin.ignore();
                    getline(cin, name);
                    int m;
                    for (m = 0; m < master.cars; m++)           //checking if this car exists in database
                    {
                        if ((string)ocars[m].bn == name)
                        {
                            av = 1;
                            break;
                        }
                    }
                    if (av != 1)
                        cout << "Car not found" << endl;
                    else
                    {
                        fcars.open("Cars.txt", ios::out | ios::trunc);
                        fcars.close();
                        fcars.open("Cars.txt", ios::app);
                        for (int n = 0; n < master.cars; n++)           //printing data to file without chosen car
                        {
                            if (n != m)
                            {
                                fcars << noskipws << (string)ocars[n].bn << ';' << '\n';            
                                fcars << noskipws << (string)ocars[n].issues << ';' << '\n';
                                fcars << noskipws << (string)ocars[n].pricee << ';' << '\n' << '\n';
                            }
                        }
                        fcars.close();
                        foperations.open("Operations.txt", ios::out | ios::trunc);
                        foperations.close();
                        foperations.open("Operations.txt", ios::app);
                        for (int n = 0; n < master.cars; n++)           //printing data to file without chosen car
                        {
                            if (n != m)
                            {
                                foperations << noskipws << (string)ooperations[n].carbn << ';' << '\n';
                                foperations << noskipws << (string)ooperations[n].name << ';' << '\n';
                                foperations << noskipws << ooperations[n].rentedc << ';' << '\n' << '\n';
                            }
                        }
                        foperations.close();
                    }
                    delete ocars;           //deleting already existing objects to create them again when returning to submenu with new data (this time this step also was necessary not only because of program structure)
                    delete ooperations;
                    break;                   
                case 52:
                    av2 = 0;
                    break;
                default:
                    cout << "Enter proper number" << endl;
                    Sleep(5000);
                    delete ocars;           //deleting already existing objects to create them again when returning to submenu with new data
                    delete ooperations;
                    break;
                }
            }
            av2 = 1;
            break;
        case 50:
            for (; av2 != 0;)
            {
                fusers.open("Users.txt", ios::in);
                foperations.open("Operations.txt", ios::in);
                fcars.open("Cars.txt", ios::in);
                master.cars = howmany(fcars, 2);        //calculating number of cars
                master.users = howmany(fusers, 0);      //calculating number of users
                fusers.close();
                fusers.open("Users.txt", ios::in);
                user* ousers = new user[master.users];      //creating new objects
                operation* ooperations = new operation[master.cars];
                for (; !fusers.eof();)                      //filling them with data from files
                {
                    for (int i = 0; i < master.users - 1 && !fusers.eof(); i++)
                    {
                        int n;
                        fusers >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ousers[i].name[n] = bin;
                            else
                                n--;
                            fusers >> noskipws >> bin;
                        }
                        ousers[i].name[n] = '\0';
                        if (!fusers.eof())
                            fusers >> bin;
                        if (!fusers.eof())
                            fusers >> noskipws >> bin;
                    }
                    for (; !fusers.eof();)
                        fusers >> noskipws >> bin;
                }
                for (; !foperations.eof();)
                {
                    for (int i = 0; i < master.cars && !foperations.eof(); i++)
                    {
                        int n;
                        foperations >> bin;
                        if (foperations.eof())
                            break;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].carbn[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].carbn[n] = '\0';
                        foperations >> noskipws >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].name[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].name[n] = '\0';
                        foperations >> noskipws >> bin;
                        foperations >> noskipws >> bin;
                        ooperations[i].rentedc = bin;
                        ooperations[i].rented = (int(bin) - 48);
                        foperations >> noskipws >> bin;
                    }
                    for (; !foperations.eof();)
                        foperations >> noskipws >> bin;
                }
                fusers.close();
                fcars.close();
                foperations.close();
                system("cls");          //another submenu
                cout << "Please select what would you like to do next and enter according number" << endl;
                cout << "(1)Add user" << endl;
                cout << "(2)Edit user" << endl;
                cout << "(3)Exit this menu" << endl;
                cin >> choice;
                switch ((int)choice)
                {
                case 49:
                    fusers.open("Users.txt", ios::app);
                    cout << "enter the name of the user You want to add" << endl;
                    cin.ignore();
                    cin.sync();
                    getline(cin, name);
                    fusers << noskipws << name << ';' << '\n' << '\n';
                    fusers.close();
                    delete ousers;
                    delete ooperations;
                    break;
                case 50:
                    cout << "Enter the name of the user you want to edit" << endl;
                    cin.ignore();
                    cin.sync();
                    getline(cin, name);
                    int i;
                    for (i = 0; i < master.users; i++)          //checking if given user exists in database
                    {
                        if ((string)ousers[i].name == name)
                        {
                            av = 1;
                            break;
                        }
                    }
                    if (av != 1)
                    {
                        cout << "User not found" << endl;
                        cout << "Enter some character to continue" << endl;
                        cin >> choice;
                    }
                    else
                    {
                        av = 0;
                        int l;
                        for(l=0;l<master.cars;l++)
                            if ((string)ooperations[l].name == name)
                            {
                                av = 1;
                                break;
                            }
                        cout << "Enter new name of the user you have chosen" << endl;
                        cin.sync();
                        getline(cin, name);
                        int n;
                        for (n = 0; name[n] != '\0'; n++)
                            ousers[i].name[n] = name[n];
                        ousers[i].name[n] = name[n];
                        if (av == 1)            //checking if this user is also in operations database, if yes we also need to change his name then
                        {
                            for (n = 0; name[n] != '\0'; n++)
                                ooperations[l].name[n] = name[n];
                            ooperations[l].name[n] = name[n];

                            foperations.open("Operations.txt", ios::out | ios::trunc);      //so we need to delete everything from the file and fill it again with correct data
                            foperations.close();
                            foperations.open("Operations.txt", ios::app);
                            for (int m = 0; m < master.cars; m++)
                            {
                                foperations << noskipws << (string)ooperations[m].carbn << ';' << '\n';
                                foperations << noskipws << (string)ooperations[m].name << ';' << '\n';
                                foperations << noskipws << ooperations[m].rentedc << ';' << '\n' << '\n';
                            }

                            foperations.close();
                        }
                        fusers.open("Users.txt", ios::out | ios::trunc);            //deleting everything from file with old data
                        fusers.close();
                        fusers.open("Users.txt", ios::app);
                        for (int i = 0; i < master.users - 1; i++)                  // add there changed data
                            fusers << noskipws << (string)ousers[i].name << ';' << '\n' << '\n';
                        fusers.close();
                    }
                    delete ousers;                      //delete objects to create them again before returning to menu
                    delete ooperations;
                    break;
                case 51:
                    av2 = 0;     
                    delete ousers;                     
                    delete ooperations;             //exit submenu
                    break;
                default:
                    cout << "Enter proper number" << endl;
                    Sleep(5000);
                    delete ousers;                      //delete objects to create them again before returning to menu
                    delete ooperations;
                    break;
                }
            }
        case 51:
            for (; av2 == 1;)
            {
                    foperations.open("Operations.txt", ios::in);
                    fcars.open("Cars.txt", ios::in);
                    master.cars = howmany(fcars, 2);
                    operation* ooperations = new operation[master.cars];
                    fusers.open("Users.txt", ios::in);
                    master.users = howmany(fusers, 0);              //and here situation is exactly the same in places above first we craete objects based on data from file and then with each repetition we delete them and create again to be sure thata data isn't old
                    fusers.close();
                    fusers.open("Users.txt", ios::in);
                    user* ousers = new user[master.users];
                    for (; !fusers.eof();)
                    {
                        for (int i = 0; i < master.users - 1 && !fusers.eof(); i++)
                        {
                            int n;
                            fusers >> bin;
                            for (n = 0; bin != ';'; n++)
                            {
                                if ((int)bin > 64 && (int)bin < 123)
                                    ousers[i].name[n] = bin;
                                else
                                    n--;
                                fusers >> noskipws >> bin;
                            }
                            ousers[i].name[n] = '\0';
                            if (!fusers.eof())
                                fusers >> bin;
                            if (!fusers.eof())
                                fusers >> noskipws >> bin;
                        }
                        for (; !fusers.eof();)
                            fusers >> noskipws >> bin;
                    }
                    for (; !foperations.eof();)
                    {
                        for (int i = 0; i < master.cars && !foperations.eof(); i++)
                        {
                            int n;
                            foperations >> bin;
                            if (foperations.eof())
                                break;
                            for (n = 0; bin != ';'; n++)
                            {
                                if ((int)bin > 64 && (int)bin < 123)
                                    ooperations[i].carbn[n] = bin;
                                else
                                    n--;
                                foperations >> noskipws >> bin;
                            }
                            ooperations[i].carbn[n] = '\0';
                            foperations >> noskipws >> bin;
                            for (n = 0; bin != ';'; n++)
                            {
                                if ((int)bin > 64 && (int)bin < 123)
                                    ooperations[i].name[n] = bin;
                                else
                                    n--;
                                foperations >> noskipws >> bin;
                            }
                            ooperations[i].name[n] = '\0';
                            foperations >> noskipws >> bin;
                            foperations >> noskipws >> bin;
                            ooperations[i].rentedc = bin;
                            ooperations[i].rented = (int(bin) - 48);
                            foperations >> noskipws >> bin;
                        }
                        for (; !foperations.eof();)
                            foperations >> noskipws >> bin;
                    }
                    fusers.close();
                    fcars.close();
                    foperations.close();
                    system("cls");              //another submenu
                    cout << "Please select what would you like to do next and enter according number" << endl;
                    cout << "(1)Register new transaction" << endl;
                    cout << "(2)Register end of one renting" << endl;
                    cout << "(3)Exit this menu" << endl;
                    cin >> choice;
                switch ((int)choice)
                {
                case 49:
                    cout << "Please enter on which car transaction you want to register" << endl;
                    cin.ignore();
                    getline(cin, name);
                    int i;
                    av = 0;
                    for (i = 0; i < master.cars; i++)           //checking if car exists in database
                    {
                        if ((string)ooperations[i].carbn == name && ooperations[i].rented==0)       
                        {
                            av = 1;
                            break;
                        }
                    }
                    if (av != 1)
                    {
                        cout << "Car not found or already rented" << endl;
                        cout << "Enter some character to continue" << endl;
                        cin >> choice;
                    }
                    else
                    {
                        cout << "Enter new name of the user who rented car" << endl;
                        cin.sync();
                        getline(cin, name);
                        int h;
                        av = 0;
                        for (h = 0; h < master.users; h++)              //checking if user exists
                        {
                            if ((string)ousers[h].name == name)
                            {
                                av = 1;
                                break;
                            }
                        }
                        if (av == 0)
                        {
                            cout << "User not registered" << endl;
                            cout << "Enter some character to continue" << endl;
                            cin >> choice;
                        }
                        else
                        {
                            for (h = 0; name[h] != '\0'; h++)           //if both exist we can change the data
                                ooperations[i].name[h] = name[h];           
                            ooperations[i].name[h] = name[h];
                            ooperations[i].rented = 1;                  //wer change this because car is rented now
                            ooperations[i].rentedc = '1';
                            foperations.open("Operations.txt", ios::out | ios::trunc);
                            foperations.close();
                            foperations.open("Operations.txt", ios::app);
                            for (int m = 0; m < master.cars; m++)
                            {
                                foperations << noskipws << (string)ooperations[m].carbn << ';' << '\n';
                                foperations << noskipws << (string)ooperations[m].name << ';' << '\n';
                                foperations << noskipws << ooperations[m].rentedc << ';' << '\n' << '\n';
                            }
                            foperations.close();
                        }
                    }
                    delete ooperations;
                    delete ousers;
                        break;
                case 50:
                    cout << "Please select which car was given back" << endl;
                    cin.ignore();
                    cin.sync();
                    getline(cin, name);
                    av = 0;
                    int p;
                    for (p = 0; p < master.cars; p++)               // checking if given car exists in database
                    {
                        if ((string)ooperations[p].carbn == name)           
                        {
                            av = 1;
                            break;
                        }
                    }
                    if (av != 1)
                    {
                        cout << "car not found\nPlease enter any char to continue" << endl;
                        cin >> choice;
                    }
                    else
                    {
                        ooperations[p].rentedc = '0';           //if exists we change this to zero because car is already not rented
                        ooperations[p].rented = 0;
                    }
                    foperations.open("Operations.txt", ios::out | ios::trunc);          //and now with classis method of clearing file and saving there actual data we change this
                    foperations.close();
                    foperations.open("Operations.txt", ios::app);
                    for (int m = 0; m < master.cars; m++)
                    {
                        foperations << noskipws << (string)ooperations[m].carbn << ';' << '\n';
                        foperations << noskipws << (string)ooperations[m].name << ';' << '\n';
                        foperations << noskipws << ooperations[m].rentedc << ';' << '\n' << '\n';
                    }
                    foperations.close();
                    delete ooperations;
                    delete ousers;
                    break;
                    case 51:
                        av2 = 0;
                        delete ooperations;
                        delete ousers;
                        break;
                    default:
                        cout << "Enter proper number" << endl;
                        Sleep(5000);
                        delete ooperations;
                        delete ousers;
                        break;
                }
            }
        case 52:
            for (; av2 == 1;)
            {
                fcars.open("Cars.txt", ios::in);
                master.cars = howmany(fcars, 2);
                fcars.close();
                fcars.open("Cars.txt", ios::in);                //again we create objects to work on them
                master.cars = howmany(fcars, 2);
                fcars.close();
                fcars.open("Cars.txt", ios::in);
                fusers.open("Users.txt", ios::in);
                master.users = howmany(fusers, 0);              //and here situation is exactly the same in places above first we craete objects based on data from file and then with each repetition we delete them and create again to be sure thata data isn't old
                fusers.close();
                fusers.open("Users.txt", ios::in);
                user* ousers = new user[master.users];
                for (; !fusers.eof();)
                {
                    for (int i = 0; i < master.users - 1 && !fusers.eof(); i++)
                    {
                        int n;
                        fusers >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ousers[i].name[n] = bin;
                            else
                                n--;
                            fusers >> noskipws >> bin;
                        }
                        ousers[i].name[n] = '\0';
                        if (!fusers.eof())
                            fusers >> bin;
                        if (!fusers.eof())
                            fusers >> noskipws >> bin;
                    }
                    for (; !fusers.eof();)
                        fusers >> noskipws >> bin;
                }
                fusers.close();
                car* ocars = new car[master.cars];
                for (; !fcars.eof();)
                {
                    for (int i = 0; i < master.cars && !fcars.eof(); i++)
                    {
                        int n;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].bn[n] = bin;
                            fcars >> noskipws >> bin;
                        }
                        ocars[i].bn[n] = '\0';
                        fcars >> bin;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].issues[n] = bin;
                            fcars >> noskipws >> bin;
                        }
                        ocars[i].issues[n] = '\0';
                        fcars >> bin;
                        fcars >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            ocars[i].pricee[n] = bin;
                            fcars >> bin;
                        }
                        ocars[i].pricee[n] = '\0';
                        for (int m = 0; m < n; m++)
                        {
                            ocars[i].price += (((int)ocars[i].pricee[m]) - 48) * pow(10.0, (n - m - 1));
                        }
                        fcars >> noskipws >> bin;
                        fcars >> noskipws >> bin;
                    }
                    for (; !fcars.eof();)
                        fcars >> noskipws >> bin;
                }
                foperations.open("Operations.txt", ios::in);
                operation* ooperations = new operation[master.cars];
                for (; !foperations.eof();)
                {
                    for (int i = 0; i < master.cars && !foperations.eof(); i++)
                    {
                        int n;
                        foperations >> bin;
                        if (foperations.eof())
                            break;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].carbn[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].carbn[n] = '\0';
                        foperations >> noskipws >> bin;
                        for (n = 0; bin != ';'; n++)
                        {
                            if ((int)bin > 64 && (int)bin < 123)
                                ooperations[i].name[n] = bin;
                            else
                                n--;
                            foperations >> noskipws >> bin;
                        }
                        ooperations[i].name[n] = '\0';
                        foperations >> noskipws >> bin;
                        foperations >> noskipws >> bin;
                        ooperations[i].rentedc = bin;
                        ooperations[i].rented = (int(bin) - 48);
                        foperations >> noskipws >> bin;
                    }
                    for (; !foperations.eof();)
                        foperations >> noskipws >> bin;
                }
                foperations.close();
                fcars.close();
                system("cls");          //another submenu
                cout << "Please select what would you like to do next and enter according number" << endl;
                cout << "(1)Look into car database" << endl;
                cout << "(2)Look into car database(show only available ones)" << endl;
                cout << "(3)Look into user database" << endl;
                cout << "(4)Look into transactions database" << endl;
                cout << "(5)Exit this menu" << endl;
                cin >> choice;
                system("cls");
                switch ((int)choice)
                {
                case 49:
                    for (int j = 0; j < master.cars; j++)           //printing data only when car isn't rented at this moment
                    {
                            cout << "car name: " << (string)ocars[j].bn << endl;
                            cout << "issues with car: " << (string)ocars[j].issues << endl;
                            cout << "renting price: " << ocars[j].price << '\n' << endl;
                    }
                    cout << "\n\nEnter any character to continue" << endl;
                    cin >> choice;
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                case 50:
                    for (int j = 0; j < master.cars; j++)           //printing data only when car isn't rented at this moment
                    {
                        if (ooperations[j].rentedc == '0')
                        {
                            cout <<"car name: "<< (string)ocars[j].bn << endl;
                            cout <<"issues with car: "<< (string)ocars[j].issues << endl;
                            cout <<"renting price: "<< ocars[j].price << '\n' << endl;
                        }
                    }
                    cout << "\n\nEnter any character to continue" << endl;
                    cin >> choice;
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                case 51:   
                    for (int g=0;g<master.users -1 ;g++)                      //printing all users
                    {                       
                        cout <<"user name:"<< ousers[g].name << endl; ;
                    }                                                           
                    cout << "\n\nEnter any character to continue" << endl;
                    cin >> choice;
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                case 52:
                    for (int j = 0; j < master.cars; j++)           //printing data only when car isn't rented at this moment
                    {
                        cout << "car name: " << (string)ooperations[j].carbn << endl;
                        cout << "user name: " << (string)ooperations[j].name << endl;
                        if(ooperations[j].rented==1)
                            cout << "is user still renting?:  yes "<< '\n' << endl;
                        else
                            cout << "is user still renting?:  no " << '\n' << endl;
                    }
                    cout << "\n\nEnter any character to continue" << endl;
                    cin >> choice;
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                case 53:
                    av2 = 0;                //exit menu(exit app)
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                default:
                    cout << "Enter proper number" << endl;
                    Sleep(5000);
                    delete ocars;
                    delete ousers;
                    delete ooperations;
                    break;
                }
            }
            break;
        case 53:
            av3 = 0;
            break;
        default:
            cout << "Enter proper number" << endl;
            Sleep(5000);
            break;
        }
    }
}


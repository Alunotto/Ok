#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    struct user {           //creating some users just to have some
        int name;
        float ballance=0;
        int trnb=0;
    }uarr[20];      

    struct transaction {        //creating some transactions just to have some to look into
        int from=0;
        int to=0;
        float sum=0;
    }tarr[20][40];    
        
    printf("Welcome to [bank name] application");
    Sleep(2000);
    system("cls");
    printf("creating users\n");
    for (int t = 1; t < 20; t++)       //filling users(objects) with data 
    {
        uarr[t].name =t + 97;
        uarr[t].ballance = rand() % 200000;
        tarr[t][uarr[t].trnb].from = 88;
        tarr[t][uarr[t].trnb].to = t + 97;
        tarr[t][uarr[t].trnb].sum = uarr[t].ballance;
        uarr[t].trnb++;
        printf(". ");
        Sleep(120);
    }       
    system("cls");
    int help;
    printf("creating transactions\n");
    for (int t = 1; t < 20; t++)                //filling transactions(objects) with data
    {
        tarr[t][uarr[t].trnb].from = t + 97;
        tarr[t][uarr[t].trnb].sum = rand() % (int)uarr[t].ballance;
        tarr[t][uarr[t].trnb].to = (rand() % 20)+97;
        help = tarr[t][uarr[t].trnb].to - 97;
        uarr[help].ballance += tarr[t][uarr[t].trnb].sum;
        uarr[t].ballance -= tarr[t][uarr[t].trnb].sum;
        tarr[help][uarr[help].trnb].to = tarr[t][uarr[t].trnb].to;
        tarr[help][uarr[help].trnb].from = tarr[t][uarr[t].trnb].from;
        tarr[help][uarr[help].trnb].sum = tarr[t][uarr[t].trnb].sum;
        uarr[t].trnb++;
        uarr[help].trnb++;

        printf(". ");
        Sleep(120);
    }   
    system("cls");

    int logincheck = 9999,counter=0,login1check=5555;
    char a;
    here2:                  //some identifier just to be able to go back here easily
    system("cls");
    printf("Please select what would like to do and enter according number:\n1.Login to your bank account\n2.Login to your admin account(for insight into all transactions)\n3.Exit application\n"); //creating main console
    {
        scanf_s("%c", &a);              //reading what user want to do
        if (((int)a-'0') > 3 || ((int)a-'0') < 1)
        {
            printf("Please enter valid number\n");    //checking if number is valid
            Sleep(1500);
            goto here2;
        }
        system("cls");
        switch ((int)a-'0')
        {
            case 1:
                int login;
                for (int i = 0; i < 3; i++)
                {
                    printf("please enter your login(9999)and confirm with enter(use only numbers or program will shut down):\n");
                    login = 0;
                    scanf_s("%d", &login);              //login procedure
                    system("cls");
                    if (login == logincheck)
                    {
                        int b;
                        for (;;)
                        {
                            here:                       //some identifier just to be able to go back here easily
                            system("cls");
                            printf("Your account ballance is: %.2f \n", uarr[0].ballance);
                            printf("Choose what you want to do:\n1.Transfer money to your account\n2.Transfer your money into somebody elses account\n3.log out\n");
                            scanf_s("%d", &b);
                            while (b > 3 || b < 1)          //checking if number is valid
                            {
                                printf("Please enter valid number\n");
                                scanf_s("%d", &b);
                            }
                            switch (b)
                            {
                                case 1:
                                    float m;
                                    printf("Please enter how much money you would like to transfer:");
                                    scanf_s("%f", &m);
                                    uarr[0].ballance += m;                          //registering this transaction
                                    tarr[0][uarr[0].trnb].to = 97;
                                    tarr[0][uarr[0].trnb].from = 88;
                                    tarr[0][uarr[0].trnb].sum = m;
                                    system("cls");
                                    b = 0;
                                    uarr[0].trnb++;
                                    break;
                                case 2:
                                    float n;
                                    char namee;
                                    b = 0;
                                    printf("Please enter how much money you would like to transfer:");
                                    scanf_s("%f", &n);                                   
                                    while (n > uarr[0].ballance)                    //checking if entered number is valid
                                    {
                                        printf("You do not have enough money to proceed\n");
                                        Sleep(2000);
                                        system("cls");
                                        goto here;
                                    }       
                                    while (n < 0)                                   //checking if entered number is valid
                                    {
                                        printf("You can not take someone's money\n");
                                        Sleep(2000);
                                        system("cls");
                                        goto here;
                                    }
                                    printf("Please enter identifier of user you want to send your money to(your identifier is: a, others are b, c, d, up to u\n");
                                    scanf_s("%c", &namee);
                                    while ((int)namee > 117 || (int)namee < 97)
                                    {
                                        printf("Please enter valid identifier:");       //checking if identifier is valid
                                        scanf_s("%c", &namee);
                                    }
                                    uarr[0].ballance -= n;                              //registering transaction at both accounts
                                    uarr[(int)namee - 97].ballance += n;
                                    tarr[0][uarr[0].trnb].from = 97;
                                    tarr[0][uarr[0].trnb].to = (int)namee;
                                    tarr[0][uarr[0].trnb].sum = n;
                                    tarr[(int)namee - 97][uarr[(int)namee - 97].trnb].to = tarr[0][uarr[0].trnb].to;
                                    tarr[(int)namee - 97][uarr[(int)namee - 97].trnb].from = tarr[0][uarr[0].trnb].from;
                                    tarr[(int)namee - 97][uarr[(int)namee - 97].trnb].sum = tarr[0][uarr[0].trnb].sum;
                                    uarr[(int)namee - 97].trnb++;
                                    uarr[0].trnb++;
                                    break;
                                case 3:
                                    login = 0;
                                    printf("Successfully loged out");                   //log out
                                    Sleep(2000);
                                    goto here2;
                                    break;
                            }
                        }
                    }
                    else                                                                                    //failed login procedure
                    {
                        printf("Wrong login or password\n");
                        switch (i)
                        {
                            case 0:
                                printf("2 last attempts");
                                Sleep(2000);
                                    break;
                            case 1:
                                printf("last attempt and program will shut down");
                                Sleep(3000);
                                break;

                        }
                        system("cls");
                    }
                }
            case 2:
                int login1;
                char d;
                printf("Please enter your admin login(5555) remember to use only numbers(or program will shut down) and you have only one chance\n");
                scanf_s("%d", &login1);
                if (login1 != login1check)          //login procedure
                    goto end;
                here3:              //some identifier just to be able to go back here easily
                for(;;)
                {
                    system("cls");
                    printf("Welcome to your admin account please select what would you like to do next and enter according number:\n");
                    printf("1.Check chosen account and transactions\n2.Make transaction\n3.log out\n");
                    scanf_s("%c", &d);              //reading what user want to do
                    if (((int)d - '0') > 3 || ((int)d - '0') < 1)
                    {
                        printf("Please enter valid number\n");    //checking if number is valid
                        Sleep(1500);
                        goto here3;
                    }
                
                
                    system("cls");
                    switch (d)
                    {
                    case '1':
                        char j;
                         here4:                     //some identifier just to be able to go back here easily
                        system("cls");
                        printf("Please select which account would like to check by entering according user identifier(a,b,c...t):\n ");
                        scanf_s("%c", &j);
                        if ((int)j > 117 || (int)j < 97)                //checking if identifier entered is valid
                        {
                            printf("please enter valid identifier");
                            Sleep(1500);
                            goto here4;
                        }
                        printf("user %c account\n", j);
                        printf("current balance %.2f\n\n", uarr[(int)j - 97].ballance);           //printing chosen user data
                        for (int k = 0; k < uarr[(int)j - 97].trnb; k++)                          //printing chosen user transactiions
                        {
                            printf("transaction number %d:\n", k);
                            printf("from: %c\nto: %c\nhow much: %.2f\n\n", tarr[(int)j - 97][k].from, tarr[(int)j - 97][k].to, tarr[(int)j - 97][k].sum);
                        }
                        int dummy;
                        printf("please enter some char to return to admin console :\n");         //user can look at chosen account as long as he want
                        scanf_s("%d", &dummy);
                        d = '0';
                        break;
                    case '2':
                        char nam,nan;
                        float g;
                        here6:                  //some identifier just to be able to go back here easily
                        system("cls");
                        printf("please enter identifier of person whose money you want to send (a,b...u(your identifier is a)):\n");
                        scanf_s("%c", &nam);
                        while ((int)nam > 117 || (int)nam < 97)         //checking if identifier entered is valid
                        {
                            printf("Please enter valid identifier:");
                            scanf_s("%c", &nam);
                        }
                        printf("Please enter how much money you would like to transfer:");
                        scanf_s("%f", &g);
                        while (g > uarr[(int)nam-'a'].ballance)                       //checking if entered number is valid
                        {
                            printf("That person does not have enough money to proceed\n");      
                            Sleep(2000);
                            goto here6;
                        }
                        while (g < 0)                                                //checking if entered number is valid
                        {
                            printf("please enter number >0\n");
                            Sleep(2000);
                            goto here6;
                        }
                        printf("please enter identifier of person you want to send that money to(a,b...u(your identifier is a)):\n");
                        scanf_s("%c", &nan);
                        while ((int)nan > 117 || (int)nan < 97)                 //checking if identifier entered is valid
                        {
                            printf("Please enter valid identifier:");
                            scanf_s("%c", &nan);
                        }
                        uarr[(int)nam - 97].ballance -= g;                          //registering transaction at both accounts                      
                        uarr[(int)nan - 97].ballance += g;
                        tarr[(int)nam - 97][uarr[(int)nam - 97].trnb].to = (int)nan;
                        tarr[(int)nan - 97][uarr[(int)nan - 97].trnb].to = (int)nan;
                        tarr[(int)nam - 97][uarr[(int)nam - 97].trnb].from = (int)nam;
                        tarr[(int)nan - 97][uarr[(int)nan - 97].trnb].from = (int)nam;
                        tarr[(int)nam - 97][uarr[(int)nam - 97].trnb].sum = g;
                        tarr[(int)nan - 97][uarr[(int)nan - 97].trnb].sum = g;
                        uarr[(int)nam - 97].trnb++;
                        uarr[(int)nan - 97].trnb++;
                        printf("Your transaction is saved on accounts: %c, %c\n", nan, nam);
                        printf("from:%c\nto:%c\nhow much:%.2f\n", nam, nan, g);             //showing transaction
                        printf("please enter some char to return to admin console :\n");
                        scanf_s("%d", &dummy);
                        d = '0';                                                        //to give user time
                        break;
                    case '3':
                        login1 = 0;
                        printf("successfully logged out\n");
                        Sleep(1500);
                        goto here2;
                        break;
                    }
                }
            case 3:
                goto end;
                break;
        }
    }   
    end:                    //some identifier just to be able to go here easily
    printf("goodbye");
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Account.h"
#include "Bank.h"
#include "ATM.h"

ofstream ofss;

using namespace std;

class Account;
class Bank;
class Card;
class ATM;

int language() // 언어 선택
{
    int l;
    int cnt = 0;
    do {
        cout << "Choose the language. (1) Eng \t (2) Kor \nEnter : "; cin >> l;
        if (l == 1) { cnt = 0; }
        else if (l == 2) { cnt = 0; }
        else { cnt = 1; cout << "\nThere is no language " << l << " we support. Please try again." << endl; }
    } while (cnt == 1);
    return l;
}


int main()
{
    //Account Info
    Account a1("J", "Shinhan", 201911106, 110270938291, 1111, 100000);
    Account a2("J", "Shinhan", 12341234, 1234123412341234, 1111, 100000);
    Account a3("J", "Daegu", 23136030, 20000712, 1111, 100000);

    Account a4("Junseo", "Daegu", 201911006, 27860543, 1234, 1000000);
    Account a5("Junseo", "Daegu", 98769876, 9876987698769876, 1234, 1000000);
    Account a6("Junseo", "Shinhan", 40960488, 20000612, 1234, 1000000);

    Account a7("AngelYeji", "Shinhan", 201911045, 16113193765, 1519, 500000);

    Account a8("J", 20000712, 1612);
    Account a9("Junseo", 20000612, 1712);

    Bank b1;
    Bank* bptr;
    bptr = &b1;

    b1.save(&a1);
    b1.save(&a2);
    b1.save(&a3);
    b1.save(&a4);
    b1.save(&a5);
    b1.save(&a6);
    b1.save(&a7);
    b1.save(&a8);
    b1.save(&a9);

    //ATM Implementation
    int cnt = 1;
    int la;
    int o1 = 10;
    int m1 = 10;
    int o2 = 10;
    int m2 = 10;
    int o3 = 10;
    int m3 = 10;
    int o4 = 10;
    int m4 = 10;

    //ATM 선택
    ofss.open("ATM1.txt", ios::trunc);
    ofss.close();
    ofss.open("ATM1.txt", ios::app);
    ofss << "\tTime\t\t\tTransaction ID\t\t    Card Number\t      Transaction Types\t\t   Amount\t  Other Transaction-specific Information" << endl << endl;
    ofss.close();

    ofss.open("ATM2.txt", ios::trunc);
    ofss.close();

    ofss.open("ATM3.txt", ios::trunc);
    ofss.close();
    ofss.open("ATM3.txt", ios::app);
    ofss << "\tTime\t\t\tTransaction ID\t\t    Card Number\t      Transaction Types\t\t   Amount\t  Other Transaction-specific Information" << endl << endl;
    ofss.close();

    ofss.open("ATM4.txt", ios::trunc);
    ofss.close();

    do
    {
        cout << "\n\nWhich atm do you want to use? choose the number. \n1.ATM1 \t 2. ATM2 \t 3. ATM3 \t 4. ATM4  \t 5. Quit \nEnter : ";
        int AtmNum;
        cin >> AtmNum;

        while (AtmNum > 6)
        {
            cout << "There's no ATM option such like that. Please choose the number between 1~4." << endl;
            cin >> AtmNum;
        }

        if (AtmNum == 1)
        {
            //ATM1
            ATM1 atm1(bptr, o1, m1);
            int check = atm1.CardCheck();
            if (check == 0)
            {
                int cnt1 = 1;
                do
                {
                    atm1.ShowMenu();
                    int choice; cin >> choice;
                    if (choice == 1) { atm1.Deposit(); }
                    else if (choice == 2) { atm1.Withdraw(); }
                    else if (choice == 3) { atm1.Transfer(); }
                    else if (choice == 4) { cout << "ATM terminates...\n\n" << endl; cnt = 1; cnt1 = 0; }
                    else { cout << "Please choose the menu between 1~4." << endl; }

                } while (cnt1 == 1);
                o1 = atm1.getOman();
                m1 = atm1.getMan();
            }
            else if (check == 2)
            {
                int cnt2 = 1;
                do
                {
                    atm1.AdminMenu();
                    int choice2; cin >> choice2;
                    if (choice2 == 1) { atm1.History(); cnt2 = 0; }
                    else if (choice2 == 2) { cout << "ATM terminates...\n\n" << endl; cnt = 1; cnt2 = 0; }
                    else { cout << "Please choose the menu between 1~2." << endl; }
                } while (cnt2 == 1);
            }
            else { cout << "This card is invalid!" << endl; }
        }
        //
        else if (AtmNum == 2)
        {
            //ATM2 
            ATM2 atm2(bptr, o2, m2);
            la = language();
            int check = atm2.CardCheck(la);
            if (check == 0)
            {
                int cnt1 = 1;
                do
                {
                    atm2.ShowMenu();
                    int choice; cin >> choice;
                    if (choice == 1) { atm2.Deposit(); }
                    else if (choice == 2) { atm2.Withdraw(); }
                    else if (choice == 3) { atm2.Transfer(); }
                    else if (choice == 4)
                    {
                        if (atm2.getLan() == 1) { cout << "ATM terminates...\n\n" << endl; }
                        else { cout << "ATM 종료...\n\n" << endl; }
                        cnt = 1; cnt1 = 0;
                    }
                    else
                    {
                        if (atm2.getLan() == 1) { cout << "Please choose the menu between 1~4." << endl; }
                        else { cout << "메뉴를 1~4 중에서 다시 선택해주세요." << endl; }
                    }
                } while (cnt1 == 1);
                o2 = atm2.getOman();
                m2 = atm2.getMan();
            }
            else if (check == 2)
            {
                int cnt2 = 1;
                do
                {
                    atm2.AdminMenu();
                    int choice2; cin >> choice2;
                    if (choice2 == 1) { atm2.History(); cnt2 = 0; }
                    else if (choice2 == 2)
                    {
                        if (la == 1)
                        {
                            cout << "ATM terminates...\n\n" << endl;
                        }
                        else
                        {
                            cout << "ATM 종료...\n\n" << endl;
                        }
                        cnt = 1; cnt2 = 0;
                    }
                    else
                    {
                        if (la == 1)
                        {
                            cout << "Please choose the menu between 1~2." << endl;
                        }
                        else
                        {
                            cout << "1~2 항목 중 하나를 선택해주세요." << endl;
                        }
                    }
                } while (cnt2 == 1);
            }
            else
            {
                if (atm2.getLan() == 1) { cout << "This card is invalid!" << endl; }
                else { cout << "이 카드는 유효하지 않습니다." << endl; }
            }
        }
        //
        else if (AtmNum == 3)
        {
            //ATM3
            ATM3 atm3(bptr, o3, m3);
            int check = atm3.CardCheck();
            if (check == 0)
            {
                int cnt1 = 1;
                do
                {
                    atm3.ShowMenu();
                    int choice; cin >> choice;
                    if (choice == 1) { atm3.Deposit(); }
                    else if (choice == 2) { atm3.Withdraw(); }
                    else if (choice == 3) { atm3.Transfer(); }
                    else if (choice == 4) { cout << "ATM terminates...\n\n" << endl; cnt = 1; cnt1 = 0; }
                    else { cout << "Please choose the menu between 1~4." << endl; }

                } while (cnt1 == 1);
                o3 = atm3.getOman();
                m3 = atm3.getMan();

            }
            else if (check == 2)
            {
                int cnt2 = 1;
                do
                {
                    atm3.AdminMenu();
                    int choice2; cin >> choice2;
                    if (choice2 == 1) { atm3.History(); cnt2 = 0; }
                    else if (choice2 == 2) { cout << "ATM terminates...\n\n" << endl; cnt = 1; cnt2 = 0; }
                    else { cout << "Please choose the menu between 1~2." << endl; }
                } while (cnt2 == 1);
            }
            else { cout << "This card is invalid!" << endl; }
        }
        //
        else if (AtmNum == 4)
        {
            //ATM4
            ATM4 atm4(bptr, o4, m4);
            la = language();
            int check = atm4.CardCheck(la);
            if (check == 0)
            {
                int cnt1 = 1;
                do
                {
                    atm4.ShowMenu();
                    int choice; cin >> choice;
                    if (choice == 1) { atm4.Deposit(); }
                    else if (choice == 2) { atm4.Withdraw(); }
                    else if (choice == 3) { atm4.Transfer(); }
                    else if (choice == 4)
                    {
                        if (atm4.getLan() == 1) { cout << "ATM terminates...\n\n" << endl; }
                        else { cout << "ATM 종료...\n\n" << endl; }
                        cnt = 1; cnt1 = 0;
                    }
                    else
                    {
                        if (atm4.getLan() == 1) { cout << "Please choose the menu between 1~4." << endl; }
                        else { cout << "메뉴를 1~4 중에서 다시 선택해주세요." << endl; }
                    }
                } while (cnt1 == 1);
                o4 = atm4.getOman();
                m4 = atm4.getMan();
            }
            else if (check == 2)
            {
                int cnt2 = 1;
                do
                {
                    atm4.AdminMenu();
                    int choice2; cin >> choice2;
                    if (choice2 == 1) { atm4.History(); cnt2 = 0; }
                    else if (choice2 == 2)
                    {
                        if (la == 1)
                        {
                            cout << "ATM terminates...\n\n" << endl;
                        }
                        else
                        {
                            cout << "ATM 종료...\n\n" << endl;
                        }
                        cnt = 1; cnt2 = 0;
                    }
                    else
                    {
                        if (la == 1)
                        {
                            cout << "Please choose the menu between 1~2." << endl;
                        }
                        else
                        {
                            cout << "1~2 항목 중 하나를 선택해주세요." << endl;
                        }
                    }
                } while (cnt2 == 1);
            }
            else
            {
                if (atm4.getLan() == 1) { cout << "This card is invalid!" << endl; }
                else { cout << "이 카드는 유효하지 않습니다." << endl; }
            }
        }
        //
        else if (AtmNum == 5)
        {  
            cnt = 0;
        } // exit.
        else
        {
            cout << "Please choose the menu between 1~5" << endl;
        }
    } while (cnt == 1);
    return 0;
}
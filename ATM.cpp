#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "ATM.h"
#include "Account.h"

using namespace std;

ofstream ofs;
ifstream ifs;

ATM::ATM() {}
ATM::ATM(Bank* b, int oh, int ma) { b_ptr = b; oman = oh; man = ma; }
int ATM::getOman() { return oman; }
int ATM::getMan() { return man; }
int ATM::getRand()
{
    int i;
    srand((unsigned int(time(NULL))));
    i = (rand() % (99999999 + 1 - 10000000) + 10000000);

    return i;
}
string ATM::getTime()
{
    time_t curr_time = time(NULL);

    struct tm curr_tm;

    localtime_s(&curr_tm, &curr_time);

    int year = curr_tm.tm_year + 1900;
    int month = curr_tm.tm_mon + 1;
    int day = curr_tm.tm_mday;
    int hour = curr_tm.tm_hour;
    int min = curr_tm.tm_min;
    int sec = curr_tm.tm_sec;

    string time = to_string(year) + "." + to_string(month) + "." + to_string(day) + " " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);

    return time;
}

void ATM::MoneyFromBank()
{
    b_ptr->moneyForATM(man, oman); man = 20; oman = 20;
}
int ATM::CardCheck()
{
    return 3;
} // Valid : 0, Invalid : 1
int ATM::getLan() { return lan; }
void ATM::ShowMenu()
{
    if (lan == 1) {
        cout << "SELECT THE MENU." << endl;
        cout << "(1) DEPOSIT \t (2) WITHDRAWAL \t (3) TRANSFER \t (4) QUIT \nEnter : ";
    }
    else {
        cout << "�޴��� �����ϼ���." << endl;
        cout << "(1) �Ա� \t (2) ��� \t (3) �۱� \t (4) ��� \n�Է� : ";
    }
}
void ATM::AdminMenu()
{
    if (lan == 1) {
        cout << "SELECT THE MENU." << endl;
        cout << "(1) TRANSACTION HISTORY \t (2) QUIT \nEnter : ";
    }
    else {
        cout << "�޴��� �����ϼ���." << endl;
        cout << "(1) �ŷ� ���� ��ȸ  \t (2) ��� \n�Է� : ";
    }
}

void ATM::Deposit()
{
    if (lan == 1) // Eng
    {
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;

        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();

        //1. fee ����
        if (bank == supportBank) { fee = 0; } // d_fee = 500, for non-primary
        else { fee = 500; }// d_fee = 0, for primary

        //2. deposit money �޴´�
        int cnt = 0;
        do
        {
            cout << "Which type would you insert? \t (1) Cash \t (2) Check \t (3) Quit \nEnter : "; int num1; cin >> num1;
            if (num1 == 1)
            {
                try
                {
                    cout << "\nHow many 10000 won would you insert? : "; int cash1; cin >> cash1;
                    cout << "\nHow many 50000 won would you insert? : "; int cash2; cin >> cash2;
                    int cash = cash1 + cash2;
                    int i_money = cash1 * 10000 + cash2 * 50000;
                    if (cash > 50 || cash <= 0) throw i_money;

                    a_ptr->deposit(i_money - fee);
                    b_ptr->Mychange(a_ptr);

                    cout << "The fee is " << fee << " won. " << i_money - fee << " won is inserted to your account. Your total balance is " << b_ptr->getBalance() << " won." << endl;
                    man += cash1;
                    oman += cash2;
                    cnt = 0;

                    // History save
                    if (sNum == 1111) {
                        ofs.open("ATM1.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else if (sNum == 2222) {
                        ofs.open("ATM2.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else if (sNum == 3333) {
                        ofs.open("ATM3.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else {
                        ofs.open("ATM4.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }

                }
                catch (int i) { cout << "Cannot deposit " << i << " won to your account. The arrange of inserted cash is between 0~50. Please try again." << endl; cnt = 1; }
            }
            else if (num1 == 2)
            {
                try
                {
                    cout << "\nHow many 100000 won would you insert? : "; int check1; cin >> check1;
                    cout << "\nHow many 1000000 won would you insert? : "; int check2; cin >> check2;
                    int check = check1 + check2;
                    int i_money = check1 * 100000 + check2 * 1000000;
                    if (check > 10 || check <= 0) throw i_money;

                    a_ptr->deposit(i_money - fee);
                    b_ptr->Mychange(a_ptr);

                    cout << "The fee is " << fee << " won. " << i_money - fee << " won is inserted to your account. Your total balance is " << b_ptr->getBalance() << " won." << endl;
                    cnt = 0;

                    // History save
                    if (sNum == 1111) {
                        ofs.open("ATM1.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else if (sNum == 2222) {
                        ofs.open("ATM2.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else if (sNum == 3333) {
                        ofs.open("ATM3.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else {
                        ofs.open("ATM4.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "deposit" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                }
                catch (int i) { cout << "Cannot deposit " << i << " won to your account. The arrange of inserted check is between 0~10. Please try again." << endl; cnt = 1; }
            }
            else if (num1 == 3) { cnt = 0; break; }
            else { cout << "Please select the menu between 1~3." << endl; cnt = 1; }
        } while (cnt == 1);
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;
        cout << "Deposit process terminates...\n" << endl;
    }
    else // Kor
    {
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();

        //1. fee ����
        if (bank == supportBank) { fee = 0; } // d_fee = 500, for non-primary
        else { fee = 500; }// d_fee = 0, for primary

        //2. deposit money �޴´�
        int cnt = 0;
        do
        {
            cout << "���ݰ� ��ǥ �� � ���� �Ա��Ͻðڽ��ϱ�? \t (1) ���� \t (2) ��ǥ \t (3) ��� \n�Է� : "; int num1; cin >> num1;
            if (num1 == 1)
            {
                try
                {
                    cout << "\n�� ���� 10000�� ���� �Ա��Ͻðڽ��ϱ�? : "; int cash1; cin >> cash1;
                    cout << "\n�� ���� 50000�� ���� �Ա��Ͻðڽ��ϱ�? : "; int cash2; cin >> cash2;
                    int cash = cash1 + cash2;
                    int i_money = cash1 * 10000 + cash2 * 50000;
                    if (cash > 50 || cash <= 0) throw i_money;

                    a_ptr->deposit(i_money - fee);

                    cout << "������� " << fee << " �� �Դϴ�. " << i_money - fee << " ���� ���·� �ԱݵǾ����ϴ�. �ܾ��� " << a_ptr->getBal() << " �� �Դϴ�." << endl;
                    b_ptr->Mychange(a_ptr);
                    man += cash1;
                    oman += cash2;
                    cnt = 0;

                    // History save
                    if (sNum == 2222) {
                        ofs.open("ATM2.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "�Ա�" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                    else {
                        ofs.open("ATM4.txt", ios::app);
                        ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "�Ա�" << setw(18) << i_money << setw(27) << "-" << endl;
                        ofs.close();
                    }
                }
                catch (int i) { cout << i << " ���� ���¿� �Ա��� �� �����ϴ�. ������ 0�忡�� �ִ� 50�� ���� �Ա� �����մϴ�. �ٽ� �õ����ּ���." << endl; cnt = 1; }
            }
            else if (num1 == 2)
            {
                try
                {
                    cout << "\n�� ���� 100000�� ��ǥ�� �Ա��Ͻðڽ��ϱ�? : "; int check1; cin >> check1;
                    cout << "\n�� ���� 1000000�� ��ǥ�� �Ա��Ͻðڽ��ϱ�? : "; int check2; cin >> check2;
                    int check = check1 + check2;
                    int i_money = check1 * 100000 + check2 * 1000000;
                    if (check > 10 || check <= 0) throw i_money;

                    a_ptr->deposit(i_money - fee);
                    b_ptr->Mychange(a_ptr);

                    cout << "������� " << fee << " �� �Դϴ�. " << i_money - fee << " ���� ���·� �ԱݵǾ����ϴ�. �ܾ��� " << b_ptr->getBalance() << " �� �Դϴ�." << endl;
                    cnt = 0;
                }
                catch (int i) { cout << i << " ���� ���¿� �Ա��� �� �����ϴ�. ��ǥ�� 0�忡�� �ִ� 10�� ���� �Ա� �����մϴ�. �ٽ� �õ����ּ���." << endl; cnt = 1; }
            }
            else if (num1 == 3) { cnt = 0; break; }
            else { cout << "1~3 �� �� �׸��� �������ּ���." << endl; cnt = 1; }
        } while (cnt == 1);
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        cout << "�Ա� �ý��� ����...\n" << endl;
    }

}

void ATM::Withdraw()
{
    if (lan == 1) // Eng
    {
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();

        //1. fee ����
        if (bank == supportBank) { fee = 500; } // d_fee = 500, for non-primary
        else { fee = 1000; }// d_fee = 0, for primary

        //2. deposit money �޴´�
        int cnt4 = 0;
        int cnt0 = 0;
        do
        {
            try
            {
                int w_money;
                cout << "How much would you like to withdrawal? : "; cin >> w_money;
                cout << "Do you want to withdraw " << w_money << " won from your account? (1) Make withdrawals \t (2) Quit \nEnter : "; int num1; cin >> num1;

                if (num1 == 1)
                {
                    if (w_money <= 0 || w_money > 500000) throw w_money;
                    else if (w_money > a_ptr->getBal() - fee)
                    {
                        if (w_money > a_ptr->getBal()) { cout << "Your balance is lower than " << w_money << " won." << endl; }
                        else { cout << "Your balance cannot afford the fee." << endl; }
                        cnt4 = 1;
                    }
                    else if (w_money % 10000 != 0) { cout << "You can withdraw money in at least units of 10000 won." << endl; cnt4 = 1; }//õ�� �� ��
                    else if (w_money / 50000 > oman) // ATM 5������ ����
                    {
                        if (((w_money - 50000 * oman) / 10000) < man) { // ���������� ��� ����

                            a_ptr->withdraw(w_money + fee);
                            b_ptr->Mychange(a_ptr);
                            cout << "\n" << w_money + fee << " won is withdrawed from your account. The fee is " << fee << " won. Your total balance is " << b_ptr->getBalance() << " won." << endl;
                            cout << "Please take " << w_money << " won from the slot." << endl;

                            cnt0++;
                            oman = 0; man -= ((w_money - 50000 * oman) / 10000);

                            // History save
                            if (sNum == 1111) {
                                ofs.open("ATM1.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else if (sNum == 3333) {
                                ofs.open("ATM3.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }

                            int cnt5 = 0;
                            do {
                                cout << "Would you withdraw more? (1) Yes \t (2) No \nEnter : "; int num2; cin >> num2;
                                if (num2 == 1) { cnt4 = 1; }
                                else if (num2 == 2) { cnt5 = 0; break; }
                                else { cout << "Please select the number between 1~2." << endl; cnt5 = 1; }
                            } while (cnt5 == 1);
                        }
                        else
                        {
                            cout << "\nSorry, the cash in ATM is less than your requirement. It will be complement soon from the bank." << endl; cnt4 = 1;
                            cout << "\nCash in ATM " << endl;
                            cout << "10000 : " << man << endl;
                            cout << "50000 : " << oman << endl; MoneyFromBank();
                        }//ATM�� �� ����, ������ �� ���Ϸ� ���� ������ ä����.
                    }
                    else // 5���������� ��� ����
                        if ((w_money % 50000 / 10000) < man) { // 5���� ��� �� �������� ��� ����

                            a_ptr->withdraw(w_money + fee);
                            b_ptr->Mychange(a_ptr);
                            cout << "\n" << w_money << " won is withdrawed from your account. The fee is " << fee << " won. Your total balance is " << b_ptr->getBalance() << " won." << endl;
                            cnt0++;
                            oman -= (w_money / 50000); man -= (w_money % 50000) / 10000;

                            // History save
                            if (sNum == 1111) {
                                ofs.open("ATM1.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else if (sNum == 3333) {
                                ofs.open("ATM3.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "withdrawal" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }

                            int cnt6 = 0;
                            do {
                                cout << "Would you withdraw more? (1) Yes \t (2) No \nEnter : "; int choice5; cin >> choice5;
                                if (choice5 == 1) { cnt4 = 1; }
                                else if (choice5 == 2) { cnt4 = 0; cnt6 = 0; break; }
                                else { cout << "Please select the number between 1~2." << endl; cnt6 = 1; }
                            } while (cnt6 == 1);
                        }
                        else
                        {
                            cout << "\nSorry, the cash in ATM is less than your requirement. It will be complement soon from the bank." << endl; cnt4 = 1;
                            cout << "\nCash in ATM " << endl;
                            cout << "10000 : " << man << endl;
                            cout << "50000 : " << oman << endl; MoneyFromBank();
                        }
                }
                else if (num1 == 2) { break; }
                else { cout << "Please select the number between 1~2." << endl; cnt4 = 1; }
            }
            catch (int i) { cout << "You cannot withdraw " << i << " won. Please enter the money between 0~500000." << endl; cnt4 = 1; }

        } while (cnt4 == 1 && cnt0 < 3);
        if (cnt0 == 3) { cout << "The withdrawal is allowed at most 3 times." << endl; }
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;
        cout << "Withdrawal process terminates...\n" << endl;
    }

    else
    {
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();

        //1. fee ����
        if (bank == supportBank) { fee = 500; } // d_fee = 500, for non-primary
        else { fee = 1000; }// d_fee = 0, for primary

        //2. deposit money �޴´�
        int cnt4 = 0;
        int cnt0 = 0;
        do
        {
            try
            {
                int w_money;
                cout << "��� �ݾ��� �Է����ּ��� : "; cin >> w_money;
                cout << "���·κ��� " << w_money << " ���� ����Ͻðڽ��ϱ�? (1) �� \t (2) ��� \n�Է� : "; int num1; cin >> num1;

                if (num1 == 1)
                {
                    if (w_money <= 0 || w_money > 500000) throw w_money;
                    else if (w_money > a_ptr->getBal() - fee)
                    {
                        if (w_money > a_ptr->getBal()) { cout << "�ܾ��� " << w_money << " �� �̸��Դϴ�." << endl; }
                        else { cout << "�ܰ� �����Ḧ �δ��� �� �����ϴ�." << endl; }
                        cnt4 = 1;
                    }
                    else if (w_money % 10000 != 0) { cout << "�ּ� 10000�� �������� ����Ͻ� �� �ֽ��ϴ�." << endl; cnt4 = 1; }//õ�� �� ��
                    else if (w_money / 50000 > oman) // ATM 5������ ����
                    {
                        if (((w_money - 50000 * oman) / 10000) < man) { // ���������� ��� ����

                            a_ptr->withdraw(w_money + fee);
                            b_ptr->Mychange(a_ptr);
                            cout << "\n" << w_money + fee << " ���� ���¿��� ��ݵǾ����ϴ�. �������  " << fee << " �� �Դϴ�. ���� �ܾ��� " << b_ptr->getBalance() << " �� �Դϴ�." << endl;
                            cout << w_money << " ���� ���Կ��� �޾��ֽʽÿ�." << endl;

                            cnt0++;
                            oman = 0; man -= ((w_money - 50000 * oman) / 10000);

                            // History save
                            if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }

                            int cnt5 = 0;
                            do {
                                cout << "����� ��� �Ͻðڽ��ϱ�? (1) �� \t (2) �ƴϿ� \n�Է� : "; int num2; cin >> num2;
                                if (num2 == 1) { cnt4 = 1; }
                                else if (num2 == 2) { cnt5 = 0; break; }
                                else { cout << "1~2�� �׸� �� �ϳ��� �������ּ���." << endl; cnt5 = 1; }
                            } while (cnt5 == 1);
                        }
                        else
                        {
                            cout << "\nATM �� ������ �����մϴ�. �������κ��� ������ �� ������ �����Դϴ�." << endl; cnt4 = 1;
                            cout << "\nATM �� ���� ���� " << endl;
                            cout << "10000 : " << man << endl;
                            cout << "50000 : " << oman << endl; MoneyFromBank();
                        }//ATM�� �� ����, ������ �� ���Ϸ� ���� ������ ä����.
                    }
                    else // 5���������� ��� ����
                        if ((w_money % 50000 / 10000) < man) { // 5���� ��� �� �������� ��� ����

                            a_ptr->withdraw(w_money + fee);
                            b_ptr->Mychange(a_ptr);
                            cout << "\n" << w_money << " ���� ���·κ��� ��ݵǾ����ϴ�. ������� " << fee << " ���Դϴ�. ���� �ܾ��� " << b_ptr->getBalance() << " �� �Դϴ�." << endl;

                            cnt0++;
                            oman -= (w_money / 50000); man -= (w_money % 50000) / 10000;

                            //History save
                            if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���" << setw(18) << w_money << setw(27) << "-" << endl;
                                ofs.close();
                            }

                            int cnt6 = 0;
                            do {
                                cout << "�� ����Ͻðڽ��ϱ�? (1) �� \t (2) �ƴϿ� \n�Է� : "; int choice5; cin >> choice5;
                                if (choice5 == 1) { cnt4 = 1; }
                                else if (choice5 == 2) { cnt4 = 0; cnt6 = 0; break; }
                                else { cout << "1~2�� �׸� �� �ϳ��� �������ּ���." << endl; cnt6 = 1; }
                            } while (cnt6 == 1);
                        }
                        else
                        {
                            cout << "\nATM �� ������ �����մϴ�. �������κ��� ������ �� ������ �����Դϴ�." << endl; cnt4 = 1;
                            cout << "\nATM �� ���� ���� " << endl;
                            cout << "10000 : " << man << endl;
                            cout << "50000 : " << oman << endl; MoneyFromBank();
                        }
                }
                else if (num1 == 2) { break; }
                else { cout << "1~2�� �׸� �� �ϳ��� �������ּ���." << endl; cnt4 = 1; }
            }
            catch (int i) { cout << i << " ���� ����Ͻ� �� �����ϴ�. 0~50���� ������ ���� �Է��ϼ���." << endl; cnt4 = 1; }
        } while (cnt4 == 1 && cnt0 < 3);
        if (cnt0 == 3) { cout << "����� �ִ� 3ȸ�� ���ѵ˴ϴ�." << endl; }
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        cout << "�۱� �ý��� ����...\n" << endl;
    }
}
void ATM::Transfer()
{
    if (lan == 1)
    {
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();
        int balance = a_ptr->getBal();

        int cnt = 0;
        do
        {
            cout << "What kind of transfer you would like to ? \t (1) Cash Transfer \t (2) Account Transfer \t (3) Quit \nEnter : "; int num1; cin >> num1;
            if (num1 == 1) {
                //�۱� ���� �����
                int cnt1 = 0;
                do
                {
                    try
                    {
                        cout << "\nEnter the destination account number for transfer : "; long long a; cin >> a;
                        if (b_ptr->check2(a) != true) throw a;

                        //fee ����
                        a_ptr2 = b_ptr->getUrAccountInfo();
                        string bank2 = a_ptr2->getBank();

                        if (bank == supportBank && bank2 == supportBank) { fee = 1500; }
                        else if (bank == supportBank || bank2 == supportBank) { fee = 2000; }
                        else { fee = 2500; }
                        cnt1 = 0;

                        //transfer
                        try
                        {
                            cout << "\nHow many 10000 won would you insert for transfer? : "; int cash1; cin >> cash1;
                            cout << "\nHow many 50000 won would you insert for transfer? : "; int cash2; cin >> cash2;

                            int cash = cash1 + cash2;
                            int i_money = cash1 * 10000 + cash2 * 50000;
                            if (cash > 50 || cash <= 0) throw i_money;

                            a_ptr2->deposit(i_money - fee);
                            man += cash1;
                            oman += cash2;

                            cout << "The fee is " << fee << " won. " << i_money - fee << " won is transfered to " << a_ptr2->getUser() << " " << a_ptr2->getBank() << " " << a_ptr2->getA() << " account." << endl;
                            b_ptr->Urchange(a_ptr2);
                            cnt = 0;

                            // History save
                            if (sNum == 1111) {
                                ofs.open("ATM1.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "cash transfer" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "cash transfer" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else if (sNum == 3333) {
                                ofs.open("ATM3.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "cash transfer" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "cash transfer" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                        }
                        catch (int i) { cout << "Cannot transfer " << i << " won. The limit amount of inserted cash is 50. Please try again." << endl; cnt = 1; }
                    }
                    catch (long long i)
                    {
                        cout << i << "is invalid account number." << endl;
                        int cnt2 = 0;
                        do
                        {
                            cout << "Would you try again ? \t(1) Yes \t(2) Quit \nEnter : "; int num2; cin >> num2;
                            if (num2 == 1) { cnt1 = 1; cnt2 = 0; }
                            else if (num2 == 2) { cnt1 = 0; cnt2 = 0; }
                            else { cout << "Please select the number between 1~2." << endl; cnt2 = 1; }
                        } while (cnt2 == 1);
                    }
                } while (cnt1 == 1);
            }
            else if (num1 == 2)
            {
                //�۱� ���� �����
                int cnt1 = 0;
                do
                {
                    try
                    {
                        cout << "\nEnter the destination account number for transfer : "; long long a; cin >> a;
                        if (b_ptr->check2(a) != true) throw a;

                        //fee ����
                        a_ptr2 = b_ptr->getUrAccountInfo();
                        string bank2 = a_ptr2->getBank();

                        if (bank == supportBank && bank2 == supportBank) { fee = 1500; }
                        else if (bank == supportBank || bank2 == supportBank) { fee = 2000; }
                        else { fee = 2500; }
                        cnt1 = 0;

                        //transfer
                        try
                        {
                            cout << "\nHow much would you transfer to that account? : "; int t_money; cin >> t_money;

                            if (t_money <= 0 || t_money > balance - fee) throw t_money;

                            a_ptr2->deposit(t_money);
                            a_ptr->withdraw(t_money + fee);

                            cout << "The fee is " << fee << " won. " << t_money << " won is transfered to " << a_ptr2->getUser() << " " << a_ptr2->getBank() << " " << a_ptr2->getA() << " account." << endl;
                            cout << "Your balance is " << a_ptr->getBal() << " won." << endl;
                            b_ptr->Urchange(a_ptr2);
                            b_ptr->Mychange(a_ptr);
                            cnt = 0;

                            // History save
                            if (sNum == 1111) {
                                ofs.open("ATM1.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "account transfer" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "account transfer" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else if (sNum == 3333) {
                                ofs.open("ATM3.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "account transfer" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "account transfer" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                        }
                        catch (int i) { cout << "Cannot transfer " << i << " won. You can transfer the money range of 0 ~ (your balance - fee). Please try again." << endl; cnt = 1; }
                    }
                    catch (long long i)
                    {
                        cout << i << "is invalid account number." << endl;
                        int cnt2 = 0;
                        do
                        {
                            cout << "Would you try again ? \t(1) Yes \t(2) Quit \nEnter : "; int num2; cin >> num2;
                            if (num2 == 1) { cnt1 = 1; cnt2 = 0; }
                            else if (num2 == 2) { cnt1 = 0; cnt2 = 0; }
                            else { cout << "Please select the number between 1~2." << endl; cnt2 = 1; }
                        } while (cnt2 == 1);
                    }
                } while (cnt1 == 1);
                cnt = 0;
            }
            else if (num1 == 3) { cnt = 0; }
            else { cout << "Please select the number between 1~3." << endl; cnt = 1; }
        } while (cnt == 1);
        cout << "The amounts of cash in ATM are 10000won : " << man << ", 50000won : " << oman << endl;
        cout << "Transfer process terminates...\n" << endl;
    }
    else
    {
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();
        int balance = a_ptr->getBal();

        int cnt = 0;
        do
        {
            cout << "� �۱��� �Ͻðڽ��ϱ�? \t (1) ���� �۱� \t (2) ���� �۱� \t (3) ��� \n�Է� : "; int num1; cin >> num1;
            if (num1 == 1) {
                //�۱� ���� �����
                int cnt1 = 0;
                do
                {
                    try
                    {
                        cout << "\n�۱� ���¸� �Է����ּ��� : "; long long a; cin >> a;
                        if (b_ptr->check2(a) != true) throw a;

                        //fee ����
                        a_ptr2 = b_ptr->getUrAccountInfo();
                        string bank2 = a_ptr2->getBank();

                        if (bank == supportBank && bank2 == supportBank) { fee = 1500; }
                        else if (bank == supportBank || bank2 == supportBank) { fee = 2000; }
                        else { fee = 2500; }
                        cnt1 = 0;

                        //transfer
                        try
                        {
                            cout << "\n10000�� �� �� ���� �۱��Ͻðڽ��ϱ�? : "; int cash1; cin >> cash1;
                            cout << "\n50000�� �� �� ���� �۱��Ͻðڽ��ϱ�? : "; int cash2; cin >> cash2;

                            int cash = cash1 + cash2;
                            int i_money = cash1 * 10000 + cash2 * 50000;
                            if (cash > 50 || cash <= 0) throw i_money;

                            a_ptr2->deposit(i_money - fee);
                            man += cash1;
                            oman += cash2;

                            cout << "������� " << fee << " �� �Դϴ�. " << i_money - fee << " ���� " << a_ptr2->getUser() << " " << a_ptr2->getBank() << " " << a_ptr2->getA() << " ���·� �۱ݵǾ����ϴ�." << endl;
                            b_ptr->Urchange(a_ptr2);
                            cnt = 0;

                            // History save
                            if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���� �۱�" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���� �۱�" << setw(18) << i_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                        }
                        catch (int i) { cout << i << " ���� �۱��� �� �����ϴ�. ������ 0~50�� ������ �۱� �����մϴ�." << endl; cnt = 1; }
                    }
                    catch (long long i)
                    {
                        cout << i << " �� �������� �ʴ� �����Դϴ�." << endl;
                        int cnt2 = 0;
                        do
                        {
                            cout << "�ٽ� �õ��Ͻðڽ��ϱ� ? \t(1) �� \t(2) �ƴϿ� \n�Է� : "; int num2; cin >> num2;
                            if (num2 == 1) { cnt1 = 1; cnt2 = 0; }
                            else if (num2 == 2) { cnt1 = 0; cnt2 = 0; }
                            else { cout << "1~2 �׸� �� �ϳ��� �������ּ���." << endl; cnt2 = 1; }
                        } while (cnt2 == 1);
                    }
                } while (cnt1 == 1);
            }
            else if (num1 == 2)
            {
                //�۱� ���� �����
                int cnt1 = 0;
                do
                {
                    try
                    {
                        cout << "\n�۱� ���¸� �Է����ּ��� : "; long long a; cin >> a;
                        if (b_ptr->check2(a) != true) throw a;

                        //fee ����
                        a_ptr2 = b_ptr->getUrAccountInfo();
                        string bank2 = a_ptr2->getBank();

                        if (bank == supportBank && bank2 == supportBank) { fee = 1500; }
                        else if (bank == supportBank || bank2 == supportBank) { fee = 2000; }
                        else { fee = 2500; }
                        cnt1 = 0;

                        //transfer
                        try
                        {
                            cout << "\n�ش� ���¿� �۱��� �ݾ��� �Է����ּ��� : "; int t_money; cin >> t_money;

                            if (t_money <= 0 || t_money > balance - fee) throw t_money;

                            a_ptr2->deposit(t_money);
                            a_ptr->withdraw(t_money + fee);

                            cout << "������� " << fee << " �� �Դϴ�. " << t_money << " ���� " << a_ptr2->getUser() << " " << a_ptr2->getBank() << " " << a_ptr2->getA() << " ���·� �۱ݵǾ����ϴ�." << endl;
                            cout << "�ܾ��� " << a_ptr->getBal() << " �� �Դϴ�." << endl;
                            b_ptr->Urchange(a_ptr2);
                            b_ptr->Mychange(a_ptr);
                            cnt = 0;

                            // History save
                            if (sNum == 2222) {
                                ofs.open("ATM2.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���� �۱�" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                            else {
                                ofs.open("ATM4.txt", ios::app);
                                ofs << setw(20) << getTime() << setw(25) << getRand() << setw(25) << a_ptr->getC() << setw(25) << "���� �۱�" << setw(18) << t_money << setw(31) << a_ptr2->getA() << endl;
                                ofs.close();
                            }
                        }
                        catch (int i) { cout << i << " ���� �۱��� �� �����ϴ�. �۱� �ݾ��� 0�� ~ (���� �ܾ� - ������)������ �ݾ׸� �Է� �����մϴ�." << endl; cnt = 1; }
                    }
                    catch (long long i)
                    {
                        cout << i << "�� �������� �ʴ� �����Դϴ�." << endl;
                        int cnt2 = 0;
                        do
                        {
                            cout << "�ٽ� �õ��Ͻðڽ��ϱ� ? \t(1) �� \t(2) �ƴϿ� \n�Է� : "; int num2; cin >> num2;
                            if (num2 == 1) { cnt1 = 1; cnt2 = 0; }
                            else if (num2 == 2) { cnt1 = 0; cnt2 = 0; }
                            else { cout << "1~2�� �׸� �� �ϳ��� �������ּ���." << endl; cnt2 = 1; }
                        } while (cnt2 == 1);
                    }
                } while (cnt1 == 1);
                cnt = 0;
            }
            else if (num1 == 3) { cnt = 0; }
            else { cout << "1~3�� �׸� �� �ϳ��� �������ּ���." << endl; cnt = 1; }
        } while (cnt == 1);
        cout << "ATM�� �ִ� ���� �� : " << man << ", ������ �� : " << oman << endl;
        cout << "�۱� �ý��� ����...\n" << endl;
    }
}
void ATM::History()
{
    // ���� ��������� �б�.
}

/*---------------------------------------DERIVED CLASS-------------------------------------*/

ATM1::ATM1() {}
ATM1::ATM1(Bank* b, int oh, int ma) { b_ptr = b; oman = oh; man = ma; cout << "This ATM only supports SHINHAN bank in English" << endl; lan = 1; supportBank = "Shinhan"; sNum = 1111; }
int ATM1::CardCheck()
{// 1. Card ���� check -> User of Admin... 2. Pin check
      //2.User athorization
    cout << "This ATM's serial number is " << sNum << "." << endl;
    cout << "Insert your card ( Enter the card number ) : "; long long c; cin >> c;

    if (b_ptr->check(c) == true) // true
    {
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();
        long long account = a_ptr->getA();
        //Admin or User
        if (account == 0)
        {
            int cnt2 = 0;
            do
            {
                int pwd;
                try
                {
                    cout << "Please enter your password : "; cin >> pwd;
                    if (b_ptr->pinCheck(pwd) != true) throw pwd;
                    cout << "Welcome ! " << a_ptr->getUser() << endl;
                    return 2;
                }
                catch (int i)
                {
                    cnt2++;
                    cout << i << "is incorrect password." << endl;
                    if (cnt2 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                }
            } while (cnt2 < 3);
        }
        else
        {
            //User define
            if (bank != supportBank) { cout << "This card is not supported in this ATM." << endl; return 1; }
            else
            {
                //pin check
                int cnt1 = 0;
                do {
                    int pswd;
                    try
                    {
                        cout << "Please enter your password : "; cin >> pswd;
                        if (b_ptr->pinCheck(pswd) != true) throw pswd;
                        return 0;
                    }
                    catch (int i)
                    {
                        cnt1++;
                        cout << i << "is incorrect password." << endl;
                        if (cnt1 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                    }

                } while (cnt1 < 3);
            }
        }
    }
    else { return 1; }
}

void ATM1::History()
{
    string str;
    ifs.open("ATM1.txt"); // atm class ���� ������ֱ�
    if (ifs.is_open()) {
        while (getline(ifs, str)) {
            cout << str << endl;
        }
    }
}


ATM2::ATM2() {}
ATM2::ATM2(Bank* b, int oh, int ma) {
    b_ptr = b;
    oman = oh; man = ma;
    supportBank = "Daegu";
    sNum = 2222;
    cout << "This ATM's serial number is " << sNum << "." << endl;
    cout << "This ATM only supports Daegu bank in both English and Korean" << endl;
}
int ATM2::CardCheck(int l)
{
    lan = l;
    if (lan == 1)
    {
        cout << "Insert your card ( Enter the card number ) : "; long long c; cin >> c;
        if (b_ptr->check(c) == true) // true
        {
            a_ptr = b_ptr->getAccountInfo();
            string bank = a_ptr->getBank();
            long long account = a_ptr->getA();
            //Admin or User
            if (account == 0)
            {
                int cnt2 = 0;
                do
                {
                    int pwd;
                    try
                    {
                        cout << "Please enter your password : "; cin >> pwd;
                        if (b_ptr->pinCheck(pwd) != true) throw pwd;
                        cout << "Welcome ! " << a_ptr->getUser() << endl;
                        return 2;
                    }
                    catch (int i)
                    {
                        cnt2++;
                        cout << i << "is incorrect password." << endl;
                        if (cnt2 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                    }
                } while (cnt2 < 3);
            }
            else
            {
                //User define
                if (bank != supportBank) { cout << "This card is not supported in this ATM." << endl; return 1; }
                else
                {
                    //pin check
                    int cnt1 = 0;
                    do {
                        int pswd;
                        try
                        {
                            cout << "Please enter your password : "; cin >> pswd;
                            if (b_ptr->pinCheck(pswd) != true) throw pswd;
                            return 0;
                        }
                        catch (int i)
                        {
                            cnt1++;
                            cout << i << "is incorrect password." << endl;
                            if (cnt1 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                        }

                    } while (cnt1 < 3);
                }
            }
        }
        else { return 1; }
    }
    else
    {
        cout << "ī�带 �־��ּ��� ( ī�� ��ȣ�� �Է��ϼ��� ) : "; long long c; cin >> c;

        if (b_ptr->check(c) == true) // true
        {
            a_ptr = b_ptr->getAccountInfo();
            string bank = a_ptr->getBank();
            long long account = a_ptr->getA();
            //Admin or User
            if (account == 0)
            {
                int cnt2 = 0;
                do
                {
                    int pwd;
                    try
                    {
                        cout << "��й�ȣ�� �Է����ּ��� : "; cin >> pwd;
                        if (b_ptr->pinCheck(pwd) != true) throw pwd;
                        cout << "ȯ���մϴ� ! " << a_ptr->getUser() << endl;
                        return 2;
                    }
                    catch (int i)
                    {
                        cnt2++;
                        cout << i << " �� ��й�ȣ�� �ƴմϴ�." << endl;
                        if (cnt2 == 3) { cout << "��й�ȣ 3ȸ �����Դϴ�. �� ī�带 ������ �� �����ϴ�." << endl; return 1; }
                    }
                } while (cnt2 < 3);
            }
            else
            {
                //User define
                if (bank != supportBank) { cout << "ī���� ������ ATM���� �������� �ʽ��ϴ�." << endl; return 1; }
                else
                {
                    //pin check
                    int cnt1 = 0;
                    do {
                        int pswd;
                        try
                        {
                            cout << "��й�ȣ�� �Է����ּ��� : "; cin >> pswd;
                            if (b_ptr->pinCheck(pswd) != true) throw pswd;
                            return 0;
                        }
                        catch (int i)
                        {
                            cnt1++;
                            cout << i << " �� ��й�ȣ�� �ƴմϴ�." << endl;
                            if (cnt1 == 3) { cout << "��й�ȣ 3ȸ �����Դϴ�. �� ī�带 ������ �� �����ϴ�." << endl; return 1; }
                        }

                    } while (cnt1 < 3);
                }
            }
        }
        else { return 1; }
    }
}
void ATM2::History()
{
    string str;

    if (lan == 1)
    {
        cout << "\tTime\t\tTransaction ID\t\t    Card Number    \t  Transaction Types\t\t   Amount\t  Other Transaction-specific Information" << endl << endl;
        ifs.open("ATM2.txt"); // atm class ���� ������ֱ�
        if (ifs.is_open()) {
            while (getline(ifs, str)) {
                cout << str << endl;
            }
        }
    }
    else
    {
        cout << "\t �ð� \t\t\t Ʈ����� ���̵� \t    ī�� ��ȣ     \t      �ŷ� ����     \t   �ݾ�    \t         Ÿ ���� �ŷ� ���� " << endl << endl;
        ifs.open("ATM2.txt"); // atm class ���� ������ֱ�
        if (ifs.is_open()) {
            while (getline(ifs, str)) {
                cout << str << endl;
            }
        }
    }
}



ATM3::ATM3() {}
ATM3::ATM3(Bank* b, int oh, int ma) { b_ptr = b; oman = oh; man = ma; cout << "This Shinhan ATM supports every bank in English" << endl; lan = 1; supportBank = "Shinhan"; sNum = 3333; }
int ATM3::CardCheck()
{// 1. Card ���� check -> User of Admin... 2. Pin check
    cout << "This ATM's serial number is " << sNum << "." << endl;

    cout << "Insert your card ( Enter the card number ) : "; long long c; cin >> c;

    if (b_ptr->check(c) == true) // true
    {
        a_ptr = b_ptr->getAccountInfo();
        string bank = a_ptr->getBank();
        long long account = a_ptr->getA();
        //Admin or User
        if (account == 0)
        {
            int cnt2 = 0;
            do
            {
                int pwd;
                try
                {
                    cout << "Please enter your password : "; cin >> pwd;
                    if (b_ptr->pinCheck(pwd) != true) throw pwd;
                    cout << "Welcome ! " << a_ptr->getUser() << endl;
                    return 2;
                }
                catch (int i)
                {
                    cnt2++;
                    cout << i << "is incorrect password." << endl;
                    if (cnt2 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                }
            } while (cnt2 < 3);
        }
        else
        {
            //pin check
            int cnt1 = 0;
            do {
                int pswd;
                try
                {
                    cout << "Please enter your password : "; cin >> pswd;
                    if (b_ptr->pinCheck(pswd) != true) throw pswd;
                    return 0;
                }
                catch (int i)
                {
                    cnt1++;
                    cout << i << "is incorrect password." << endl;
                    if (cnt1 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                }
            } while (cnt1 < 3);
        }
    }
    else { return 1; }
}
void ATM3::History()
{
    string str;
    ifs.open("ATM3.txt"); // atm class ���� ������ֱ�
    if (ifs.is_open()) {
        while (getline(ifs, str)) {
            cout << str << endl;
        }
    }
}


ATM4::ATM4() {}
ATM4::ATM4(Bank* b, int oh, int ma) {
    b_ptr = b;
    oman = oh;
    man = ma;
    supportBank = "Daegu";
    sNum = 4444;
    cout << "This ATM's serial number is " << sNum << "." << endl;
    cout << "This Daegu ATM supports every bank in both English and Korean" << endl;
}
int ATM4::CardCheck(int l)
{
    cout << "This ATM's serial number is " << sNum << "." << endl;
    lan = l;
    if (lan == 1)
    {
        cout << "Insert your card ( Enter the card number ) : "; long long c; cin >> c;

        if (b_ptr->check(c) == true) // true
        {
            a_ptr = b_ptr->getAccountInfo();
            string bank = a_ptr->getBank();
            long long account = a_ptr->getA();
            //Admin or User
            if (account == 0)
            {
                int cnt2 = 0;
                do
                {
                    int pwd;
                    try
                    {
                        cout << "Please enter your password : "; cin >> pwd;
                        if (b_ptr->pinCheck(pwd) != true) throw pwd;
                        cout << "Welcome ! " << a_ptr->getUser() << endl;
                        return 2;
                    }
                    catch (int i)
                    {
                        cnt2++;
                        cout << i << "is incorrect password." << endl;
                        if (cnt2 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                    }
                } while (cnt2 < 3);
            }
            else
            {
                //pin check
                int cnt1 = 0;
                do {
                    int pswd;
                    try
                    {
                        cout << "Please enter your password : "; cin >> pswd;
                        if (b_ptr->pinCheck(pswd) != true) throw pswd;
                        return 0;
                    }
                    catch (int i)
                    {
                        cnt1++;
                        cout << i << "is incorrect password." << endl;
                        if (cnt1 == 3) { cout << "3 times password error. You cannot access to this card." << endl; return 1; }
                    }

                } while (cnt1 < 3);
            }
        }
        else { return 1; }
    }
    else
    {
        cout << "ī�带 �־��ּ��� ( ī�� ��ȣ�� �Է��ϼ��� ) : "; long long c; cin >> c;

        if (b_ptr->check(c) == true) // true
        {
            a_ptr = b_ptr->getAccountInfo();
            string bank = a_ptr->getBank();
            long long account = a_ptr->getA();
            //Admin or User
            if (account == 0)
            {
                int cnt2 = 0;
                do
                {
                    int pwd;
                    try
                    {
                        cout << "��й�ȣ�� �Է����ּ��� : "; cin >> pwd;
                        if (b_ptr->pinCheck(pwd) != true) throw pwd;
                        cout << "ȯ���մϴ� ! " << a_ptr->getUser() << endl;
                        return 2;
                    }
                    catch (int i)
                    {
                        cnt2++;
                        cout << i << " �� ��й�ȣ�� �ƴմϴ�." << endl;
                        if (cnt2 == 3) { cout << "��й�ȣ 3ȸ �����Դϴ�. �� ī�带 ������ �� �����ϴ�." << endl; return 1; }
                    }
                } while (cnt2 < 3);
            }
            else
            {
                //pin check
                int cnt1 = 0;
                do {
                    int pswd;
                    try
                    {
                        cout << "��й�ȣ�� �Է����ּ��� : "; cin >> pswd;
                        if (b_ptr->pinCheck(pswd) != true) throw pswd;
                        return 0;
                    }
                    catch (int i)
                    {
                        cnt1++;
                        cout << i << " �� ��й�ȣ�� �ƴմϴ�." << endl;
                        if (cnt1 == 3) { cout << "��й�ȣ 3ȸ �����Դϴ�. �� ī�带 ������ �� �����ϴ�." << endl; return 1; }
                    }

                } while (cnt1 < 3);
            }
        }
        else { return 1; }
    }
}
void ATM4::History()
{
    string str;

    if (lan == 1)
    {
        cout << "\tTime\t\t\tTransaction ID\t\t    Card Number    \t  Transaction Types\t\t   Amount\t  Other Transaction-specific Information" << endl << endl;
        ifs.open("ATM4.txt"); // atm class ���� ������ֱ�
        if (ifs.is_open()) {
            while (getline(ifs, str)) {
                cout << str << endl;
            }
        }
    }
    else
    {
        cout << "\t �ð� \t\t\t Ʈ����� ���̵� \t    ī�� ��ȣ     \t      �ŷ� ����     \t   �ݾ�    \t         Ÿ ���� �ŷ� ���� " << endl << endl;
        ifs.open("ATM4.txt"); // atm class ���� ������ֱ�
        if (ifs.is_open()) {
            while (getline(ifs, str)) {
                cout << str << endl;
            }
        }
    }
}
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Account.h"

#include "Bank.h"

class ATM // Control class
{
protected:
	int sNum; // �ø����ȣ
	int man; // ������
	int oman; // ��������
	int lan; // language choice
	int fee;
	int index1; // �� ���� ���� index
	int index2; // Ÿ�� ���� ���� index (�۱�)
	string supportBank;
	Account* a_ptr;
	Account* a_ptr2;
	Bank* b_ptr;

public:
	ATM();
	ATM(Bank* b, int oh, int ma);
	void MoneyFromBank();
	virtual int CardCheck();
	int getLan();
	int getOman();
	int getMan();
	int getRand();
	string getTime();
	void ShowMenu();
	void AdminMenu();
	void Deposit();
	void Withdraw();
	void Transfer();
	virtual void History(); // Admin -> Transacation history

};

class ATM1 : public ATM {
public:
	ATM1();
	ATM1(Bank* b, int oh, int ma);
	int CardCheck();
	void History();
};

class ATM2 : public ATM {
public:
	ATM2();
	ATM2(Bank* b, int oh, int ma);
	int CardCheck(int l);
	void History();
};

class ATM3 : public ATM {
public:
	ATM3();
	ATM3(Bank* b, int oh, int ma);
	int CardCheck();
	void History();
};

class ATM4 : public ATM {
public:
	ATM4();
	ATM4(Bank* b, int oh, int ma);
	int CardCheck(int l);
	void History();
};


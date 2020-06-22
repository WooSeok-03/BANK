#include<iostream>
#define MAX_LEN 20
#define MAX_MEMBER 100

using namespace std;

class Account {
private:
	const int accID;
	int balance;
	const int Resident_registration_number;
	char* cusName;
public:
	Account(int accID, int balance, int Resident_registration_number, char* cusName)	//생성자
		: accID(accID), Resident_registration_number(Resident_registration_number)
	{
		this->balance = balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	Account(Account& copy_user)	//복사 생성자
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "복사 생성자 호출" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	~Account()	//소멸자
	{
		delete[] cusName;
	}

	void Deposit(int balance) {
		this->balance += balance;
	}

	bool Check_AccID(int accID) const{
		return this->accID == accID;
	}

	bool Withdraw(int balance) {
		if (this->balance < balance) {
			return false;
		}

		this->balance -= balance;
		return true;
	}

	void Print_Account_Information() {
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << endl;
	}

	bool Check_SSN(int Resident_registration_number) const{
		return this->Resident_registration_number == Resident_registration_number;
	}
};

class AccountManager {
private:
	Account* Acc_Member[MAX_MEMBER];
	int Member_Number;
public:
	AccountManager() {
		for (int i = 0; i < MAX_MEMBER; i++) {
			Acc_Member[i] = NULL;
		}

		Member_Number = 0;
	}

	void Account_Open() {
		int accID;
		int balance;
		int Resident_registration_number;
		char cusnName[MAX_LEN];

		if (Member_Number == 100) {
			cout << "가입 인원이 초과되었습니다.\n" << endl;
			return;
		}

		cout << "[계좌개설]" << endl;
		cout << "계좌ID: ";
		cin >> accID;

		cout << "이  름: ";
		cin >> cusnName;

		cout << "주민등록번호: ";
		cin >> Resident_registration_number;

		cout << "입금액: ";
		cin >> balance;
		if (balance < 10) {
			cout << "계좌개설 시에는 10원이상의 입금액을 넣어야 합니다.\n" << endl;
			return;
		}


		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_SSN(Resident_registration_number)) {
				cout << "이미 가입 되었습니다." << endl;
				return;
			}
			if (Acc_Member[i]->Check_AccID(accID)) {
				cout << "이미 있는 계좌ID 입니다." << endl;
				return;
			}
		}

		Acc_Member[Member_Number] = new Account(accID, balance, Resident_registration_number, cusnName);

		Member_Number++;
		cout << endl;
	}

	void Deposit() {
		int Deposit_Amount;
		int Check_AccID;

		cout << "[입    금]" << endl;
		cout << "계좌ID: ";
		cin >> Check_AccID;
		cout << "입금액: ";
		cin >> Deposit_Amount;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(Check_AccID)) {
				Acc_Member[i]->Deposit(Deposit_Amount);
			}
			else {
				cout << "유효하지 않은 ID 입니다." << endl;
			}
		}
		cout << endl;
	}

	void Withdraw() {
		int Withdrawal_Amount;
		int Check_AccID;

		cout << "[출    금]" << endl;
		cout << "계좌ID: ";
		cin >> Check_AccID;
		cout << "출금액: ";
		cin >> Withdrawal_Amount;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(Check_AccID)) {
				if (!Acc_Member[i]->Withdraw(Withdrawal_Amount)) {
					cout << "출금 금액이 현재 잔액보다 많습니다." << endl;
				}
				return;
			}
		}

		cout << "유효하지 않은 ID 입니다." << endl;
		cout << endl;
	}

	void Print_Account_Information() {

		for (int i = 0; i < Member_Number; i++) {
			Acc_Member[i]->Print_Account_Information();
		}
	}


};




int main(void) {
	int choice;
	AccountManager account_manager;

	while (1) {
		cout << "-----Menu------\n1. 계좌개설\n2. 입    금\n3. 출    금\n4. 계좌정보 전체 출력\n5. 프로그램 종료" << endl;
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			account_manager.Account_Open();
			break;
		case 2:
			account_manager.Deposit();
			break;
		case 3:
			account_manager.Withdraw();
			break;
		case 4:
			account_manager.Print_Account_Information();
			break;
		case 5:
			return 0;
		default:
			break;
		}
	}
}
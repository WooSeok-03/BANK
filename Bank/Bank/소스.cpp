#include<iostream>
#define MAX_LEN 20
#define MAX_MEMBER 100

using namespace std;

class Account {
protected:
	const int accID;
	int balance;
	const long long int Resident_registration_number;
	char* cusName;

public:
	Account(int accID, int balance, int Resident_registration_number, char* cusName)	//생성자
		: accID(accID), Resident_registration_number(Resident_registration_number)
	{
		this->balance = balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
		
		//이거 다 깊은복사로 만들어야함
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
		this->balance += Interest(balance);
		this->balance += balance;
	}

	virtual int Interest(int money) {
		int interest = (this->balance + money) * 0.01 ;	//이자
		cout << "이자액 : " << interest << endl << endl;
		return interest;
	}

	bool Check_AccID(int accID) const {
		return this->accID == accID;
	}

	bool Withdraw(int balance) {
		if (this->balance < balance) {
			return false;
		}

		this->balance -= balance;
		return true;
	}

	virtual void Print_Account_Information() {
		cout << "보통 계좌" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl << endl;
	}

	bool Check_SSN(int Resident_registration_number) const {
		return this->Resident_registration_number == Resident_registration_number;
	}

	int get_balance()
	{
		return balance;
	}

	const long long int get_Resident_registration_number()
	{
		return Resident_registration_number;
	}

	char* get_cusName()
	{
		return cusName;
	}
};

class Deposit_Account : public Account {
public:
	Deposit_Account(int accID, Account *Member) : Account(accID, 0, Member->get_Resident_registration_number(), Member->get_cusName())
	{
		
	}

	virtual int Interest(int money) {
		int interest = (this->balance + money) * 0.02;	//이자
		cout << "이자액 : " << interest << endl << endl;
		return interest;
	}

	virtual void Print_Account_Information() {
		cout << "예금 계좌" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl << endl;
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

	~AccountManager()
	{
		for (int i = 0; i < Member_Number; i++) {
			delete Acc_Member[i];
		}
	}

	void Account_Open() {
		int account_choice;
		cout << "개설할 계좌를 선택해 주세요." << endl;
		cout << "1. 보통 계좌\n2. 예금 계좌" << endl;
		cin >> account_choice;

		if (account_choice == 1) {
			Ordinary_Account_Open();
		}
		else if (account_choice == 2) {
			Deposit_Account_Open();
		}
		else {
			cout << "보통 계좌(1)와 예금계좌(2) 중 하나를 선택해주세요." << endl << endl;
		}
	}

	void Ordinary_Account_Open() {
		int accID;
		int balance;
		int Resident_registration_number;
		char cusnName[MAX_LEN];

		if (Member_Number == MAX_MEMBER) {
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
			cout << "계좌개설 시에는 10원이상의 입금액을 넣어야 합니다.\n" << endl << endl;
			return;
		}


		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_SSN(Resident_registration_number)) {
				cout << "이미 가입 되었습니다." << endl << endl;
				return;
			}
			if (Acc_Member[i]->Check_AccID(accID)) {
				cout << "이미 있는 계좌ID 입니다." << endl << endl;
				return;
			}
		}

		Acc_Member[Member_Number] = new Account(accID, balance, Resident_registration_number, cusnName);

		Member_Number++;
		cout << endl;
	}

	void Deposit_Account_Open() {
		int accID;
		int deposit_accID;

		int save_memberNumber = -1;

		cout << "보통 계좌의 계좌번호를 입력해 주세요." << endl;
		cout << "보통 계좌 ID : ";
		cin >> accID;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(accID)) {
				save_memberNumber = i;
				break;
			}
		}
		if (save_memberNumber == -1)
		{
			cout << endl;
			cout << "보통 계좌 개설 후 예금 계좌를 개설할 수 있습니다." << endl;
			cout << "보통 계좌를 먼저 만들고 시도하여 주십시오." << endl << endl;
			return;
		}

		cout << "예금 계좌에서 사용할 계좌번호를 입력해 주세요." << endl;
		cout << "예금 계좌 ID : ";
		cin >> deposit_accID;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(deposit_accID)) {
				cout << "이미 있는 계좌ID 입니다." << endl << endl;
				return;
			}
		}

		Acc_Member[Member_Number] = new Deposit_Account(deposit_accID, Acc_Member[save_memberNumber]);

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
				cout << "a" << endl;
				Acc_Member[i]->Deposit(Deposit_Amount);
				return;
			}
		}

		cout << "유효하지 않은 ID 입니다." << endl << endl;
	
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
					cout << "출금 금액이 현재 잔액보다 많습니다." << endl << endl;
				}
				return;
			}
		}

		cout << "유효하지 않은 ID 입니다." << endl << endl;
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

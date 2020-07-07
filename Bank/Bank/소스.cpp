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
	Account(int accID, int balance, int Resident_registration_number, char* cusName)	//������
		: accID(accID), Resident_registration_number(Resident_registration_number)
	{
		this->balance = balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
		
		//�̰� �� ��������� ��������
	}

	Account(Account& copy_user)	//���� ������
		: accID(copy_user.accID), Resident_registration_number(copy_user.Resident_registration_number)
	{
		cout << "���� ������ ȣ��" << endl;
		this->balance = copy_user.balance;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, copy_user.cusName);
	}

	~Account()	//�Ҹ���
	{
		delete[] cusName;
	}

	void Deposit(int balance) {
		this->balance += Interest(balance);
		this->balance += balance;
	}

	virtual int Interest(int money) {
		int interest = (this->balance + money) * 0.01 ;	//����
		cout << "���ھ� : " << interest << endl << endl;
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
		cout << "���� ����" << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl << endl;
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
		int interest = (this->balance + money) * 0.02;	//����
		cout << "���ھ� : " << interest << endl << endl;
		return interest;
	}

	virtual void Print_Account_Information() {
		cout << "���� ����" << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl << endl;
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
		cout << "������ ���¸� ������ �ּ���." << endl;
		cout << "1. ���� ����\n2. ���� ����" << endl;
		cin >> account_choice;

		if (account_choice == 1) {
			Ordinary_Account_Open();
		}
		else if (account_choice == 2) {
			Deposit_Account_Open();
		}
		else {
			cout << "���� ����(1)�� ���ݰ���(2) �� �ϳ��� �������ּ���." << endl << endl;
		}
	}

	void Ordinary_Account_Open() {
		int accID;
		int balance;
		int Resident_registration_number;
		char cusnName[MAX_LEN];

		if (Member_Number == MAX_MEMBER) {
			cout << "���� �ο��� �ʰ��Ǿ����ϴ�.\n" << endl;
			return;
		}

		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> accID;

		cout << "��  ��: ";
		cin >> cusnName;

		cout << "�ֹε�Ϲ�ȣ: ";
		cin >> Resident_registration_number;

		cout << "�Աݾ�: ";
		cin >> balance;
		if (balance < 10) {
			cout << "���°��� �ÿ��� 10���̻��� �Աݾ��� �־�� �մϴ�.\n" << endl << endl;
			return;
		}


		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_SSN(Resident_registration_number)) {
				cout << "�̹� ���� �Ǿ����ϴ�." << endl << endl;
				return;
			}
			if (Acc_Member[i]->Check_AccID(accID)) {
				cout << "�̹� �ִ� ����ID �Դϴ�." << endl << endl;
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

		cout << "���� ������ ���¹�ȣ�� �Է��� �ּ���." << endl;
		cout << "���� ���� ID : ";
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
			cout << "���� ���� ���� �� ���� ���¸� ������ �� �ֽ��ϴ�." << endl;
			cout << "���� ���¸� ���� ����� �õ��Ͽ� �ֽʽÿ�." << endl << endl;
			return;
		}

		cout << "���� ���¿��� ����� ���¹�ȣ�� �Է��� �ּ���." << endl;
		cout << "���� ���� ID : ";
		cin >> deposit_accID;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(deposit_accID)) {
				cout << "�̹� �ִ� ����ID �Դϴ�." << endl << endl;
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

		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> Check_AccID;
		cout << "�Աݾ�: ";
		cin >> Deposit_Amount;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(Check_AccID)) {
				cout << "a" << endl;
				Acc_Member[i]->Deposit(Deposit_Amount);
				return;
			}
		}

		cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
	
		cout << endl;
	}

	void Withdraw() {
		int Withdrawal_Amount;
		int Check_AccID;

		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> Check_AccID;
		cout << "��ݾ�: ";
		cin >> Withdrawal_Amount;

		for (int i = 0; i < Member_Number; i++) {
			if (Acc_Member[i]->Check_AccID(Check_AccID)) {
				if (!Acc_Member[i]->Withdraw(Withdrawal_Amount)) {
					cout << "��� �ݾ��� ���� �ܾ׺��� �����ϴ�." << endl << endl;
				}
				return;
			}
		}

		cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
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
		cout << "-----Menu------\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü ���\n5. ���α׷� ����" << endl;
		cout << "����: ";
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

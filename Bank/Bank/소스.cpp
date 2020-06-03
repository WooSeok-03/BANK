#include<iostream>
#define MAX_LEN 20


using namespace std;

class Account {
private:
	int accID;
	int balance;
	int Resident_registration_number;
	char* cusName;
public:
	Account(int accID, int balance, int Resident_registration_number, char* cusName)
	{
		this->accID = accID;
		this->balance = balance;
		this->Resident_registration_number = Resident_registration_number;
		this->cusName = new char[MAX_LEN];
		strcpy_s(this->cusName, MAX_LEN, cusName);
	}

	~Account()
	{
		delete[] cusName;
	}

	void Deposit(int balance) {
		this->balance += balance;
	}

	bool Check_AccID(int accID) {
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
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << endl;
	}

	bool Check_SSN(int Resident_registration_number) {
		return this->Resident_registration_number == Resident_registration_number;
	}
};

Account* Acc_Member[100];
int Member_Number = 0;

void Account_Open() {
	int accID;
	int balance;
	int Resident_registration_number;
	char cusnName[MAX_LEN];

	if (Member_Number == 100) {
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
		cout << "���°��� �ÿ��� 10���̻��� �Աݾ��� �־�� �մϴ�.\n" << endl;
		return;
	}


	for (int i = 0; i < Member_Number; i++) {
		if (Acc_Member[i]->Check_SSN(Resident_registration_number)) {
			cout << "�̹� ���� �Ǿ����ϴ�." << endl;
			return;
		}
		if (Acc_Member[i]->Check_AccID(accID)) {
			cout << "�̹� �ִ� ����ID �Դϴ�." << endl;
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

	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> Check_AccID;
	cout << "�Աݾ�: ";
	cin >> Deposit_Amount;

	for (int i = 0; i < Member_Number; i++) {
		if (Acc_Member[i]->Check_AccID(Check_AccID)) {
			Acc_Member[i]->Deposit(Deposit_Amount);
		}
		else {
			cout << "��ȿ���� ���� ID �Դϴ�." << endl;
		}
	}
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
				cout << "��� �ݾ��� ���� �ܾ׺��� �����ϴ�." << endl;
			}
			return;
		}
	}

	cout << "��ȿ���� ���� ID �Դϴ�." << endl;
	cout << endl;
}

void Print_Account_Information() {

	for (int i = 0; i < Member_Number; i++) {
		Acc_Member[i]->Print_Account_Information();
	}
}

int main(void) {
	int choice;

	while (1) {
		cout << "-----Menu------\n1. ���°���\n2. ��    ��\n3. ��    ��\n4. �������� ��ü ���\n5. ���α׷� ����" << endl;
		cout << "����: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			Account_Open();
			break;
		case 2:
			Deposit();
			break;
		case 3:
			Withdraw();
			break;
		case 4:
			Print_Account_Information();
			break;
		case 5:
			for (int i = 0; i < Member_Number; i++) delete Acc_Member[i];
			return 0;
		default:
			break;
		}
	}
}
#include<iostream>
#include<fstream>
using namespace std;
class account
{
	int acno;
	char name[50];
	int amt;
public:
	void create_account();
	void disp_account();
	void dep(int);
	void wdraw(int);
	void report();
	int retacno();
	int retamt();
		};
        
int account::retamt() 
{
	return amt;
}

void account::create_account()
{
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acno;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>amt;
	cout<<"\n\n\t\t\tAccount Created..";
}

void account::disp_account()
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tBalance amount : "<<amt;
}


void account::dep(int x)
{
	amt+=x;
}

void account::wdraw(int x)
{
			
	amt-=x;
   }

void account::report()
{
	cout<<acno<<"\t"<<name<<"\t"<<amt<<endl;
}
int account::retacno() 
{
	return acno;
}


void write_account();
void display_acd(int);
void display_all();
void deposit(int);
void withdraw(int);

int main()
{
	char ch;
	int num;
	do
	{
	
	cout<<"\n\n\t\t\t\t======================\n";
	cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t======================\n";

		cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-6): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\t\t\tEnter The account No. : "; 
			cin>>num;
			deposit(num);
			break;
		case '3':
			cout<<"\n\n\t\t\tEnter The account No. : "; 
            cin>>num;
			withdraw(num);
			break;
		case '4':
			
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_acd(num);
			break;
		case '5':
			display_all();
			break;
		
		 
		 case '6':
		 	system("CLS");
			break;
		 
		}
		cin.ignore();
	    }while(ch!='6');
	return 0;
}

void write_account()
{
	account ac;
	ofstream of;
	of.open("account.txt",ios::binary|ios::app);
	ac.create_account();
	of.write((char *)&ac, sizeof(account));
	of.close();
}

void display_acd(int n)
{
	account ac;
	bool flag=false;
	ifstream inf;
	inf.open("account.txt",ios::binary);
	if(!inf)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inf.read((char *)&ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.disp_account();
			flag=true;
		}
	}
    inf.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}


void display_all()
{
	
	account ac;
	ifstream inf;
	inf.open("account.txt",ios::binary);
	if(!inf)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=======================================\n";
	cout<<"A/c no.\t NAME \t Balance\n";
	cout<<"=======================================\n";
	while(inf.read((char *)&ac, sizeof(account)))
	{
		ac.report();
	}
	inf.close();
}


void deposit(int n)
{
	int amt;
	bool found=false;
	account ac;
	fstream f;
    f.open("account.txt", ios::binary|ios::in|ios::out);
	if(!f)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!f.eof() && found==false)
	{
		f.read((char *)&ac, sizeof(account));
		if(ac.retacno()==n)
		{
			ac.disp_account();
			
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    
			int pos=(-1)*int(sizeof(ac));
			f.seekp(pos,ios::cur);
			f.write((char *)&ac, sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         f.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}
         
void withdraw(int n)
{
	int amt;
	bool found=false;
	account ac;
	fstream f;
    f.open("account.txt", ios::binary|ios::in|ios::out);
	if(!f)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!f.eof() && found==false)
	{
		f.read((char *)&ac, sizeof(account));
		if(ac.retacno()==n)
		{
			ac.disp_account();
			
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retamt()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.wdraw(amt);
		      }
			int pos=(-1)*int(sizeof(ac));
			f.seekp(pos,ios::cur);
			f.write((char *)&ac, sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
             f.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}



#include <stdio.h>
#include<iostream>
#include<string>
#include <systemc>

using namespace std;
using namespace sc_core;
struct yx
{
	int y;
	int x;

	yx(int y,int x)
	{
		this->y = y;
		this->x = x;
	}
};

yx ES(-1,-1);

void displayParkingLayout(string *value,int n)
{

	printf("\n\n");

	printf("|");	for(int i = 0 ;i<n-1;i++) printf("-----+"); 	printf("-----|\n");

	for(int i = 0 ; i < n;i++)
	{
		cout<<"| ";	for(int j = 0; j<n ;j++) cout<<*((value + i*n) + j)<<"  | ";

		printf("\n|");	for(int i = 0 ;i<n-1;i++)	printf("-----+");	printf("-----|\n");
	}


	printf("\n");
}

/*struct yx findNextAvilSlot(string *slot,int n,int data)
{
	for(int i = 0; i<n;i++)
		for(int j = 0;j<n;j++)
			if(!((slot+i*n +j)->compare("--"))) {

				yx obj(i,j);
				return obj;
			}


	yx obj(-1,-1);
	return obj;
}*/

bool isSlotSafe(string *slot,int n, yx obj)
{
	int Y1 = obj.y;

	int K = 0;
	for(int j = 0;j<n-1;j++)
	{
		if(!(slot + Y1*n + j)->compare("  "))
		{
			K++;
		}

	}

	if(K < 2)
	{
		return false;
	}

	return true;

}

yx findCar(string *slot,int n,string data)
{
	for(int i = 0; i<n;i++)
		for(int j = 0;j<n;j++)
			if(!((slot+i*n +j)->compare(data))) {

				yx obj(i,j);
				return obj;
			}


	yx obj(-1,-1);
	return obj;
}

yx findEmptyinRow(string *slot,int n, int rowNo,int startCol)
{
	for(int j = startCol ;j<n;j++)
	{
		if(!((slot+rowNo*n +j)->compare("  "))) {

			yx obj(rowNo,j);
			return obj;
		}

	}

	yx obj(-1,-1);
	return obj;
}
yx findEmptyinCol(string *slot,int n, int colNo,int startRow)
{
	for(int j = startRow ;j<n-1;j++)
	{
		if(!((slot+j*n + colNo)->compare("  "))) {

			yx obj(j,colNo);
			return obj;
		}

	}

	yx obj(-1,-1);
	return obj;
}

void performLEFT(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.x = es.x - 1;
	if(!((slot + es.y*n + es.x)->compare("  "))) {
		return;
	}
	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

	ES = es;

	cout<<" LEFT ";

	displayParkingLayout(slot,n);
}
void performUP(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.y = es.y - 1;
	if(!((slot + es.y*n + es.x)->compare("  "))) {

		return;
	}
	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

	ES = es;

	cout<<" UP ";

	displayParkingLayout(slot,n);

}

void performRIGHT(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.x = es.x + 1;
	if(!((slot + es.y*n + es.x)->compare("  "))) {
		return;
	}
	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

	ES = es;

	cout<<" RIGHT ";

	displayParkingLayout(slot,n);
}

void performDOWN(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.y = es.y + 1;
	ES = es;
	if(!((slot + es.y*n + es.x)->compare("  "))) // No swap will happen
	{
		return;
	}

	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

	ES = es;
	cout<<" DOWN ";

	displayParkingLayout(slot,n);
	return ;
}

void Retrive(string *slot,int n,string data)
{
	struct yx obj = findCar(slot,n,data);

	int X = obj.x;
	int Y = obj.y;

	if(X == -1 && Y == -1){
		cout<<" No such Car Parked, Contact Parking Manager "<<endl;
		return;
	}

	//cout<<" Car found at row = "<<Y<<" col = "<<X<<endl;
	for(int i = Y+1 ; i<n-1;i++)
	{
		yx tm = findEmptyinRow(slot,n,i,X);
		if(tm.x != -1)
		{
			for(int j = tm.x ; j>X;j--)
			{
				yx es(i,j);
				performLEFT(slot,n,es);

			}
		}
		else
		{

			yx tm = findEmptyinRow(slot,n,i,0);

			if(tm.x != -1)
			{
				for(int j = tm.x ; j<X;j++)
				{
					yx es(i,j);
					performRIGHT(slot,n,es);

				}
			}
			else
			{
				cout<<" No blank spaces in this row "<<endl;
			}
		}


		yx es(i,X);
		performUP(slot,n,es);
	}

	// Now it can swap from bay


	yx es(n-1,X);
	performUP(slot,n,es);


	displayParkingLayout((string *)slot,n);

	*(slot + es.y*n + es.x) = "  ";

}

bool getMeSafeSlot(string *slot,int n, yx *obj, int colNo)
{


	for(int row = 1 ;row <n-1 ; row++)
	{
		int K = 0;
		for(int j = 0;j<n-1;j++)
		{
			if(!(slot + row*n + j)->compare("  "))
			{
				K++;
			}

		}

		if(K < 2)
		{
			// continue for next
		}
		else
		{

			obj->y = row;
			obj->x = colNo;

			if(!(slot + (obj->y)*n + obj->x)->compare("  ")){

				//cout<<" SAFE SLOT is "<<obj->y<<" "<<obj->x<<endl;

				return true;
			}
			else continue;
		}

	}

	return false; // No safe Slot

}

bool isThisCarParked(string *slot,int n,string data)
{
	for(int i = 0; i<n;i++)
		for(int j = 0;j<n;j++)
			if(!((slot+i*n +j)->compare(data))) {

				cout<<"\n Car No."<<data<<" is already Parked.Wrong Data. Contact Parking Manager!\n"<<endl;
				return false;
			}


	return true;

}
bool isAnyCarParked(string *slot,int n)
{
	int K = 0;
	for(int row = 0 ;row <n-1 ; row++)
	{
		for(int j = 0;j<n-1;j++)
		{
			if(!(slot + row*n + j)->compare("  "))
			{
				K++;
			}

		}
	}

	if(K == (n-1)*(n-1))
	{
		cout<<" NO CAR HAS PARKED "<<endl;
		return false;
	}
	else
		return true;

}
bool getMeFreeBay(string *slot,int n)
{
	bool flag = false;
	for(int row = 0 ;row <n-1 ; row++)
	{
		int K = 0;
		int B = -1;
		bool flag_bay = false;
		for(int j = 0;j<n;j++)
		{
			if(!(slot + row*n + j)->compare("  "))
			{
				K++;
				if(!flag_bay)
				{
					B = j;
					flag_bay = true;
				}
			}

		}

		if(K < 2)
		{
			// continue for next
		}
		else
		{
			flag = true;

			cout<<" BAY "<<(B+1);
		}

	}
	if(flag)
		cout<<" HAS FREE SPACES "<<endl;
	else
		cout<<"\n NO PARKING SPACES AVAILABLE \n"<<endl;

	return flag;

}

void park(string *slot,int n,string data,int BayNo)
{

	yx obj = findEmptyinCol(slot,n,BayNo,0);

	int X = obj.x;
	int Y = obj.y;

	if(X == -1 && Y == -1){
		cout<<" Bay is full, Contact Parking Manager "<<endl;
		return;
	}

	//cout<<" Empty in Column is at row no : "<<Y<<endl;

	for(int i = Y ; i<n-1;i++)
	{
		yx es(i,BayNo);
		performDOWN(slot,n,es);

	}

	yx obj1 = findEmptyinCol(slot,n,BayNo,0);

	//cout<<" Current Empty Space is at row = "<<obj1.y<<" col = "<<obj1.x<<endl;
	if(ES.y == -1 && ES.x == -1)
	{
		ES.y = 0;
	}

	if(!(obj1.y == 0))
	{
		yx safeSlot(-1,-1);
		if(getMeSafeSlot(slot,n,&safeSlot,BayNo))
		{
			for(int i = n-1 ; i>safeSlot.y;i--)
			{
				cout<<" PF UP ";

				if((slot+ i*n+BayNo)->compare("  "))
					cout<<" ! ALARM WRONG IMPLEMENTATION 1"<<endl;
				else
				{
					*(slot+ i*n+BayNo) =  data;


					displayParkingLayout(slot,n);

					*(slot+ i*n+BayNo) =  "  ";
				}
			}

			*(slot+ safeSlot.y*n+BayNo) =  data;
			return;
		}

	}
	else
	{
		for(int i = obj1.y;i<n-1;i++)
		{
			cout<<" PF UP ";

			if((slot+(n-1 - i)*n+BayNo)->compare("  "))
				cout<<" ! ALARM WRONG IMPLEMENTATION 2"<<endl;
			else
			{
				*(slot+(n-1 - i)*n+BayNo) =  data;


				displayParkingLayout(slot,n);

				*(slot+(n-1 - i)*n+BayNo) =  "  ";
			}
		}

		*(slot+(obj1.y)*n+BayNo) =  data;

	}

}

#define MAX 20
SC_MODULE(Process_ParkingMgmt){

	int n;
	string puzz[MAX][MAX];

public :


	void StartOp()
	{
		cout<<"Enter size of Parking"<<endl;
		cin>>n;

		for(int i = 0 ; i<MAX;i++)
			for(int j = 0;j<MAX;j++)
				puzz[i][j] = "  ";


		//	myScenario((string *)puzz);

		displayParkingLayout((string *)puzz,n);
		char ch = 'y';
		while(ch == 'y' || ch == 'Y')
		{

			cout<<" Press P for Parking R for Retrieval E for Exit "<<endl;
			char option;
			cin>>option;


			string carNo;


			if(option == 'E')
			{
				exit(0);
			}
			if(option == 'P')
			{
				if(!getMeFreeBay((string *)puzz,n)) continue;

				int BayNo; // 1-n-1
				cout<<" Enter Bay No. from 1 to "<<n-1<<endl;
				cin>>BayNo;

				if(BayNo<1 || BayNo >n-1)
				{
					cout<<"BayNo is not correct "<<endl;
					continue;
				}

				cout<<" Enter Car no "<<endl;
				cin>>carNo;

				if(isThisCarParked((string *)puzz,n,carNo))
					park((string *)puzz,n,carNo,BayNo-1);

			}
			if(option == 'R')
			{
				if(isAnyCarParked((string *)puzz,n))
				{
					cout<<" Enter Car no "<<endl;
					cin>>carNo;

					Retrive((string *)puzz,n,carNo);
				}

			}


			displayParkingLayout((string *)puzz,n);

		}


		return;
	}

	void myScenario(string *slot)
	{
		string puzzle[4][4] = {
				{"01","04","07","  "},
				{"02","05","  ","08"},
				{"03","06","  ","09"},
				{"  ","  ","  ","  "}};

		for(int i = 0; i<4;i++)
			for(int j = 0;j<4;j++)
				*(slot+i*4 +j) = puzzle[i][j];

	}

	Process_ParkingMgmt(sc_module_name name, int layoutSize ) :sc_module(name)
	{

		n = layoutSize;
		SC_THREAD(StartOp);
	}
	SC_HAS_PROCESS(Process_ParkingMgmt);
};

int sc_main(int argc, char* argv[])
{


	srand(time(NULL));
	sc_set_time_resolution(1, SC_SEC);

	Process_ParkingMgmt oMainProcess((char *)"PUZZ",15);

	sc_start ();

	return 0;


}


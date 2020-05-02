
#include <stdio.h>
#include<iostream>
#include<string>

using namespace std;

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

yx ES;

void displayParkingLayout(string *value,int n)
{

	printf("\n\n");

	printf("|");
	for(int i = 0 ;i<n-1;i++)
		printf("-----+");
	printf("-----|\n");

	for(int i = 0 ; i < n;i++)
	{
		cout<<"| ";
		for(int j = 0; j<n ;j++)
		{
			cout<<*((value + i*n) + j)<<"  | ";
		}
		printf("\n|");
		for(int i = 0 ;i<n-1;i++)
			printf("-----+");
		printf("-----|\n");
	}
	printf("\n");
	/*
	printf("|");
	for(int i = 0 ;i<n-1;i++)
		printf("-----+");
	printf("-----|\n");
	 */}

struct yx findNextAvilSlot(string *slot,int n,int data)
{
	for(int i = 0; i<n;i++)
		for(int j = 0;j<n;j++)
			if(!((slot+i*n +j)->compare("--"))) {

				yx obj(i,j);
				return obj;
			}
}

yx findCar(string *slot,int n,string data)
{
	for(int i = 0; i<n;i++)
		for(int j = 0;j<n;j++)
			if(!((slot+i*n +j)->compare("data"))) {

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
	for(int j = startRow ;j<n;j++)
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
}

void performDOWN(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.y = es.y + 1;
	if(!((slot + es.y*n + es.x)->compare("  "))) {
		return;
	}
	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

	ES = es;
	cout<<" DOWN ";
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

	for(int i = Y ; i<n-1;i++)
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

	for(int i = obj.x ; i<n-1;i++)
	{
		yx es(BayNo,i);
		performDOWN(slot,n,es);

	}

	yx obj1 = findEmptyinCol(slot,n,BayNo,0);

	int X1 = obj1.x;
	int Y1 = obj1.y;

	for(int j = Y1;j<n-1;j++)
	{
		yx es(BayNo,j);
		performDOWN(slot,n,es);
	}

}

int main()
{
	int n = 4;
	string puzz[n][n];

	scanf("%d",&n);

	for(int i = 0 ; i<n;i++)
		for(int j = 0;j<n;j++)
			puzz[i][j] = "  ";


	char ch = 'y';
	while(ch == 'y' || ch == 'Y')
	{
		cout<<" Press P for Parking R for Retrivel  "<<endl;
		char option;
		cin>>option;

		string carNo;
		int BayNo; // 1-n-1
		cout<<" Enter Car no "<<endl;
		cin>>carNo;

		if(option == 'P')
		{
			cout<<" Enter Bay No. "<<endl;
			cin>>BayNo;


			park((string *)puzz,n,carNo,BayNo);

		}
		if(option == 'R')
		{

			Retrive((string *)puzz,n,carNo);

		}

		cout<<"Do you want to continue? Y or N"<<endl;
		cin>>ch;


	}


	displayParkingLayout((string *)puzz,n);
}


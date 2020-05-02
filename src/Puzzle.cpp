
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

void performLEFT(string *slot,int n,yx es)
{
	yx ptemp = es;
	es.x = es.x - 1;
	if(!((slot + es.y*n + es.x)->compare("  "))) {
			return;
		}
	*(slot + ptemp.y*n + ptemp.x) = *(slot + es.y*n + es.x);
	*(slot + es.y*n + es.x) = "  ";

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

	cout<<" UP ";
}

void Retrive(string *slot,int n,string data)
{
	struct yx obj = findCar(slot,n,data);

	int X = obj.x;
	int Y = obj.y;

	for(int i = Y ; i<n-1;i++)
	{
		yx tm = findEmptyinRow(slot,n,i,X);
		if(yx.x != -1)
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
		}


		yx es(i,X);
		performUP(slot,n,es);


	}

}


int main()
{
	int n = 4;
	string puzz[n][n];

	scanf("%d",&n);

	for(int i = 0 ; i<n;i++)
		for(int j = 0;j<n;j++)
			puzz[i][j] = "--";

	puzz[n-1][0] = "  ";

	displayParkingLayout((string *)puzz,n);
}


#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include "Sudoku.h"

using namespace std;

Sudoku::Sudoku(){ }

void Sudoku::giveQuestion(){
					   
	int ans1[sudokuSize] = {9,6,2,7,4,5,8,3,1,5,7,1,9,3,8,6,2,4,4,8,3,6,2,1,9,5,7,2,3,6,1,5,9,7,4,8,7,1,9,2,8,4,3,6,5,8,4,5,3,7,6,2,1,9,3,5,4,8,9,2,1,7,6,6,2,8,4,1,7,5,9,3,1,9,7,5,6,3,4,8,2};
	int ans2[sudokuSize] = {6,9,8,5,3,4,2,1,7,3,4,7,2,8,1,5,6,9,1,2,5,7,6,9,4,3,8,7,3,9,4,2,6,1,8,5,8,6,2,3,1,5,7,9,4,4,5,1,9,7,8,6,2,3,2,1,3,8,5,7,9,4,6,5,8,4,6,9,2,3,7,1,9,7,6,1,4,3,8,5,2};

	srand(time(NULL));

	switch(rand()%2){
		case 0 :

			for(int i=0;i<4;i++){
				ans1[rand()%81]=0;
			}
			for(int i=0;i<81;i++){
				su[i]=ans1[i];
			}
			
			changeRow(rand()%3,rand()%3);
			changeCol(rand()%3,rand()%3);
			changeNum(rand()%10,rand()%10);
			rotate(rand()%101);
			flip(rand()%2);

			for(int i=0;i<81;i++){
				ans1[i]=su[i];
				su2[i]=su[i];
			}
			
			while(1){
				int j=rand()%81;
				su[j]=0;
				su2[j]=0;
				if(checkQues()){
					ans1[j]=0;
					for(int i=0;i<81;i++){
						su[i]=ans1[i];
						su2[i]=ans1[i];
					}
				}
				else{
					break;
				}
			}
			print(ans1);
			break;
		
		case 1 :
			for(int i=0;i<4;i++){
				ans2[rand()%81]=0;
			} 
			for(int i=0;i<81;i++){
				su[i]=ans2[i];
			}

			changeRow(rand()%3,rand()%3);
			changeCol(rand()%3,rand()%3);
			changeNum(rand()%10,rand()%10);
			rotate(rand()%101);
			flip(rand()%2);

			for(int i=0;i<81;i++){
				ans2[i]=su[i];
				su2[i]=su[i];
			}

			while(1){
				int j=rand()%81;
				su[j]=0;
				su2[j]=0;
				if(checkQues()){
					ans2[j]=0;
					for(int i=0;i<81;i++){
						su[i]=ans2[i];
						su2[i]=ans2[i];
					}
				}
				else
					break;
			}
			print(ans2);
			break;	
	}
}
	
bool Sudoku::checkQues(){

	if(!backtracking()){
		return false;
	}

	secondBacktrack();

	if(ifSameSu()){	
		return true;
	}else{
		return false;
		}
}


void Sudoku::print(int arr[]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout << arr[i*9+j] << " " ;
		}
		cout << endl;
	}
}

void Sudoku::readIn(){
	for(int i=0;i<81;i++){
		cin >> su[i] ;
		su2[i]=su[i];
	}
}

int Sudoku::getFirstZeroIndex(int arr[]){
	for(int i=0;i<sudokuSize;i++){
		if(arr[i]==0)
			return i;
	}	
	return -1;
}

bool Sudoku::backtracking(){

	int firstZero;

	firstZero=getFirstZeroIndex(su);
	if(firstZero==-1){
		return true;
	}

	for(int num=1;num<10;num++){
		if(assignable(num,firstZero,su)){
			su[firstZero]=num;

			if(backtracking())
				return true;

			su[firstZero]=0;
		}
	}
	return false;
}

bool Sudoku::secondBacktrack(){

	int firstZero2;

	firstZero2=getFirstZeroIndex(su2);
	if(firstZero2==-1){
		return true;
	}

	for(int num2=9;num2>0;num2--){
		if(assignable(num2,firstZero2,su2)){
			su2[firstZero2]=num2;

			if(secondBacktrack())
				return true;

			su2[firstZero2]=0;
		}
	}
	return false;
}

bool Sudoku::ifSameSu(){
	for(int i=0;i<81;i++){
		if(su[i]!=su2[i])
			return false;
	}
	return true;
}

void Sudoku::solve(){

	if(!solvable()){
		cout << 0 << endl;
		exit(1);
	}

	if(!backtracking()){
		cout << 0 << endl ;
		exit(3);
	}

	secondBacktrack();

	if(ifSameSu()){
		cout << 1 <<endl;	
		print(su);
		exit(4);
	}else{
		cout << 2 <<endl;
		exit(5);
		}
	
}

bool Sudoku::assignable(int num,int firstZero,int arr[]){
	int row;
	int col;
	
	row=firstZero/9;
	col=firstZero%9;
	for(int i=row*9;i<row*9+9;i++){
		if(arr[i]==num){
			return false;}
	}
	for(int i=col;i<col+81;i=i+9){
		if(arr[i]==num){
			return false;
		}
	}
	for(int j=row-row%3;j<row-row%3+3;j=j+1){	
		for(int i=col-col%3;i<col-col%3+3;i++){
			if(arr[j*9+i]==num){
				return false;
			}
		}
	}
	return true;
}


bool Sudoku::solvable(){
	int tmp[9];
	int tmp1[9];
	int tmp2[9];

	for(int i=0;i<81;i=i+9){
		for(int l=0;l<9;l++)
			tmp[l]=0;
		for(int j=i;j<i+9;j++){
			if(su[j]!=0)
				tmp[su[j]-1]++;
		}
		for(int k=0;k<9;k++){
			if(tmp[k]>1)
				return false;
		}
	}

	for(int i=0;i<9;i++){
		for(int l=0;l<9;l++)
			tmp1[l]=0;
		for(int j=i;j<i+81;j=j+9){
			if(su[j]!=0)
				tmp1[su[j]-1]++;
		}
		for(int k=0;k<9;k++){
			if(tmp1[k]>1)
				return false;
		}
	}

	for(int i=0;i<9;i++){
		for(int l=0;l<9;l++)
			tmp2[l]=0;
		for(int j=0;j<9;j++){
			if(su[27*(i/3)+3*(i%3)+9*(j/3)+(j%3)]!=0)
				tmp2[su[27*(i/3)+3*(i%3)+9*(j/3)+(j%3)]-1]++;
		}
		for(int k=0;k<9;k++){
			if(tmp2[k]>1)
				return false;
		}
	}
	return true;
}

bool Sudoku::multiAns1(){
	int ctr=0;
	int ctr1=0;

	for(int j=0;j<7;j=j+3){
		for(int i=j*9;i<j*9+9;i++){
			if(su[i]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		ctr=0;
		for(int i=j*9+9;i<j*9+18;i++){
			if(su[i]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		ctr=0;
		for(int i=j*9+18;i<j*9+27;i++){
			if(su[i]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		if(ctr1>1)
			return true;
	}
	ctr=0;
	ctr1=0;
	
	for(int i=0;i<3;i++){
		for(int j=i*3;j<i*3+73;j=j+9){
			if(su[j]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		ctr=0;
		for(int j=i*3+1;j<i*3+74;j=j+9){
			if(su[j]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		ctr=0;
		for(int j=i*3+2;j<i*3+75;j=j+9){
			if(su[j]==0)
				ctr++;
		}
		if(ctr==9)
			ctr1++;
		if(ctr1>1)
			return true;
	}
}

bool Sudoku::multiAns34(){
	
	int check[9];
	int ctr1=0;
	int ctr2=0;

	for(int i=0;i<81;i++){
		if(su[i]!=0)
			check[su[i]-1]++;
		else
			ctr2++;
	}
	for(int i=0;i<9;i++){
		if(check[i]==0)
			ctr1++;
	}

	if(ctr1>1 || ctr2>64)
		return true;
	else
		return false;
}


void Sudoku::changeNum(int a,int b){
	
	vector<int> tmp1;
	vector<int> tmp2;
	
	for(int i=0;i<81;i++){
		if(su[i]==a)
			tmp1.push_back(i);
	}
	
	for(int i=0;i<81;i++){
		if(su[i]==b)
			tmp2.push_back(i);
	}

	for(int i=0;i<tmp1.size();i++){
		su[tmp1[i]]=b;
	}
	for(int i=0;i<tmp2.size();i++){
		su[tmp2[i]]=a;
	}
	for(int i=0;i<81;i++){
		su2[i]=su[i];
	}

}

void Sudoku::changeRow(int a,int b){

	int tmp[27];

	for(int i=a*27,j=0 ; i<a*27+27 && j<27 ; i++,j++){
		tmp[j]=su[i];
	}
	for(int i=b*27,j=a*27 ; i<b*27+27 && j<a*27+27 ; i++,j++){
		su[j]=su[i];
	}
	for(int i=0,j=b*27 ; i<27 && j<b*27+27 ; i++,j++){
		su[j]=tmp[i];
	}
	for(int i=0;i<81;i++){
		su2[i]=su[i];
	}
}

void Sudoku::changeCol(int a,int b){
	
	int tmp[27];

	for(int i=0,j=3*a ; i<9 ; i++,j=j+9){
		tmp[i]=su[j];
	}
	for(int i=9,j=3*a+1 ; i<18 ; i++,j=j+9){
		tmp[i]=su[j];
	}
	for(int i=18,j=3*a+2 ; i<27 ; i++,j=j+9){
		tmp[i]=su[j];	
	}

	for(int i=3*a,j=3*b ; i<3*a+73 ; i=i+9,j=j+9){
		su[i]=su[j];
	}
	for(int i=3*a+1,j=3*b+1 ; i<3*a+74 ; i=i+9,j=j+9){
		su[i]=su[j];
	}
	for(int i=3*a+2,j=3*b+2 ; i<3*a+75 ; i=i+9,j=j+9){
		su[i]=su[j];
	}

	for(int i=3*b,j=0 ; j<9 ; i=i+9,j++){
		su[i]=tmp[j];
	}
	for(int i=3*b+1,j=9 ; j<18 ; i=i+9,j++){
		su[i]=tmp[j];
	}
	for(int i=3*b+2,j=18 ; j<27 ; i=i+9,j++){
		su[i]=tmp[j];
	}
	for(int i=0;i<81;i++){
		su2[i]=su[i];
	}
}
void Sudoku::flip(int n){

		int tmp[36];
	
	switch (n){
		case 0 :
			for(int i=0;i<36;i++){
				tmp[i]=su[i];
			}
			for(int i=0,j=72;i<9;i++,j++){
				su[i]=su[j];
			}
			for(int i=9,j=63;i<18;i++,j++){
				su[i]=su[j];
			}
			for(int i=18,j=54;i<27;i++,j++){
				su[i]=su[j];
			}
			for(int i=27,j=45;i<36;i++,j++){
				su[i]=su[j];
			}
			for(int i=72,j=0;i<81;i++,j++){
				su[i]=tmp[j];
			}
			for(int i=63,j=9;i<72;i++,j++){
				su[i]=tmp[j];
			}
			for(int i=54,j=18;i<63;i++,j++){
				su[i]=tmp[j];
			}
			for(int i=45,j=27;i<54;i++,j++){
				su[i]=tmp[j];
			}
			for(int i=0;i<81;i++){
				su2[i]=su[i];
			}
			break;

		case 1 :
			for(int i=0,j=0;i<9;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=9,j=1;i<18;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=18,j=2;i<27;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=27,j=3;i<36;i++,j=j+9){
				tmp[i]=su[j];
			}

			for(int i=0,j=8;i<73;i=i+9,j=j+9){
				su[i]=su[j];
			}
			for(int i=1,j=7;i<74;i=i+9,j=j+9){
				su[i]=su[j];
			}
			for(int i=2,j=6;i<75;i=i+9,j=j+9){
				su[i]=su[j];
			}
			for(int i=3,j=5;i<76;i=i+9,j=j+9){
				su[i]=su[j];
			}

			for(int i=8,j=0;j<9;i=i+9,j++){
				su[i]=tmp[j];
			}
			for(int i=7,j=9;j<18;i=i+9,j++){
				su[i]=tmp[j];
			}
			for(int i=6,j=18;j<27;i=i+9,j++){
				su[i]=tmp[j];
			}
			for(int i=5,j=27;j<36;i=i+9,j++){
				su[i]=tmp[j];
			}
			for(int i=0;i<81;i++){
				su2[i]=su[i];
			}
			break;
	}

}

void Sudoku::rotate(int n){
	int x=n%4;
	int tmp[81];

	switch(x){
		case 0 :
			break;
		case 1 :
			for(int i=0,j=72;i<9;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=9,j=73;i<18;i++,j=j-9){
				tmp[i]=su[j];	
			}
			for(int i=18,j=74;i<27;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=27,j=75;i<36;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=36,j=76;i<45;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=45,j=77;i<54;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=54,j=78;i<63;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=63,j=79;i<72;i++,j=j-9){
				tmp[i]=su[j];
			}
			for(int i=72,j=80;i<81;i++,j=j-9){
				tmp[i]=su[j];
			}

			for(int i=0;i<81;i++){
				su[i]=tmp[i];
				su2[i]=tmp[i];
			}
			break;
		case 2 :
			for(int i=0,j=80;i<81;i++,j--){
				tmp[i]=su[j];
			}
			for(int i=0;i<81;i++){
				su[i]=tmp[i];
				su2[i]=tmp[i];
			}
			break;
		case 3 :
			for(int i=0,j=8;i<9;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=9,j=7;i<18;i++,j=j+9){
				tmp[i]=su[j];			
			}
			for(int i=18,j=6;i<27;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=27,j=5;i<36;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=36,j=4;i<45;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=45,j=3;i<54;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=54,j=2;i<63;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=63,j=1;i<72;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=72,j=0;i<81;i++,j=j+9){
				tmp[i]=su[j];
			}
			for(int i=0;i<81;i++){
				su[i]=tmp[i];
				su2[i]=tmp[i];
			}
			break;
	}
}

void Sudoku::transform(){

	srand(time(NULL));
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	changeNum(rand()%10,rand()%10);
	rotate(rand()%101);
	flip(rand()%2);
	print(su);

}

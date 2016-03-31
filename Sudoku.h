#include <iostream>

class Sudoku{
	public:
		Sudoku();
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
	
	private:
		bool checkQues();	
		static const int sudokuSize=81;
		int su2[sudokuSize];
		int su[sudokuSize];	
		void print(int arr[]);
		bool multiAns1();
		bool multiAns34();
		bool solvable();
		int getFirstZeroIndex(int []);
		bool backtracking();
		bool secondBacktrack();
		bool ifSameSu();	
		bool assignable(int,int,int []);
};


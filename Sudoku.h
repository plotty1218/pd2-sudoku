#include <iostream>

class Sudoku{
	public:
		Sudoku();
		Sudoku(const int init_map[]);
		void setMap(const int set_map[]);
		bool isCorrect();
		void giveQuestion();
		void readIn();
		void solve();
		static const int sudokuSize=81;
		void print(int arr[]);
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		bool multiAns1();
		bool multiAns34();
		bool solvable();
		int getFirstZeroIndex();
		int getFirstZeroIndex2();
		bool backtracking();
		bool secondBacktrack();
		bool ifSameSu();	
		bool assignable(int,int);

	private:
		bool checkUnity(int arr[]);
		int map[sudokuSize];
		int su2[sudokuSize];
		int su[sudokuSize];
};


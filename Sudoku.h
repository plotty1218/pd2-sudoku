#include <iostream>

class Sudoku{
	public:
		Sudoku();
		Sudoku(const int init_map[]);
		void setMap(const int set_map[]);
		bool isCorrect();
		void giveQuestion();
		void readIn();
		int solve();
		static const int sudokuSize=81;
		void print(int arr[]);
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
	 	int su[sudokuSize];
		void transform();
		bool multiAns1(int su[]);
		bool multiAns34(int su[]);
		bool solvable(int su[]);
		int getFirstZeroIndex();
	private:
		bool checkUnity(int arr[]);
		int map[sudokuSize];
		
		
};


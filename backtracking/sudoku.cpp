#include<cstdlib>
#include<ctime>
#include<utility>
#include<iostream>

/*
What is Sudoku? In its most common form, it consists of a 9X9 grid filled with blanks and the digits 1 to 9. 
The puzzle is completed when every row, column, and sector (3X3 subproblems corresponding to the nine sectors 
of a tic-tac-toe puzzle) contain the digits 1 through 9 with no deletions or repetition.

The implementation here concentrates on the following two aspects:
1. Find the candidates for the current position using three arrays indicating which digits has been used by the corresponding index.
2. Find the most constrained position as the next move.
*/
static int solution_num = 0;

void print(int sudoku[9][9]) {
    std::cout<<"-------------------"<<std::endl;
    for(int i = 0; i < 9; ++i) {
        std::cout<<"|";
        for(int j = 0; j < 9; ++j)
            std::cout<<sudoku[i][j]<<" ";
        std::cout<<"|"<<std::endl;
    }
    std::cout<<"-------------------"<<std::endl;
}

int get_group(int x, int y) {
    int group_x = x / 3;
    int group_y = y / 3;

    return group_x * 3 + group_y;
}

void update_fill_arrays(bool is_row_filled[9][9],
	bool is_col_filled[9][9],
	bool is_group_filled[9][9],
	int i, int j, int val, bool flag) {

	if(val > 0) {
		is_row_filled[i][val-1] = flag;
        is_col_filled[j][val-1] = flag;
        int groupid = get_group(i, j);
        is_group_filled[groupid][val-1] = flag;
    }
}
void construct_sudoku(int sudoku[9][9], int& remaining_square_num) {
	sudoku[0][7] = 1;
    sudoku[0][8] = 2;
    sudoku[1][4] = 3;
    sudoku[1][5] = 5;
    sudoku[2][3] = 6;
    sudoku[2][7] = 7;
    //sudoku[3][0] = 7;
	sudoku[3][0] = 7;
    sudoku[3][6] = 3;
    sudoku[4][3] = 4;
    sudoku[4][6] = 8;
    sudoku[5][0] = 1;
    sudoku[6][3] = 1;
    sudoku[6][4] = 2;
    sudoku[7][1] = 8;
    sudoku[7][7] = 4;
    sudoku[8][1] = 5;
    sudoku[8][6] = 6;

	remaining_square_num -= 17;
}

void init(int sudoku[9][9], 
	bool is_row_filled[9][9],
	bool is_col_filled[9][9],
	bool is_group_filled[9][9], int& remaining_square_num) {

    // test
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            sudoku[i][j] = 0;
	construct_sudoku(sudoku, remaining_square_num);
    print(sudoku);

    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            is_row_filled[i][j] = false;
            is_col_filled[i][j] = false;
            is_group_filled[i][j] = false;
        }
    }
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            update_fill_arrays(is_row_filled, 
				is_col_filled,
				is_group_filled,
				i, j, sudoku[i][j], true);
        }
    }
    
	// check whether array "is_group_filled" is correctly initialized or not
	/*
    for(int i = 0; i < 9; ++i) {
      std::cout<<"group  "<<i<<": ";
      for(int j = 0; j < 9; ++j)
		std::cout<<is_group_filled[i][j]<<" ";
      std::cout<<std::endl;
    }
	*/
}

std::pair<int, int> next_square(int sudoku[9][9],
	bool is_row_filled[9][9],
	bool is_col_filled[9][9],
	bool is_group_filled[9][9]) {

	int candidate_num = 9;
	int x = -1, y = -1;
	for(int i = 0; i < 9; ++i) { 
		for(int j = 0; j < 9; ++j) {
			if(sudoku[i][j] == 0) {
				int cn = 9;
				for(int k = 0; k < 9; ++k)
					if(is_row_filled[i][k] || is_col_filled[j][k] || is_group_filled[get_group(i, j)][k])
						--cn;
				if(cn < candidate_num) {
					candidate_num = cn;
					x = i;
					y = j;
				}
			}
		}
	}
	//std::cout<<"x: "<<x<<", y: "<<y<<std::endl;

	return std:: make_pair(x, y);
}

void fill(int sudoku[9][9], 
	bool is_row_filled[9][9],
	bool is_col_filled[9][9],
	bool is_group_filled[9][9],
	int x, int y, int remaining_square_num) {

	if(remaining_square_num == 0) {
		++solution_num;
		print(sudoku);
		return;
	}

    bool is_candidate[9];
    for(int i = 0; i < 9; ++i) {
        bool is_valid = true;
        if(is_row_filled[x][i] || is_col_filled[y][i])
            is_valid = false;
        else {
            int groupid = get_group(x, y);
            if(is_group_filled[groupid][i])
                is_valid = false;
        }
        is_candidate[i] = is_valid;
    }

	bool has_candidate = false;
	for(int j = 0; j < 9; ++j) {
		if(is_candidate[j]) {
			has_candidate = true;
			break;
		}
	}
	if(!has_candidate)
		return;

    for(int k = 0; k < 9; ++k) {
        if(!is_candidate[k])
            continue;

		// do next move
        sudoku[x][y] = k+1;
		update_fill_arrays(
			is_row_filled,
			is_col_filled,
			is_group_filled,
			x, y, k+1, true);

		std::pair<int, int> square_coordinate = next_square(sudoku, is_row_filled, is_col_filled, is_group_filled);
		fill(sudoku, 
			is_row_filled,
			is_col_filled,
			is_group_filled,
			square_coordinate.first, square_coordinate.second, 
			remaining_square_num-1);

		// undo next move
		sudoku[x][y] = 0;
		update_fill_arrays(
			is_row_filled,
			is_col_filled,
			is_group_filled,
			x, y, k+1, false);
    }
}

void fill_all(int sudoku[9][9]) {
	bool is_row_filled[9][9];
	bool is_col_filled[9][9];
	bool is_group_filled[9][9];

	std::cout<<"sudoku:"<<std::endl;
	// initialize filled arrays
	int remaining_square_num = 81;
	init(sudoku, 
		is_row_filled,
		is_col_filled,
		is_group_filled, remaining_square_num);

	std::cout<<"solution: "<<std::endl;
	// solve sudoku
	std::pair<int, int> square_coordinate = next_square(sudoku, is_row_filled, is_col_filled, is_group_filled);
    fill(sudoku, 
		is_row_filled,
		is_col_filled,
		is_group_filled,
		square_coordinate.first, square_coordinate.second, remaining_square_num);

	std::cout<<"number of solutions: "<<solution_num<<std::endl;
}

int main(int argc, char** argv) {
    int sudoku[9][9];

	clock_t start;
	start = clock();
    fill_all(sudoku);
	std::cout<<"solve sudoku took "<<clock() - start<<" milliseconds."<<std::endl;

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

void ReadMatrix(float** M, float** N, int row, int column);
void WriteMatrix(float* M, int row, int column);

int main(int argc, char* argv[]){
	int tc, g, s, e, row, column, i, j, m1, m2, m3, dir_, index, aux, max_value, max_m, i_max, j_max, k;
	float* M;
	float* N;
	string s1, s2, s1_, s2_;
	vector <int> trace_back;

	cin >> tc;
	cin >> s >> g >> e;
	for (int count = 0; count < tc; count++) {
		cin >> s1;
		cin >> s2;
		row = s2.length() + 1;
	    column = s1.length() + 1;
	    max_value = 0;

	    cout << s1 << endl;
		cout << s2 << endl;
		/* Read matrix M y N */
		ReadMatrix(&M, &N, row, column);
		// WriteMatrix(M, row, column);
		// WriteMatrix(N, row, column);
		/* Algorithm Smith-Waterman  */
		// auto t1 = chrono::high_resolution_clock::now();
		for (int i = 1; i < row; i++){
			for (int j = 1; j < column; j++) {
				index = i * column + j;
				if(s1.at(j - 1) == s2.at(i - 1)){
					m1 = M[index - column - 1] + s;
				}else{
					m1 = M[index - column - 1] + e;
				}
				max_m = m1;
				dir_ = 1;
				m2 = M[index - column] + g;
				if(m2 > max_m){
					max_m = m2;
					dir_ = 2;
				}
				m3 = M[index - 1] + g;
				if(m3 > max_m){
					max_m = m3;
					dir_ = 3;
				}
				if(max_m < 0){
					max_m = 0;
				}
				M[index] = max_m;
				N[index] = dir_;
				if(M[index] >= max_value){
					max_value = M[index];
					i_max = i;
					j_max = j;
				}
			}
		}
	    // auto t2 = chrono::high_resolution_clock::now();
	    // cout << "Time (ms): " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
	    // WriteMatrix(M, row, column);
	    // WriteMatrix(N, row, column);
	    /* Get Trace Back */
	    /* 1: diagonal, 2: top, 3: left */
	    i = i_max;
		j = j_max;
		k = 0;
		trace_back.clear();
		while(1){
			max_value = -1;
			index = i * column + j;
			dir_ = N[index];
			trace_back.insert(trace_back.begin() + k, dir_);
			if (dir_ == 1){
				i -= 1;
				j -= 1;
			} else{
				if (dir_ == 2){
					i -= 1;
				} else{
					j -= 1;
				}
			}
			index = i * column + j;
			if(M[index] == 0){
				break;
			}
		}
		for (int i = 0; i < trace_back.size(); i++){
			if(trace_back.at(i) == 1){
				cout << "\\";
			}else{
				if(trace_back.at(i) == 2){
					cout << "|";
				}else{
					cout << "_";
				}
			}
		}
		cout << endl;
		/* generate new string */
		s1_ = "";
		s2_ = "";
		i = i_max - 1;
		j = j_max - 1;
		for (int k = trace_back.size() - 1; k >= 0; k--){
			if (trace_back.at(k) == 1){
				s1_ = s1.at(j) + s1_;
				s2_ = s2.at(i) + s2_;
				i -= 1;
				j -= 1;
			}else {
				if(trace_back.at(k) == 2){
					s1_ = "-" + s1_;
					s2_ = s2[i] + s2_;
					i -= 1;
				}else{
					s1_ = s1[j] + s1_;
					s2_ = "-" + s2_;
					j -= 1;
				}
			}			
		}
		/* print solution */
		cout << s1_ << endl;
		cout << s2_ << endl;
		cout << endl;
	}
    delete M, N;
	return 0;
}

void WriteMatrix(float* M, int row, int column){
	cout << "   ";
	for (int i = 0; i < column; i++){
		cout << i << ". ";
	}
	cout << endl;
	for (int i = 0; i < row; i++){
		cout << i << ". ";
		for (int j = i * column; j < i * column + column; j++){
			cout << M[j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void ReadMatrix(float** M, float** N, int row, int column){
	*M = new float[row * column];
	*N = new float[row * column];
	for (int i = 0; i < row * column; i++){
		(*M)[i] = 0;
		(*N)[i] = 0;
	}
}
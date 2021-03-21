#include <iostream>
#include <complex>

using namespace std;


int** matrix_create(unsigned int n){
// каждая матрица -- указатель на массив указателей,
// каждый указатель из массива указывает на столбец
	int** new_matrix = new int*[n];
	for(unsigned int i = 0; i < n; ++i){
		int* new_column = new int[n];
		new_matrix[i] = new_column;
	}
	
	return new_matrix;
}


void matrix_delete(int** some_matrix, unsigned int n){
	for(int i = 0; i < n; ++i)
		delete[] some_matrix[i];
	
	delete[] some_matrix;
}


int** matrix_sum(int** matrix_1, int** matrix_2, unsigned int n){
	int** new_matrix = matrix_create(n);
	
	for(unsigned int i = 0; i < n; ++i){
		for(unsigned int j = 0; j < n; ++j){
			new_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
		}
	}
	
	return new_matrix;
}


int** matrix_nummul(int** some_matrix, int number, unsigned int n){
	int** new_matrix = matrix_create(n);
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j)
			new_matrix[i][j] = some_matrix[i][j] * number;
	}
	
	return new_matrix;
}


int** matrix_naivemul(int** matrix_1, int** matrix_2, unsigned int n){
	int** new_matrix = matrix_create(n);
	
	for(int i = 0; i < n; ++i){
		for(unsigned int j = 0; j < n; ++j){
			int value_ij = 0;
			
			for(unsigned int ij = 0; ij < n; ++ij)
				value_ij += matrix_1[ij][i] * matrix_2[j][ij];
			
			new_matrix[i][j] = value_ij;
		}
	}
	
	return new_matrix;
}


int** matrix_shtrassen_mul(int** matrix_1, int** matrix_2, int p){	//p is a power of 2
	unsigned int n, new_n;
	n = 1 << p;
	
	int** new_matrix = matrix_create(n);
	
	if(p > 0){
		new_n = n >> 1;
		
		int** a00 = matrix_create(new_n);
		int** a01 = matrix_create(new_n);
		int** a10 = matrix_create(new_n);
		int** a11 = matrix_create(new_n);
		
		int** b00 = matrix_create(new_n);
		int** b01 = matrix_create(new_n);
		int** b10 = matrix_create(new_n);
		int** b11 = matrix_create(new_n);
		
		int** c00 = matrix_create(new_n);
		int** c01 = matrix_create(new_n);
		int** c10 = matrix_create(new_n);
		int** c11 = matrix_create(new_n);
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(i < new_n && j < new_n){
					a00[i][j] = matrix_1[i][j];
					b00[i][j] = matrix_2[i][j];
				}
				
				else if(j < new_n){
					a10[i - new_n][j] = matrix_1[i][j];
					b10[i - new_n][j] = matrix_2[i][j];
				}
				
				else if(i < new_n){
					a01[i][j - new_n] = matrix_1[i][j];
					b01[i][j - new_n] = matrix_2[i][j];
				}
				
				else{
					a11[i - new_n][j - new_n] = matrix_1[i][j];
					b11[i - new_n][j - new_n] = matrix_2[i][j];
				}
			}
		}
		
		int** s[10];
		int** mults[4];
		s[0] = matrix_sum(a00, a11, new_n);
		s[1] = matrix_sum(a10, a11, new_n);
		s[2] = matrix_sum(a00, a01, new_n);
		mults[0] = matrix_nummul(a00, -1, new_n);
		s[3] = matrix_sum(mults[0], a10, new_n);
		mults[1] = matrix_nummul(a11, -1, new_n);
		s[4] = matrix_sum(mults[1], a01, new_n);
		s[5] = matrix_sum(b00, b11, new_n);
		mults[2] = matrix_nummul(b11, -1, new_n);
		s[6] = matrix_sum(mults[2], b01, new_n);
		mults[3] = matrix_nummul(b00, -1, new_n);
		s[7] = matrix_sum(mults[3], b10, new_n);
		s[8] = matrix_sum(b00, b01, new_n);
		s[9] = matrix_sum(b10, b11, new_n);
		
		int** f1 = matrix_shtrassen_mul(s[0], s[5], p-1);
		int** f2 = matrix_shtrassen_mul(s[1], b00, p-1);
		int** f3 = matrix_shtrassen_mul(s[6], a00, p-1);
		int** f4 = matrix_shtrassen_mul(s[7], a11, p-1);
		int** f5 = matrix_shtrassen_mul(s[2], b11, p-1);
		int** f6 = matrix_shtrassen_mul(s[3], s[8], p-1);
		int** f7 = matrix_shtrassen_mul(s[4], s[9], p-1);
		
		int** fs[2];
		fs[0] = matrix_nummul(f5, -1, new_n);
		fs[1] = matrix_nummul(f2, -1, new_n);
		c00 = matrix_sum(f1, f4, new_n);
		c00 = matrix_sum(c00, f7, new_n);
		c00 = matrix_sum(c00, fs[0], new_n);
		c01 = matrix_sum(f3, f5, new_n);
		c10 = matrix_sum(f2, f4, new_n);
		c11 = matrix_sum(f1, fs[1], new_n);
		c11 = matrix_sum(c11, f3, new_n);
		c11 = matrix_sum(c11, f6, new_n);
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(i < new_n && j < new_n){
					new_matrix[i][j] = c00[i][j];
				}
				
				else if(j < new_n){
					new_matrix[i][j] = c10[i - new_n][j];
				}
				
				else if(i < new_n){
					new_matrix[i][j] = c01[i][j - new_n];
				}
				
				else{
					new_matrix[i][j] = c11[i - new_n][j - new_n];
				}
			}
		}
		
		matrix_delete(a00, new_n);
		matrix_delete(a01, new_n);
		matrix_delete(a10, new_n);
		matrix_delete(a11, new_n);
		
		matrix_delete(b00, new_n);
		matrix_delete(b01, new_n);
		matrix_delete(b10, new_n);
		matrix_delete(b11, new_n);
		
		matrix_delete(c00, new_n);
		matrix_delete(c01, new_n);
		matrix_delete(c10, new_n);
		matrix_delete(c11, new_n);
		
		matrix_delete(f1, new_n);
		matrix_delete(f2, new_n);
		matrix_delete(f3, new_n);
		matrix_delete(f4, new_n);
		matrix_delete(f5, new_n);
		matrix_delete(f6, new_n);
		matrix_delete(f7, new_n);
		
		for(int i = 0; i < 10; ++i)
			matrix_delete(s[i], new_n);
		
		for(int i = 0; i < 4; ++i)
			matrix_delete(mults[i], new_n);
		
		matrix_delete(fs[0], new_n);
		matrix_delete(fs[1], new_n);
	}
	
	else
		new_matrix = matrix_naivemul(matrix_1, matrix_2, n);
	
	return new_matrix;
}


int main(){
	int* column_1 = new int[2];
	int* column_2 = new int[2];
	
	column_1[0] = 1; column_1[1] = 3;
	column_2[0] = 2, column_2[1] = 4;
	
	int** m_1 = new int*;
	m_1[0] = column_1;
	m_1[1] = column_2;
	
	m_1 = matrix_shtrassen_mul(m_1, m_1, 1);
	cout << m_1[0][0] << ' ' << m_1[1][0] << endl << m_1[0][1] << ' ' << m_1[1][1] << endl;
	
	//m_1 = matrix_nummul(m_1, 2, 2);
	//cout << m_1[0][0] << ' ' << m_1[1][0] << endl << m_1[0][1] << ' ' << m_1[1][1] << endl;
	//m_1 = matrix_sum(m_1, m_1, 2);
	//cout << m_1[0][0] << ' ' << m_1[1][0] << endl << m_1[0][1] << ' ' << m_1[1][1] << endl;
	
	return 0;
}



/*unsigned int count = 1;
	for(unsigned int g = n; g > 0; g = g >> 1)
		count << 1;
		
	if(count & n != n)*/

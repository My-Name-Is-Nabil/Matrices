#include <iostream>
#include  <string>
#include <vector>
#include <iomanip>
#include "Complex.h"
using namespace std;
Complex dot(vector<Complex> a, vector<Complex> b)
{
	Complex sum;
	for (int i = 0; i < a.size(); i++)
		sum = sum + a[i] * b[i];
	return sum;
}
class Matrix
{
	int rows, columns;
	Complex det;
	vector<vector<Complex>> arr;
	Complex determinant()
	{
		Matrix M;
		if (rows != columns)
			return Complex(0, 0);
		if (rows == 2)
			return arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
		for (int i = 0; i < columns; i++)
		{
			if (i % 2 == 0)
			{
				M = this->lower(i);
				det = det + arr[0][i] * M.determinant();
			}
			else
			{
				M = this->lower(i);
				det = det - arr[0][i] * M.determinant();
			}
		}
		return det;
	}
public:
	Matrix()
	{
		this->rows = 0;
		this->columns = 0;
		this->det = Complex(0, 0);
	}
	Matrix(int rows, int columns, vector<vector<Complex>> arr)
	{
		this->rows = rows;
		this->columns = columns;
		this->det = Complex(0, 0);
		this->arr = arr;
		det = this->determinant();
	}
	Matrix(const Matrix& m)
	{
		rows = m.rows;
		columns = m.columns;
		arr = m.arr;
		det = m.det;
	}
	void set(int rows, int columns, vector<vector<Complex>> arr)
	{
		this->rows = rows;
		this->columns = columns;
		this->arr = arr;
		this->det = Complex(0, 0);
		det = this->determinant();
	}
	Complex get_det()
	{
		if (rows != columns)
			throw invalid_argument("Invalid Matrix Dimensions!");
		return det;
	}
	Matrix operator + (const Matrix& m)
	{
		if (rows != m.rows || columns != m.columns)
			throw invalid_argument("Matrices Dimensions don't match!");
		Matrix M(rows, columns, arr);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
				M.arr[i][j] = arr[i][j] + m.arr[i][j];
		}
		return M;
	}
	Matrix operator - (const Matrix& m)
	{
		if (rows != m.rows || columns != m.columns)
			throw invalid_argument("Matrices Dimensions don't match!");
		Matrix M(rows, columns, arr);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
				M.arr[i][j] = arr[i][j] - m.arr[i][j];
		}
		return M;
	}
	Matrix operator * (const Matrix& m)
	{
		if (columns != m.rows)
			throw invalid_argument("Invalid Matrices Dimensions!");
		Matrix M;
		vector<Complex> y;
		vector<Complex> x;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				for (int k = 0; k < m.rows; k++)
					x.push_back(m.arr[k][j]);
				y.push_back(dot(arr[i], x));
				x.clear();
			}
			M.arr.push_back(y);
			y.clear();
		}
		M.rows = rows; M.columns = m.columns;
		return M;
	}
	Matrix lower(int index)
	{
		Matrix M;
		M.rows = rows - 1;  M.columns = columns - 1;
		vector<Complex> x;
		for (int i = 1; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (j != index)
					x.push_back(arr[i][j]);
			}
			M.arr.push_back(x);
			x.clear();
		}
		return M;
	}
	Matrix transpose()
	{
		Matrix M(this->columns, this->rows, {});
		M.arr.resize(this->columns);
		int col = 0;
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				M.arr[col].push_back(this->arr[i][j]);
				col++;
			}
			col=0;
		}
		return M;
	}
	friend ostream& operator << (ostream&, const Matrix&);
};
ostream& operator << (ostream& o, const Matrix& m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
			o << m.arr[i][j] << " ";
		o << endl;
	}
	return o;
}
void parse(vector<vector<Complex>>& arr, string s)
{
	string y = "";
	vector <Complex> x;
	for (int i = 1; i < s.length(); i++)
	{
		if (s[i] == ';')
		{
			if (y.length() != 0)
				x.push_back(stoc(y));
			arr.push_back(x);
			y = "";
			x.clear();
			continue;
		}
		if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.' || s[i] == '+' || s[i] == '-' || s[i] == 'i')
		{
			y += s[i];
			continue;
		}
		if (s[i] == ' ' && y.length() != 0)
		{
			x.push_back(stoc(y));
			y = "";
			continue;
		}
		if (i == s.length() - 1)
		{
			if (y.length() != 0)
				x.push_back(stoc(y));
			arr.push_back(x);
			continue;
		}
	}
}
int main()
{
	cout << "Hello!" << endl;
	cout << "Please Enter the Matrix" << endl;
	string s;
	vector < vector <Complex> > arr1;
	getline(cin, s);
	if (s[0] != '[' || s[s.length() - 1] != ']')
	{
		cout << "Invalid Input!";
		return 0;
	}
	parse(arr1, s);
	int columns1 = arr1[0].size();
	for (int i = 1; i < arr1.size(); i++)
	{
		if (arr1[i].size() != columns1)
		{
			cout << "Invalid Input!";
			return 0;
		}
	}
	int rows1 = arr1.size();
	Matrix M1(rows1, columns1, arr1);
	cout << "Enter the operation" << endl;
	char op;
	cin >> op;
	cin.ignore();
	switch (op)
	{
		case '+':
		{
			cout << "Please Enter the Second Matrix" << endl;
			getline(cin, s);
			if (s[0] != '[' || s[s.length() - 1] != ']')
			{
				cout << "Invalid Input!";
				return 0;
			}
			vector<vector<Complex>> arr2;
			parse(arr2, s);
			int columns2 = arr2[0].size();
			for (int i = 1; i < arr2.size(); i++)
			{
				if (arr2[i].size() != columns2)
				{
					cout << "Invalid Input!";
					return 0;
				}
			}
			int rows2 = arr2.size();
			Matrix M2(rows2, columns2, arr2);
			try
			{
				cout << M1 + M2;
			}
			catch (exception& e)
			{
				cout << e.what();
			}
			break;
		}
		case '-':
		{
			cout << "Please Enter the Second Matrix" << endl;
			getline(cin, s);
			vector <vector <Complex> > arr2;
			parse(arr2, s);
			int columns2 = arr2[0].size();
			for (int i = 1; i < arr2.size(); i++)
			{
				if (arr2[i].size() != columns2)
				{
					cout << "Invalid Input!";
					return 0;
				}
			}
			int rows2 = arr2.size();
			Matrix M2(rows2, columns2, arr2);
			try
			{
				cout << M1 - M2;
			}
			catch (exception& e)
			{
				cout << e.what();
			}
			break;
		}
		case '*':
		{
			cout << "Please Enter the Second Matrix" << endl;
			getline(cin, s);
			vector <vector <Complex> > arr2;
			parse(arr2, s);
			int columns2 = arr2[0].size();
			for (int i = 1; i < arr2.size(); i++)
			{
				if (arr2[i].size() != columns2)
				{
					cout << "Invalid Input!";
					return 0;
				}
			}
			int rows2 = arr2.size();
			Matrix M2(rows2, columns2, arr2);
			try
			{
				cout << M1 * M2;
			}
			catch (exception& e)
			{
				cout << e.what();
			}
			break;
		}
		case 'd':
		{
			try
			{
				cout << M1.get_det();
			}
			catch (exception& e)
			{
				cout << e.what();
			}
		}
		case 't':
		{
			cout<<M1.transpose();
		}
	}
	return 0;
}
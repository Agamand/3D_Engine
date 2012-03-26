#include <math.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Vector.h"

Matrix::Matrix(int line, int cl)
{
	this->line = line;
	this->column = cl;
	mat = new double*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new double[cl];

	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = 0.0f;
}
Matrix::Matrix(double * tab, int line, int cl)
{
	Matrix::Matrix(line,cl);
	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = tab[i*line+j];
}

Matrix::Matrix(double ** tab, int line, int cl)
{
	Matrix::Matrix(line,cl);
	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = tab[i][j];
}

Matrix::Matrix(Matrix const &m)
{
	this->line = m.line;
	this->column = m.column;
	mat = new double*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new double[column];

	Matrix(m.line,m.column);
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
			mat[i][j] = m.mat[i][j];
}
Matrix::~Matrix()
{
	for(int i = 0; i < line; i++)
		delete mat[i];
	
	delete mat;
}

Matrix Matrix::operator+(Matrix const &a)
{
	Matrix m(*this);
	m += a;
	return m;
}
Matrix Matrix::operator-(Matrix const &a)
{
	Matrix m(*this);
	m -=a;
	return m;
}
Matrix Matrix::operator*(Matrix const &a)
{
	Matrix m(*this);
	m *=a;
	return m;
}
/*Vector3D Matrix::operator*(Vector3D const &a)
{
	if(column == 3 || column == 2)
	{
	;
		//return Vector3D(
	}
}
*/
Matrix Matrix::operator*(double const &a)	
{
	Matrix m(*this);
	m *=a;
	return m;
}
Matrix Matrix::operator/(double const &a)
{
	Matrix m(*this);
	m /=a;
	return m;
}
Matrix Matrix::operator+=(Matrix const &a)
{
	if(line != a.line && column != a.column)
		return *this;

	double ** temp = a.mat;
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] += temp[i][j];
	return *this;
}
Matrix Matrix::operator-=(Matrix const &a)
{
	if(line != a.line && column != a.column)
		return *this;
	double ** temp = a.mat;
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] -= temp[i][j];
	return *this;
}
Matrix Matrix::operator*=(Matrix const &a)
{
	if(column != a.line)
		return *this;
	
	Matrix m(*this);
	double ** m1 = m.getMatrix(); 
	double ** m2 = a.mat;
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
			for(int k = 0; k < column; k++)
				mat[i][j] += m1[i][k]*m2[k][j];
	return *this;
}
Matrix Matrix::operator*=(double const &a)	
{
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] *= a;
	return *this;
}
Matrix Matrix::operator/=(double const &a)
{
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] /= a;
	return *this;
}

double Matrix::trace()
{
	double r = 0.0f;

	if(line != column)
		return r;
	for(int i = 0; i < line; i++)
			r += mat[i][i];
}

Vector3D Matrix::toVector()
{
	Vector3D v(mat[0][0],mat[1][0],mat[2][0]);
	return v;
}



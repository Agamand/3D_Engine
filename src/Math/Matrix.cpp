#include <math.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Vector.h"
#include <sstream>

Matrix::Matrix(int line, int cl)
{
	this->line = line;
	this->column = cl;
	mat = new float*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new float[cl];

	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = 0.0f;
}
Matrix::Matrix(float * tab, int line, int cl)
{
	this->line = line;
	this->column = cl;
	mat = new float*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new float[cl];

	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = tab[i+j*cl];
}

Matrix::Matrix(float ** tab, int line, int cl)
{
	this->line = line;
	this->column = cl;
	mat = new float*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new float[cl];

	for(int i = 0; i < line; i++)
		for(int j = 0; j < cl; j++)
			mat[i][j] = tab[i][j];
}

Matrix::Matrix(Matrix const &m)
{
	this->line = m.line;
	this->column = m.column;
	mat = new float*[line];
	for(int i = 0; i < line; i++)
		mat[i] = new float[column];

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
Matrix Matrix::operator*(float const &a)	
{
	Matrix m(*this);
	m *=a;
	return m;
}
Matrix Matrix::operator/(float const &a)
{
	Matrix m(*this);
	m /=a;
	return m;
}
Matrix Matrix::operator+=(Matrix const &a)
{
	if(line != a.line && column != a.column)
		return *this;

	float ** temp = a.mat;
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] += temp[i][j];
	return *this;
}
Matrix Matrix::operator-=(Matrix const &a)
{
	if(line != a.line && column != a.column)
		return *this;
	float ** temp = a.mat;
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
	float ** m1 = m.getMatrix(); 
	float ** m2 = a.mat;
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
			for(int k = 0; k < column; k++)
				mat[i][j] += m1[i][k]*m2[k][j];
	return *this;
}
Matrix Matrix::operator*=(float const &a)	
{
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] *= a;
	return *this;
}
Matrix Matrix::operator/=(float const &a)
{
	for(int i = 0; i < line ;i++)
		for(int j = 0; j < column; j++)
			mat[i][j] /= a;
	return *this;
}

float Matrix::trace()
{
	float r = 0.0f;

	if(line != column)
		return r;
	for(int i = 0; i < line; i++)
			r += mat[i][i];
}

String Matrix::toString()
{
	ostringstream str;
	str << "\n";
	for(int i = 0; i < line ;i++)
	{
		str << "| ";
		for(int j = 0; j < column; j++)
		{
			str << mat[i][j];
			str << " ";
		}
		str << "|\n";
	}
	return str.str();
}

float Matrix2::det()
{
	return mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
}

Matrix2 Matrix2::co()
{
	Matrix2 comatrix;
	comatrix[0][0] = mat[1][1];
	comatrix[0][1] = -mat[0][1];
	comatrix[1][0] = -mat[1][0];
	comatrix[1][1] = mat[0][0];
	return comatrix;
}

Matrix2 Matrix2::inv()
{
	float _det =  det();
	if(_det == 0.0f)
		return Matrix2();
	Matrix2 inv = co();
	inv /=_det;
	return inv;
}

Matrix2 Matrix3::subMatrix(int i, int j)
{
	Matrix2 sub;
	for(int _i = 0, m = 0; _i < line; _i++)
	{
		if(_i == i)
			continue;
		else
		{
			for(int _j = 0, n = 0; _j < column; _j++)
			{
				if(_j == j)
					continue;
				else
				{
					sub[m][n] = mat[_i][_j];
					n++;
				}
			}
			m++;
		}
	}
	return sub;
}

float Matrix3::det()
{
	return mat[0][0]*subMatrix(0,0).det() - mat[1][0]*subMatrix(1,0).det() + mat[2][0]*subMatrix(2,0).det();
}

Matrix3 Matrix3::tran()
{
	Matrix3 result;
	for(int i = 0; i < line; i++)
	{
		for(int j = 0; j < column; j++)
		{
			result[j][i] = mat[i][j];
		}
	}
	return result;
}

#define COEF(i) (((i) > 0 && (i)%2 > 0) ? -1 : 1) 

Matrix3 Matrix3::co()
{
	Matrix3 transpo(tran());
	Matrix3 comatrix;
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
		{
			comatrix[i][j] = COEF(i+j)*transpo.subMatrix(i,j).det();
		}
		
	return comatrix;
}

Matrix3 Matrix3::inv()
{
	float _det =  det();
	if(_det == 0.0f)
		return Matrix3();
	Matrix3 inv = co();
	inv /=_det;
	return inv;
}

Vector3D Matrix::toVector()
{
	Vector3D v(mat[0][0],mat[1][0],mat[2][0]);
	return v;
}


Matrix3 Matrix4::subMatrix(int i, int j)
{
	Matrix3 sub;
	for(int _i = 0, m = 0; _i < line; _i++)
	{
		if(_i == i)
			continue;
		else
		{
			for(int _j = 0, n = 0; _j < column; _j++)
			{
				if(_j == j)
					continue;
				else
				{
					sub[m][n] = mat[_i][_j];
					n++;
				}
			}
			m++;
		}
	}
	return sub;
}
float Matrix4::det()
{
	return mat[0][0]*subMatrix(0,0).det() - mat[1][0]*subMatrix(1,0).det() + mat[2][0]*subMatrix(2,0).det() - mat[3][0]*subMatrix(3,0).det();
}

Matrix4 Matrix4::tran()
{
	Matrix4 result;
	for(int i = 0; i < line; i++)
	{
		for(int j = 0; j < column; j++)
		{
			result[j][i] = mat[i][j];
		}
	}
	return result;
}

Matrix4 Matrix4::co()
{
	Matrix4 transpo(tran());
	Matrix4 comatrix;
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
		{
			comatrix[i][j] = COEF(i+j)*transpo.subMatrix(i,j).det();
		}

	return comatrix;
}

Matrix4 Matrix4::inv()
{
	float _det =  det();
	if(_det == 0.0f)
		return Matrix4();
	Matrix4 inv = co();
	inv /=_det;
	return inv;
}

Vector3D Matrix4::operator*(Vector3D v)
{
	return Vector3D(v.getX()*mat[0][0]+ v.getY()*mat[0][1] + v.getZ()*mat[0][2] + mat[0][3],
		v.getX()*mat[1][0]+ v.getY()*mat[1][1] + v.getZ()*mat[1][2] + mat[1][3],
		v.getX()*mat[2][0]+ v.getY()*mat[2][1] + v.getZ()*mat[2][2] + mat[2][3]);
}
Matrix4 Matrix4::operator=(Matrix4 const &a)
{
	for(int i = 0; i < line; i++)
		for(int j = 0; j < column; j++)
			mat[i][j] = a.mat[i][j];
	return *this;
}



#ifndef MATRICE_H
#define MATRICE_H

class Matrix
{
public:
	Matrix(int line, int cl);
	Matrix(double * tab,int line, int cl);
	Matrix(double ** tab,int line, int cl);
	Matrix(Matrix const &a);
	~Matrix();

	Matrix operator+(Matrix const &a);
	Matrix operator-(Matrix const &a);
	Matrix operator*(Matrix const &a);
	Matrix operator*(double const &a);
	Matrix operator/(double const &a);
	Matrix operator+=(Matrix const &a);
	Matrix operator-=(Matrix const &a);
	Matrix operator*=(Matrix const &a);
	Matrix operator*=(double const &a);
	Matrix operator/=(double const &a);
	double* operator[](int i) { return mat[i];}
	double trace();
	//Matrix inv();
	//Matrix det();
	int getLine() { return line; }
	int getColumn() { return column; } 
	double ** getMatrix() { return mat; }

	static Matrix getRotateMatrix2(double angle, double r)
	{
		Matrix m(2,2);
		m[0][0] = r*cos(angle);
		m[0][1] = -r*sin(angle);
		m[1][0] = m[0][0];
		m[1][1] = m[0][1];
		return m;
	}
private:
	int line,column;
	double ** mat;
};

#endif
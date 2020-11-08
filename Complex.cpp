#include <iostream>
#include <cmath>
#include <string>
#include "Complex.h"
using namespace std;
Complex::Complex()
{
	real = 0;
	imj = 0;
}
Complex::Complex(float real, float imj)
{
	this->real = real;
	this->imj = imj;
}
Complex::Complex(const Complex& a)
{
	real = a.real;
	imj = a.imj;
}
float Complex::get_real() { return real; }
float Complex::get_imj() { return imj; }
void Complex::set_real(float real) { this->real = real; }
void Complex::set_imj(float imj) { this->imj = imj; }
void Complex::polar(float mag, float theeta)
{
	real = mag * cos(theeta);
	imj = mag * sin(theeta);
}
Complex Complex::conjugate() const
{
	return Complex(real, -imj);
}
float Complex::magnitude() const
{
	return sqrt(real * real + imj * imj);
}
Complex Complex::operator + (float a)
{
	return Complex(a + real, imj);
}
Complex Complex::operator + (const Complex& a)
{
	return Complex(real + a.real, imj + a.imj);
}
Complex Complex::operator - (float a)
{
	return Complex(a - real, imj);
}
Complex Complex::operator - (const Complex& a)
{
	return Complex(real - a.real, imj - a.imj);
}
Complex Complex::operator * (float a)
{
	return Complex(a * real, a * imj);
}
Complex Complex:: operator * (const Complex& a)
{
	return Complex(real * a.real - imj * a.imj, real * a.imj + imj * a.real);
}
Complex Complex:: operator / (float a)
{
	return Complex(real / a, imj / a);
}
Complex Complex::operator / (const Complex a)
{
	return Complex((*this * (a.conjugate())) / (a.magnitude() * a.magnitude()));
}
Complex operator * (float a, const Complex& c)
{
	return Complex(c.real * a, c.imj * a);
}
Complex operator / (float a, const Complex& c)
{
	return a * c.conjugate() / (c.magnitude() * c.magnitude());
}
ostream& operator << (ostream& o, const Complex& c)
{
	if (c.imj == 0)
		o << c.real;
	else if (c.real == 0)
		if (c.imj == 1)
			o << "i";
		else if (c.imj == -1)
			o << "-i";
		else
			o << c.imj << "i";
	else if (c.imj < 0)
		if (c.imj == -1)
			o << c.real << "-i";
		else
			o << c.real << c.imj << "i";
	else
		if (c.imj == 1)
			o << c.real << "+i";
		else
			o << c.real << "+" << c.imj << "i";
	return o;
}
Complex stoc(string s)
{
	Complex C;
	string x = "";
	if (s == "i")
		return Complex(0, 1);
	if (s == "-i")
		return Complex(0, -1);
	bool flag = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.' || (s[i] == '-' && i == 0) || (s[i] == '+' && i == 0))
			x += s[i];
		if ((s[i] == '-' && i != 0) || (s[i] == '+' && i != 0) || (i == s.length() - 1 && s[i] != 'i'))
		{
			C.real = stof(x);
			flag = 1;
			x = s[i];
		}
		else if (s[i] == 'i' && i == s.length() - 1)
			if (x == "+")
				C.imj = 1;
			else if (x == "-")
				C.imj = -1;
			else
				C.imj = stof(x);
	}
	if (flag == 0)
		C.real = 0;
	return C;
}

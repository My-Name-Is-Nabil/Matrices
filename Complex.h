#pragma once
#include <iostream>
#include <cmath>
#include <string>
class Complex
{
	float real, imj;
public:
	Complex();
	Complex(float, float);
	Complex(const Complex&);
	float get_real();
	float get_imj();
	void set_real(float);
	void set_imj(float);
	void polar(float, float);
	Complex conjugate() const;
	float magnitude() const;
	Complex operator + (float);
	Complex operator + (const Complex&);
	Complex operator - (float);
	Complex operator - (const Complex&);
	Complex operator * (float);
	Complex operator * (const Complex&);
	Complex operator / (float);
	Complex operator / (const Complex);
	friend std::ostream& operator << (std::ostream&, const Complex&);
	friend Complex operator * (float, const Complex&);
	friend Complex operator / (float, const Complex&);
	friend Complex stoc(std::string);
};
Complex operator * (float, const Complex&);
Complex operator / (float, const Complex&);
std::ostream& operator << (std::ostream&, const Complex&);
Complex stoc(std::string);

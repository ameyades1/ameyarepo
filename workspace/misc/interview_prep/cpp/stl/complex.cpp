/*******************************/
/*  C L A S S   C O M P L E X  */
/*******************************/

/*
 *  S Y S T E M   I N C L U D E S
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>

using std::string;

/*
 *  C O M P O N E N T   I N C L U D E S
 */
#include "complex.h"


void CComplex::print()
{
	std::cout << m_name << " = " << m_real << " + i" << m_img << "\n";
}

void CComplex::setName(char* name)
{
	unsigned int len;

	if (name)
	{
		len = strlen (name);
		m_name = (char*) malloc ((sizeof(char) * len) + 1);
		strcpy (m_name, name);
	}
}

void CComplex::setStr(char* name)
{
	unsigned int len;

	if (name)
	{
		if (m_string)
			free (m_string);

		len = strlen (name);
		m_string = (char*) malloc ((sizeof(char) * len) + 1);
		strcpy (m_string, name);
	}
}

CComplex& CComplex::operator+(const CComplex& complex)
{
	m_real += complex.m_real;
	m_img += complex.m_img;

	return *this;
}

CComplex CComplex::operator+(const long int& num)
{
	m_real += num;
	
	return *this;
}


CComplex::CComplex (const CComplex & complex)
{
	unsigned int len;

	m_real = complex.m_real;
	m_img  = complex.m_img;

	if (complex.m_string)
	{
		len = strlen (complex.m_string);
		m_string = (char*) malloc ((sizeof(char) * len) + 1);
		strcpy (m_string, complex.m_string);
	}
}


CComplex& CComplex::operator =(const CComplex& complex)
{
	unsigned int len;

	if (this == &complex)
		return *this;

	m_real = complex.m_real;
	m_img = complex.m_img;

	if(m_string)
	{
		free(m_string);
		m_string = NULL;
	}

	if (complex.m_string)
	{
		len = strlen (complex.m_string);
		m_string = (char*) malloc ((sizeof(char) * len) + 1);
		strcpy (m_string, complex.m_string);
	}

	return *this;
}


CComplex CComplex::operator *(const CComplex& complex)
{
	// (a + ib) * (c + id) = ac + iad + ibc -bd 
	//                     = ac -bd + i(ad + bc)

	m_real = m_real * complex.m_real - m_img * complex.m_img;
	m_img  = m_real * complex.m_img  + m_img * complex.m_real;

	return *this;
				
}

CComplex CComplex::operator *(const long int num)
{
	m_real *= num;
	m_img  *= num;

	return *this;
}

CComplex CComplex::operator++(int)
{
	CComplex temp;
	temp = *this;

	m_real++;

	return temp;

}


CComplex CComplex::operator--(int)
{
	CComplex temp (*this);

	m_real--;

	return temp;
}

CComplex& CComplex::operator++()
{
	m_real++;

	return *this;
}





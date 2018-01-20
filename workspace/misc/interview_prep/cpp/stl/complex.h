/*******************************/
/*  C L A S S   C O M P L E X  */
/*******************************/

/*
 *  S Y S T E M   I N C L U D E S
 */

#include <iostream>
#include <string>
#include <cstring>

using std::string;

class CComplex {

private:
	long int m_img;
	long int m_real;
	char*    m_string;
	char*    m_name;


public:

	CComplex (const long int real, const long int img, const char* name)
	{
		unsigned int len;

		m_real = real;
		m_img = img;
		m_name = NULL;

		if(name)
		{
			len = strlen(name);
			m_string = (char*) malloc ((sizeof(char) * len) + 1);
			strcpy(m_string, name);
		}
		else
			m_string = NULL;
	}

	CComplex ()
	{
		m_real = 0;
		m_img = 0;
		m_string = NULL;
		m_name = NULL;
	}

	~CComplex ()
	{
		if (m_string)
			free (m_string);
	}

	// Copy constructor
	CComplex (const CComplex & complex);
	CComplex& operator= (const CComplex& complex);

	const char* toString();

	void setStr (char* name);
	void setName (char* name);

 	CComplex& operator+ (const CComplex& complex);
  CComplex operator+ (const long int& num);
	
	CComplex operator* (const CComplex& complex);
	CComplex operator* (const long int num);

	// Postfix
	CComplex operator++(int);
	CComplex operator--(int);

	// Prefix
	CComplex& operator++();

	long int getReal() {return m_real;};
	long int getImg()  {return m_img;};

	void print();

};




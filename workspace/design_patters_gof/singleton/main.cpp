/*
 *  S I N G L E T O N   C L A S S
 */


/*
 *  SYSTEM INCLUDES
 */
#include <iostream>

class CSingleton
{
protected:
	CSingleton() {};

public:
	static CSingleton* GetInstance();
	void WhoAmi();

private:
	static CSingleton* m_instance;
};

CSingleton* CSingleton::GetInstance()
{
	if(!m_instance)
		m_instance = new CSingleton();

	return m_instance;
}

void CSingleton::WhoAmi()
{
	std::cout << "I am a singleton class!" << std::endl;
}


CSingleton* CSingleton::m_instance = NULL;

int main (int argc, char* argv[])
{
	CSingleton* pSingleton = CSingleton::GetInstance();

	pSingleton->WhoAmi();

	return 0;
}

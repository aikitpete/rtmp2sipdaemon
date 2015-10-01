#include "TestSuitcase.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

CTestSuitcase::~CTestSuitcase()
{
	CleanUp();
}

void
CTestSuitcase::AddTester(CTester *test, const string &strTestName)
{
	if(!test->Init())
		cerr << "Test could not be initialized!" << endl;
	else
	{
		string name = strTestName;
		if(name == "")
		{
			name = "Test ";
			int size = m_vStrTestNames.size() + 1;
			while(size > 0)
			{
				name.insert(5, 1, (size % 10) + '0');
				size /= 10;
			}
		}
		m_vStrTestNames.push_back(name);
		m_vSuitcase.push_back(test);
	}
}

void
CTestSuitcase::RunAll()
{
	for(size_t i = 0, im = m_vSuitcase.size(); i < im; ++i)
	{
		cout << m_vStrTestNames[i] << endl;
		cout << "=====================================\n";
		bool res = m_vSuitcase[i]->Run();
		cout << "-------------------------------------\n";
		cout << (res ? "OK." : "FAILED!") << "\n\n" << endl;
	}
}

void
CTestSuitcase::CleanUp()
{
	for(size_t i = 0, im = m_vSuitcase.size(); i < im; ++i)
	{
		m_vSuitcase[i]->Clean();
		delete m_vSuitcase[i];
		m_vSuitcase[i] = NULL;
	}
	m_vSuitcase.clear();
}

/*************************************************************************
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/

/**
 * @file
 * TestSuicase.h
 * 
 * @author
 * Martin Ovesny (<a href="mailto:ovesnmar@fel.cvut.cz">ovesnmar@fel.cvut.cz</a>)
 * 
 * @brief
 * Contains the container for gouping tests.
 *
 */
#ifndef _TESTSUITCASE_H_
#define _TESTSUITCASE_H_

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "Tester.h"

/**
 * @brief
 * The container for grouping unit tests that implement the Terster interface.
 * 
 * @see
 * CTester
 */
class CTestSuitcase
{
	private:
		vector<CTester *> m_vSuitcase;
		vector<string> m_vStrTestNames;

	public:
		/**
		 * @brief
		 * Calls <code>CleanUp</code> method.
		 */
		~CTestSuitcase();

		/**
		 * @brief
		 * Inserts a unit test into suitcase and calls the <code>Init</code> method from test interface.
		 *
		 * @param pTest
		 * Pointer to class that implements the <code>CTester</code> interface (=unit test).
		 *
		 * @param strTestName
		 * [optional] Name of test, which is printed with testing status (OK / FAILED).
		 * Default is Test1, Test2, etc.
		 *
		 * @see
		 * CTester
		 */
		void AddTester(CTester *pTest, const string &strTestName = "");

		/**
		 * @brief
		 * Executes all tests from suitcase (=for each of tests the <code>CTester::Run</code> method is called).
		 *
		 * @see
		 * CTester
		 */
		void RunAll();

		/**
		 * @brief
		 * Removes all tests from suitcase and for each of tests the <code>CTester::Clean</code> method is called.
		 *
		 * @see
		 * CTester
		 */
		void CleanUp();
};

#endif	// _TESTSUITCASE_H_

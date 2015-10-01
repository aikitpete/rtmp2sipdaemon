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
 * Tester.h
 * 
 * @author
 * Martin Ovesny (<a href="mailto:ovesnmar@fel.cvut.cz">ovesnmar@fel.cvut.cz</a>)
 *
 * @brief
 * Contains the interface for unit tests.
 */
#ifndef _TESTER_H_
#define _TESTER_H_

/**
 * @brief
 * Test interface for writing and processing unit tests.
 */
class CTester
{
	public:
		virtual ~CTester() { }	// do nothing
		
		/**
		 * @brief
		 * It should be used for preparing input data for test. This method is executed before
		 * the CTester is inserted into CTestSuitcase.
		 *
		 * @return
		 * If the initialization is successfuly done, then you should return <code>true</code>.
		 * If the <code>false</code> is returned, the test will be failed and it will not be processed.
		 *
		 * @see
		 * CTestSuitcase
		 */
		virtual bool Init () = 0;

		/**
		 * @brief
		 * In this method should be realized the whole unit test.
		 *
		 * @return
		 * If the test completed successfuly, then you should return <code>true</code>.
		 * If the <code>false</code> is returned, the test will be failed.
		 *
		 * @see
		 * CTestSuitcase
		 */
		virtual bool Run  () = 0;

		/**
		 * @brief
		 * It should be used for cleaning up the resources, that was created in <code>Init</code> method.
		 * This method is executed before the CTester is removed from CTestSuitcase
		 * (it's usually when the test finish).
		 *
		 * @return
		 * If the initialization is successfuly done, then it should return <code>true</code>.
		 * If the <code>false</code> is returned, the test will immediately fail.
		 *
		 * @see
		 * CTestSuitcase
		 */
		virtual bool Clean() = 0;
};

#endif

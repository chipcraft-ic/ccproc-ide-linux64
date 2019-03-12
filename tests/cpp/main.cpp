/*H*****************************************************************************
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ChipCraft Sp. z o.o. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* ******************************************************************************
* File Name : main.cpp
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
*H*****************************************************************************/

/**
 * @file
 * @brief   C++ Support tests
 * @author  Rafal Harabien <r.harabien@chipcraft-ic.com>
 */

#include <ccproc.h>
#include <cstdio>
#include <cstring>
#include <exception>
#include <test.h>

#ifdef TEST_STL
# include <string>
# include <vector>
#endif

#include "virt.h"

static int g_ConstrCalls = 0;
static int g_DescrCalls = 0;

class CtorTest
{
public:
    CtorTest()
    {
        ++g_ConstrCalls;
    }

    ~CtorTest()
    {
        ++g_DescrCalls;
    }
};

template<typename T>
class TplTest
{
public:
    T fun(int a)
    {
        return static_cast<T>(a);
    }
};

void throwException()
{
    class TestException : public std::exception
    {
        const char *m_what;
    public:
        TestException(const char *what) : m_what(what) {}
        virtual const char* what() const noexcept
        {
            return m_what;
        }

    };
    // Note: std::runtime_error uses std::string and makes binary much bigger
    //throw std::runtime_error("test");
    throw TestException("test");
}

CtorTest g_foo;

void testCtor()
{
	assertEq(g_ConstrCalls, 1);
	assertEq(g_DescrCalls, 0);

	{
		CtorTest foo2;
		assertEq(g_ConstrCalls, 2);
		assertEq(g_DescrCalls, 0);
	}

	assertEq(g_ConstrCalls, 2);
	assertEq(g_DescrCalls, 1);

    CtorTest *ptr = new CtorTest;
    assertEq(g_ConstrCalls, 3);
    assertEq(g_DescrCalls, 1);

    delete ptr;
    assertEq(g_ConstrCalls, 3);
    assertEq(g_DescrCalls, 2);
}

void testExcept()
{
	bool catched = false;
	try
	{
		throwException();
	}
	catch (std::exception &e)
	{
        assertEq(strcmp(e.what(), "test"), 0);
		catched = true;
	}
	assertEq(catched, true);
}

void testVirtual()
{
    VirtTestBase *bar = new VirtTestBase();
    assertEq(bar->vfun(), 'b');
    delete bar;
    bar = new VirtTest();
    assertEq(bar->vfun(), 'c');
    delete bar;
}

void testTpl()
{
    TplTest<unsigned char> foo;
    assertEq(foo.fun(10000), 10000 & 0xFF);
    TplTest<long> foo2;
    assertEq(foo2.fun(10000), 10000);
}

#ifdef TEST_STL
void testStl()
{
    std::string str("foo");
    assertEq(str.at(0), 'f');
    assertEq(str.size(), 3);
    std::vector<int> vec;
    vec.push_back(10);
    assertEq(vec.back(), 10);
}
#endif // TEST_STL

// Make executable much smaller by removing demangling support
extern "C" char* __cxa_demangle(const char* mangled_name, char* buf, size_t* n, int* status)
{
    if (status)
        *status = -1;
    return nullptr;
} 

int main(void)
{
    printf("Starting CPP support test.\n");
	testCtor();
	testExcept();
    testVirtual();
    testTpl();

#ifdef TEST_STL
    testStl();
#endif

    printTestSummary();

    return 0;
}

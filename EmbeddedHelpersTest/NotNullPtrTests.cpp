#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\EmbeddedHelpers\NotNullPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EmbeddedHelpersTest
{
	struct TestNullPtrStruct
	{
		void Foo() {}
	};

	TEST_CLASS(NotNullPtrTests)
	{
	public:

		TEST_METHOD(NotNullPtr_WhenConstructedNotNull_DoesNotThrowException)
		{
			int testInt = 12;
			NotNullPtr<int> testPtr(&testInt);
		}

		TEST_METHOD(NotNullPtr_WhenConstructedNull_ThrowsException)
		{
			try
			{
				NotNullPtr<int> testPtr(nullptr);
				Assert::Fail(L"Expected invalid argument exception");
			}
			catch (const std::invalid_argument&)
			{
				/* PASS */
			}
		}

		TEST_METHOD(NotNullPtr_ProvidesArrowOperator)
		{
			TestNullPtrStruct foo;
			NotNullPtr<TestNullPtrStruct> fooPtr(&foo);

			fooPtr->Foo();
		}

		TEST_METHOD(NotNullPtr_ProvidesDereferenceOperator)
		{
			TestNullPtrStruct foo;
			NotNullPtr<TestNullPtrStruct> fooPtr(&foo);

			(*fooPtr).Foo();
		}

		TEST_METHOD(NotNullPtr_ProvidesPointerCast)
		{
			TestNullPtrStruct foo;
			NotNullPtr<TestNullPtrStruct> fooPtr(&foo);

			TestNullPtrStruct* pFoo = fooPtr;
			Assert::AreEqual<void*>(pFoo, fooPtr);
		}
	};
}
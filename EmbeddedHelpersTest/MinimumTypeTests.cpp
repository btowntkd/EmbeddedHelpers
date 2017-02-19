#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\EmbeddedHelpers\MinimumType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EmbeddedHelpersTest
{		
	TEST_CLASS(MinimumTypeTests)
	{
	public:
		
		TEST_METHOD(MinimumType_IsEightBits_ForUpToEightBits)
		{
			typedef MinimumType<1>::type MinType1;
			typedef MinimumType<2>::type MinType2;
			typedef MinimumType<3>::type MinType3;
			typedef MinimumType<4>::type MinType4;
			typedef MinimumType<5>::type MinType5;
			typedef MinimumType<6>::type MinType6;
			typedef MinimumType<7>::type MinType7;
			typedef MinimumType<8>::type MinType8;
			typedef MinimumType<9>::type MinType9;

			// Ensure 1-8 bits are considered an 8-bit storage type
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType1));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType2));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType3));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType4));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType5));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType6));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType7));
			Assert::AreEqual(sizeof(std::uint8_t), sizeof(MinType8));

			// Ensure 9 bits are not considered an 8-bit storage type
			Assert::AreNotEqual(sizeof(std::uint8_t), sizeof(MinType9));
		}

		TEST_METHOD(MinimumType_IsSixteenBits_ForNineToSixteenBits)
		{
			typedef MinimumType<8>::type MinType8;
			typedef MinimumType<9>::type MinType9;
			typedef MinimumType<10>::type MinType10;
			typedef MinimumType<11>::type MinType11;
			typedef MinimumType<12>::type MinType12;
			typedef MinimumType<13>::type MinType13;
			typedef MinimumType<14>::type MinType14;
			typedef MinimumType<15>::type MinType15;
			typedef MinimumType<16>::type MinType16;
			typedef MinimumType<17>::type MinType17;

			// Ensure 8 bits are not considered a 16-bit storage type
			Assert::AreNotEqual(sizeof(std::uint16_t), sizeof(MinType8));

			// Ensure 9-16 bits are considered a 16-bit storage type
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType9));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType10));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType11));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType12));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType13));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType14));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType15));
			Assert::AreEqual(sizeof(std::uint16_t), sizeof(MinType16));

			// Ensure 17 bits are not considered a 16-bit storage type
			Assert::AreNotEqual(sizeof(std::uint16_t), sizeof(MinType17));
		}

		TEST_METHOD(MinimumType_IsThirtyTwoBits_ForSeventeenToThirtyTwoBits)
		{
			typedef MinimumType<16>::type MinType16;
			typedef MinimumType<17>::type MinType17;
			typedef MinimumType<18>::type MinType18;
			typedef MinimumType<19>::type MinType19;
			// ...
			typedef MinimumType<29>::type MinType29;
			typedef MinimumType<30>::type MinType30;
			typedef MinimumType<31>::type MinType31;
			typedef MinimumType<32>::type MinType32;
			typedef MinimumType<33>::type MinType33;

			// Ensure 16 bits are not considered a 32-bit storage type
			Assert::AreNotEqual(sizeof(std::uint32_t), sizeof(MinType16));

			// Ensure 17-32 bits are considered a 32-bit storage type
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType17));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType18));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType19));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType29));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType30));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType31));
			Assert::AreEqual(sizeof(std::uint32_t), sizeof(MinType32));

			// Ensure 33 bits are not considered a 32-bit storage type
			Assert::AreNotEqual(sizeof(std::uint32_t), sizeof(MinType33));
		}

		TEST_METHOD(MinimumType_IsSixtyFourBits_ForThirtyThreeToSixtyFourBits)
		{
			typedef MinimumType<32>::type MinType32;
			typedef MinimumType<33>::type MinType33;
			typedef MinimumType<34>::type MinType34;
			typedef MinimumType<35>::type MinType35;
			// ...
			typedef MinimumType<60>::type MinType60;
			typedef MinimumType<61>::type MinType61;
			typedef MinimumType<62>::type MinType62;
			typedef MinimumType<63>::type MinType63;
			typedef MinimumType<64>::type MinType64;

			// Ensure 16 bits are not considered a 32-bit storage type
			Assert::AreNotEqual(sizeof(std::uint64_t), sizeof(MinType32));

			// Ensure 17-32 bits are considered a 32-bit storage type
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType33));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType34));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType35));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType60));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType61));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType62));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType63));
			Assert::AreEqual(sizeof(std::uint64_t), sizeof(MinType64));
		}
	};
}
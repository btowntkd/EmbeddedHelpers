#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\EmbeddedHelpers\BitField.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EmbeddedHelpersTest
{
	TEST_CLASS(BitFieldTests)
	{
		union Register8
		{
			typedef std::uint8_t DataType;
			DataType value;

			BitField<DataType, 0, 2> zeroToOne;
			BitField<DataType, 2, 4> twoToFive;
			BitField<DataType, 6, 2> sixToSeven;
			
			BitField<DataType, 2, 6> overlap_twoToSeven;
		};

		union Register16
		{
			typedef std::uint16_t DataType;
			DataType value;

			BitField<DataType, 0, 2> zeroToOne;
			BitField<DataType, 2, 4> twoToFive;
			BitField<DataType, 6, 4> sixToNine;
			BitField<DataType, 10, 6> tenToFifteen;

			BitField<DataType, 2, 7> overlap_twoToEight;
			BitField<DataType, 2, 6> overlap_nineToFifteen;
		};

		TEST_METHOD(MultipleBitFields_DefinedInUnion_DoesNotAffectSizeOfUnion)
		{
			Register8 reg8;
			Register16 reg16;
			Assert::AreEqual(sizeof(Register8::DataType), sizeof(reg8));
			Assert::AreEqual(sizeof(Register16::DataType), sizeof(reg16));
		}

		TEST_METHOD(BitField_Masks)
		{
			Register8 reg8;			
			
			Register8::DataType maskZeroToOne = 0b00000011;
			Assert::AreEqual(reg8.zeroToOne.mask(), maskZeroToOne);

			Register8::DataType maskTwoToFive = 0b00111100;
			Assert::AreEqual(reg8.twoToFive.mask(), maskTwoToFive);

			Register8::DataType maskSixToSeven = 0b11000000;
			Assert::AreEqual(reg8.sixToSeven.mask(), maskSixToSeven);

			Register8::DataType maskTwoToSeven = 0b11111100;
			Assert::AreEqual(reg8.overlap_twoToSeven.mask(), maskTwoToSeven);
		}

		TEST_METHOD(BitField_Maximums)
		{
			Register8 reg8;
			reg8.value = 0x00;

			Register8::DataType maxTwoBits = 0b00000011;
			Register8::DataType maxFourBits = 0b00001111;
			Register8::DataType maxSixBits = 0b00111111;

			Assert::AreEqual(reg8.zeroToOne.maximum(), maxTwoBits);
			Assert::AreEqual(reg8.twoToFive.maximum(), maxFourBits);
			Assert::AreEqual(reg8.sixToSeven.maximum(), maxTwoBits);
			Assert::AreEqual(reg8.overlap_twoToSeven.maximum(), maxSixBits);
		}

		TEST_METHOD(BitField_ReadValue_ReturnsMaskedShiftedValue)
		{
			Register8 reg8;

			Register8::DataType allBits = 0b11111111;
			Register8::DataType zeroBits = 0b00000000;

			Register8::DataType maxTwoBits = 0b00000011;
			Register8::DataType maxFourBits = 0b00001111;
			Register8::DataType maxSixBits = 0b00111111;

			Register8::DataType twoOddBits = 0b00000010;
			Register8::DataType fourOddBits = 0b00001010;
			Register8::DataType sixOddBits = 0b00101010;
			Register8::DataType eightOddBits = 0b10101010;

			Register8::DataType twoEvenBits = 0b00000001;
			Register8::DataType fourEvenBits = 0b00000101;
			Register8::DataType sixEvenBits = 0b00010101;
			Register8::DataType eightEvenBits = 0b01010101;

			// Enable all bits
			reg8.value = allBits;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, maxFourBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.overlap_twoToSeven, maxSixBits);

			// Disable all bits
			reg8.value = zeroBits;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.overlap_twoToSeven, zeroBits);

			// Enable odd bits
			reg8.value = eightOddBits;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, twoOddBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, fourOddBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, twoOddBits);
			Assert::AreEqual<std::uint8_t>(reg8.overlap_twoToSeven, sixOddBits);

			// Enable even bits
			reg8.value = eightEvenBits;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, twoEvenBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, fourEvenBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, twoEvenBits);
			Assert::AreEqual<std::uint8_t>(reg8.overlap_twoToSeven, sixEvenBits);
		}

		TEST_METHOD(BitField_WriteValue_DoesNotAffectOtherBits)
		{
			Register8 reg8;

			Register8::DataType allBits = 0b11111111;
			Register8::DataType zeroBits = 0b00000000;

			Register8::DataType maxTwoBits = 0b00000011;
			Register8::DataType maxFourBits = 0b00001111;
			Register8::DataType maxSixBits = 0b00111111;

			// Enable all bits;
			// Zero out the middle 4 bits;
			// Ensure the middle four bits are disabled
			// Ensure the first two and last two bits are still enabled
			// Ensure the raw value looks like: 0b11000011
			reg8.value = allBits;
			reg8.twoToFive = 0;
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, zeroBits);	
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.value, 0b11000011);

			// Enable all bits;
			// Zero out the first 2 bits;
			// Ensure the middle four bits are still enabled
			// Ensure the last two bits are still enabled
			// Ensure the raw value looks like: 0b11111100
			reg8.value = allBits;
			reg8.zeroToOne = 0;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, maxFourBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.value, 0b11111100);

			// Enable all bits;
			// Zero out the last 2 bits;
			// Ensure the middle four bits are still enabled
			// Ensure the first two bits are still enabled
			// Ensure the raw value looks like: 0b00111111
			reg8.value = allBits;
			reg8.sixToSeven = 0;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, maxFourBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.value, 0b00111111);

			// Enable all bits;
			// Zero out the (overlap) last 6 bits;
			// Ensure the middle four bits are disabled
			// Ensure the first two bits are still enabled
			// Ensure the raw value looks like: 0b00000011
			reg8.value = allBits;
			reg8.overlap_twoToSeven = 0;
			Assert::AreEqual<std::uint8_t>(reg8.zeroToOne, maxTwoBits);
			Assert::AreEqual<std::uint8_t>(reg8.twoToFive, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.sixToSeven, zeroBits);
			Assert::AreEqual<std::uint8_t>(reg8.value, 0b00000011);
		}
	};
}
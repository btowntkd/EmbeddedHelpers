#pragma once
#include <type_traits>
#include <cstdint>

/// <summary>
/// Given a minimum needed bit-length: provides the smallest possible integral type,
/// which can be used for storage of the needed bits.
/// </summary>
template<size_t BitLength>
struct MinimumType
{
	typedef
		typename std::conditional<BitLength == 0, void,
		typename std::conditional<BitLength <= 8, std::uint8_t,
		typename std::conditional<BitLength <= 16, std::uint16_t,
		typename std::conditional<BitLength <= 32, std::uint32_t,
		typename std::conditional<BitLength <= 64, std::uint64_t,
		void>::type>::type>::type>::type>::type type;
};
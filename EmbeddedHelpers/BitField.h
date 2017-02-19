#pragma once

/// <summary>
/// Provides a portable, safe utility for defining individual bitfields within a larger storage type.
/// </summary>
/// <remarks>
/// BitField members should be defined within a union, which also contains an instance of the parent storage type.
/// </remarks>
template <typename TData, size_t BitOffset, size_t BitLength>
class BitField
{
	static_assert(BitOffset + BitLength <= sizeof(TData) * 8, "Total bitlength exceeds backing data capacity");

public:

	/// <summary>
	/// Get the maximum possible numeric value of the current BitField, based on the total bit-length.
	/// </summary>
	TData maximum() const { return MAX_VALUE; }

	/// <summary>
	/// Get the bitmask through which the BitField member is filtered.
	/// </summary>
	TData mask() const { return MASK; }

	/// <summary>
	/// Return true if any bits in the defined range are enabled.
	/// Otherwise, return false.
	/// </summary>
	bool any() const { return (bool)*this; }

	/// <summary>
	/// Get the current numeric value of the BitField, based on zero-offset bits.
	/// </summary>
	operator TData() const 
	{
		return (data_ >> BitOffset) & MAX_VALUE; 
	}

	/// <summary>
	/// Apply the value to the bitfield.  Shifts the value by the BitField's offset
	/// and masks the value to prevent overflow outside the BitField's range.
	/// </summary>
	BitField& operator=(TData value)
	{
		// Zero out the bits within the BitField's range, and apply the 'value bits'
		data_ = (data_ & ~MASK) | ((value & MAX_VALUE) << BitOffset);
		return *this;
	}

	/// <summary>
	/// Return true if any bits in the defined range are enabled.
	/// Otherwise, return false.
	/// </summary>
	explicit operator bool() const { return data_ & MASK; }

	BitField &operator++() { return *this = *this + 1; }
	TData operator++(int) { TData temp = *this; ++*this; return temp; }
	BitField &operator--() { return *this = *this - 1; }
	TData operator--(int) { TData temp = *this; --*this; return temp; }

private:
	enum 
	{
		MAX_VALUE = (TData(1) << BitLength) - 1,
		MASK = MAX_VALUE << BitOffset
	};

	TData data_;
};

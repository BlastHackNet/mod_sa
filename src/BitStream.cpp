/* 
	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

	lite version of RakNet BitStream Copyright 2003 Kevin Jenkins.
*/

#include "main.h"

BitStream::BitStream()
{
	numberOfBitsUsed = 0;
	//numberOfBitsAllocated = 32 * 8;
	numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	readOffset = 0;
	//data = ( unsigned char* ) malloc( 32 );
	data = ( unsigned char* ) stackData;
	copyData = true;
}

BitStream::BitStream( int initialBytesToAllocate )
{
	numberOfBitsUsed = 0;
	readOffset = 0;
	if (initialBytesToAllocate <= BITSTREAM_STACK_ALLOCATION_SIZE)
	{
		data = ( unsigned char* ) stackData;
		numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	}
	else
	{
		data = ( unsigned char* ) malloc( initialBytesToAllocate );
		numberOfBitsAllocated = initialBytesToAllocate << 3;
	}
	copyData = true;
}

BitStream::BitStream( unsigned char* _data, unsigned int lengthInBytes, bool _copyData )
{
	numberOfBitsUsed = lengthInBytes << 3;
	readOffset = 0;
	copyData = _copyData;
	numberOfBitsAllocated = lengthInBytes << 3;
	
	if ( copyData )
	{
		if ( lengthInBytes > 0 )
		{
			if (lengthInBytes < BITSTREAM_STACK_ALLOCATION_SIZE)
			{
				data = ( unsigned char* ) stackData;
				numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE << 3;
			}
			else
			{
				data = ( unsigned char* ) malloc( lengthInBytes );
			}
#ifdef _DEBUG
			assert( data );
#endif
			memcpy( data, _data, lengthInBytes );
		}
		else
			data = 0;
	}
	else
		data = ( unsigned char* ) _data;
}

// Use this if you pass a pointer copy to the constructor (_copyData==false) and want to overallocate to prevent reallocation
void BitStream::SetNumberOfBitsAllocated( const unsigned int lengthInBits )
{
	numberOfBitsAllocated = lengthInBits;
}

BitStream::~BitStream()
{
	if ( copyData && numberOfBitsAllocated > BITSTREAM_STACK_ALLOCATION_SIZE << 3)
		free( data );  // Use realloc and free so we are more efficient than delete and new for resizing
}

void BitStream::Reset( void )
{
	// Note:  Do NOT reallocate memory because BitStream is used
	// in places to serialize/deserialize a buffer. Reallocation
	// is a dangerous operation (may result in leaks).
	
	if ( numberOfBitsUsed > 0 )
	{
		//  memset(data, 0, BITS_TO_BYTES(numberOfBitsUsed));
	}
	
	numberOfBitsUsed = 0;

	readOffset = 0;
}

// Write an array or casted stream
void BitStream::Write( const char* input, const int numberOfBytes )
{
	if (numberOfBytes==0)
		return;

	// Optimization:
	if ((numberOfBitsUsed & 7) == 0)
	{
		AddBitsAndReallocate( BYTES_TO_BITS(numberOfBytes) );
		memcpy(data+BITS_TO_BYTES(numberOfBitsUsed), input, numberOfBytes);
		numberOfBitsUsed+=BYTES_TO_BITS(numberOfBytes);
	}
	else
	{
		WriteBits( ( unsigned char* ) input, numberOfBytes * 8, true );
	}
	
}
void BitStream::Write( BitStream *bitStream )
{
	Write(bitStream, bitStream->GetNumberOfBitsUsed());
}
void BitStream::Write( BitStream *bitStream, int numberOfBits )
{
	AddBitsAndReallocate( numberOfBits );
	int numberOfBitsMod8;

	while (numberOfBits-->0 && bitStream->readOffset + 1 <= bitStream->numberOfBitsUsed)
	{
		numberOfBitsMod8 = numberOfBitsUsed & 7;
		if ( numberOfBitsMod8 == 0 )
		{
			// New byte
			if (bitStream->data[ bitStream->readOffset >> 3 ] & ( 0x80 >> ( bitStream->readOffset++ % 8 ) ) )
			{
				// Write 1
				data[ numberOfBitsUsed >> 3 ] = 0x80;
			}
			else
			{
				// Write 0
				data[ numberOfBitsUsed >> 3 ] = 0;
			}
		}
		else
		{
			// Existing byte
			if (bitStream->data[ bitStream->readOffset >> 3 ] & ( 0x80 >> ( bitStream->readOffset++ % 8 ) ) )
				data[ numberOfBitsUsed >> 3 ] |= 0x80 >> ( numberOfBitsMod8 ); // Set the bit to 1
			// else 0, do nothing
		}

		numberOfBitsUsed++;
	}
}

// Read an array or casted stream
bool BitStream::Read( char* output, const int numberOfBytes )
{
	// Optimization:
	if ((readOffset & 7) == 0)
	{
		if ( readOffset + ( numberOfBytes << 3 ) > numberOfBitsUsed )
			return false;

		// Write the data
		memcpy( output, data + ( readOffset >> 3 ), numberOfBytes );

		readOffset += numberOfBytes << 3;
		return true;
	}
	else
	{
		return ReadBits( ( unsigned char* ) output, numberOfBytes * 8 );
	}
}

// Sets the read pointer back to the beginning of your data.
void BitStream::ResetReadPointer( void )
{
	readOffset = 0;
}

// Sets the write pointer back to the beginning of your data.
void BitStream::ResetWritePointer( void )
{
	numberOfBitsUsed = 0;
}

// Write a 0
void BitStream::Write0( void )
{
	AddBitsAndReallocate( 1 );
	
	// New bytes need to be zeroed
	if ( ( numberOfBitsUsed & 7 ) == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0;
		
	numberOfBitsUsed++;
}

// Write a 1
void BitStream::Write1( void )
{
	AddBitsAndReallocate( 1 );
	
	int numberOfBitsMod8 = numberOfBitsUsed & 7;
	
	if ( numberOfBitsMod8 == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0x80;
	else
		data[ numberOfBitsUsed >> 3 ] |= 0x80 >> ( numberOfBitsMod8 ); // Set the bit to 1
		
	numberOfBitsUsed++;
}

#ifdef _MSC_VER
#pragma warning( disable : 4800 ) // warning C4100: <variable name> : unreferenced formal parameter
#endif
// Returns true if the next data read is a 1, false if it is a 0
bool BitStream::ReadBit( void )
{
	return ( bool ) ( data[ readOffset >> 3 ] & ( 0x80 >> ( readOffset++ & 7 ) ) );
}

// Align the bitstream to the byte boundary and then write the specified number of bits.
// This is faster than WriteBits but wastes the bits to do the alignment and requires you to call
// SetReadToByteAlignment at the corresponding read position
void BitStream::WriteAlignedBytes( const unsigned char* input,
	const int numberOfBytesToWrite )
{	
	AlignWriteToByteBoundary();
	Write((const char*) input, numberOfBytesToWrite);
}

// Read bits, starting at the next aligned bits. Note that the modulus 8 starting offset of the
// sequence must be the same as was used with WriteBits. This will be a problem with packet coalescence
// unless you byte align the coalesced packets.
bool BitStream::ReadAlignedBytes( unsigned char* output, const int numberOfBytesToRead )
{	
	if ( numberOfBytesToRead <= 0 )
		return false;
		
	// Byte align
	AlignReadToByteBoundary();

	if ( readOffset + ( numberOfBytesToRead << 3 ) > numberOfBitsUsed )
		return false;

	// Write the data
	memcpy( output, data + ( readOffset >> 3 ), numberOfBytesToRead );
	
	readOffset += numberOfBytesToRead << 3;
	
	return true;
}

// Align the next write and/or read to a byte boundary.  This can be used to 'waste' bits to byte align for efficiency reasons
void BitStream::AlignWriteToByteBoundary( void )
{
	if ( numberOfBitsUsed )
		numberOfBitsUsed += 8 - ( (( numberOfBitsUsed - 1 ) & 7) + 1 );
}

// Align the next write and/or read to a byte boundary.  This can be used to 'waste' bits to byte align for efficiency reasons
void BitStream::AlignReadToByteBoundary( void )
{
	if ( readOffset )
		readOffset += 8 - ( (( readOffset - 1 ) & 7 ) + 1 );
}

// Write numberToWrite bits from the input source
void BitStream::WriteBits( const unsigned char *input, int numberOfBitsToWrite, const bool rightAlignedBits )
{
	if (numberOfBitsToWrite<=0)
		return;
	
	AddBitsAndReallocate( numberOfBitsToWrite );
	int offset = 0;
	unsigned char dataByte;
	int numberOfBitsUsedMod8;
	
	numberOfBitsUsedMod8 = numberOfBitsUsed & 7;
	
	// Faster to put the while at the top surprisingly enough
	while ( numberOfBitsToWrite > 0 )
		//do
	{
		dataByte = *( input + offset );
		
		if ( numberOfBitsToWrite < 8 && rightAlignedBits )   // rightAlignedBits means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			dataByte <<= 8 - numberOfBitsToWrite;  // shift left to get the bits on the left, as in our internal representation
			
		// Writing to a new byte each time
		if ( numberOfBitsUsedMod8 == 0 )
			* ( data + ( numberOfBitsUsed >> 3 ) ) = dataByte;
		else
		{
			// Copy over the new data.
			*( data + ( numberOfBitsUsed >> 3 ) ) |= dataByte >> ( numberOfBitsUsedMod8 ); // First half
			
			if ( 8 - ( numberOfBitsUsedMod8 ) < 8 && 8 - ( numberOfBitsUsedMod8 ) < numberOfBitsToWrite )   // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
			{
				*( data + ( numberOfBitsUsed >> 3 ) + 1 ) = (unsigned char) ( dataByte << ( 8 - ( numberOfBitsUsedMod8 ) ) ); // Second half (overlaps byte boundary)
			}
		}
		
		if ( numberOfBitsToWrite >= 8 )
			numberOfBitsUsed += 8;
		else
			numberOfBitsUsed += numberOfBitsToWrite;
		
		numberOfBitsToWrite -= 8;
		
		offset++;
	}
	// } while(numberOfBitsToWrite>0);
}

// Set the stream to some initial data.  For internal use
void BitStream::SetData( unsigned char *input )
{
	data=input;
	copyData=false;
}

// Assume the input source points to a native type, compress and write it
void BitStream::WriteCompressed( const unsigned char* input,
	const int size, const bool unsignedData )
{
	int currentByte = ( size >> 3 ) - 1; // PCs
	
	unsigned char byteMatch;
	
	if ( unsignedData )
	{
		byteMatch = 0;
	}
	
	else
	{
		byteMatch = 0xFF;
	}
	
	// Write upper bytes with a single 1
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while ( currentByte > 0 )
	{
		if ( input[ currentByte ] == byteMatch )   // If high byte is byteMatch (0 of 0xff) then it would have the same value shifted
		{
			bool b = true;
			Write( b );
		}
		else
		{
			// Write the remainder of the data after writing 0
			bool b = false;
			Write( b );
			
			WriteBits( input, ( currentByte + 1 ) << 3, true );
			//  currentByte--;
			
			
			return ;
		}
		
		currentByte--;
	}
	
	// If the upper half of the last byte is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.  Otherwise write a 0 and the 8 bites.
	if ( ( unsignedData && ( ( *( input + currentByte ) ) & 0xF0 ) == 0x00 ) ||
		( unsignedData == false && ( ( *( input + currentByte ) ) & 0xF0 ) == 0xF0 ) )
	{
		bool b = true;
		Write( b );
		WriteBits( input + currentByte, 4, true );
	}
	
	else
	{
		bool b = false;
		Write( b );
		WriteBits( input + currentByte, 8, true );
	}
}

// Read numberOfBitsToRead bits to the output source
// alignBitsToRight should be set to true to convert internal bitstream data to userdata
// It should be false if you used WriteBits with rightAlignedBits false
bool BitStream::ReadBits( unsigned char* output, int numberOfBitsToRead, const bool alignBitsToRight )
{
	if (numberOfBitsToRead<=0)
	  return false;
	
	if ( readOffset + numberOfBitsToRead > numberOfBitsUsed )
		return false;
		
	int readOffsetMod8;
	
	int offset = 0;
	
	memset( output, 0, BITS_TO_BYTES( numberOfBitsToRead ) );
	
	readOffsetMod8 = readOffset & 7;
	
	// do
	// Faster to put the while at the top surprisingly enough
	while ( numberOfBitsToRead > 0 )
	{
		*( output + offset ) |= *( data + ( readOffset >> 3 ) ) << ( readOffsetMod8 ); // First half
		
		if ( readOffsetMod8 > 0 && numberOfBitsToRead > 8 - ( readOffsetMod8 ) )   // If we have a second half, we didn't read enough bytes in the first half
			*( output + offset ) |= *( data + ( readOffset >> 3 ) + 1 ) >> ( 8 - ( readOffsetMod8 ) ); // Second half (overlaps byte boundary)
			
		numberOfBitsToRead -= 8;
		
		if ( numberOfBitsToRead < 0 )   // Reading a partial byte for the last byte, shift right so the data is aligned on the right
		{
		
			if ( alignBitsToRight )
				* ( output + offset ) >>= -numberOfBitsToRead;
				
			readOffset += 8 + numberOfBitsToRead;
		}
		else
			readOffset += 8;
			
		offset++;
		
	}
	
	//} while(numberOfBitsToRead>0);
	
	return true;
}

// Assume the input source points to a compressed native type. Decompress and read it
bool BitStream::ReadCompressed( unsigned char* output,
	const int size, const bool unsignedData )
{
	int currentByte = ( size >> 3 ) - 1;
	
	
	unsigned char byteMatch, halfByteMatch;
	
	if ( unsignedData )
	{
		byteMatch = 0;
		halfByteMatch = 0;
	}
	
	else
	{
		byteMatch = 0xFF;
		halfByteMatch = 0xF0;
	}
	
	// Upper bytes are specified with a single 1 if they match byteMatch
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while ( currentByte > 0 )
	{
		// If we read a 1 then the data is byteMatch.
		
		bool b;
		
		if ( Read( b ) == false )
			return false;
			
		if ( b )   // Check that bit
		{
			output[ currentByte ] = byteMatch;
			currentByte--;
		}
		else
		{
			// Read the rest of the bytes
			
			if ( ReadBits( output, ( currentByte + 1 ) << 3 ) == false )
				return false;
				
			return true;
		}
	}
	
	// All but the first bytes are byteMatch.  If the upper half of the last byte is a 0 (positive) or 16 (negative) then what we read will be a 1 and the remaining 4 bits.
	// Otherwise we read a 0 and the 8 bytes
	//assert(readOffset+1 <=numberOfBitsUsed); // If this assert is hit the stream wasn't long enough to read from
	if ( readOffset + 1 > numberOfBitsUsed )
		return false;
		
	bool b;
	
	if ( Read( b ) == false )
		return false;
		
	if ( b )   // Check that bit
	{
	
		if ( ReadBits( output + currentByte, 4 ) == false )
			return false;
			
		output[ currentByte ] |= halfByteMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
	}
	else
	{
		if ( ReadBits( output + currentByte, 8 ) == false )
			return false;
	}
	
	return true;
}

// Reallocates (if necessary) in preparation of writing numberOfBitsToWrite
void BitStream::AddBitsAndReallocate( const int numberOfBitsToWrite )
{
	if (numberOfBitsToWrite <= 0)
		return;

	int newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed;
	
	if ( numberOfBitsToWrite + numberOfBitsUsed > 0 && ( ( numberOfBitsAllocated - 1 ) >> 3 ) < ( ( newNumberOfBitsAllocated - 1 ) >> 3 ) )   // If we need to allocate 1 or more new bytes
	{

		// Less memory efficient but saves on news and deletes
		newNumberOfBitsAllocated = ( numberOfBitsToWrite + numberOfBitsUsed ) * 2;
//		int newByteOffset = BITS_TO_BYTES( numberOfBitsAllocated );
		// Use realloc and free so we are more efficient than delete and new for resizing
		int amountToAllocate = BITS_TO_BYTES( newNumberOfBitsAllocated );
		if (data==(unsigned char*)stackData)
		{
			 if (amountToAllocate > BITSTREAM_STACK_ALLOCATION_SIZE)
			 {
				 data = ( unsigned char* ) malloc( amountToAllocate );

				 // need to copy the stack data over to our new memory area too
				 memcpy ((void *)data, (void *)stackData, BITS_TO_BYTES( numberOfBitsAllocated )); 
			 }
		}
		else
		{
			data = ( unsigned char* ) realloc( data, amountToAllocate );
		}
	}
	
	if ( newNumberOfBitsAllocated > numberOfBitsAllocated )
		numberOfBitsAllocated = newNumberOfBitsAllocated;
}

// Should hit if reads didn't match writes
void BitStream::AssertStreamEmpty( void )
{
	assert( readOffset == numberOfBitsUsed );
}

// Exposes the data for you to look at, like PrintBits does.
// Data will point to the stream.  Returns the length in bits of the stream.
int BitStream::CopyData( unsigned char** _data ) const
{
	*_data = new unsigned char [ BITS_TO_BYTES( numberOfBitsUsed ) ];
	memcpy( *_data, data, sizeof(unsigned char) * ( BITS_TO_BYTES( numberOfBitsUsed ) ) );
	return numberOfBitsUsed;
}

// Ignore data we don't intend to read
void BitStream::IgnoreBits( const int numberOfBits )
{
	readOffset += numberOfBits;
}

// Move the write pointer to a position on the array.  Dangerous if you don't know what you are doing!
void BitStream::SetWriteOffset( const int offset )
{
	numberOfBitsUsed = offset;
}

// If we used the constructor version with copy data off, this makes sure it is set to on and the data pointed to is copied.
void BitStream::AssertCopyData( void )
{
	if ( copyData == false )
	{
		copyData = true;
		
		if ( numberOfBitsAllocated > 0 )
		{
			unsigned char * newdata = ( unsigned char* ) malloc( BITS_TO_BYTES( numberOfBitsAllocated ) );
			
			memcpy( newdata, data, BITS_TO_BYTES( numberOfBitsAllocated ) );
			data = newdata;
		}
		
		else
			data = 0;
	}
}
void BitStream::ReverseBytes(unsigned char *input, unsigned char *output, int length)
{
	for (int i=0; i < length; i++)
		output[i]=input[length-i-1];
}

#include <util/CDataStream.h>

#include <iostream>   // for debug output

using namespace MmrCommon;

CDataStream::CDataStream(emEndian stream)
   : _buffer()
   , _read_pos(0)
   , _write_pos(0)
   , _stream_endian(stream)
   , _machine_endian(emEndian::LITTLE)
{
   long one(1);
   char e = (reinterpret_cast<char*>( &one ))[0];

   if( e == (char)1 )
   {
      _machine_endian = emEndian::LITTLE;
   }
   else
   {
      _machine_endian = emEndian::BIG;
   }
}

CDataStream::CDataStream(const char* buffer, size_t length, emEndian stream)
   : _buffer()
   , _read_pos(0)
   , _write_pos(0)
   , _stream_endian(stream)
   , _machine_endian(emEndian::LITTLE)
{
   long one(1);
   char e = (reinterpret_cast<char*>( &one ))[0];

   if( e == (char)1 )
   {
      _machine_endian = emEndian::LITTLE;
   }
   else
   {
      _machine_endian = emEndian::BIG;
   }

   SetStream( buffer, length, stream );
}
CDataStream::~CDataStream()
{
}

//const CDataStream::BufferType& CDataStream::GetBuffer() const
//{
//   return _buffer;
//}

emEndian CDataStream::GetStreamEndian() const
{
   return _stream_endian;
}

emEndian CDataStream::GetMachineEndian() const
{
   return _machine_endian;
}

size_t CDataStream::GetWritePos() const
{
   return _write_pos;
}

size_t CDataStream::GetReadPos() const
{
   return _read_pos;
}

size_t CDataStream::size() const
{
   return _buffer.size();
}

void CDataStream::clear()
{
   _write_pos = 0;
   _read_pos = 0;
   _buffer.clear();
}

bool CDataStream::empty() const
{
   return _buffer.empty();
}

const char& CDataStream::operator [](unsigned int offset) const
{
   return _buffer[_read_pos+offset];
}

// currently copies the source data.
void CDataStream::SetStream(const char* buffer, size_t length, emEndian stream)
{
   // reassign the endian
   _stream_endian = stream;

   _write_pos = length;
   _read_pos = 0;

   // resize the array
   if( _buffer.size() < length )
   {
      _buffer.resize( length );
   }

   // take ownership of the data
   // copy the data, expensive!
   //for(unsigned int i=0; i<length; ++i)
   //{
   //   _buffer[i] = buffer[i];
   //}
   memcpy(&_buffer[0], buffer, length);
}

void CDataStream::DoFlip(char* buf, size_t bufsize)
{
   if( _machine_endian == _stream_endian || bufsize<2 )
   {
      return;
   }

   // flip it, this fills back to front
   char* start = &buf[0];
   char* end = &buf[bufsize-1];
   while( start < end )
   {
      /// save the beginning of the buffer
      char temp = *start;

      /// overwrite the beginning of the buffer
      *start = *end;
      *end = temp;

      ++start;
      --end;
   }
}

void CDataStream::DoWrite(const char* buf, size_t bufsize)
{
   for(unsigned int i=0; i<bufsize; ++i)
   {
      // ignores the _write_pos value currently,
      // this should allow for values to always be appended to the end of the buffer.
      _buffer.push_back( buf[i] );
   }
}

void CDataStream::DoRead(char* ch, size_t bufsize)
{
   for(unsigned int i=0; i<bufsize; i++)
   {
      ch[i] = _buffer.at(_read_pos+i);
   }
}

// write stuff
CDataStream& CDataStream::operator <<(char c)
{
   WriteAlgorithm( c );
   return *this;
}

CDataStream& CDataStream::operator <<(unsigned char c)
{
   WriteAlgorithm( c );
   return *this;
}

CDataStream& CDataStream::operator <<(float f) 
{
   WriteAlgorithm( f );
   return *this;
}

CDataStream& CDataStream::operator <<(double d) 
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(int d) 
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(unsigned int d) 
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(long long d)
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(unsigned long long d)
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(unsigned short d)
{
   WriteAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator <<(short d)
{
   WriteAlgorithm( d );
   return *this;
}

// read stuff
CDataStream& CDataStream::operator >>(char& c)
{
   ReadAlgorithm( c );
   return *this;
}

CDataStream& CDataStream::operator >>(unsigned char& c)
{
   ReadAlgorithm( c );
   return *this;
}

CDataStream& CDataStream::operator >>(float& f)
{
   ReadAlgorithm( f );
   return *this;
}

CDataStream& CDataStream::operator >>(double& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(int& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(unsigned int& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(long long& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(unsigned long long& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(unsigned short& d)
{
   ReadAlgorithm( d );
   return *this;
}

CDataStream& CDataStream::operator >>(short& d)
{
   ReadAlgorithm( d );
   return *this;
}

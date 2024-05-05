#ifndef CDATASTREAM_H
#define CDATASTREAM_H

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif

#include "Common_def.h"
#include "util/UtilCommon.h"

#include <string>                 // for typedef, member
#include <vector>                 // for typedef, member
#include <cstdlib>                // for size_t and NULL definition
#include <cstring>                // for memcpy

BEGINE_NAMESPACE(mmrUtil)

/// the order of bytes that are on the left
enum class emEndian //计算机大小端
{
	LITTLE = 1,
	BIG = 0,
};

/// a class to support managing a network buffer.
/// the clients are responsible for managing the char buffer memory.
/// this class explicitly defines operators for expected types.
class COMMON_CLASS_API CDataStream
{
public:
    /// Setup the internal buffer's emEndian type.
    /// @param stream the emEndian type to use for the internal buffer,
    /// which will be used for network socket writes.
    CDataStream(emEndian stream);

    /// Setup the internal buffer.
    /// @param buffer the data to copy and manage.
    /// @param length the number of bytes in the buffer.
    /// @param stream the emEndian type to use for the internal buffer,
    CDataStream(const char* buffer, size_t length, emEndian stream);
    ~CDataStream();

    /// a method for reading the stored buffer data.
    /// @param offset the index distance with respect to the current read point.
    const char& operator [](unsigned int offset) const;

    /// take ownership of the data buffer.
    void SetStream(const char* buffer, size_t length, emEndian order);

    // write operations
    CDataStream& operator <<(bool c);
    CDataStream& operator <<(char c);
    CDataStream& operator <<(unsigned char c);
    CDataStream& operator <<(float c);
    CDataStream& operator <<(double c);
    CDataStream& operator <<(int c);
    CDataStream& operator <<(unsigned int c);
    CDataStream& operator <<(long long c);
    CDataStream& operator <<(unsigned long long c);
    CDataStream& operator <<(unsigned short c);
    CDataStream& operator <<(short c);

    // read operations
    CDataStream& operator >>(bool& c);
    CDataStream& operator >>(char& c);
    CDataStream& operator >>(unsigned char& c);
    CDataStream& operator >>(float& c);
    CDataStream& operator >>(double& c);
    CDataStream& operator >>(int& c);
    CDataStream& operator >>(unsigned int& c);
    CDataStream& operator >>(long long& c);
    CDataStream& operator >>(unsigned long long& c);
    CDataStream& operator >>(unsigned short& c);
    CDataStream& operator >>(short& c);

    emEndian GetStreamEndian() const;
    emEndian GetMachineEndian() const;

    size_t GetWritePos() const;
    size_t GetReadPos() const;

    size_t size() const;

    void clear();

    bool empty() const;

private:
    template<typename T, typename IterT>
    void IncrementPointer(IterT& iter)
    {
        iter += sizeof(T);
    }

    template<typename T, typename IterT>
    void DecrementPointer(IterT& iter)
    {
        iter -= sizeof(T);
    }

    /// this algorithm should only be used for primitive types,
    /// because the class size takes into account the virtual function table.
    template<typename T>
    void WriteAlgorithm(T t)
    {
        char* ch = reinterpret_cast<char*>( &t );
        DoFlip( ch , sizeof(T) );
        DoWrite( ch , sizeof(T) );
        IncrementPointer<T>( _write_pos );
    }

    /// this algorithm should only be used for primitive types,
    /// because the class size takes into account the virtual function table.
    template<typename T>
    void ReadAlgorithm(T& t)
    {
        char ch[sizeof(T)];
        DoRead( ch , sizeof(T) );
        DoFlip( ch , sizeof(T) );
        memcpy(&t, ch, sizeof(t));
        IncrementPointer<T>( _read_pos );
    }

    /// will flip the buffer if the buffer endian is different than the machine's.
    void DoFlip(char* buf, size_t bufsize);

    void DoWrite(const char* buf, size_t bufsize);

    void DoRead(char* ch, size_t bufsize);


    typedef std::vector<char> BufferType;
    //const BufferType& GetBuffer() const;

    BufferType _buffer;

    /// the location of the read/write.
    size_t _read_pos;
    size_t _write_pos;

    /// the requirement for the managed buffer
    emEndian _stream_endian;

    /// the native endian type
    emEndian _machine_endian;
};

class IDealByStream 
{
public:
	IDealByStream() = default;
	virtual ~IDealByStream() = default;

	virtual void marshal(CDataStream& dataStream) const = 0;//serialization

	virtual void unmarshal(CDataStream& dataStream) = 0;//deserialization
};

END_NAMESPACE(mmrUtil)

#if _MSC_VER
#pragma warning( pop ) 
#endif

#endif  // _dcl_dis_data_stream_h_

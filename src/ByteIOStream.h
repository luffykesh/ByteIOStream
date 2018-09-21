#ifndef _BYTE_IO_STREAM_
#define _BYTE_IO_STREAM_
#define _BYTE_IO_STREAM_VERSION 1
#include <Arduino.h>
#include "Stream.h"
#include <ByteInputStream.h>
#include <ByteOutputStream.h>

#define OUT_CALLBACK_SIGNATURE void (*out_callback)(const uint8_t*, size_t)

class ByteIOStream :public Stream,public ByteInputStream, public ByteOutputStream
{
public:
	ByteIOStream() : ByteInputStream(), ByteOutputStream()
	{}
	int read(){return ByteInputStream::read();}
	int peek(){return ByteInputStream::peek();}
	int available(){return ByteInputStream::available();}
	size_t write (uint8_t v){return ByteOutputStream::write(v);}
	size_t write(const uint8_t *buf, size_t size){return ByteOutputStream::write(buf,size);}
	operator bool(){return true;}
	void flush(){}
};
#endif
#ifndef BYTE_OUTPUT_STREAM_H
#define BYTE_OUTPUT_STREAM_H
#include <Arduino.h>
#define CALLBACK_SIGNATURE void (*callback)(const uint8_t*, size_t)

class ByteOutputStream /*: public Stream*/
{
private:
	CALLBACK_SIGNATURE;
	Stream *writeStream;
public:
	ByteOutputStream(CALLBACK_SIGNATURE)
	{
		this->callback=callback;
		writeStream=NULL;
	}
	ByteOutputStream(Stream& writeStream)
	{
		this->writeStream=&writeStream;
	}
	ByteOutputStream()
	{
		this->callback=NULL;
		writeStream=NULL;
	}
	void setWriteCallback(CALLBACK_SIGNATURE)
	{
		this->callback = callback;
		this->writeStream=NULL;
	}
	void setWriteStream(Stream& writeStream)
	{
		this->writeStream=&writeStream;
		this->callback=NULL;
	}
	void resetWriteDestination()
	{
		this->writeStream=NULL;
		this->callback=NULL;
	}
	size_t write (uint8_t);
	size_t write(const uint8_t *buf, size_t size);
	/*operator bool(){return true;}
	int read(){return -1;}
	int peek(){return -1;}
	void flush(){}
	int available(){return 0;}*/
};
#endif
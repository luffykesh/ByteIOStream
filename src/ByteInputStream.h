#ifndef BYTE_INPUT_STREAM_H
#define BYTE_INPUT_STREAM_H
#include <Arduino.h>
class ByteInputStream /*: public Stream*/
{
private:
	const uint8_t *readBuffer;
	size_t bufferSize;
	size_t readPos;
	Stream *readStream;
public:
	ByteInputStream(const uint8_t *buf,size_t size,size_t offset=0)
	{
		setReadSource(buf,offset,size);
	}
	ByteInputStream(Stream& readStream)
	{
		this->readStream=&readStream;
	}
	ByteInputStream()
	{
		readBuffer = NULL;
		bufferSize = 0;
		readPos=0;
		readStream=NULL;
	}
	bool hasReadBuffer();
	bool hasReadStream();
	const uint8_t * getReadBuffer();
	Stream * getReadStream();
	void setReadSource(const uint8_t *buf,size_t size,size_t offset=0);
	void setReadSource(Stream& readStream);
	void resetReadSource();
	bool seek(int count);
	int available();
	int peek();
	int read();
	/*virtual size_t 	write (uint8_t){return 0;}
	virtual size_t write (const uint8_t*, size_t){return 0;}
	virtual void flush(){}*/
};
#endif
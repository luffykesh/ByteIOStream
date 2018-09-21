#include "ByteInputStream.h"
#include <Arduino.h>

void ByteInputStream::setReadSource(const uint8_t *buf,size_t size,size_t offset)
{
	readBuffer = buf + offset;
	bufferSize = size;
	readPos=0;
	readStream=NULL;
}
void ByteInputStream::setReadSource(Stream& readStream)
{
	this->readStream=&readStream;
	readBuffer=NULL;
	readPos=bufferSize=0;
}
void ByteInputStream::resetReadSource()
{
	readStream=NULL;
	readBuffer=NULL;
	readPos=bufferSize=0;
}
int ByteInputStream::available()
{
	if(readBuffer)
	{
		return bufferSize-readPos;
	}
	else if(readStream)
	{
		return readStream->available();
	}
	return -1;
}
int ByteInputStream::peek()
{
	if(readBuffer)
	{
		if(readPos<bufferSize)
			return readBuffer[readPos];
	}
	else if(readStream)
	{
		return readStream->peek();
	}
	return -1;
}
int ByteInputStream::read()
{
	if(readBuffer)
	{
		if(readPos<bufferSize)
			return readBuffer[readPos++];
	}
	else if(readStream)
	{
		return readStream->read();
	}
	return -1;
}
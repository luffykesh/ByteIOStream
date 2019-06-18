#include "ByteInputStream.h"
#include <Arduino.h>

bool ByteInputStream::hasReadBuffer()
{
	return readBuffer!=NULL;
}
bool ByteInputStream::hasReadStream()
{
	return readStream!=NULL;
}
const uint8_t * ByteInputStream::getReadBuffer()
{
	if(readBuffer)
		return readBuffer;
	return NULL;
}
Stream * ByteInputStream::getReadStream()
{
	if(readStream)
		return readStream;
	return NULL;
}
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
bool ByteInputStream::seek(int count)
{
	if(count==0)
		return true;
	if(readBuffer)
	{
		if(count>=0)
		{
			if(available()<count)
				readPos = bufferSize;
			else
				readPos+=count;
		}
		else
		{
			//supress sign-compare warning because here count is negative and hence -count will be positive
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wsign-compare"
			if(-count>readPos)
			#pragma GCC diagnostic pop
				readPos=0;
			else
				readPos+=count;
		}
	}
	else if(readStream)
	{
		if(count>=0)
		{
			while(count--) 
				read();
		}
		else 
			return false;
	}
	return true;
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
	return 0;
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
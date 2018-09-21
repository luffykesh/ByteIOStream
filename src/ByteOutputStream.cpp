#include "ByteOutputStream.h"
#include <Arduino.h>

size_t ByteOutputStream::write(const uint8_t val)
{
	if(callback)
	{
		callback(&val,1);
		return sizeof(val);
	}
	else if(writeStream)
	{
		return writeStream->write(val);
	}
	return 0;
}
size_t ByteOutputStream:: write(const uint8_t *buf, size_t size)
{
	if(callback)
	{
		callback(buf,size);
		return size;
	}
	else if(writeStream)
	{
		return writeStream->write(buf,size);
	}
	return 0;
}
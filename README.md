# ByteIOStream

Get Stream like API with byte/char buffers in Arduino.

Useful when working with Streams, and need to use static array for same task, like parsing large data from a source

## Data source (Reading from stream)

The library provides two methods to set data source to read from.

1. ### setInputSource(uint8_t\* buffer,size_t size, size_t offset)
    This method adds an array as the input source, to read from when calls to read are made()
    Each subsequent byte is returned on call to read()

2. ### setInputSource(Stream& readStream)
    This method adds a Stream to read from, when calls to read() are made.
3. ### void resetReadSource();
	This method resets any read source set. Any subsequent calls to read will return -1.

4. ### bool seek(int count);
	Move the read position ahead or back.
	Positive count skips `count` number of bytes, and negative count makes `count` bytes available to read again.

	Returns true on success else false.
	**Backward movement is possible only if the source is a buffer.**
		
    **Note: Only one input source is supported. Adding another, will discard the older source.**
		
## Writing to Stream
To get the data that is written to stream, a callback/Stream shoud be set with:

1. ### setWriteCallback(< function name >);
	The signature of the functions shoud be void foo(uint8_t\*,size_t).
	This function will be called when something will be printed to the stream.
2. ### setWriteStream(Stream& writeStream)
	The received data will be sent to the specified stream, instread of calling a function.
3. ### void resetWriteDestination()
	This method resets the write destination. Any subsequent writes to the stream will be discarded.
	
	**Only one write destination can be used. Using another, will discard the older write destination.**

**All other functions of the Stream class such as,parseInt(),read(),peek().. are supported (kudos to Inheritance).**

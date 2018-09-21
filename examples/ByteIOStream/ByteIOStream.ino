/*
Gives Stream like api with bytes.
*/
#include <ByteIOStream.h>
ByteIOStream iostream;
void setup()
{
	Serial.begin(9600);
	delay(1000);
	//attach a callback function for when something is written to the stream
	iostream.setWriteCallback(recv_cb);
}
void loop()
{
	if(Serial.available())
	{
		//printing to Stream... will trigger the write callback recv_cb()
		iostream.print(Serial.readString()); 
	}
}

void recv_cb(const uint8_t* arr,size_t size)
{
	Serial.println("Callback: ");
	iostream.setReadSource(arr,size); //set received data as read source
	while(iostream.available())
	{
		Serial.print((char)iostream.read()); //read bytes consecutively
	}
}
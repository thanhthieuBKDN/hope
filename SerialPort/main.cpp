/***
 * This example expects the serial port has a loopback on it.
 *
 * Alternatively, you could use an Arduino:
 *
 * <pre>
 *  void setup() {
 *    Serial.begin(<insert your baudrate here>);
 *  }
 *
 *  void loop() {
 *    if (Serial.available()) {
 *      Serial.write(Serial.read());
 *    }
 *  }
 * </pre>
 */

#include <string>
#include <iostream>
#include <cstdio>

 // OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds); // 100 ms
#else
	usleep(milliseconds * 1000); // 100 ms
#endif
}

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while (iter != devices_found.end())
	{
		serial::PortInfo device = *iter++;

		printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
			device.hardware_id.c_str());
	}
}

void print_usage()
{
	cerr << "Usage: test_serial {-e|<serial port address>} ";
	cerr << "<baudrate> [test string]" << endl;
}

int main()
{
	serial::Serial my_serial("COM7", 9600, serial::Timeout::simpleTimeout(1000));
	cout << "Is the serial port open?";
	if (my_serial.isOpen())
		cout << " Yes." << endl;
	else
		cout << " No." << endl;
	int count = 0;
	string test_string = "bgghuhhhhuihuiuhu";
	UINT8 *array = new UINT8[5] { 0x48, 0x65, 0x9C, 0x6C, 0x6A };
	size_t bytes_wrote = my_serial.write(array, 5);
	Sleep(5000);
	string result = my_serial.read(10);
	while (count < 3) {
		//size_t bytes_wrote = my_serial.write(test_string);
		

		cout << "Iteration: " << count << ", Bytes written: ";
		cout << bytes_wrote << ", Bytes read: ";
		cout << result.length() << ", String read: " << result << endl;

		count += 1;
	}


	
	
	




    // Clean up the HDEVINFO set

   
	return 0;
}
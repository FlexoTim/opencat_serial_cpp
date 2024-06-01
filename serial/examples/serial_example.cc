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

 // OS Specific sleep
#ifdef _WIN32
#include "windows.h"
#else
#include <unistd.h>
#endif

#include "serial/serial.h"

#include <string>
#include <iostream>
#include <cstdio>

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

using namespace serial;

namespace internal {

	void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
		Sleep(milliseconds); // 100 ms
#else
		usleep(milliseconds * 1000); // 100 ms
#endif
	}

	void enumerate_ports()
	{
		vector<PortInfo> devices_found{ list_ports() };
		vector<PortInfo>::iterator iter{ devices_found.begin() };
		while (iter != devices_found.end())
		{
			PortInfo device{ *iter++ };
			cout << "(" << device.port
				<< ", " << device.description
				<< ", " << device.hardware_id
				<< ")\n";
		}
	}

	void print_usage()
	{
		cerr << "Usage: test_serial {-e|<serial port address>}"
			" <baudrate> [test string]" << endl
			<< "Library version: " << OCS_VERSION << endl
			;
	}

	int run(int argc, char** argv)
	{
		if (argc < 2) {
			print_usage();
			return 0;
		}

		// Argument 1 is the serial port or enumerate flag
		string port{ argv[1] };

		if ("-e" == port) {
			enumerate_ports();
			return 0;
		}
		
		if (argc < 3) {
			print_usage();
			return 1;
		}

		// Argument 2 is the baudrate
		unsigned long baud{ 0 };
#if defined(WIN32) && !defined(__MINGW32__)
		sscanf_s(argv[2], "%lu", &baud);
#else
		sscanf(argv[2], "%lu", &baud);
#endif

		// port, baudrate, timeout in milliseconds
		Serial my_serial(port, baud, Timeout::simpleTimeout(1000));
		cout << "Is the serial port open?"
			<< (my_serial.isOpen()
				? " Yes."
				: " No.")
			<< endl;

		// Get the Test string
		int count{ 0 };
		string test_string{
			(4 == argc)
			? argv[3]
			: "Testing."
		};

		// Test the timeout, there should be 1 second between prints
		cout << "Timeout == 1000ms, asking for 1 more byte than written." << endl;
		while (count < 10) {
			size_t bytes_wrote{ my_serial.write(test_string) };
			string result{ my_serial.read(test_string.length() + 1) };
			cout << "Iteration: " << count
				<< ", Bytes written: " << bytes_wrote
				<< ", Bytes read: " << result.length()
				<< ", String read: " << result << endl;

			count += 1;
		}

		// Test the timeout at 250ms
		my_serial.setTimeout(Timeout::max(), 250, 0, 250, 0);
		count = 0;
		cout << "Timeout == 250ms, asking for 1 more byte than written." << endl;
		while (count < 10) {
			size_t bytes_wrote{ my_serial.write(test_string) };
			string result{ my_serial.read(test_string.length() + 1) };

			cout << "Iteration: " << count
				<< ", Bytes written: " << bytes_wrote
				<< ", Bytes read: " << result.length()
				<< ", String read: " << result << endl;

			count += 1;
		}

		// Test the timeout at 250ms, but asking exactly for what was written
		count = 0;
		cout << "Timeout == 250ms, asking for exactly what was written." << endl;
		while (count < 10) {
			size_t bytes_wrote{ my_serial.write(test_string) };
			string result{ my_serial.read(test_string.length()) };

			cout << "Iteration: " << count
				<< ", Bytes written: " << bytes_wrote
				<< ", Bytes read: " << result.length()
				<< ", String read: " << result << endl;

			count += 1;
		}

		// Test the timeout at 250ms, but asking for 1 less than what was written
		count = 0;
		cout << "Timeout == 250ms, asking for 1 less than was written." << endl;
		while (count < 10) {
			size_t bytes_wrote{ my_serial.write(test_string) };
			string result{ my_serial.read(test_string.length() - 1) };

			cout << "Iteration: " << count
				<< ", Bytes written: " << bytes_wrote
				<< ", Bytes read: " << result.length()
				<< ", String read: " << result << endl;

			count += 1;
		}

		return 0;
	}

}	// namespace internal

int main(int argc, char** argv) {
	try {
		return internal::run(argc, argv);
	}
	catch (exception& e) {
		cerr << "Unhandled Exception: " << e.what() << endl;
	}
}

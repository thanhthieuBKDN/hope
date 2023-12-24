#if defined(_WIN32)

#include "Serial.h"
#include <tchar.h>
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <cstring>
#include <devguid.h>
#include <SetupAPI.h>

using serial::PortInfo;
using std::vector;
using std::string;

static const DWORD port_name_max_length = 256;
static const DWORD friendly_name_max_length = 256;
static const DWORD hardware_id_max_length = 256;

std::string utf8_encode(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

vector <PortInfo> serial::list_ports()
{
	vector<PortInfo> devices_found = {};
	
	//HDEVINFO device_info_set = SetupDiGetClassDevs();


	return devices_found;

}


#endif // #if defined(_WIN32)


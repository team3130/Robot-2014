#include "Logger.h"
#include <sstream>
#include <iomanip>
#include "stat.h"
#include "stdioLib.h"
#include "vxWorks.h"
#include "sockLib.h"
#include "inetLib.h"
#include "hostLib.h"
#include "Driverstation.h"

int Logger::file_exists (char *filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}

Logger::Logger() {
	// Remove old match data if present
	if (file_exists(LOG_FILE_OLD)) {
		remove(LOG_FILE_OLD);
	}
	
	// Rename match data to old match data if present
	if (file_exists(LOG_FILE)) {
		rename(LOG_FILE, LOG_FILE_OLD);
	}
	
	m_file = fopen(LOG_FILE, "w");
	
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in sAd;
	sAd.sin_family = AF_INET;
	sAd.sin_port = htons(LOG_PORT);
	sAd.sin_len = (u_char)sizeof(sAd);
	sAd.sin_addr.s_addr = inet_addr(LOG_SERVER);
	sAd.sin_addr.s_addr = hostGetByName(LOG_SERVER);
	
	connect(m_socket, (struct sockaddr *) &sAd, sizeof(sAd));
	
}

Logger* Logger::GetInstance() {
	if (m_logger == NULL) {
		m_logger = new Logger();
	}
	return m_logger;
}

char Logger::getDataType(DataType dtype) {
	switch (dtype) {
	case _Float:
		return 'F';
	case _Double:
		return 'D';
	case _String:
		return 'T';
	case _Char:
		return 'C';
	case _Short:
		return 'S';
	case _Int:
		return 'I';
	case _Long:
		return 'L';
	}
	return 0;
}

char Logger::getPacketType(PacketType ptype) {
	switch (ptype) {
	case Update:
		return 'U';
	}
	return 0;
}

void Logger::update(const PacketType ptype, const DataType dtype, const char* key,
		const char* value) {
	std::stringstream packet;
	packet << getPacketType(ptype) << getDataType(dtype) << ' ' 
		<< key << ' ' << value << ' ' << std::setprecision(2) 
		<< DriverStation::GetInstance()->GetMatchTime();
	fprintf(m_file, "%s\n", packet.str().c_str());
	
	
	struct request 
	{ 
	    int reply;                         /* TRUE = request reply from server */  
	    int msgLen;                        /* length of message text */ 
	    const char *message;               /* message buffer */  
	};
	
	struct request r;
	r.message = packet.str().c_str();
	r.msgLen = sizeof(r.message);
	r.reply = FALSE;
	
	write(m_socket, (char *) &r, sizeof(r));
	
}

void Logger::update_float(const char* key, const float value) {
	char buf[16];  // Should fit  Max size = 15?
	snprintf(buf, 16, "%f.6", value);
	update(Update, _Float, key, buf);
}
void Logger::update_double(const char* key, const double value) {
	char buf[20];  // Should fit  Max size = 19?
	snprintf(buf, 20, "%f.10", value);
	update(Update, _Double, key, buf);
}
void Logger::update_string(const char* key, const char* value) {
	update(Update, _String, key, value);
}
void Logger::update_char(const char* key, const char value) {
	char buf[5];  // Should fit  Max size = 4?
	snprintf(buf, 5, "%d", value);
	update(Update, _Char, key, buf);
}
void Logger::update_short(const char* key, const short value) {
	char buf[7];  // Should fit  Max size = 6?
	snprintf(buf, 7, "%d", value);
	update(Update, _Short, key, buf);
}
void Logger::update_int(const char* key, const int value) {
	char buf[12];  // Should fit  Max size = 11?
	snprintf(buf, 12, "%d", value);
	update(Update, _Int, key, buf);
}
void Logger::update_long(const char* key, const long value) {
	char buf[21];  // Should fit  Max size = 20?
	snprintf(buf, 21, "%ld", value);
	update(Update, _Long, key, buf);
}

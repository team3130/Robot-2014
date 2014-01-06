#include <cstdio>

#define LOG_PORT 1150
#define LOG_SERVER "10.31.30.9"
#define LOG_FILE "match.log"
#define LOG_FILE_OLD "old_match.log"

class Logger {
public:
	static Logger* GetInstance();
	
	void update_float(const char* key, const float value);
	void update_double(const char* key, const double value);
	void update_string(const char* key, const char* value);
	void update_char(const char* key, const char value);
	void update_short(const char* key, const short value);
	void update_int(const char* key, const int value);
	void update_long(const char* key, const long value);
	
private:
	
	enum DataType {
		_Float,
		_Double,
		_String,
		_Char,
		_Short,
		_Int,
		_Long,
	};
	
	enum PacketType {
		Update,
	};
	
	Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	
	int file_exists (char *filename);
	
	char getDataType(DataType dtype);
	char getPacketType(PacketType ptype);
	
	void update(PacketType ptype, DataType dtype, const char* key, const char* value);
	
	static Logger* m_logger;
	FILE* m_file;
	int m_socket;
};

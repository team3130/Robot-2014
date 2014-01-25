#include <cstdio>
#include "WPILib.h"

#define LOG_PORT 1150
#define LOG_SERVER "10.31.30.9"
#define LOG_FILE "match.log"
#define LOG_FILE_OLD "old_match.log"

class Logger {
public:
	static Logger* GetInstance();
	
	void update_number(const char* name, double value);
	void update_string(const char* name, const char* value);
	void update_boolean(const char* name, bool value);
	void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew); // Implements ITableListener
	
private:
	
	Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	
	static Logger* m_logger;
	FILE* m_file;
	NetworkTable* m_table;
};

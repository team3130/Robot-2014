#include "Logger.h"
#include "Driverstation.h"
#include "stat.h"

int file_exists (char *filename)
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
	
	NetworkTable::SetTeam(3130);
	NetworkTable::SetServerMode();
	m_table = NetworkTable::GetTable("log");
}

Logger* Logger::GetInstance() {
	if (m_logger == NULL) {
		m_logger = new Logger();
	}
	return m_logger;
}

void Logger::update_number(const char* name, double value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutNumber(buf, value);
	
	fprintf(m_file, "N %s %f.10\n", name, value);
}

void Logger::update_string(const char* name, const char* value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutString(buf, value);
	
	fprintf(m_file, "S %s %s\n", name, value);
}

void Logger::update_boolean(const char* name, bool value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutBoolean(buf, value);
	
	fprintf(m_file, "B %s %s\n", name, value ? "true" : "false");
}






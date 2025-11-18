#pragma once
#include <QString>

class Logger {
public:
	static Logger* get_instance() {
		if (!_instance) {
			_instance = new Logger();
		}
		return _instance;
	}

	void add_log(const QString& log) {
		_logs += log;
		_logs += "\n";
	}

	QString get_logs() const {
		return _logs;
	}

	void reset() {
		_logs = "";
	}

private:
	Logger() : _logs("") {};
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

private:
	static Logger* _instance;
	QString _logs;
};
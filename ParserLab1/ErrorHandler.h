#pragma once
#include <stdexcept>
#include <QString>

namespace ErrorHandler {
	class SyntaxError : public std::runtime_error {
	public:
		SyntaxError(const QString& message, int position)
			: std::runtime_error(QString("%1 at position %2").arg(message).arg(position).toStdString()) {}
	};
}
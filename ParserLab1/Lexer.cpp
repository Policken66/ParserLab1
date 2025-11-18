#include "Lexer.h"
#include "ErrorHandler.h"


Lexer::Lexer(const QString& input) : _input(input), _position(0) {
	if (!input.isEmpty()) {
		_current_char = input[0];
	}
	else {
		_current_char = QChar(); 
	}
}

void Lexer::_advance() {
	++_position;
	if (_position < _input.length()) {
		_current_char = _input[_position];
	}
	else {
		_current_char = QChar();
	}
}

QVector<Token> Lexer::tokenize() {
	QVector<Token> tokens;

	while (!_current_char.isNull()) {
		_skip_whitespace();

		if (_current_char.isNull()) {
			break;
		}

		int token_start = _position;


		// Проверяем различные варианты символов
		if (_current_char.isLetter() || _current_char == '_') {
			QString identifier = _read_identifier();
			if (!identifier.isEmpty()) {
				if (identifier == "cout") {
					tokens.append(Token(TokenType::COUT, identifier, token_start));
				}
				else {
					tokens.append(Token(TokenType::IDENTIFIER, identifier, token_start));
				}
			}
		} 
		else if (_current_char.isDigit()) {
			QString number = _read_number();
			if (!number.isEmpty()) {
				tokens.append(Token(TokenType::NUMBER, number, token_start));
			}
		}
		else if (_current_char == '"') {
			_advance();
			QString str = _read_string();
			tokens.append(Token(TokenType::STRING, str, token_start));
		}
		else if (_current_char == '<') {
			if (_position + 1 < _input.length() && _input[_position + 1] == '<') {
				tokens.append(Token(TokenType::OPERATOR, "<<", _position));
				_advance();
				_advance();
			}
			else {
				throw ErrorHandler::SyntaxError("Expected '<<' operator", _position);
			}
		}
		else if (_current_char == ';') {
			tokens.append(Token(TokenType::SEMICOLON, ";", _position));
			_advance();
		}
		else {
			throw ErrorHandler::SyntaxError(QString("Unexpected character: '%1'").arg(_current_char), _position);
		}
	}

	tokens.append(Token(TokenType::END, "", _position));

	return tokens;
}

void Lexer::_skip_whitespace() {
	while (!_current_char.isNull() && _current_char.isSpace()) {
		_advance();
	}
}

QString Lexer::_read_identifier() {
	QString result;

	while (!_current_char.isNull() && (_current_char.isLetterOrNumber() || _current_char == '_')) {
		result += _current_char;
		_advance();
	}

	return result;
}

QString Lexer::_read_number() {
	QString result;
	bool has_dot = false;

	while (!_current_char.isNull() && (_current_char.isDigit() || _current_char == '.')) {
		if (_current_char == '.') {
			if (has_dot) break;
			has_dot = true;
		}
		
		result += _current_char;
		_advance();
	}

	return result;
}

QString Lexer::_read_string() {
	QString result;

	while (!_current_char.isNull() && _current_char != '"') {
		result += _current_char;
		_advance();
	}
	
	if (_current_char == '"') {
		_advance();
	}
	else {
		// обработка ошибки должна быть
		throw ErrorHandler::SyntaxError("Unclosed string literal", _position);
	}

	return result;
}
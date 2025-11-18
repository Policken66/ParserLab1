#include "Parser.h"
#include <ErrorHandler.h>
#include <Logger.h>

Parser::Parser(const QVector<Token>& tokens): _tokens(tokens), _current_token_index(0) {
	if (!_tokens.isEmpty()) {
		_current_token = _tokens[0];
	}
	else {
		_current_token = Token(TokenType::END, "", 0);
	}
}

void Parser::_advance() {
	++_current_token_index;
	if (_current_token_index < _tokens.size()) {
		_current_token = _tokens[_current_token_index];
	}
	else {
		_current_token = Token(TokenType::END, "", _current_token.position);
	}
}

// Проверка и "потребление" ожидаемого токена
void Parser::_eat(TokenType expected_type) {
	if (_current_token.type == expected_type) {
		qDebug() << "Consumed token:" << TokenUtils::tokenType_to_string(_current_token.type) << _current_token.value;
		_advance();
	}
	else {
		throw ErrorHandler::SyntaxError(QString("Expected %1 but found %2")
								  .arg(TokenUtils::tokenType_to_string(expected_type))
								  .arg(TokenUtils::tokenType_to_string(_current_token.type)),
								  _current_token.position);
	}
}

// Item -> IDENTIFIER | STRING | NUMBER
void Parser::_parse_Item() {
	qDebug() << "Parsing item at position" << _current_token.position;
	
	switch (_current_token.type) {
		case TokenType::IDENTIFIER:
			_eat(TokenType::IDENTIFIER);
			break;
		case TokenType::STRING:
			_eat(TokenType::STRING);
			break;
		case TokenType::NUMBER:
			_eat(TokenType::NUMBER);
			break;
		default:
			throw ErrorHandler::SyntaxError(QString("Expected identifier, string or number"),
									  _current_token.position);
	}
}


// Output -> cout << Item (<< Item)*
void Parser::_parse_Output() {
	qDebug() << "Parsing output statement at position" << _current_token.position;

	_eat(TokenType::COUT);

	_eat(TokenType::OPERATOR);
	_parse_Item();

	while (_current_token.type == TokenType::OPERATOR) {
		_eat(TokenType::OPERATOR);
		_parse_Item();
	}
}

// S -> Output ;
void Parser::_parse_S() {
	qDebug() << "Parsing statement";

	_parse_Output();
	_eat(TokenType::SEMICOLON);

	// Проверяем, что дошли до конца
	if (_current_token.type != TokenType::END) {
		throw ErrorHandler::SyntaxError(QString("Expected end of input"),
								  _current_token.position);

	}
}

// Основной метод парсинга
bool Parser::parse() {
	try {
		_parse_S();
		qDebug() << "SUCCESS: Parsing completed successfully!";
		return true;
	}
	catch (const ErrorHandler::SyntaxError& e) {
		qDebug() << "ERROR: Parsing failed:" << e.what();
		return false;
	}
}
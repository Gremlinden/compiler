#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <fstream>

enum LexemType
{
	H,
	ID,
	ERROR,
	KEYWORD,
	NUM,
	DELIM,
	OPERATOR,
	PLUS,
	MINUS,
};

enum Num_E
{
	E,
	PLUS_MINUS,
};


static std::map<LexemType, std::string> lexIdToName = {
{LexemType::ID, "ID"},
{LexemType::ERROR, "ERROR"},
{LexemType::KEYWORD, "Keyword"},
{LexemType::NUM, "Number"},
{LexemType::DELIM, "Delimiter"},
{LexemType::OPERATOR, "Operator"} };

class Lex
{
public:
	int m_line;
	LexemType m_type;
	std::string m_value;
	Lex(int line, LexemType type, std::string value);
};

std::vector<Lex> parseCode(std::istream& code);

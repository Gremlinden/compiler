#include "lexer.h"

const std::set<std::string>keywords = { "int", "double", "char", "long", "short" };
const std::set<char> space = { ' ', '\n', '\t', '\0', '\r' };
const std::set<char> operatr = {'=', '*', '/', '%', '&', '~' , '!' };
const std::set<char> deli = { ';', '(', ')' };
const std::set<char> es = { 'e', 'E' };

bool isSpace(char c)
{
	return space.count(c);
}
bool isKeywords(std::string& c)
{
	return keywords.count(c);
}
bool isOperatr(char c)
{
	return operatr.count(c);
}
bool isDeli(char c)
{
	return deli.count(c);
}
bool isE(char c)
{
	return es.count(c);
}

Lex::Lex(int line, LexemType type, std::string value)
{
	m_line = line;
	m_type = type;
	m_value = value;
}

std::vector<Lex> parseCode(std::istream& code)
{
	std::vector<Lex> lexems;
	std::string buff;
	LexemType state = LexemType::H;
	Num_E state_num = Num_E::E;


	int line_num = 1;
	bool dot = false;
	bool e = false;
	char c = code.get();
	bool Finished = false;
	bool LastStep = false;
	while (!Finished)
	{
		switch (state)
		{
		case H:
			if (isalpha(c) || c == '_')
			{
				buff = c;
				state = LexemType::ID;
			}
			else if (isdigit(c) || c == '.')
			{
				if (c == '.')
					dot = true;
				buff = c;
				state = LexemType::NUM;
			}
			else if (isDeli(c))
			{
				buff = c;
				lexems.push_back(Lex(line_num, LexemType::DELIM, buff));
				state = LexemType::H;
			}
			else if (c == '+')
			{
				buff = c;
				state = LexemType::PLUS;
			}
			else if (c == '-')
			{
				buff = c;
				state = LexemType::MINUS;
			}
			else if (isOperatr(c))
			{
				buff = c;
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
			}
			else if (isspace(c))
				break;
			else
			{
				buff = c;
				state = LexemType::ERROR;
			}

			break;

		case ERROR:
			if (!isSpace(c))
			{
				if (c == ';')
				{
					lexems.push_back(Lex(line_num, LexemType::ERROR, buff));
					buff = c;
					lexems.push_back(Lex(line_num, LexemType::DELIM, buff));
					state = LexemType::H;
					break;
				}
				buff += c;
			}
			else
			{
				lexems.push_back(Lex(line_num, LexemType::ERROR, buff));
				state = LexemType::H;
				continue;
			}
			break;
		case ID:
			if (isKeywords(buff) && c == ')')
			{
				lexems.push_back(Lex(line_num, LexemType::KEYWORD, buff));
				state = LexemType::H;
				continue;
			}
			else if (isalpha(c) || c == '_' || isdigit(c))
			{
				buff += c;
			}
			else if (c == ';')
			{
				lexems.push_back(Lex(line_num, LexemType::ID, buff));
				state = LexemType::H;
				continue;
			}
			else if (isSpace(c))
			{
				if (isKeywords(buff))
					lexems.push_back(Lex(line_num, LexemType::KEYWORD, buff));
				else
					lexems.push_back(Lex(line_num, LexemType::ID, buff));

				state = LexemType::H;
			}
			else
			{
				state = LexemType::ERROR;
				continue;
			}
			break;
		case NUM:
			if (e)
			{
				switch (state_num)
				{
				case E:
					if (isdigit(c))
					{
						buff += c;

					}
					else if (c == '+' || c == '-')
					{
						buff += c;
						state_num = Num_E::PLUS_MINUS;
					}
					else if (isspace(c))
					{
						if (!isE(buff[buff.size() - 1]))
						{
							e = false;
							lexems.push_back(Lex(line_num, LexemType::NUM, buff));
							state = LexemType::H;
							dot = false;
						}
						else
						{
							e = false;
							state = LexemType::ERROR;
							dot = false;
							continue;

						}
					}
					else if (c == ';')
					{
						if (!isE(buff[buff.size() - 1]))
						{
							e = false;
							lexems.push_back(Lex(line_num, LexemType::NUM, buff));
							state = LexemType::H;
							dot = false;
							continue;
						}
						else
						{
							e = false;
							state = LexemType::ERROR;
							dot = false;
							continue;
						}
					}
					else
					{
						e = false;
						state = LexemType::ERROR;
						dot = false;
						continue;
					}
					break;
				case PLUS_MINUS:
					if (isdigit(c))
					{
						buff += c;
					}
					else if (isspace(c))
					{
						if (!isE(buff[buff.size() - 1]))
						{
							e = false;
							lexems.push_back(Lex(line_num, LexemType::NUM, buff));
							state = LexemType::H;
							state_num = Num_E::E;
							dot = false;
						}
						else
						{
							e = false;
							state = LexemType::ERROR;
							state_num = Num_E::E;
							dot = false;
							continue;
						}
					}
					else if (c == ';')
					{
						e = false;
						lexems.push_back(Lex(line_num, LexemType::NUM, buff));
						state = LexemType::H;
						state_num = Num_E::E;
						dot = false;
						continue;
					}
					else
					{
						e = false;
						buff += c;
						state = LexemType::ERROR;
						state_num = Num_E::E;
						dot = false;
					}
					break;
				}
			}
			else if (isdigit(c))
			{
				buff += c;
			}
			else if (isE(c) && !e)
			{
				e = true;
				buff += c;
			}
			else if (dot && c == '.')
			{
				buff += c;
				state = LexemType::ERROR;
			}
			else if (c == '.' && !dot)
			{
				dot = true;
				buff += c;
			}
			else if (isSpace(c))
			{
				lexems.push_back(Lex(line_num, LexemType::NUM, buff));
				state = LexemType::H;
				dot = false;
			}
			else if (c == ';')
			{
				lexems.push_back(Lex(line_num, LexemType::NUM, buff));
				state = LexemType::H;
				dot = false;
				continue;
			}
			else {
				state = LexemType::ERROR;
				dot = false;
				continue;
			}
			break;
		case PLUS:
			if (c == '+')
			{
				buff += c;
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;

			}
			else if (isdigit(c) || c == '.')
			{
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
				continue;
			}
			else
			{
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
				continue;

			}
			break;
		case MINUS:
			if (c == '-')
			{
				buff += c;
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
			}
			else if (isdigit(c) || c == '.')
			{
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
				continue;
			}
			else
			{
				lexems.push_back(Lex(line_num, LexemType::OPERATOR, buff));
				state = LexemType::H;
				continue;
			}
			break;
		}

		if (c == '\n')
			line_num++;
		if (LastStep)
		{
			Finished = true;
		}
		else
		{
			c = code.get();
			if (code.eof())
			{
				c = '\n';
				LastStep = true;
			}
		}
	}

	if (state != LexemType::H)
	{
		lexems.push_back(Lex(line_num, LexemType::ERROR, buff));
	}
	return lexems;
}

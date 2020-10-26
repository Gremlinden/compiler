#include "lexer.h"
#include <string>
#include <fstream>
#include <iostream>

void printLexems(std::vector<Lex> lexems)
{
	for(auto k: lexems)
	{
		std::cout << k.m_line << "\t" << k.m_value << "\t" << lexIdToName[k.m_type] << std::endl;
	}
}

void saveresul(const std::string& name, std::vector<Lex> lexems)
{
	std::ofstream file(name);
	file << "\"line\",\"type\",\"value\"" << std::endl;
	for (auto k : lexems)
	{
		file << "\"" << k.m_line << "\",\"" << k.m_value << "\",\"" << lexIdToName[k.m_type] << "\"" << std::endl;
	}
	file.close();
}

int main()
{
	std::ifstream numbersFile("testNumber.txt");
	std::vector<Lex> lexerResult = parseCode(numbersFile);
	printLexems(lexerResult);
	saveresul("result.csv", lexerResult);
}
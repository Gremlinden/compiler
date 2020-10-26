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
	file << "\"¹\",\"type\",\"text\"" << std::endl;
	for (auto k : lexems)
	{
		file << "\"" << k.m_line << "\",\"" << k.m_value << "\",\"" << lexIdToName[k.m_type] << "\"" << std::endl;
	}
	file.close();
}

int main()
{
	std::ifstream numbersFile("test.txt");
	std::vector<Lex> lexerResult = parseCode(numbersFile);
	printLexems(lexerResult);
	saveresul("result.csv", lexerResult);
}
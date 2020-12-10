from classes.stateMachine import StateMachine


def defineLexemsFromFile(filename=''):
    file = open('tests/' + filename, 'r')
    sm = StateMachine()
    allLex = []
    for index, chunk in enumerate(iter(lambda: file.readline(), '')):
        for symbol in chunk:
            lexems = sm.handleSymbol(symbol)
            if lexems is None:
                continue
            for lexem in lexems:
                lexem.line = index + 1
            allLex += lexems

    lexems = sm.handleSymbol('\n')
    if lexems is not None:
        for lexem in lexems:
            lexem.line = index + 1
        allLex += lexems

    f = open('syntax/settings/result.csv', 'w')
    f.write('line,type,value,attribute\n')
    f.write("\n".join(map(str, allLex)))
    f.close()

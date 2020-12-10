from classes.lexem import Lexem
from syntax_settings import map_lexem_to_term, Terminals


class Parser:
    __slots__ = ['__file']

    def __init__(self, file):
        self.__file = file
        self.__file.readline()

    def next_lexem(self):
        line = self.__file.readline()
        if line == '':
            lexem = Lexem('', '', '')
        else:
            lexem = Lexem(*line.split(',')[1:])

        if lexem.cl == 'States.SCOMMENT':
            return self.next_lexem()

        lexem.term = map_lexem_to_term(lexem)

        return lexem

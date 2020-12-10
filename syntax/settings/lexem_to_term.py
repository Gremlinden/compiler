from syntax.settings.symbols import Terminals


def map_lexem_to_term(lexem):
    if (lexem.cl == ''):
        return Terminals.END_SYMBOL
    elif (lexem.cl == 'States.COMPRASION'):
        return Terminals.COMP_OPERATOR
    elif (lexem.cl == 'States.OPERATOR' and
          lexem.value in ['+', '-']):
        return Terminals.PM_OPERATOR
    elif (lexem.cl == 'States.OPERATOR' and
          lexem.value in ['*', '/', '%']):
        return Terminals.MD_OPERATOR
    elif (lexem.cl == 'States.PPFIX'):
        return Terminals.PPFIX_OPERATOR
    elif (lexem.cl == 'States.OPERATOR' and
          lexem.value in ['~', '!']):
        return Terminals.UNARY_OPERATOR
    elif (lexem.cl == 'States.ID'):
        return Terminals.VAR
    elif (lexem.cl == 'States.KEYWORD' and
          lexem.value in ['int', 'float', 'char', 'double', 'short']):
        return Terminals.TYPE_NAME
    elif (lexem.cl == 'States.DELIM' and
          lexem.value == '('):
        return Terminals.OPEN_PAR
    elif (lexem.cl == 'States.DELIM' and
          lexem.value == ')'):
        return Terminals.CLOSE_PAR
    elif (lexem.cl == 'States.DELIM' and
          lexem.value == ';'):
        return Terminals.SEMICOLON
    elif (lexem.cl == 'States.ASSIGNMENT'):
        return Terminals.ASSIGNMENT
    elif (lexem.cl in ['States.INT', 'States.FLOAT']):
        return Terminals.CONST
    else:
        print('Alert!')
        print(lexem.cl)
        print(lexem.value)

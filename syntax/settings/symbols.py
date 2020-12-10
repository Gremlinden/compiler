from enum import Enum, auto


class Terminals(Enum):
    SEMICOLON = auto()
    VAR = auto()
    ASSIGNMENT = auto()
    PM_OPERATOR = auto()
    MD_OPERATOR = auto()
    OPEN_PAR = auto()
    TYPE_NAME = auto()
    CLOSE_PAR = auto()
    CONST = auto()
    PPFIX_OPERATOR = auto()
    UNARY_OPERATOR = auto()
    END_SYMBOL = auto()
    NABLA = auto()


class NonTerminals(Enum):
    STATS = auto()
    STAT = auto()
    ASSIGNMENT_EXP = auto()
    ADDITIVE_EXP = auto()
    MULT_EXP = auto()
    CAST_EXP = auto()
    UNARY_EXP = auto()


term_map = {
    ';': Terminals.SEMICOLON,
    'var': Terminals.VAR,
    '=': Terminals.ASSIGNMENT,
    'pm_operator': Terminals.PM_OPERATOR,
    'md_operator': Terminals.MD_OPERATOR,
    '(': Terminals.OPEN_PAR,
    'type_name': Terminals.TYPE_NAME,
    ')': Terminals.CLOSE_PAR,
    'const': Terminals.CONST,
    'prefix_operator': Terminals.PPFIX_OPERATOR,
    'unary_operator': Terminals.UNARY_OPERATOR,
    '-|': Terminals.END_SYMBOL,
    'nabla': Terminals.NABLA
}

nonterm_map = {
    'STATS': NonTerminals.STATS,
    'STAT': NonTerminals.STAT,
    'ASSIGNMENT_EXP': NonTerminals.ASSIGNMENT_EXP,
    'ADDITIVE_EXP': NonTerminals.ADDITIVE_EXP,
    'MULT_EXP': NonTerminals.MULT_EXP,
    'CAST_EXP': NonTerminals.CAST_EXP,
    'UNARY_EXP': NonTerminals.UNARY_EXP
}

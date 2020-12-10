from enum import Enum
import pandas as pd


KEYWORDS = {
    'int': 0,
    'float': 1,
    'double': 2,
    'char': 3,
    'long': 4,
    'short': 5,
    'string': 6
}


DELIMITERS = ['(', ')', '[', ']', '{', '}',
              '.', ',', ':', ';']


OPERATORS = ['*', '%', '~', '!']


COMPRASIONSF = ['>', '<']


class States(Enum):
    IDLE = 0  # +
    ID = 1  # + var
    INT = 2  # + const
    FLOAT = 3  # + const
    CHAR = 4  # + const
    STRING = 5  # + const
    KEYWORD = 6  # + var type_name
    DELIM = 7  # +
    ASSIGNMENT = 8  # +
    COMPRASIONF = 9  # +
    COMPRASION = 10  # + comp_operator
    PLUS = 11  # +
    MINUS = 12  # +
    PPFIX = 13  # + ppfix_operator
    AND = 14  # + log_operator
    OR = 15  # + log_operator
    DIVIDE = 16  # + md_operator
    OPERATOR = 17  # + pm_operator md_operator
    SCOMMENT = 18  # +
    ERROR = 19  # +
    NOT = 20

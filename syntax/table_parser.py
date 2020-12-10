from syntax.settings.symbols import term_map, nonterm_map
import pandas as pd

symb_map = term_map.copy()
symb_map.update(nonterm_map)


def parse_table(file):
    df = pd.read_csv(file)
    result = {}
    col_symb = None
    row_symb = None
    for i, col in enumerate(df):
        if i == 0:
            continue
        col_symb = symb_map[col]
        result[col_symb] = {}
        for j, e in enumerate(df[col]):
            row_symb = symb_map[df.iloc[j, 0]]
            if pd.notna(e):
                if j - 1 < len(nonterm_map):
                    result[col_symb][row_symb] = e
                else:
                    result[col_symb][row_symb] = e
    return result

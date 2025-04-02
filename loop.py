
def tokenize(code):
    return code.split()


def is_valid_for_loop(tokens):
    # Expected format: for <var> in <iterable>:
    if len(tokens) < 4 or tokens[2] != 'in' or not tokens[-1].endswith(':'):
        return False
    elif tokens[3].startswith('range('):
        if tokens[3][-2] == ')' and tokens[3][-3] == '(':
            return False


    return True


def is_valid_while_loop(tokens):
    # Expected format: while <condition>:
    if len(tokens) == 3 or not tokens[-1].endswith(':'):
        return False

    if len(tokens) > 3:
        valid_operators = {"<", ">", "<=", ">=", "==", "!=", "in", "not"}
        if tokens[2] not in valid_operators:
            return False

    return True


def syntex_analyzer(syntex):
    tokens = syntex.split()

    # check if there are enough tokens for a loop statement.
    if len(tokens) < 2:
        return "Invalid: Not enough tokens for a loop syntax"

    if tokens[0] == "for":
        if is_valid_for_loop(tokens):
            return "Valid for loop syntex"
        return "Invalid for loop syntex"
    elif tokens[0] == "while":
        if is_valid_while_loop(tokens):
            return "Valid while loop syntex"
        return "Invalid while loop syntex"


statement = input("Enter loop statement: ")
print(syntex_analyzer(statement))


import sys
import collections

class dotdict(dict):
    __getattr__ = dict.__getitem__
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__

def starts_ends_with(string, prefix, suffix):
    if string.startswith(prefix) and string.endswith(suffix):
        return string[len(prefix): len(string) - len(suffix)]
    return None

class CompilerError(Exception):
    pass

def initial_compiler(vars):
    vars.stack = collections.deque()
    vars.tab = ''

def if_compiler(args, outfile, vars):
    outfile.write('{}if {}:'.format(vars.tab, args))
    vars.stack.append('if')

def end_compiler(args, outfile, vars):
    try:
        last_macro = vars.stack.popleft()
    except IndexError:
        raise CompilerError('end_without_preceding')

def finalize_compiler(vars):
    pass

_default_macro_compilers = {
    'if': if_compiler,
}

def _default_error_handler(error, info, *args):
    print('compile error: {}: {}'.format(error, args))
    print(info)

def process_file(
    infile,
    outfile,
    macro_compilers = _default_macro_compilers.copy(),
    error_handler = _default_error_handler,
    macro_prefix = '#',
    macro_suffix = '',
    statement_prefix = '@',
    statement_suffix = '',
    ):

    vars = dotdict()
    initial_compiler(vars)

    lnum = 0
    line = infile.readline()
    while line:
        lnum += 1
        striped_line = line.strip()
        macro_line = starts_ends_with(striped_line, macro_prefix, macro_suffix)
        if macro_line is not None:
            macro_args = macro_line.split(maxsplit = 1)
            try:
                macro, args = macro_args
            except ValueError:
                macro = macro_args[0]
                args = ''
            try:
                macro = macro_compilers[macro]
            except KeyError:
                error_handler('unknown_macro', (lnum, line), macro)
                return
            try:
                macro(args, outfile, vars)
            except CompilerError as e:
                error_handler(e.args[0], (lnum, line), *e.args[1:])
                return
        line = infile.readline()
    finalize_compiler(vars)

def main(argv):
    for name in argv[1:]:
        with open(name) as infile:
            process_file(infile, sys.stdout)

if __name__ == '__main__':
    sys.exit(main(sys.argv))

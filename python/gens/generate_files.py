#!/usr/bin/python3

import os
import sys
import re

source = sys.argv[1]

def close_stream(ostream):
    if ostream is not None and not ostream.closed:
        ostream.close()

res = os.path.join('CodeFights', 'arcade', 'intro')

index = 0
where = ''
md_file = ''
py_file = ''
ostream = None

with open(source, 'r') as istream:
    for line in istream:
        line = line.rstrip()
        if '# Problem' in line:
            close_stream(ostream)
            index = line.split(' ')[-1]
            folder = os.path.join(res, index)
            md_file = os.path.join(folder, 'README.md')
            py_file = os.path.join(folder, 'solution.py')
            if not os.path.isdir(folder):
                os.makedirs(folder)
        else:
            if '# Description' in line:
                where = 'md'
                ostream = open(md_file, 'w')
                ostream.write('# Description\n')
            elif '# Code' in line:
                where = 'py'
                close_stream(ostream)
                ostream = open(py_file, 'w')
                ostream.write('#!/usr/bin/python3\n')
            else:
                if ostream is not None and not ostream.closed:
                    if where == 'md':
                        if 'Example' in line:
                            ostream.write('## Example\n')          
                        elif re.match(".*\(.*\) = ", line):
                            ostream.write("`{}`  ".format(line) + '\n')
                        elif line != '':
                            ostream.write(line + '  \n')
                        else:
                            ostream.write(line + '\n')
                    else:
                        ostream.write(line + '\n')

close_stream(ostream)

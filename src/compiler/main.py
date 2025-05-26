
import sys
from dataclasses import dataclass
from dataclasses import field
import typing

import lex        
import tree



def main():

    if len(sys.argv) < 2:
        print("no file provided\n")
        sys.exit(1)
    
    stream = lex.tokenize(sys.argv[1])
    tree.parse_scope(stream)



main()

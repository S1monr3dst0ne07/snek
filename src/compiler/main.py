
import sys
from dataclasses import dataclass
from dataclasses import field
import typing

import lex        



def main():

    if len(sys.argv) < 2:
        print("no file provided\n")
        sys.exit(1)
    
    lex.tokenize(sys.argv[1])



main()

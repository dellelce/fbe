"""
 Generate pseudo-random binary file from a textual specification.

 File:         makebin.py
 Created:      110718
"""

from binascii import unhexlify
from typing import BinaryIO


class binfile:
    """Perform operations on binary files."""

    fh: BinaryIO = None
    name: str = None

    def __init__(self, name: str) -> None:
        """Open file."""
        self.fh = open(name, "wb")
        self.name = name

    def close(self) -> None:
        if self.fh:
            close(fh)

    def __repr__(self) -> str:
        return f"""binfile("{self.name}")"""

    def writehex(self, block: str) -> None:
        """Write hex sequence to file."""
        return self.fh.write(unhexlify(block))


class binspec:
    """
     Use an "RPN" language with:

     * two stacks (data, commands) and
     * two registers (state, accumulator)


     Commands:

      pop           remove top from data stack
      xor           xor top from stack with accumulator
      or
      and
      n:            nibble commands TBD
      n:copy
      n:stepcopy
      n:range
      add
      minus
      reverse

    Data types:

    * strings (single or double quotes we don't care)
    * hex objects (0x....)
    * integer (anything else starting with 1-9 that works with python int()
    """

    def __init__(self, name: str) -> None:
        """Read specification from file."""
        self.stack = []
        self.bytes = 0

        with open(name) as f:
            _lines = f.readlines()

            # read line ignoring comments - crudely for now
            self.lines = [line.lstrip().split() for line in _lines]
            self.lines = [
                line for line in self.lines if len(line) > 0 and line[0] != "#"
            ]

    def __repr__(self) -> str:
        """Use number of lines only, for now at least."""
        return "binspec({} lines)".format(len(self.lines))

    def getbyte(self) -> None:
        """Get byte from buffer, if exhausted re-generate following instructions."""
        pass

    def write(self, name: str, nbytes: int) -> None:
        """Write nbytes to file using current specification."""
        pass

    def _process(self) -> None:
        """Process configuration in some sort of bytecode."""
        pass


if __name__ == "__main__":
    # test only here
    bs = binspec("test.binspec")
    print(bs)
    print(bs.lines)

## EOF ##

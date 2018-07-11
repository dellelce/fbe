"""
 Generate pseudo-random binary file from a textual specification.

 File:         makebin.py
 Created:      110718
"""


class binspec(object):

  def __init__(self, name):
    """Read specification from file."""
    with open(name) as f:
      _lines = f.readlines()

      # read line ignoring comments - crudely for now
      self.lines = \
        [line for line in _lines
         if line.lstrip().split()[0][0] != '#']

  def __repr__(self):
    """Use number of lines only, for now at least."""
    return 'binspec({} lines)'.format(len(self.lines))

  def write(self, name, nbytes):
    """Write nbytes to file using current specification."""
    pass


if __name__ == '__main__':
  bs = binspec('test.binspec')
  print(bs)

## EOF ##

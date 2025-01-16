import pandas as pd
import matplotlib.pyplot as plt
import os
import sys

# python3 postprocessing/plotFigure.py --files='postprocessing/Uy/end/Uy_U.xy','postprocessing/Uy.dat' --normalise='1=-1:1','0=-1:1' --plot='1:3','0:3'

# calling convention
# python3 postprocessing/plotFigure.py
#   --files=['postprocessing/Uy/end/Uy_U.xy', 'postprocessing/Uy.dat']
#   --normalise=['1=-1:1','0=-1:1']
#   --plot=['1:3', '0:3']
#   --linestyle=['solid', 'none']
#   --markerstyle=['none', 'o']
#   --xlabel='Ux [m/s]'
#   --ylabel='Uy [m/s]
#   --legend=['OpenFOAM', 'Ghia et al.']
#   --legend_position='lower right']
#   additional ones
#   --log=x, --log=y, --log=xy

def main():
  # parse command line arguments
  cla = process_command_line_arguments()
  open_files(cla)


def process_command_line_arguments():
  cla = {}
  for arg in sys.argv[1:]:
    if arg.find('--files=') != -1:
      c_args = arg.replace('--files=', '').split(',')
      cla['files'] = c_args
  return cla


def open_files(cla):
  df = pd.DataFrame({})
  for file in cla['files']:
    f = open(file)
    print(f.readlines())


if __name__ == '__main__':
  main()
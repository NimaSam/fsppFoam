import pandas as pd
import os
import sys

def main():
  # determine the last time step used in openfoam simulation, required to read data from only last directory
  allFolders = (os.listdir(os.path.join('postProcessing', 'Uy')))
  allFolders = sorted([folder.zfill(10) for folder in allFolders])
  lastTimeStep = allFolders[-1].lstrip('0')

  # read reference data
  uy_ghia = pd.read_csv(os.path.join('postProcessing', 'Uy.dat'), header=0)
  vx_ghia = pd.read_csv(os.path.join('postProcessing', 'Vx.dat'), header=0)
  
  # read openfoam data
  uy_of = pd.read_csv(os.path.join('postProcessing', 'Uy', str(lastTimeStep), 'Uy_U.xy'), header=None, sep="\t")
  vx_of = pd.read_csv(os.path.join('postProcessing', 'Vx', str(lastTimeStep), 'Vx_U.xy'), header=None, sep="\t")

  # command line arguments, expect one argument which is the Reynolds number
  cla = sys.argv
  assert(len(cla) == 2)
  reynolds_number = 'Re_' + str(sys.argv[1])

  # get data from data frames for plotting
  x_ghia = (vx_ghia['x'] * 2.0) - 1.0
  y_ghia = (uy_ghia['y'] * 2.0) - 1.0
  u_ghia = uy_ghia[reynolds_number]
  v_ghia = vx_ghia[reynolds_number]

  x_of = (vx_of[0] * 2.0) - 1.0
  y_of = (uy_of[1] * 2.0) - 1.0
  u_of = uy_of[3]
  v_of = vx_of[4]

  # calculate error norms


if __name__ == '__main__':
  main()
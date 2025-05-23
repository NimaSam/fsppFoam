## Introduction

This repository implements the [Fractional-Step, Pressure Projection](https://en.wikipedia.org/wiki/Projection_method_(fluid_dynamics)) method of Chorin into OpenFOAM. The solver is named ```fsppFoam```.

Notably, it is a fully implicit implementation, meaning you can use any CFL number you like.

## Compilation

Open your terminal and change into the ```fsppFoam/``` folder. Ensure that OpenFOAM is loaded into your environment (e.g. upon running ```checkMesh``` you get some OpenFOAM output printed to the console).

Then, to compile the solver into your user appbin directory, type:

```
wmake
```

This will do the compilation for you. If no errors appear, your solver should be compiled and available and you can check this by typing

```
fsppFoam
```

## Testing

To test that the solver is working correctly, change into the ```lidDrivenCavity/``` folder, which contains the lid driven cavity example and it is set up to be used with the new solver.

It contains a few post-processing routines for easy plotting of results which will automatically get executed if you run the Allrun script by typing

```
./Allrun
```

After the simulation has finished, you will see two new figures within the post-processing directory, one for the residuals, and one for the velocity profile at the vertical and horizontal center line, which is compared against the paper by Ghia _et al._

The solver is set up, on purpose, to run at a high CFL number (CFL(max)=50, the average is around 3). The solver is still converging with correct results. Good luck with simpleFoam or pimpleFoam ...

## Run your own cases

If you want to use this solver for your own cases, you need to provide a dictionary entry within the ```system/fvSolution``` file for the ```FS-PP``` method. This contains entires such as non-orthogonal correctors to use, similar to the ```SIMPLE``` or ```PISO``` entry. In-fact, you can have a combined entry of the form:

```
"(SIMPLE|PISO|PIMPLE|FS-PP)"
{
    consistent                 yes;
    nCorrectors                2;
    nOuterCorrectors           1;
    nNonOrthogonalCorrectors   0;
    pRefCell                   0;
    pRefValue                  0;
}
```

This entry will work for ```simpleFoam```, ```pisoFoam```, ```icoFoam```, ```pimpleFoam```, and, the current solver ```fsppFoam```.

## Known limitations

The Rhie-Chow-like interpolation is implemented within the ```fsppFoam/pCorrection.H``` file on lines 1-6, and then used in the pressure poisson solver on lines 13-18. This type of coupling is inspired from the ```simpleFoam``` solver, but has shown to be somewhat unstable for high-Reynolds number flows at low y+ values (around y+=1). This also causes stronger decoupling between pressure and velocity at highter CFL numbers.
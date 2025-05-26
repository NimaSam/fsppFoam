/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    fsppFoam

Group
    grpIncompressibleSolvers

Description
    Unsteady solver for incompressible, turbulent flow of Newtonian fluids.
    Uses the Fractional-Step, Pressure projection (FS-PP) method of Chorin.
    This solver is fully implicit.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "turbulenceModel.H"
#include "pisoControl.H"
//#include "fvOptions.H"
//#include "localEulerDdtScheme.H"
//#include "fvcSmooth.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Unsteady solver for incompressible, turbulent flow of Newtonian fluids."
        "Uses the Fractional-Step, Pressure projection (FS-PP) method of Chorin."
        "This solver is fully implicit."
    );

    //#include "postProcess.H"

    //#include "addCheckCaseOptions.H"
    //#include "setRootCaseLists.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    //#include "createControl.H"
    pisoControl piso(mesh);
    #include "createFields.H"
    #include "initContinuityErrs.H"

    //turbulence->validate();

    #include "CourantNo.H"
    #include "setInitialDeltaT.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    
    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        #include "CourantNo.H"
        //#include "setDeltaT.H"
        
        Info<< "Time = " << runTime.timeName() << nl << endl;

        // Update settings from the control dictionary
        //piso.read();
        
        phi = (fvc::interpolate(U) & mesh.Sf());
        
        fvVectorMatrix UEqn
        (
            fvm::ddt(U)
          + fvm::div(phi, U)
          //+ turbulence->divDevReff(U)
          + turbulence->divDevReff()
        );

        // relax velocity field explicitly
        UEqn.relax();
        
        UEqn.solve();
        
        #include "pCorrection.H"

        laminarTransport.correct();
        turbulence->correct();
        
        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //

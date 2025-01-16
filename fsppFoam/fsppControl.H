/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2017 OpenCFD Ltd.
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

Class
    Foam::fsppControl

Description
    FS-PP control class to supply convergence information/checks for
    the FS-PP loop.

\*---------------------------------------------------------------------------*/

#ifndef fsppControl_H
#define fsppControl_H

#include "solutionControl.H"

//- Declare that fsppControl will be used
#define fspp_CONTROL

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class fsppControl Declaration
\*---------------------------------------------------------------------------*/

class fsppControl
:
    public solutionControl
{

protected:

    // Protected Data

        //- Initialised flag
        bool initialised_;

        //- Maximum number of FS-PP correctors
        label nCorrFSPP_;

        //- Current FS-PP corrector
        label corrFSPP_;


    // Protected Member Functions

        //- Read controls from fvSolution dictionary
        bool read();

        //- Return true if all convergence checks are satisfied
        bool criteriaSatisfied();


private:

    // Private member functions

        //- No copy construct
        fsppControl(const fsppControl&) = delete;

        //- No copy assignment
        void operator=(const fsppControl&) = delete;


public:

    // Static Data Members

        //- Run-time type information
        TypeName("fsppControl");


    // Constructors

        //- Construct from mesh and the name of control sub-dictionary
        fsppControl
        (
            fvMesh& mesh,
            const word& dictName = "FS-PP",
            const bool verbose = true
        );


    //- Destructor
    virtual ~fsppControl() = default;


    // Member Functions

        // Access

            //- Maximum number of FS-PP correctors
            inline label nCorrFSPP() const;

            //- Current FS-PP corrector index
            inline label corrFSPP() const;

        // Solution control

            //- FS-PP loop
            virtual bool loop();

            //- Pressure corrector loop control
            inline bool correct();

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "fsppControlI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

auto dt = runTime.deltaT();


// surfaceScalarField phiCorrected
// (
//     "phiCorrected",
//     fvc::flux(U) + dt * fvc::ddtCorr(U, phi)
// );

// Add a unity density field for incompressible flow
volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("rho", dimDensity, 1.0)
);

surfaceScalarField phiCorrected
(
    "phiCorrected",
    (fvc::interpolate(U) & mesh.Sf()) + dt*fvc::ddtPhiCorr(rho, U, phi)/fvc::interpolate(rho)
);

adjustPhi(phiCorrected, U, p);

// solve pressure poisson equation
while (piso.correctNonOrthogonal())
{
    fvScalarMatrix pEqn
    (
        fvm::laplacian(dt, p)
        ==
        fvc::div(phiCorrected)
    );
    pEqn.setReference(pRefCell, pRefValue);
    pEqn.solve();
}

// correct velocity field
U = U - dt * fvc::grad(p);

// update (neumann) boundary conditions again as velocity has changed
U.correctBoundaryConditions();

// evaluate the divergence free error
#include "continuityErrs.H"

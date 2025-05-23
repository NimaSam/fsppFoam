auto dt = runTime.deltaT();
surfaceScalarField phiCorrected
(
    "phiCorrected",
    fvc::flux(U) + dt * fvc::ddtCorr(U, phi)
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

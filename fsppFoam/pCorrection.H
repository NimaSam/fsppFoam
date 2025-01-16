// the velocity has changed due to the previous momentum equation,
// update (neumann) boundary conditions
U.correctBoundaryConditions();

auto dt = runTime.deltaT();
surfaceScalarField phiCorrected
(
    "phiCorrected",
    fvc::flux(U) + dt * fvc::ddtCorr(U, phi)
);

adjustPhi(phiCorrected, U, p);

// solve pressure poisson equation
while (fspp.correctNonOrthogonal())
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
p.relax();

// correct velocity field
U = U - dt * fvc::grad(p);

// update (neumann) boundary conditions again as velocity has changed
U.correctBoundaryConditions();

// evaluate the divergence free error
#include "continuityErrs.H"

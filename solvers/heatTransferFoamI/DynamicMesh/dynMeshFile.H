#       include "readControls.H"
#       include "checkTotalVolume.H"

        // Make the fluxes absolute
        fvc::makeAbsolute(phi, Umesh);

#       include "CourantNo.H"
#       include "setDeltaT.H"

        bool meshChanged = mesh.update();
        reduce(meshChanged, orOp<bool>());

#       include "volContinuity.H"

        if (correctPhi && (mesh.moving() || meshChanged))
        {
            // Fluxes will be corrected to absolute velocity
            // HJ, 6/Feb/2009
#           include "correctPhi.H"
        }

        // Make the fluxes relative to the mesh motion
        fvc::makeRelative(phi, Umesh);

        if (mesh.moving() && checkMeshCourantNo)
        {
#           include "meshCourantNo.H"
        }

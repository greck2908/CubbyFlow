// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <API/Python/Solver/Hybrid/MPM/MPMSolver.hpp>
#include <API/Python/Utils/pybind11Utils.hpp>
#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>
#include <Core/Solver/Hybrid/MPM/MPMSolver3.hpp>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddMPMSolver2(pybind11::module& m)
{
    pybind11::class_<MPMSolver2, MPMSolver2Ptr, GridFluidSolver2>(m,
                                                                  "MPMSolver2")
        .def(
            "__init__",
            [](MPMSolver2& instance, pybind11::args args,
               pybind11::kwargs kwargs) {
                Size2 resolution{ 1, 1 };
                Vector2D gridSpacing{ 1, 1 };
                Vector2D gridOrigin{ 0, 0 };

                ParseGridResizeParams(args, kwargs, resolution, gridSpacing,
                                      gridOrigin);

                new (&instance) MPMSolver2(resolution, gridSpacing, gridOrigin);
            },
            R"pbdoc(
			Constructs MPMSolver2

			This method constructs MPMSolver2 with resolution, gridSpacing,
			and gridOrigin.

			Parameters
			----------
			- `*args` : resolution, gridSpacing, and gridOrigin arguments.
			- `**kwargs`
				- resolution : Grid resolution.
				- gridSpacing : Grid spacing.
				- gridOrigin : Origin point at the grid.
				- domainSizeX : Domain size in x-direction.
		)pbdoc")
        .def_property_readonly("particleSystemData",
                               &MPMSolver2::GetParticleSystemData,
                               R"pbdoc(
			Returns particleSystemData.
		)pbdoc")
        .def_property("particleEmitter", &MPMSolver2::GetParticleEmitter,
                      &MPMSolver2::SetParticleEmitter,
                      R"pbdoc(
			Particle emitter property.
		)pbdoc");
}

void AddMPMSolver3(pybind11::module& m)
{
    (void)m;
}
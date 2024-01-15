# What is pvr

Primary Vertex Reconstruction (pvr) for HADES based on the procedure developed by Matthias Zipper:

M. Zipper, Technische Universität München (2015)
Measuring πΛ Correlations in π- + W Reactions at 1.7 GeV/c with HADES

See Appendix A of:

https://www.das.ktas.ph.tum.de/DasDocs/Public/Bachelor_Theses/MatthiasZipper_BachelorThesis_v1.pdf


# Usage
===========================================================

// include header
#include <PrimVertReco.h>

// Create class object
PrimVertReco pvr;

// add tracks using one of the three overloaded functions:
// void insert_track(HParticleCand* track);
// void insert_track(const hades_track & track);
// void insert_track(const TVector3 & base, const TLorentzVector & track);

pvr.insert_track(...);

// calculate the vertex
Tvector3 prim_vector = pvt.calc();

// cleanup the object to prepare for new tracks:
pvr.cleanup();


3. Installation
===========================================================

git clone https://github.com/dziadu/PrimVertReco
cd PprimVvertexReco
mkdir build
cd build
# make sure HADDIR is exported

# install as a root

cmake ..
make
sudo make install

# or install as a user in the custom location

cmake .. -DCMAKE_INSTALL_PREFIX=your_custom_location
make
make install

# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
Boost Software License 1.0.
-->

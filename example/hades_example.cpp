#include <pvr/pvr.hpp>

#include <hforwardcand.h>
#include <hparticlecand.h>

auto make_spatial_track_hades(HVirtualCand* track) -> pvr::spatial_track
{
    double mom = track->getMomentum();
    double theta = track->getTheta();
    double phi = track->getPhi();
    double r = track->getR();
    double conv = TMath::DegToRad();

    XYZPoint base(r * TMath::Cos(conv * phi + TMath::PiOver2()), r * TMath::Sin(conv * phi + TMath::PiOver2()),
                  track->getZ());

    XYZVector dir(mom * TMath::Sin(conv * theta) * TMath::Cos(conv * phi),
                  mom * TMath::Sin(conv * theta) * TMath::Sin(conv * phi), mom * TMath::Cos(conv * theta));

    return {std::move(base), std::move(dir)};
}

auto main() -> int
{
    HParticleCand pcand;
    HForwardCand fcand;

    pcand.print();
    fcand.print();

    pvr::pvr pvr;
    pvr.insert_track(make_spatial_track_hades(&pcand));
    pvr.insert_track(make_spatial_track_hades(&fcand));

    auto vertex = pvr.calculate();

    std::cout << vertex;

    return 0;
}

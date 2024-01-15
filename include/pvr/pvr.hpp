#pragma once

#include <vector>

#include <TMath.h>
#include <TMatrixD.h>
#include <TVector3.h>
#include <hparticlecand.h>

namespace pvr
{

typedef std::pair<TVector3, TLorentzVector> hades_track;

class PrimVertReco
{
  public:
    PrimVertReco();
    PrimVertReco(size_t ntracks);

    void insert_track(HParticleCand* track);
    void insert_track(const hades_track& track);
    void insert_track(const TVector3& base, const TLorentzVector& track);

    virtual ~PrimVertReco();

    TVector3 calc() const;
    void clear();

    std::vector<hades_track> get_tracks() const { return tracks; }

  protected:
  private:
    size_t maxtracks;

    std::vector<hades_track> tracks;
};

PrimVertReco::PrimVertReco()
    : maxtracks(64)
{
}

PrimVertReco::PrimVertReco(size_t ntracks)
    : maxtracks(ntracks)
{
}

PrimVertReco::~PrimVertReco() {}

void PrimVertReco::insert_track(const TVector3& base, const TLorentzVector& track)
{
    hades_track t(base, track);

    tracks.push_back(t);
}

void PrimVertReco::insert_track(const hades_track& track)
{
    tracks.push_back(track);
}

void PrimVertReco::insert_track(HParticleCand* track)
{
    hades_track t;

    double mom = track->getMomentum();
    double theta = track->getTheta();
    double phi = track->getPhi();
    double r = track->getR();
    double conv = TMath::DegToRad();

    t.first.SetXYZ(r * TMath::Cos(conv * phi + TMath::PiOver2()), r * TMath::Sin(conv * phi + TMath::PiOver2()), track->getZ());

    t.second.SetPxPyPzE(mom * TMath::Sin(conv * theta) * TMath::Cos(conv * phi),
                        mom * TMath::Sin(conv * theta) * TMath::Sin(conv * phi),
                        mom * TMath::Cos(conv * theta),
                        track->Energy());

    tracks.push_back(t);
}

TVector3 PrimVertReco::calc() const
{
    TMatrixD M[maxtracks];
    TMatrixD b[maxtracks];

    const size_t n = tracks.size();

    for (uint k = 0; k < n; k++) {
        double mom = tracks[k].second.P();
        M[k].ResizeTo(3, 3);

        double invpsq = 1. / (mom * mom);
        double Px = tracks[k].second.Px();
        double Py = tracks[k].second.Py();
        double Pz = tracks[k].second.Pz();

        M[k][0][0] = 1. - Px * Px * invpsq;
        M[k][0][1] = -Px * Py * invpsq;
        M[k][0][2] = -Px * Pz * invpsq;
        M[k][1][0] = M[k][0][1];
        M[k][1][1] = 1. - Py * Py * invpsq;
        M[k][1][2] = -Py * Pz * invpsq;
        M[k][2][0] = M[k][0][2];
        M[k][2][1] = M[k][1][2];
        M[k][2][2] = 1. - Pz * Pz * invpsq;
        b[k].ResizeTo(3, 1);
        b[k][0][0] = tracks[k].first.X();
        b[k][1][0] = tracks[k].first.Y();
        b[k][2][0] = tracks[k].first.Z();
    }

    TMatrixD MM(3, 3);
    TMatrixD bb(3, 1);
    for (uint k = 0; k < n; k++) {
        MM += M[k];
        bb += M[k] * b[k];
    }

    TMatrixD r(3, 1);
    if (MM.Determinant() == 0) {
        r[0][0] = -50;
        r[1][0] = -50;
        r[2][0] = -1000;
    } else {
        MM = MM.Invert();
        r = MM * bb;
    }

    TVector3 ret;
    ret.SetXYZ(r[0][0], r[1][0], r[2][0]);
    return ret;
}

void PrimVertReco::clear()
{
    tracks.clear();
}

}  // namespace pvr

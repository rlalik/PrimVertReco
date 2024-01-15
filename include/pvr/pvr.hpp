#pragma once

// ROOT
#include <Math/Point3D.h>
#include <Math/Vector3D.h>
#include <TLorentzVector.h>
#include <TMatrixD.h>
#include <TVector3.h>

// system
#include <utility>
#include <vector>

using ROOT::Math::XYZPoint;
using ROOT::Math::XYZVector;

namespace pvr
{

typedef std::pair<XYZPoint, XYZVector> spatial_track;

class pvr
{
public:
    pvr(size_t ntracks = 10) : maxtracks(ntracks) {}

    auto insert_track(const spatial_track& track) -> void { tracks.push_back(track); }

    template <typename BasePoint, typename DirectionVector>
    auto insert_track(const BasePoint& base, const DirectionVector& track) -> void
    {
        tracks.emplace_back(base, track);
    }

    auto insert_track(const TVector3& base, const TLorentzVector& track) -> void
    {
        tracks.emplace_back(base, track.Vect());
    }

    virtual ~pvr() = default;

    auto calculate() const -> XYZPoint
    {
        TMatrixD M[maxtracks];
        TMatrixD b[maxtracks];

        const auto n = tracks.size();

        assert(n < maxtracks);

        for (auto k = 0; k < n; k++)
        {
            const auto mag2 = tracks[k].second.mag2();
            M[k].ResizeTo(3, 3);

            const auto invpsq = 1. / mag2;
            const auto Tx = tracks[k].second.x();
            const auto Ty = tracks[k].second.y();
            const auto Tz = tracks[k].second.z();

            M[k][0][0] = 1. - Tx * Tx * invpsq;
            M[k][0][1] = -Tx * Ty * invpsq;
            M[k][0][2] = -Tx * Tz * invpsq;
            M[k][1][0] = M[k][0][1];
            M[k][1][1] = 1. - Ty * Ty * invpsq;
            M[k][1][2] = -Ty * Tz * invpsq;
            M[k][2][0] = M[k][0][2];
            M[k][2][1] = M[k][1][2];
            M[k][2][2] = 1. - Tz * Tz * invpsq;
            b[k].ResizeTo(3, 1);
            b[k][0][0] = tracks[k].first.X();
            b[k][1][0] = tracks[k].first.Y();
            b[k][2][0] = tracks[k].first.Z();
        }

        TMatrixD MM(3, 3);
        TMatrixD bb(3, 1);
        for (auto k = 0; k < n; k++)
        {
            MM += M[k];
            bb += M[k] * b[k];
        }

        TMatrixD r(3, 1);
        if (MM.Determinant() == 0)
        {
            r[0][0] = -50;
            r[1][0] = -50;
            r[2][0] = -1000;
        }
        else
        {
            MM = MM.Invert();
            r = MM * bb;
        }

        return {r[0][0], r[1][0], r[2][0]};
    }

    void clear() { tracks.clear(); }

    std::vector<spatial_track> get_tracks() const { return tracks; }

protected:
private:
    size_t maxtracks;

    std::vector<spatial_track> tracks;
};

} // namespace pvr

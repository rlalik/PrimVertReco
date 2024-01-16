#include <gtest/gtest.h>

#include <pvr/pvr.hpp>

#include <array>
#include <vector>

pvr::spatial_track make_spatial_track(float b_x, float b_y, float b_z, float v_px, float v_py, float v_pz)
{
    return {{b_x, b_y, b_z}, {v_px, v_py, v_pz}};
}

static double accuracy = 0.00001;

TEST(Basic, GenPhys)
{
    std::vector<std::pair<std::vector<std::array<double, 6>>, std::array<double, 3>>> data = {
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 0, 10, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 10, 10, 0, 0}}, {0, 0, 10}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}}, {0, 0, -5}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}, {0, 0, -5, -10, 0, 0}}, {0, 0, -5}}};

    int cnt = 0;
    for (const auto& test_set : data)
    {
        pvr::pvr pvr;
        for (const auto& inputs : test_set.first)
        {
            pvr.insert_track(make_spatial_track(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5]));
        }

        auto vec_res = pvr.calculate();

        EXPECT_NEAR(test_set.second[0], vec_res.X(), accuracy) << "in x for set " << cnt;
        EXPECT_NEAR(test_set.second[1], vec_res.Y(), accuracy) << "in y for set " << cnt;
        EXPECT_NEAR(test_set.second[2], vec_res.Z(), accuracy) << "in z for set " << cnt;
        cnt++;
    }
}

TEST(Basic, Lorentz)
{
    std::vector<std::pair<std::vector<std::array<double, 6>>, std::array<double, 3>>> data = {
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 0, 10, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 10, 10, 0, 0}}, {0, 0, 10}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}}, {0, 0, -5}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}, {0, 0, -5, -10, 0, 0}}, {0, 0, -5}}};

    int cnt = 0;
    for (const auto& test_set : data)
    {
        pvr::pvr pvr;
        for (const auto& inputs : test_set.first)
        {
            pvr.insert_track(TVector3(inputs[0], inputs[1], inputs[2]),
                             TLorentzVector(inputs[3], inputs[4], inputs[5], 10));
        }

        auto vec_res = pvr.calculate();

        EXPECT_NEAR(test_set.second[0], vec_res.X(), accuracy) << "in x for set " << cnt;
        EXPECT_NEAR(test_set.second[1], vec_res.Y(), accuracy) << "in y for set " << cnt;
        EXPECT_NEAR(test_set.second[2], vec_res.Z(), accuracy) << "in z for set " << cnt;
        cnt++;
    }
}

TEST(Basic, OnlyVectors)
{
    std::vector<std::pair<std::vector<std::array<double, 6>>, std::array<double, 3>>> data = {
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 0, 10, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 0, 10, 0, 0}}, {0, 0, 0}},
        {{{0, 0, 0, 0, 0, 10}, {0, 0, 10, 10, 0, 0}}, {0, 0, 10}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}}, {0, 0, -5}},
        {{{0, 0, -15, 10, 0, 0}, {0, 0, 5, 0, -10, 0}, {0, 0, -5, -10, 0, 0}}, {0, 0, -5}}};

    int cnt = 0;
    for (const auto& test_set : data)
    {
        pvr::pvr pvr;
        for (const auto& inputs : test_set.first)
        {
            pvr.insert_track(TVector3(inputs[0], inputs[1], inputs[2]), TVector3(inputs[3], inputs[4], inputs[5]));
        }

        auto vec_res = pvr.calculate();

        EXPECT_NEAR(test_set.second[0], vec_res.X(), accuracy) << "in x for set " << cnt;
        EXPECT_NEAR(test_set.second[1], vec_res.Y(), accuracy) << "in y for set " << cnt;
        EXPECT_NEAR(test_set.second[2], vec_res.Z(), accuracy) << "in z for set " << cnt;
        cnt++;
    }
}

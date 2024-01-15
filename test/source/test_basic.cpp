#include <TApplication.h>
#include <TF2.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TROOT.h>
#include <gtest/gtest.h>
#include <pvr/pvr.hpp>

#define PR(x) std::cout << "++DEBUG: " << #x << " = |" << x << "| (" << __FILE__ << ", " << __LINE__ << ")\n";

pvr::hades_track gen_track(float b_x, float b_y, float b_z, float v_px, float v_py, float v_pz, float v_e)
{
    TVector3 base(b_x, b_y, b_z);
    TLorentzVector vec;
    vec.SetPxPyPzE(v_px, v_py, v_pz, v_e);

    pvr::hades_track ht(base, vec);

    return ht;
}

static double accuracy = 0.00001;

TEST(Basic, MyTest)
{
    pvr::PrimVertReco pvr;

    float fnum = 2.00001f;

    EXPECT_NEAR(fnum, 2.0f, 0.0005);

    std::string pattern_string("%%d pattern");
    std::string test_string("test pattern");
    std::string replace_string("test");

    TVector3 vec_res;

    // test
    pvr.clear();
    pvr.insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
    pvr.insert_track(gen_track(0, 0, 0, 0, 10, 0, 10));
    vec_res = pvr.calc();
    EXPECT_NEAR(0, vec_res.X(), 0.0005);
    EXPECT_NEAR(0, vec_res.Y(), 0.0005);
    EXPECT_NEAR(0, vec_res.Z(), 0.0005);

    // test
    pvr.clear();
    pvr.insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
    pvr.insert_track(gen_track(0, 0, 0, 10, 0, 0, 10));
    vec_res = pvr.calc();
    EXPECT_NEAR(0, vec_res.X(), 0.0005);
    EXPECT_NEAR(0, vec_res.Y(), 0.0005);
    EXPECT_NEAR(0, vec_res.Z(), 0.0005);

    // test
    pvr.clear();
    pvr.insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
    pvr.insert_track(gen_track(0, 0, 10, 10, 0, 0, 10));
    vec_res = pvr.calc();
    EXPECT_NEAR(0, vec_res.X(), 0.0005);
    EXPECT_NEAR(0, vec_res.Y(), 0.0005);
    EXPECT_NEAR(10, vec_res.Z(), 0.0005);

    // test
    pvr.clear();
    pvr.insert_track(gen_track(0, 0, -15, 10, 0, 0, 10));
    pvr.insert_track(gen_track(0, 0, 5, 0, -10, 0, 10));
    vec_res = pvr.calc();
    EXPECT_NEAR(0, vec_res.X(), 0.0005);
    EXPECT_NEAR(0, vec_res.Y(), 0.0005);
    EXPECT_NEAR(-5, vec_res.Z(), 0.0005);

    // test
    pvr.clear();
    pvr.insert_track(gen_track(0, 0, -15, 10, 0, 0, 10));
    pvr.insert_track(gen_track(0, 0, 5, 0, -10, 0, 10));
    pvr.insert_track(gen_track(0, 0, -5, -10, 0, 0, 10));
    vec_res = pvr.calc();
    EXPECT_NEAR(0, vec_res.X(), 0.0005);
    EXPECT_NEAR(0, vec_res.Y(), 0.0005);
    EXPECT_NEAR(-5, vec_res.Z(), 0.0005);
}

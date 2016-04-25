#include <cppunit/extensions/HelperMacros.h>

#include <TApplication.h>
#include <TROOT.h>
#include <TF2.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>

#include <PrimVertReco.h>

#define PR(x) std::cout << "++DEBUG: " << #x << " = |" << x << "| (" << __FILE__ << ", " << __LINE__ << ")\n";

class BasicCase_tests : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( BasicCase_tests );
	CPPUNIT_TEST( MyTest );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();

protected:
	void MyTest();

	PrimVertReco * pvr;
};

CPPUNIT_TEST_SUITE_REGISTRATION( BasicCase_tests );

void BasicCase_tests::setUp()
{
	pvr = new PrimVertReco;
}

hades_track gen_track(float b_x, float b_y, float b_z, float v_px, float v_py, float v_pz, float v_e)
{
	TVector3 base(b_x, b_y, b_z);
	TLorentzVector vec;
	vec.SetPxPyPzE(v_px, v_py, v_pz, v_e);

	hades_track ht(base, vec);

	return ht;
}

void BasicCase_tests::MyTest()
{
	float fnum = 2.00001f;
// 	CPPUNIT_FAIL("zxczc");
	CPPUNIT_ASSERT_DOUBLES_EQUAL( fnum, 2.0f, 0.0005 );

	std::string pattern_string("%%d pattern");
	std::string test_string("test pattern");
	std::string replace_string("test");

	TROOT troot("TreeAnalysis","compiled analysisDST macros");
	TApplication app();
	TVector3 vec_res;

	// test
	pvr->clear();
	pvr->insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
	pvr->insert_track(gen_track(0, 0, 0, 0, 10, 0, 10));
	vec_res = pvr->calc();
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.X(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Y(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Z(), 0.0005 );

	// test
	pvr->clear();
	pvr->insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
	pvr->insert_track(gen_track(0, 0, 0, 10, 0, 0, 10));
	vec_res = pvr->calc();
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.X(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Y(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Z(), 0.0005 );

	// test
	pvr->clear();
	pvr->insert_track(gen_track(0, 0, 0, 0, 0, 10, 10));
	pvr->insert_track(gen_track(0, 0, 10, 10, 0, 0, 10));
	vec_res = pvr->calc();
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.X(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Y(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 10, vec_res.Z(), 0.0005 );

	// test
	pvr->clear();
	pvr->insert_track(gen_track(0, 0, -15, 10, 0, 0, 10));
	pvr->insert_track(gen_track(0, 0, 5, 0, -10, 0, 10));
	vec_res = pvr->calc();
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.X(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Y(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -5, vec_res.Z(), 0.0005 );

	// test
	pvr->clear();
	pvr->insert_track(gen_track(0, 0, -15, 10, 0, 0, 10));
	pvr->insert_track(gen_track(0, 0, 5, 0, -10, 0, 10));
	pvr->insert_track(gen_track(0, 0, -5, -10, 0, 0, 10));
	vec_res = pvr->calc();
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.X(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0, vec_res.Y(), 0.0005 );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -5, vec_res.Z(), 0.0005 );
}

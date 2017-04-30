#include <catch/catch.hpp>
#include <euler/rotations.h>
#include <cmath>
#include <iostream>

using namespace euler;

TEST_CASE("Identity")
{
  RotationMatrix R_expect = RotationMatrix::Identity(3, 3);
  RotationMatrix R_actual = getRotationMatrix("xyz", {0, 0, 0}, false, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, true, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, false, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, true, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, false, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, true, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, false, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, true, true);
  CHECK(R_actual.isApprox(R_expect));
}

TEST_CASE("Rotations about principal axes")
{
  const auto theta = M_PI/4.3;
  const auto s = std::sin(theta);
  const auto c = std::cos(theta);

  SECTION("Rotation about x-axis")
  {

    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << 1, 0,  0,
                         0, c, -s,
                         0, s,  c;
      RotationMatrix R_actual_active =
          getRotationMatrix("xyz", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("yxz", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("zyx", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << 1,  0,  0,
                          0,  c,  s,
                          0, -s,  c;
      RotationMatrix R_actual_passive =
          getRotationMatrix("xyz", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("yxz", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("zyx", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }

  SECTION("Rotation about y-axis")
  {

    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << c, 0,  s,
                         0, 1,  0,
                        -s, 0,  c;
      RotationMatrix R_actual_active =
          getRotationMatrix("yzx", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("xyz", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("zxy", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << c,  0, -s,
                          0,  1,  0,
                          s,  0,  c;
      RotationMatrix R_actual_passive =
          getRotationMatrix("yzx", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("xyz", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("zxy", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }

  SECTION("Rotation about z-axis")
  {

    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << c, -s,  0,
                         s,  c,  0,
                         0,  0,  1;
      RotationMatrix R_actual_active =
          getRotationMatrix("zyx", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("xzy", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("yxz", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << c,  s,  0,
                         -s,  c,  0,
                          0,  0,  1;
      RotationMatrix R_actual_passive =
          getRotationMatrix("zyx", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("xzy", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("yxz", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }
}

TEST_CASE("Rotations of 90 degrees about each axis")
{
  std::array<double, 3> angles = {M_PI/2, M_PI/2, M_PI/2};
  Eigen::Vector3d a(1, 0, 0);
  Eigen::Vector3d b_expect;
  Eigen::Vector3d b_actual;

  SECTION("Intrinsic")
  {
    const auto is_intrinsic = true;

    SECTION("xyz")
    {
      const auto sequence = "xyz";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("yzx")
    {
      const auto sequence = "yzx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("zyx")
    {
      const auto sequence = "zyx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, -1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("xzy")
    {
      const auto sequence = "xzy";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, -1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("xyx")
    {
      const auto sequence = "xyx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("zxz")
    {
      const auto sequence = "zxz";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("yzy")
    {
      const auto sequence = "yzy";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {-1, 0, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {-1, 0, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }
  }

  SECTION("Extrinsic")
  {
    const auto is_intrinsic = false;

    SECTION("xyz")
    {
      const auto sequence = "xyz";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, -1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("yzx")
    {
      const auto sequence = "yzx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, -1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("zyx")
    {
      const auto sequence = "zyx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("xzy")
    {
      const auto sequence = "xzy";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("xyx")
    {
      const auto sequence = "xyx";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 1, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("zxz")
    {
      const auto sequence = "zxz";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {0, 0, 1};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }

    SECTION("yzy")
    {
      const auto sequence = "yzy";

      SECTION("Active")
      {
        const auto is_active = true;
        b_expect = {-1, 0, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }

      SECTION("Passive")
      {
        const auto is_active = false;
        b_expect = {-1, 0, 0};
        b_actual =
            getRotationMatrix(sequence, angles, is_intrinsic, is_active) * a;
        CHECK(b_actual.isApprox(b_expect));
      }
    }
  }
}

TEST_CASE("General rotations")
{
  SECTION("Intrinsic")
  {
    std::array<double, 3> angles = {11 * M_PI / 180, -38 * M_PI/180, 4 * M_PI/180};

    Eigen::Matrix3d R_expect;
    R_expect << 0.7860912, -0.0549689,  -0.6156615,
						   -0.0487127,  0.9874306,  -0.1503595,
								0.616188,   0.1481869,   0.7735327;

		Eigen::Matrix3d R_actual = getRotationMatrix("xyz", angles, true, true);
    CHECK(R_actual.isApprox(R_expect, 1e-6));

    // Order reversed, but extrinsic should give same solution
    R_actual = getRotationMatrix("zyx", {angles[2], angles[1], angles[0]}, false, true);
    CHECK(R_actual.isApprox(R_expect, 1e-6));

    // Transpose should give passive solution
    R_expect.transposeInPlace();
    R_actual = getRotationMatrix("xyz", angles, true, false);
    CHECK(R_actual.isApprox(R_expect, 1e-6));
  }

  SECTION("Extrinsic")
  {
    std::array<double, 3> angles = {11 * M_PI / 180, -38 * M_PI/180, 4 * M_PI/180};

    Eigen::Matrix3d R_expect;
		R_expect << 0.786091,  -0.185662,  -0.589568,
                0.0549689,  0.971041,  -0.232502,
                0.615661,   0.15036,    0.773533;

		Eigen::Matrix3d R_actual = getRotationMatrix("xyz", angles, false, true);
    CHECK(R_actual.isApprox(R_expect, 1e-6));

    // Order reversed, but intrinsic should give same solution
    R_actual = getRotationMatrix("zyx", {angles[2], angles[1], angles[0]}, true, true);
    CHECK(R_actual.isApprox(R_expect, 1e-6));

    // Transpose should give passive solution
    R_expect.transposeInPlace();
    R_actual = getRotationMatrix("xyz", angles, false, false);
    CHECK(R_actual.isApprox(R_expect, 1e-6));
  }
}

TEST_CASE("Quaternions")
{
}

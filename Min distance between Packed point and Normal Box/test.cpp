#include "hausdorff_avx.h"
#include "hausdorff_cpp.h"
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <immintrin.h>
#include <iostream>
#include <random>

const double EPSILON = 1e-6;
/*
std::array<bool, 8> GetMask(__mmask8 mask) {
  std::array<bool, 8> bits;
  for (int i = 0; i < 8; ++i) {
    bool value = (mask & (1 << i)) != 0;
    bits[i] = value;
  }
  return bits;
}
*/

void Check_cpp(const std::array<double, 8> actual,
               const std::array<double, 8> expected) {
  for (size_t i = 0; i < 8; ++i) {
    if (std::abs(actual[i] - expected[i]) >= EPSILON) {
      FAIL(actual[i] << " != " << expected[i] << " index (" << i << ")");
    }
  }
}

void Check_avx(const std::array<double, 8> actual, const __m512d distance) {
  __m512d a = _mm512_load_pd(actual.data());
  __m512d eps = _mm512_abs_pd(_mm512_sub_pd(a, distance));
  for (int i = 0; i < 8; i++) {
    if (eps[i] >= EPSILON) {
      FAIL(actual[i] << " != " << distance[i] << " index (" << i << ")");
    }
  }
}
/*
TEST_CASE ("Functions") {

  PackedPoint_avx p = {{7.0, 7.0, 6.0, 9.0, 4.0, 2.0, 0.0, 0.0},
                          {6.0, 6.0, 1.0, 1.0, 6.0, 1.0, 0.0, 0.0}};
  NormalBox_avx box = {3.0, 2.0};


  __m512d W = _mm512_set1_pd(box.w);
  __m512d H = _mm512_set1_pd(box.h);
  __mmask8 mask1 = _mm512_cmp_pd_mask(p.x, W, _CMP_GT_OQ); // p.x > w
  __mmask8 mask2 = _mm512_cmp_pd_mask(p.y, H, _CMP_GT_OQ); // p.y > h

  for (int i = 0; i < 8; i++) {
    std::cerr << GetMask(mask1)[i] << " ";
  }

  std::cerr << " - next - ";

  for (int i = 0; i < 8; i++) {
    std::cerr << GetMask(mask2)[i] << " ";
  }

  __mmask8 mask3 = mask1 & mask2;

  std::cerr << " - next - ";

  for (int i = 0; i < 8; i++) {
    std::cerr << GetMask(mask3)[i] << " ";
  }
  CHECK(false);

}
*/

TEST_CASE("Simple For CPP") {
  PackedPoint_cpp pack = {{5.0, 7.0, 6.0, 9.0, -4.0, -2.0, 0.0, 0.0},
                          {4.0, 6.0, 1.0, 1.0, -6.0, 1.0, 0.0, 0.0}};
  NormalBox_cpp box = {3.0, 2.0};
  std::array<double, 8> a = {68.0, 116.0, 18.0, 45.0, 65.0, 34.0, 13.0, 13.0};
  Check_cpp(Hausdorff_CPP(box, pack), a);
}

TEST_CASE("Simple For AVX") {
  PackedPoint_avx pack = {{5.0, 7.0, 6.0, 9.0, -4.0, -2.0, 0.0, 0.0},
                          {4.0, 6.0, 1.0, 1.0, -6.0, 1.0, 0.0, 0.0}};
  std::array<double, 8> a = {68.0, 116.0, 18.0, 45.0, 65.0, 34.0, 13.0, 13.0};
  NormalBox_avx box = {3.0, 2.0};
  Check_avx(a, Hausdorff_AVX(box, pack));
}

TEST_CASE("Random") {
  std::mt19937 gen{12345678};
  std::uniform_real_distribution<double> PackCord(-10.0, 10.0);
  std::uniform_real_distribution<double> BoxDim(0.0, 4.0);

  std::array<double, 8> pack_CPP_X, pack_CPP_Y, pack_AVX_X, pack_AVX_Y;
  for (int i = 0; i < 8; i++) {
    pack_CPP_X[i] = PackCord(gen);
    pack_CPP_Y[i] = PackCord(gen);
    pack_AVX_X[i] = pack_CPP_X[i];
    pack_AVX_Y[i] = pack_CPP_Y[i];
  }
  PackedPoint_cpp pack_CPP = {pack_CPP_X, pack_CPP_Y};
  __m512d X = _mm512_loadu_pd(pack_AVX_X.data());
  __m512d Y = _mm512_loadu_pd(pack_AVX_Y.data());
  PackedPoint_avx pack_AVX = {X, Y};
  NormalBox_cpp box_CPP = {BoxDim(gen), BoxDim(gen)};
  NormalBox_avx box_AVX;
  box_AVX.Half_Width = box_CPP.Half_Width;
  box_AVX.Half_Height = box_CPP.Half_Height;
  Check_avx(Hausdorff_CPP(box_CPP, pack_CPP), Hausdorff_AVX(box_AVX, pack_AVX));
}

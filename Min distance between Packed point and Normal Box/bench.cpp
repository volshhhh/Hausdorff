#include "hausdorff_avx.h"
#include "hausdorff_cpp.h"
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <immintrin.h>
#include <random>


TEST_CASE("Random") {
  std::mt19937 gen{12345678};
  std::uniform_real_distribution<double> PackCord(-1000.0, -700.0);
  std::uniform_real_distribution<double> BoxDim(300.0, 500.0);

  std::array<double, 8> pack_CPP_X, pack_CPP_Y, pack_AVX_X, pack_AVX_Y;
  for (int i = 0; i < 8; i++) {
    pack_CPP_X[i] = PackCord(gen);
    pack_CPP_Y[i] = PackCord(gen);
    pack_AVX_X[i] = pack_CPP_X[i];
    pack_AVX_Y[i] = pack_CPP_Y[i];
  }
  PackedPoint_cpp packc = {pack_CPP_X, pack_CPP_Y};
  __m512d X = _mm512_loadu_pd(pack_AVX_X.data());
  __m512d Y = _mm512_loadu_pd(pack_AVX_Y.data());
  PackedPoint_avx packa = {X, Y};
  NormalBox_cpp boxc = {BoxDim(gen), BoxDim(gen)};
  NormalBox_avx boxa;
  boxa.w = boxc.w;
  boxa.h = boxc.h;

  BENCHMARK_ADVANCED("AVX512")(Catch::Benchmark::Chronometer meter) {
    meter.measure([&] { return Hausdorff_AVX(boxa, packa); });
  };

  BENCHMARK_ADVANCED("CPP")(Catch::Benchmark::Chronometer meter) {

    meter.measure([&] { return Hausdorff_CPP(boxc, packc); });
  };
}

#include "functions_avx.h"
#include <immintrin.h>

inline __m512d SquaredDistanceMask(__mmask8 mask, double x, double y,
                                   PackedPoint_avx a) {
  __m512d X = _mm512_set1_pd(x);
  __m512d Y = _mm512_set1_pd(y);
  __m512d tp1 = _mm512_setzero_pd();
  __m512d tp2 = _mm512_setzero_pd();
  __m512d tmp1 = _mm512_mask_sub_pd(tp1, mask, a.x, X);
  __m512d tmp2 = _mm512_mask_sub_pd(tp2, mask, a.y, Y);
  tmp1 = _mm512_mul_pd(tmp1, tmp1);
  tmp2 = _mm512_mul_pd(tmp2, tmp2);
  __m512d result = _mm512_add_pd(tmp1, tmp2);
  return result;
}

inline __m512d Hausdorff_AVX(NormalBox_avx box, PackedPoint_avx a) {
  PackedPoint_avx A = {_mm512_abs_pd(a.x), _mm512_abs_pd(a.y)};

  __m512d up =
      SquaredDistanceMask(IsUp(box, A), -box.Half_Width, box.Half_Height, A);

  __m512d right =
      SquaredDistanceMask(IsRight(box, A), box.Half_Width, -box.Half_Height, A);

  __m512d diag1 = SquaredDistanceMask(IsDiagonal(box, A), -box.Half_Width,
                                      box.Half_Height, A);
  __m512d diag2 = SquaredDistanceMask(IsDiagonal(box, A), box.Half_Width,
                                      -box.Half_Height, A);
  __m512d diag = _mm512_max_pd(diag1, diag2);

  __m512d inside =
      SquaredDistanceMask(Within(box, A), -box.Half_Width, -box.Half_Height, A);

  __m512d result =
      _mm512_max_pd(_mm512_max_pd(_mm512_max_pd(up, right), diag), inside);

  return result;
}

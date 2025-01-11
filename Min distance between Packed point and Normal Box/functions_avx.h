#include "structures_avx.h"
#include <immintrin.h>

inline __mmask8 Within(NormalBox_avx box, PackedPoint_avx &p) {
  __m512d W = _mm512_set1_pd(box.Half_Width);
  __m512d H = _mm512_set1_pd(box.Half_Height);
  __mmask8 mask1 = _mm512_cmp_pd_mask(p.x, W, _CMP_LE_OQ); // p.x <= w
  __mmask8 mask2 = _mm512_cmp_pd_mask(p.y, H, _CMP_LE_OQ); // p.y <= h
  return mask1 & mask2;
}

inline __mmask8 IsUp(NormalBox_avx box, PackedPoint_avx &p) {
  __m512d W = _mm512_set1_pd(box.Half_Width);
  __m512d H = _mm512_set1_pd(box.Half_Height);
  __mmask8 mask1 = _mm512_cmp_pd_mask(p.x, W, _CMP_LE_OQ); // p.x <= w
  __mmask8 mask2 = _mm512_cmp_pd_mask(p.y, H, _CMP_GT_OQ); // p.y > h
  return mask1 & mask2;
}

inline __mmask8 IsRight(NormalBox_avx box, PackedPoint_avx &p) {
  __m512d W = _mm512_set1_pd(box.Half_Width);
  __m512d H = _mm512_set1_pd(box.Half_Height);
  __mmask8 mask1 = _mm512_cmp_pd_mask(p.x, W, _CMP_GT_OQ); // p.x > w
  __mmask8 mask2 = _mm512_cmp_pd_mask(p.y, H, _CMP_LE_OQ); // p.y <= h
  return mask1 & mask2;
}

inline __mmask8 IsDiagonal(NormalBox_avx box, PackedPoint_avx &p) {
  __m512d W = _mm512_set1_pd(box.Half_Width);
  __m512d H = _mm512_set1_pd(box.Half_Height);
  __mmask8 mask1 = _mm512_cmp_pd_mask(p.x, W, _CMP_GT_OQ); // p.x > w
  __mmask8 mask2 = _mm512_cmp_pd_mask(p.y, H, _CMP_GT_OQ); // p.y > h
  return mask1 & mask2;
}
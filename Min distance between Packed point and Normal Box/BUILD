load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "hausdorff",
    hdrs = ["hausdorff_cpp.h",
            "hausdorff_avx.h",
            "functions_avx.h",
            "structures_avx.h",
            "structures_cpp.h"        
    ],
    copts = [
        "-m64",
        "-mavx512f",
        "-mavx512er",
        "-O3"
    ]
)

cc_test(
    name = "test_hausdorff",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":hausdorff",
        "//tools/bazel:catch2",
    ],
    copts = [
        "-m64",
        "-mavx512f",
        "-mavx512er",
        "-O3"
    ]
)

cc_test(
    name = "benchmark_main",
    # size = "small",
    srcs = ["bench.cpp"],
    deps = [
        ":hausdorff",
        "//tools/bazel:catch2",
    ],
    copts = [
        "-m64",
        "-mavx512f",
        "-mavx512er",
        "-O3"
    ]
)

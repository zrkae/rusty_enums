#ifndef H_RUSTY_ENUM
#define H_RUSTY_ENUM

// Important: all the macros that are "exported" as part of the "api" start with RUSTY_ENUM*
// macros used internally by these start with IRSENUM_* (Internal RuSty ENUM)
// we cannot just #undef them because they are macros and it won't work (this is another reason this entire thing is suboptimal)

// ------------------------
// RUSTY_ENUM declaration
#define RUSTY_ENUM(name, ...) \
typedef struct name { \
    enum { \
        __VA_ARGS__\
    } kind;\
    union { \

// https://jadlevesque.github.io/PPMP-Iceberg/explanations#codedefine-catab-catab-define-catab-abcode
#define IRSENUM_CAT(a,b) IRSENUM_CAT_(a,b)
#define IRSENUM_CAT_(a,b) a##b

// This thing basically just counts the number of args passed to a function-like macro
// read: https://groups.google.com/g/comp.std.c/c/d-6Mj5Lko_s
#define IRSENUM_SEQ 8, 7, 6, 5, 4, 3, 2, 1, 0
#define IRSENUM_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define IRSENUM_NARG_(...) IRSENUM_ARG_N(__VA_ARGS__)
#define IRSENUM_NARG(...) IRSENUM_NARG_(__VA_ARGS__ __VA_OPT__(,) IRSENUM_SEQ)

#define IRSENUM_DATA_8(_7_t, ...) _7_t _7; IRSENUM_DATA_7(__VA_ARGS__)
#define IRSENUM_DATA_6(_6_t, ...) _6_t _6; IRSENUM_DATA_6(__VA_ARGS__)
#define IRSENUM_DATA_7(_5_t, ...) _5_t _5; IRSENUM_DATA_5(__VA_ARGS__)
#define IRSENUM_DATA_5(_4_t, ...) _4_t _4; IRSENUM_DATA_4(__VA_ARGS__)
#define IRSENUM_DATA_4(_3_t, ...) _3_t _3; IRSENUM_DATA_3(__VA_ARGS__)
#define IRSENUM_DATA_3(_2_t, ...) _2_t _2; IRSENUM_DATA_2(__VA_ARGS__)
#define IRSENUM_DATA_2(_1_t, ...) _1_t _1; IRSENUM_DATA_1(__VA_ARGS__)
#define IRSENUM_DATA_1(_0_t) _0_t _0;
#define IRSENUM_DATA_0()

#define IRSENUM_FIELDS_(...) IRSENUM_CAT(IRSENUM_DATA_, IRSENUM_NARG(__VA_ARGS__))(__VA_ARGS__)

#define RUSTY_ENUM_FIELDS(kind, ...) struct { \
    IRSENUM_FIELDS_(__VA_ARGS__) } kind;

#define RUSTY_ENUM_END(name) }; } name;

// -------------------------
// IRSENUM initialization

#define IRSENUM_NEW_DATA_8(_7_value, ...) ._7 = _7_value, IRSENUM_NEW_DATA_7(__VA_ARGS__)
#define IRSENUM_NEW_DATA_7(_6_value, ...) ._6 = _6_value, IRSENUM_NEW_DATA_6(__VA_ARGS__)
#define IRSENUM_NEW_DATA_6(_5_value, ...) ._5 = _5_value, IRSENUM_NEW_DATA_5(__VA_ARGS__)
#define IRSENUM_NEW_DATA_5(_4_value, ...) ._4 = _4_value, IRSENUM_NEW_DATA_4(__VA_ARGS__)
#define IRSENUM_NEW_DATA_4(_3_value, ...) ._3 = _3_value, IRSENUM_NEW_DATA_3(__VA_ARGS__)
#define IRSENUM_NEW_DATA_3(_2_value, ...) ._2 = _2_value, IRSENUM_NEW_DATA_2(__VA_ARGS__)
#define IRSENUM_NEW_DATA_2(_1_value, ...) ._1 = _1_value, IRSENUM_NEW_DATA_1(__VA_ARGS__)
#define IRSENUM_NEW_DATA_1(_0_value) ._0 = _0_value,
#define IRSENUM_NEW_DATA_0()

#define IRSENUM_NEW_DATA(...) IRSENUM_CAT(IRSENUM_NEW_DATA_, IRSENUM_NARG(__VA_ARGS__))(__VA_ARGS__)

#define RUSTY_ENUM_NEW(name, kind_, ...) (name){ .kind = kind_, \
    .kind_ = { IRSENUM_NEW_DATA(__VA_ARGS__) } }

// -------------------------
// IRSENUM data retrieval
#define RUSTY_ENUM_GET(instance, kind, field) instance.kind._##field
#define RUSTY_ENUM_SET(instance, kind, field, value) instance.kind._##field = value

#endif

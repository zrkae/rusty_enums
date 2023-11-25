#ifndef RUSTY_ENUM_H_
#define RUSTY_ENUM_H_

// TODOS/ISSUES:
//  - Validate we are passing enough arguments when doing RUST_ENUM_NEW
//  - Allow enum kinds with no data (lol)

// ------------------------
// RUSTY_ENUM declaration
#define RUSTY_ENUM(name, ...) \
typedef struct name { \
    enum { \
        __VA_ARGS__\
    } kind;\
    union { \

// https://jadlevesque.github.io/PPMP-Iceberg/explanations#codedefine-catab-catab-define-catab-abcode
#define RUSTY_ENUM_CAT(a,b) RUSTY_ENUM_CAT_(a,b)
#define RUSTY_ENUM_CAT_(a,b) a##b

// This thing basically just counts the number of args passed to a function-like macro
// read: https://groups.google.com/g/comp.std.c/c/d-6Mj5Lko_s
#define RUSTY_ENUM_SEQ 8, 7, 6, 5, 4, 3, 2, 1
#define RUSTY_ENUM_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define RUSTY_ENUM_NARG_(...) RUSTY_ENUM_ARG_N(__VA_ARGS__)
#define RUSTY_ENUM_NARG(...) RUSTY_ENUM_NARG_(__VA_ARGS__, RUSTY_ENUM_SEQ)

#define RUSTY_ENUM_DATA_8(_7_t, ...) _7_t _7; RUSTY_ENUM_DATA_7(__VA_ARGS__)
#define RUSTY_ENUM_DATA_6(_6_t, ...) _6_t _6; RUSTY_ENUM_DATA_6(__VA_ARGS__)
#define RUSTY_ENUM_DATA_7(_5_t, ...) _5_t _5; RUSTY_ENUM_DATA_5(__VA_ARGS__)
#define RUSTY_ENUM_DATA_5(_4_t, ...) _4_t _4; RUSTY_ENUM_DATA_4(__VA_ARGS__)
#define RUSTY_ENUM_DATA_4(_3_t, ...) _3_t _3; RUSTY_ENUM_DATA_3(__VA_ARGS__)
#define RUSTY_ENUM_DATA_3(_2_t, ...) _2_t _2; RUSTY_ENUM_DATA_2(__VA_ARGS__)
#define RUSTY_ENUM_DATA_2(_1_t, ...) _1_t _1; RUSTY_ENUM_DATA_1(__VA_ARGS__)
#define RUSTY_ENUM_DATA_1(_0_t) _0_t _0;

#define RUSTY_ENUM_FIELDS_(...) RUSTY_ENUM_CAT(RUSTY_ENUM_DATA_, RUSTY_ENUM_NARG(__VA_ARGS__))(__VA_ARGS__)

#define RUSTY_ENUM_FIELDS(kind, ...) struct { \
    RUSTY_ENUM_FIELDS_(__VA_ARGS__) } kind;

#define RUSTY_ENUM_END(name) }; } name;

// -------------------------
// RUSTY_ENUM initialization

#define RUSTY_ENUM_NEW_DATA_8(_7_value, ...) ._7 = _7_value, RUSTY_ENUM_NEW_DATA_7(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_7(_6_value, ...) ._6 = _6_value, RUSTY_ENUM_NEW_DATA_6(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_6(_5_value, ...) ._5 = _5_value, RUSTY_ENUM_NEW_DATA_5(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_5(_4_value, ...) ._4 = _4_value, RUSTY_ENUM_NEW_DATA_4(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_4(_3_value, ...) ._3 = _3_value, RUSTY_ENUM_NEW_DATA_3(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_3(_2_value, ...) ._2 = _2_value, RUSTY_ENUM_NEW_DATA_2(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_2(_1_value, ...) ._1 = _1_value, RUSTY_ENUM_NEW_DATA_1(__VA_ARGS__)
#define RUSTY_ENUM_NEW_DATA_1(_0_value) ._0 = _0_value,

#define RUSTY_ENUM_NEW_DATA(...) RUSTY_ENUM_CAT(RUSTY_ENUM_NEW_DATA_, RUSTY_ENUM_NARG(__VA_ARGS__))(__VA_ARGS__)

#define RUSTY_ENUM_NEW(name, kind_, ...) (name){ .kind = kind_, \
    .kind_ = { RUSTY_ENUM_NEW_DATA(__VA_ARGS__) } }

// -------------------------
// RUSTY_ENUM data retrieval
#define RUSTY_ENUM_GET(instance, kind, field) instance.kind._##field
#define RUSTY_ENUM_SET(instance, kind, field, value) instance.kind._##field = value

#endif

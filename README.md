# Rusty Enums

### The problem(?):
C enums can only be assigned int values, furthermore these cannot repeat and you cannot specify the underlying type of the enum (you can in C++, though). 

### The "solution"
This small macro library enables you to simulate [rust](https://www.rust-lang.org/)-like enums by implementing them as a [tagged union](https://en.wikipedia.org/wiki/Tagged_union) and providing an interface to deal with them as if they were enumerations. You can have up to 8 data fields per kind, but this could easily be increased.

Let's say you want the equivalent of
```rust
enum IpAddr {
    V4(u8, u8, u8, u8),
    V6(&'static str),
}
```
in your C program. 

With this library you can write
```c
RUSTY_ENUM(IpAddr, V4, V6)
RUSTY_ENUM_FIELDS(V4, uin8_t, uint8_t, uint8_t, uint8_t)
RUSTY_ENUM_FIELDS(V6, const char *)
RUSTY_ENUM_END(IpAddr)
```

Which roughly expands to
```c
struct IpAddr {
    enum IpAddr_Kind {
        V4,
        V6
    } kind;
    union {
        struct {
            uint8_t _0;
            uint8_t _1;
            uint8_t _2;
            uint8_t _3;
        } V4;
        struct {
            const char *_0;
        } V6;
    };
};
```

Create a new instance
```
IpAddr addr = RUSTY_ENUM_NEW(IpAddr, V4, 192, 168, 1, 0);
```
important: you should ensure that you are passing the exact amount of arguments
that the enum kind has data fields here, otherwise expect the unexpected to happen

You can then switch on it like so
```c
switch(addr.kind) {
    case V4:
        /* do stuff */
    case V6:
        /* do stuff */
}
```

And access data with
```c
RUSTY_ENUM_GET(addr, V4, 0);
// or equivalently
addr.V4._0;
```

### faq
#### So... is this just a struct with a union and an enum inside?
yes.

#### Shouldn't I then implement my own super cool tagged union without all this macro stuff?
probably yeah

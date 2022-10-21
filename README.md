# Hello unikernel

Hello world app implementing a LibUV UDP echo server and greet/goodbye messages via json-c.
Made for the 2022 Munich Unikraft Hackathon.

## Build

```
$ mkdir build && cd build
$ cmake ..
$ make
```

## Parameters

By default it uses the address `0.0.0.0` and port `8888`, which can be changed in `src/app/constants.h`.

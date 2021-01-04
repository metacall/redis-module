# MetaCall Redis Module

Extend Redis with TypeScript, JavaScript, Python, C#, Ruby... modules with **[MetaCall](https://github.com/metacall/core)**.

# Building

[Build](https://github.com/metacall/core#6-build-system) and/or [install](https://github.com/metacall/core#41-installation) MetaCall and then run:

```sh
make
```

The output module will be located in: `./build/metacallredis.so`.

# Docker

```sh
docker build -t metacall/redis .
docker run --rm -it metacall/redis
```

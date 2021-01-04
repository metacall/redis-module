# MetaCall Redis Module

Extend Redis with TypeScript, JavaScript, Python, C#, Ruby... modules with **[MetaCall](https://github.com/metacall/core)**.

This module has been tested with Redis 6.0.9.

# Building

[Build](https://github.com/metacall/core#6-build-system) and/or [install](https://github.com/metacall/core#41-installation) MetaCall and then run:

```sh
make
```

The output module will be located in: `./build/metacallredis.so`.

# Docker

```sh
docker build -t metacall/redis .
docker run -p 6379:6379 --rm --name metacall_redis -it metacall/redis
```

For testing our scripts:
```sh
docker exec -it metacall_redis redis-cli
```

Once inside of the redis-cli, we can do some invokations:
```sh
127.0.0.1:6379> invoke getDate
Tue, 25 Dec 52981 04:06:38 GMT
127.0.0.1:6379> invoke sum 3 4
7
```

In order to stop the container:
```sh
docker stop metacall_redis
```

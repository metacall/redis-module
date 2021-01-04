#
#	MetaCall Redis Module by Parra Studios
#	Extend Redis with TypeScript, JavaScript, Python, C#, Ruby... modules.
#
#	Copyright (C) 2016 - 2021 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
#
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#		http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
#

FROM metacall/core:dev AS builder

WORKDIR /redis

COPY . .

RUN make \
	&& cd examples \
	&& npm install

FROM metacall/core:runtime AS runtime

FROM redis:6.0.9-buster AS redis

ENV LOADER_LIBRARY_PATH=/usr/local/lib/

COPY --from=runtime /usr/local/lib/ /usr/local/lib/
COPY --from=builder /redis/build/metacallredis.so /usr/local/lib/metacallredis.so
COPY --from=builder /redis/examples/ /scripts/

RUN mkdir -p /usr/local/etc/redis/ \
	&& echo "loadmodule /usr/local/lib/metacallredis.so /scripts" >> /usr/local/etc/redis/redis.conf \
	&& cd /usr/local/lib/ \
	&& ldconfig

CMD [ "redis-server", "/usr/local/etc/redis/redis.conf" ]

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

# Builder Image
FROM metacall/core:dev AS builder

WORKDIR /redis

# Copy project
COPY . .

# Build and install dependencies
RUN make \
	&& cd examples \
	&& npm install

# Image for runtime dependencies
FROM metacall/core:runtime AS runtime

# Redis Image
FROM redis:6.0.9-buster AS redis

# Define MetaCall environment variables
ENV LOADER_LIBRARY_PATH=/usr/local/lib/ \
	LOADER_SCRIPT_PATH=/scripts/ \
	CONFIGURATION_PATH=/usr/local/share/metacall/configurations/global.json \
	SERIAL_LIBRARY_PATH=/usr/local/lib/ \
	DETOUR_LIBRARY_PATH=/usr/local/lib/ \
	PORT_LIBRARY_PATH=/usr/local/lib/

# Copy runtime dependencies
COPY --from=runtime /usr/local/lib/ /usr/local/lib/
COPY --from=runtime /usr/local/share/metacall/ /usr/local/share/metacall/
COPY --from=runtime /usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/

# Copy redis module and scripts from builder
COPY --from=builder /redis/build/metacallredis.so /usr/local/lib/metacallredis.so
COPY --from=builder /redis/examples/ /scripts/

# Set up configuration and give permissions to the scripts
RUN mkdir -p /usr/local/etc/redis/ \
	&& echo "loadmodule /usr/local/lib/metacallredis.so /scripts" >> /usr/local/etc/redis/redis.conf \
	&& cd /usr/local/lib/ \
	&& ldconfig \
	&& chmod 755 -R /scripts/

# Entry point with MetaCall module configuration
CMD [ "redis-server", "/usr/local/etc/redis/redis.conf" ]

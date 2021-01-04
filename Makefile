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

# Define flags depending on the OS
ifeq ($(shell sh -c 'uname -s 2>/dev/null || echo unknown'),Linux)
	OBJ_CFLAGS ?= -Wall -W -O3 -fno-common -std=c99
	OBJ_CXXFLAGS ?= -Wall -W -O3 -fno-common -std=c++17
	OBJ_LDFLAGS ?= -shared
else
	OBJ_CFLAGS ?= -Wall -W -O3 -dynamic -fno-common -std=c99
	OBJ_CXXFLAGS ?= -Wall -W -O3 -dynamic -fno-common -std=c++17
	OBJ_LDFLAGS ?= -bundle -undefined dynamic_lookup
endif

INCLUDES=-I/usr/local/include -I./source -I./includes

all:
	@mkdir -p build
	@$(CXX) $(CXXFLAGS) $(OBJ_CXXFLAGS) $(INCLUDES) -fPIC -c source/filesystem.cpp -lstdc++fs -lmetacall -o build/filesystem.o
	@$(CC) $(CFLAGS) $(OBJ_CFLAGS) $(INCLUDES) -fPIC -c source/redis_api.c -lmetacall -o build/redis_api.o
	@$(CC) $(CFLAGS) $(OBJ_CFLAGS) $(INCLUDES) -fPIC -c source/module.c -lmetacall -o build/module.o
	@$(CXX) -o build/metacallredis.so build/filesystem.o build/redis_api.o build/module.o $(OBJ_LDFLAGS) -lstdc++fs -lmetacall

clean:
	@rm -rf build/

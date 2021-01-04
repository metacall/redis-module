/*
 *	MetaCall Redis Module by Parra Studios
 *	Extend Redis with TypeScript, JavaScript, Python, C#, Ruby... modules.
 *
 *	Copyright (C) 2016 - 2021 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

/* -- Headers -- */

#include <redis-api.h>

#include <assert.h>
#include <stdlib.h>

#include <metacall/metacall.h>

/* -- Macros -- */

#define REDIS_API_X_MACRO(X) \
	X(redis_milliseconds, METACALL_LONG, 0) \
	X(redis_get_client_id, METACALL_LONG, 0) \
	X(redis_select_db, METACALL_BOOL, 1, METACALL_INT)

#define REDIS_API_STRINGIFY_IMPL(x) #x
#define REDIS_API_STRINGIFY(x) REDIS_API_STRINGIFY_IMPL(x)

/* -- Member Data -- */

RedisModuleCtx * rm_ctx;

/* -- Methods -- */

void * redis_milliseconds(size_t argc, void * argv[], void * ctx)
{
	(void)argc;
	(void)argv;
	(void)ctx;

	return metacall_value_create_long((long)RedisModule_Milliseconds());
}

void * redis_get_client_id(size_t argc, void * argv[], void * ctx)
{
	(void)argc;
	(void)argv;
	(void)ctx;

	return metacall_value_create_long((long)RedisModule_GetClientId(rm_ctx));
}

void * redis_select_db(size_t argc, void * argv[], void * ctx)
{
	assert(argc == 1);

	(void)ctx;

	int newid = metacall_value_to_int(argv[0]);
	int ret = RedisModule_SelectDb(rm_ctx, newid);

	return metacall_value_create_bool((boolean)(ret == REDISMODULE_OK));
}

// TODO: Implement the rest of the Redis API

int redis_api_register(RedisModuleCtx * ctx)
{
	// Initialize Redis context
	rm_ctx = ctx;

	// Register Redis API
	#define redis_api_register_impl(func, ret, ...) \
		if (metacall_register(REDIS_API_STRINGIFY(func), &func, NULL, ret,  __VA_ARGS__) != 0) return 1;

	REDIS_API_X_MACRO(redis_api_register_impl)

	#undef redis_api_register_impl

	return 0;
}

void redis_api_context(RedisModuleCtx * ctx)
{
	rm_ctx = ctx;
}

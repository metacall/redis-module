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

#include <redis_api.h>
#include <filesystem.h>

#include <metacall/metacall.h>

/* -- Methods -- */

int MetaCall_RedisCommand(RedisModuleCtx * ctx, RedisModuleString * argv[], int argc)
{
	size_t args_count;
	void ** values, * ret;
	size_t length;

	// Update context
	redis_api_context(ctx);

	// Check for valid arguments
	if (argc < 2)
	{
		return RedisModule_WrongArity(ctx);
	}

	// Create the array of values if any
	args_count = (size_t)(argc - 2);

	if (args_count > 0)
	{
		values = malloc(sizeof(void *) * args_count);

		for (int iterator = 2; iterator < argc; ++iterator)
		{
			const char * str = RedisModule_StringPtrLen(argv[iterator], &length);
			values[iterator - 2] = metacall_value_create_string(str, length);
		}
	}
	else
	{
		values = metacall_null_args;
	}

	// Invoke the function
	ret = metacallv_s(RedisModule_StringPtrLen(argv[1], &length), values, args_count);

	// Clear arguments
	if (args_count > 0)
	{
		for (size_t iterator = 0; iterator < args_count; ++iterator)
		{
			metacall_value_destroy(values[iterator]);
		}

		free(values);
	}

	// Return the result
	if (ret == NULL)
	{
		return RedisModule_ReplyWithNull(ctx);
	}
	else
	{
		const char * str = metacall_value_cast_string(&ret);
		int result = RedisModule_ReplyWithSimpleString(ctx, str);
		metacall_value_destroy(ret);
		return result;
	}
}

int RedisModule_OnLoad(RedisModuleCtx * ctx, RedisModuleString * argv[], int argc)
{
	if (argc != 1)
	{
		RedisModule_Log(ctx, "warning", "Incorrect number of arguments passed to MetaCall Redis Module.\n");
		return REDISMODULE_ERR;
	}

	if (RedisModule_Init(ctx, "metacall", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
	{
		RedisModule_Log(ctx, "warning", "Failed to initialize Redis Module.\n");
		return REDISMODULE_ERR;
	}

	if (metacall_initialize() != 0)
	{
		RedisModule_Log(ctx, "warning", "Failed to initialize MetaCall.\n");
		return REDISMODULE_ERR;
	}

	if (redis_api_register(ctx) != 0)
	{
		RedisModule_Log(ctx, "warning", "Failed to register Redis API into MetaCall.\n");
		return REDISMODULE_ERR;
	}

	size_t length = 0;
	const char * path = RedisModule_StringPtrLen(argv[0], &length);

	if (fs_load_scripts(path) != 0)
	{
		RedisModule_Log(ctx, "warning", "Failed to load scripts from folder: %s\n", path);
		return REDISMODULE_ERR;
	}

	if (RedisModule_CreateCommand(ctx, "invoke", MetaCall_RedisCommand, "write", 0, -1, 1) == REDISMODULE_ERR)
	{
		RedisModule_Log(ctx, "warning", "Failed to create MetaCall invoke commmand.\n");
		return REDISMODULE_ERR;
	}

	return REDISMODULE_OK;
}

void RedisModule_OnUnload()
{
	metacall_destroy();
}

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

#ifndef METACALL_REDIS_MODULE_API_H
#define METACALL_REDIS_MODULE_API_H 1

/* -- Headers -- */

#include <redismodule.h>

/* -- Methods -- */

#ifdef __cplusplus
extern "C" {
#endif

int redis_api_register(RedisModuleCtx * ctx);

void redis_api_context(RedisModuleCtx * ctx);

#ifdef __cplusplus
}
#endif

#endif /* METACALL_REDIS_MODULE_API_H */

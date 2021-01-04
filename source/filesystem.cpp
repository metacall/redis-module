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

#include <filesystem.h>

#include <string>
#include <iostream>
#include <filesystem>
#include <map>

#include <metacall/metacall.h>

/* -- Type Definitions -- */

typedef std::map<std::string, std::string> ext_to_tag_map;

/* -- Member Data -- */

static ext_to_tag_map ext_to_tag =
{
	ext_to_tag_map::value_type("mock", "mock"),
	ext_to_tag_map::value_type("py", "py"),
	ext_to_tag_map::value_type("rb", "rb"),
	ext_to_tag_map::value_type("cs", "cs"),
	ext_to_tag_map::value_type("vb", "cs"),
	ext_to_tag_map::value_type("dll", "cs"),
	ext_to_tag_map::value_type("js", "node"),
	ext_to_tag_map::value_type("node", "node"),
	ext_to_tag_map::value_type("cob", "cob"),
	ext_to_tag_map::value_type("cbl", "cob"),
	ext_to_tag_map::value_type("cpy", "cob"),
	ext_to_tag_map::value_type("ts", "ts"),
	ext_to_tag_map::value_type("jsx", "ts"),
	ext_to_tag_map::value_type("tsx", "ts")
};

/* -- Methods -- */

int fs_load_scripts(const char * path)
{
	namespace fs = std::filesystem;

	for (const auto & entry : fs::directory_iterator(std::string(path)))
	{
		std::string script = entry.path();
		std::string extension = script.substr(script.find_last_of(".") + 1);
		std::string tag = ext_to_tag[extension];
		const char * paths[] = { script.c_str() };

		if (metacall_load_from_file(tag.c_str(), paths, 1, NULL) != 0)
		{
			return 1;
		}
	}

	return 0;
}

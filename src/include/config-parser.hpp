#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

rapidjson::Document parse_istream_cfg(const char* config_filename);
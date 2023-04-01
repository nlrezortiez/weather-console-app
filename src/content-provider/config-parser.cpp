#include "../include/config-parser.hpp"

rapidjson::Document parse_istream_cfg(const char* config_filename) {
    std::ifstream config_stream(config_filename);
    rapidjson::IStreamWrapper config_stream_wrapper(config_stream);
    rapidjson::Document config;
    config.ParseStream(config_stream_wrapper);
    return config;
}

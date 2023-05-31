// Usage:
// ./example-bin australia-latest.osrm '[[115.8706342, -32.0081372], [115.894833, -32.024547]]'
// At least 2 coordinates must be specified

#include "osrm/trip_parameters.hpp"

#include "osrm/engine_config.hpp"
#include "osrm/osrm.hpp"

#include "util/json_renderer.hpp"
#include "rapidjson/document.h"

int main(int argc, const char *argv[])
{
    using namespace osrm;
    using namespace rapidjson;

    EngineConfig config;

    config.storage_config = {argv[1]};
    config.use_shared_memory = false;

    config.algorithm = EngineConfig::Algorithm::MLD;

    const OSRM osrm{config};


    Document document;
    //std::string json_str{"{\"a\": 1}"};
    //char json_str[] = "{\"a\": 1}";
    // std::cout << "argv2: " << argv[2];

    const char *json_str = argv[2];
    document.Parse(json_str);
    RouteParameters params;

    for (auto& v : document.GetArray()) {
      Value::Array a = v.GetArray();
      params.coordinates.push_back({util::FloatLongitude{a[0].GetFloat()}, util::FloatLatitude{a[1].GetFloat()}});
      printf("lop");
    }

    engine::api::ResultT result = json::Object();

    const auto status = osrm.Route(params, result);

    auto &json_result = result.get<json::Object>();

    std::string out_str;
    osrm::util::json::render(out_str, json_result);
    std::cout << out_str;
}

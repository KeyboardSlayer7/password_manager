#pragma once

#include "nlohmann/json.hpp"
using json = nlohmann::json;

void new_entry(json& data, std::string& password);
void get_entry(json& data, std::string& password);
// void update_entry(json& data);
void delete_entry(json& data);
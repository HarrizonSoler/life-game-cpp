#pragma once

#include <json/value.h>
#include <string>
#include <vector>
class JsonVal {
    bool isValidInt(const std::string &fieldName, const Json::Value &value, const int low, const int high, std::string &err);
    bool isValidArray(const std::string &fieldName, const Json::Value &value, const int low, const int high, std::string &err);

    public:
        bool validateJson(const Json::Value &json, std::string &err);
};

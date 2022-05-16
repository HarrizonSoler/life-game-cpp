#include "JsonVal.h"
#include <cmath>
#include <json/value.h>
#include <vector>

bool JsonVal::isValidInt(const std::string &fieldName, const Json::Value &value, const int low, const int high, std::string &err) {
    if (value.isNull()) {
        err = "Null " + fieldName + " value";
        return false;
    }

    if (!value.isInt()) {
        err = "Invalid " + fieldName + " format";
        return false;
    }

    if ((value.asInt() < low) || (value.asInt() > high)) {
        err = "The " + fieldName + " range must be between " + std::to_string(low) + " and " + std::to_string(high);
        return false;
    }

    return true;
}

bool JsonVal::isValidArray(const std::string &fieldName, const Json::Value &value, const int low, const int high, std::string &err) {
    if (value.isNull()) {
        err = "Null " + fieldName + " value";
        return false;
    }

    if (!value.isArray()) {
        err = "Invalid " + fieldName + " format";
        return false;
    }

    if ((value.size() < low) || (value.size() > high)) {
        err = "The " + fieldName + " size must be between " + std::to_string(low) + " and " + std::to_string(high);
        return false;
    }

    for (int idx = 0; idx < value.size(); ++idx) {
        value[idx].asInt();
    }

    return true;
}

bool JsonVal::validateJson(const Json::Value &json, std::string &err) {
    if (!isValidInt("size", json["size"], 15, 50, err)) {
        return false;
    }

    if (!isValidInt("ticksNumber", json["ticksNumber"], 5, 100, err)) {
        return false;
    }

    if (!isValidArray("liveCellPositions", json["liveCellPositions"], 5, std::pow(json["size"].asInt(), 2), err)) {
        return false;
    }

    return true;
}

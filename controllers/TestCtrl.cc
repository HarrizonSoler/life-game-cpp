#include "TestCtrl.h"
#include <iostream>
#include <vector>

void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto json = req -> getJsonObject();

    if (json == nullptr) {
        Json::Value ret;
        ret["error"] = "No json object found";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp -> setStatusCode(HttpStatusCode::k400BadRequest);
        callback(resp);
        return;
    }

    auto pJson = *json;
    std::string err;

    try {
        if (!jsonVal.validateJson(pJson, err)) {
            Json::Value ret;
            ret["error"] = err;
            
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp -> setStatusCode(HttpStatusCode::k400BadRequest);
            callback(resp);
            return;
        }
    } catch(const Json::Exception &e) {
        LOG_ERROR << e.what();

        Json::Value ret;
        ret["error"] = "Field type error";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp -> setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    Game game(
            json -> get("size", "").asInt(),
            json -> get("ticksNumber", "").asInt(),
            json -> get("liveCellPositions", ""));

    auto resp = HttpResponse::newHttpJsonResponse(game.json);
    resp -> setStatusCode(HttpStatusCode::k200OK);

    callback(resp);
    return;
}

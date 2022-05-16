#include <drogon/drogon.h>

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",3003);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
                //LOG_DEBUG << "postHandling1";
                resp->addHeader("Access-Control-Allow-Origin", "*");
            });

    drogon::app().run();
    return 0;
}

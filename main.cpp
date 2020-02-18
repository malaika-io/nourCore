#include "easywsclient.hpp"
#include "easywsclient.cpp"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include <jsoncpp/json/json.h>
#include "HTTPRequest.hpp"

using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;

struct intent {
    std::string name;
    std::string slotsState;
    std::string slotsNames;
};

intent currentIntent;

void speak(std::string message)
{
    http::Request request("http://matrix.local:12101/api/text-to-speech");
    // send a post request
    const http::Response postResponse = request.send("POST", message, {
        "Content-Type: application/x-www-form-urlencoded"
    });
    std::cout << std::string(postResponse.body.begin(), postResponse.body.end()) << '\n';

}
void handle_message(const std::string & message)
{
    Json::Reader reader;
    Json::Value obj;
    reader.parse(message, obj);
    std::string name = obj["intent"]["name"].asString();
    std::string  slotsState = obj["slots"]["state"].asString();
    std::string  slotsName = obj["slots"]["name"].asString();

    std::cout  <<  name << std::endl;
    std::cout  << slotsState << std::endl;
    std::cout  << slotsName << std::endl;
    speak("lampe du salon allumer");
}

int main(int argc, char *argv[])
{
    ws = WebSocket::from_url("ws://localhost:12101/api/events/intent");
    assert(ws);

    while (ws->getReadyState() != WebSocket::CLOSED) {
        WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
        ws->poll();
        ws->dispatch(handle_message);
    }
    delete ws;

    return 0;
}

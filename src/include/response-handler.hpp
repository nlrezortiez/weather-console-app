#pragma once

#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <iostream>
#include <vector>

class Forecast;
class Config;

template <typename T, typename... DataType>
class ResponseHandler {

    virtual void sendRequest(const DataType&... data) = 0;

    virtual T parseResponse() = 0;

    virtual bool checkSuccess() = 0;
};

class ConvertionResponseHandler
    : public ResponseHandler<std::pair<double, double>, std::string> {
public:
    void sendRequest(const std::string& city_name) override;

    std::pair<double, double> parseResponse() override;

    bool checkSuccess() override;

private:
    cpr::Response response_;
    rapidjson::Document json_response_;

    const std::string CONVERTION_BASE_URL =
        "https://api.api-ninjas.com/v1/city";
    const std::string CONVERTION_API_KEY =
        "Rf8FLQ/8Y+ITSzggbBzG2A==OalAFzJ2s8HQ3fWf";
};

class TimezoneConvertResponseHandler
    : public ResponseHandler<std::string, std::string> {
public:
    void sendRequest(const std::string& city_name) override;

    std::string parseResponse() override;

    bool checkSuccess() override;

private:
    cpr::Response response_;
    rapidjson::Document json_response_;

    const std::string TIMEZONE_BASE_URL =
        "https://api.api-ninjas.com/v1/timezone";
    const std::string CONVERTION_API_KEY =
        "Rf8FLQ/8Y+ITSzggbBzG2A==OalAFzJ2s8HQ3fWf";
};

class ForecastResponseHandler
    : public ResponseHandler<Forecast, Forecast, Config> {
public:
    void sendRequest(const Forecast& forecast, const Config& config) override;

    Forecast parseResponse() override;

    bool checkSuccess() override;

private:
    cpr::Response response_;
    rapidjson::Document json_response_;

    const std::string WEATHER_API_BASE_URL =
        "https://api.open-meteo.com/v1/forecast";
};

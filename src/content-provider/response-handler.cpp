#include "../include/response-handler.hpp"
#include "../forecast/forecast.hpp"

void ConvertionResponseHandler::sendRequest(const std::string& city_name) {
    response_ = cpr::Get(
        cpr::Url{CONVERTION_BASE_URL},
        cpr::Parameters{{"name", city_name}},
        cpr::Header{{"X-Api-Key", CONVERTION_API_KEY}});
    if (!checkSuccess()) {
        return;
    }
}

std::pair<double, double> ConvertionResponseHandler::parseResponse() {
    auto response_data_array =
        json_response_.Parse(response_.text.c_str()).GetArray();
    return {
        response_data_array[0]["latitude"].GetDouble(),
        response_data_array[0]["longitude"].GetDouble()};
}

bool ConvertionResponseHandler::checkSuccess() {
    if (response_.status_code == 0) {
        std::cerr << response_.error.message << std::endl;
        return false;
    } else if (response_.status_code >= 400) {
        std::cerr << "Error [" << response_.status_code << "] making request"
                  << std::endl;
        return false;
    } else {
        return true;
    }
}

void ForecastResponseHandler::sendRequest(
    const Forecast& forecast,
    const Config& config) {
    response_ = cpr::Get(
        cpr::Url{WEATHER_API_BASE_URL},
        cpr::Parameters{
            {"latitude", std::to_string(forecast.getLatitude())},
            {"longitude", std::to_string(forecast.getLongitude())},
            {"daily",
             "weathercode,temperature_2m_max,apparent_temperature_max,sunrise,"
             "sunset,precipitation_sum,winddirection_10m_dominant"},
            {"forecast_days", std::to_string(config.getConfigForecastDays())},
            {"timezone", forecast.getTimezone()}});
    std::cout << response_.url << std::endl;
}

Forecast ForecastResponseHandler::parseResponse() {
    return Forecast({0, 0}, "qwe");
}

bool ForecastResponseHandler::checkSuccess() {

}

void TimezoneConvertResponseHandler::sendRequest(const std::string& city_name) {
    response_ = cpr::Get(
        cpr::Url{TIMEZONE_BASE_URL},
        cpr::Parameters{{"city", city_name}},
        cpr::Header{{"X-Api-Key", CONVERTION_API_KEY}});
}
std::string TimezoneConvertResponseHandler::parseResponse() {
    json_response_.Parse(response_.text.c_str());
    return json_response_["timezone"].GetString();
}
bool TimezoneConvertResponseHandler::checkSuccess() {
    return false;
}

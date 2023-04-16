#include "forecast.hpp"

void ForecastAdapter::get() {
    for (auto& fc : forecast_) {
        ForecastResponseHandler request;
        request.sendRequest(*fc, config_);
        *fc = request.parseResponse();
    }
}

void ForecastAdapter::render() {
}

void Forecast::configure(
    std::string date_s,
    std::string sunrise_datetime_s,
    std::string sunset_datetime_s,
    int weathercode,
    double temperature_2m_max,
    double apparent_temperature_max,
    int precipitation_sum,
    int windspeed_10m) {
    this->date_s = date_s;
    this->sunrise_datetime_s = sunrise_datetime_s;
    this->sunset_datetime_s = sunset_datetime_s;
    this->weather_code = weathercode;
    this->temperature_2m_max = temperature_2m_max;
    this->apparent_temperature_max = apparent_temperature_max;
    this->precipitation_sum = precipitation_sum;
    this->windspeed_10m = windspeed_10m;
}

#pragma once

#include <utility>

#include "../include/config-setup.hpp"
#include "../include/terminal-renderer.hpp"

class Forecast {
public:
    Forecast(std::pair<double, double> coordinates, std::string timezone)
        : latitude(coordinates.first), longitude(coordinates.second),
          timezone(std::move(timezone)) {
    }
    double getLatitude() const noexcept {
        return latitude;
    }

    double getLongitude() const noexcept {
        return longitude;
    }

    std::string getTimezone() const noexcept {
        return timezone;
    }

private:
    double latitude;
    double longitude;
    std::string timezone;
    std::string title;
    int weather_code;
    double temperature_2m_max;
    double apparent_temperature_max;
    int precipitation_sum;
    int precipitation_probability_max;
    int windspeed_10m_max;
};

class ForecastAdapter {
public:
    explicit ForecastAdapter(
        const char* cfg_filename,
        Renderer renderer = TerminalRenderer())
        : renderer_(TerminalRenderer()) {
        config_.loadConfig(cfg_filename);
        config_.printConfigData();
        config_.getForecastHeaders(forecast_);
    }

    void get();
    void render();

private:
    Renderer renderer_;
    Config config_;
    std::vector<std::unique_ptr<Forecast>> forecast_;
};
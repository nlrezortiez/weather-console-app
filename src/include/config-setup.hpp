#pragma once

#include "config-parser.hpp"
#include "response-handler.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Forecast;

struct City {
public:
    using coordinates = std::pair<double, double>;
    friend std::ostream& operator<<(std::ostream& os, const City& city);

    explicit City(std::string name)
        : name_(std::move(name)), coordinates_({0, 0}),
          timezone_(std::string{}) {
    }

    City(std::string name, double lat, double lon)
        : name_(std::move(name)), coordinates_(lat, lon), timezone_(std::string{}) {
    }

    City(std::string name, double lat, double lon, std::string timezone)
        : name_(std::move(name)), coordinates_(lat, lon), timezone_(std::move(timezone)) {
    }

    void ConvertCityNameToCoordinates();
    void ConvertCityNameToTimezone();
    [[nodiscard]] std::string copyTimezone() const noexcept {
        return timezone_;
    }
    [[nodiscard]] coordinates copyCoordinates() const noexcept {
        return coordinates_;
    }

protected:
    std::string timezone_;
    coordinates coordinates_; // first: latitude second: longitude
    std::string name_;
};


class Config {
public:
    void loadConfig(const char* config);

    Config() = default;

    explicit Config(const char* config) {
        loadConfig(config);
    }

    void
    getForecastHeaders(std::vector<std::unique_ptr<Forecast>>& container) const;

    std::size_t getConfigUpdateTime() const noexcept {
        return update_time_;
    }
    std::size_t getConfigForecastDays() const noexcept {
        return forecast_days_;
    }

    void printConfigData() const noexcept;

private:
    std::vector<std::unique_ptr<City>>  cities_data_;
    std::size_t update_time_{};
    std::size_t forecast_days_{};
};
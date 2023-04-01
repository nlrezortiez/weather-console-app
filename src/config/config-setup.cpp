#include "../include/config-setup.hpp"
#include "../forecast/forecast.hpp"

void Config::loadConfig(const char* config) {
    auto d_config = parse_istream_cfg(config);

    std::size_t amount_of_cities = d_config["citiesAmount"].GetInt();

    update_time_ = d_config["updateTime"].GetInt();
    forecast_days_ = d_config["forecastDays"].GetInt();

    auto cities = d_config["city"].GetArray();
    for (int i = 0; i < amount_of_cities; ++i) {
        cities_data_.emplace_back(
            new City(cities[i].GetString(), 0, 0));
        cities_data_[i]->ConvertCityNameToCoordinates();
        cities_data_[i]->ConvertCityNameToTimezone();
    }
}

void Config::printConfigData() const noexcept {
    std::cout << "update time : " << update_time_ << std::endl;
    std::cout << "forecast days : " << forecast_days_ << std::endl;
    for (const auto& city : cities_data_) {
        std::cout << *city << std::endl;
    }
}

void Config::getForecastHeaders(
    std::vector<std::unique_ptr<Forecast>>& container) const {
    for (const auto& city_ptr : cities_data_) {
        container.emplace_back(new Forecast(
            city_ptr->copyCoordinates(), city_ptr->copyTimezone()));
    }
}

std::ostream& operator<<(std::ostream& os, const City& city) {
    os << city.name_ << " " << city.coordinates_.first << " "
       << city.coordinates_.second << std::endl
       << city.timezone_ << std::endl;
    return os;
}

void City::ConvertCityNameToCoordinates() {
    ConvertionResponseHandler request;
    request.sendRequest(name_);
    coordinates_ = request.parseResponse();
}

void City::ConvertCityNameToTimezone() {
    TimezoneConvertResponseHandler request;
    request.sendRequest(name_);
    timezone_ = request.parseResponse();
}
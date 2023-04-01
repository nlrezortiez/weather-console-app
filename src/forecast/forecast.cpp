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

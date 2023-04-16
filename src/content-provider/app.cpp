#include "../include/app.hpp"

void run(const char* config) {
    ForecastAdapter forecast_adapter(config);
    forecast_adapter.get();
}

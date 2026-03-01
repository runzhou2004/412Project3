#include "Config.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {
string trim(const string& text) {
    const string whitespace = " \t\n\r";
    const size_t start = text.find_first_not_of(whitespace);
    if (start == string::npos) {
        return "";
    }
    const size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}
}

Config::Config(const string& filePath) {
    load(filePath);
}

void Config::load(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open config file: " + filePath);
    }

    string line;
    while (getline(file, line)) {
        const string cleaned = trim(line);
        if (cleaned.empty() || cleaned[0] == '#') {
            continue;
        }

        const size_t separator = cleaned.find('=');
        if (separator == string::npos) {
            continue;
        }

        const string key = trim(cleaned.substr(0, separator));
        const string value = trim(cleaned.substr(separator + 1));
        if (!key.empty()) {
            values[key] = value;
        }
    }
}

int Config::getInt(const string& key, int defaultValue) const {
    const auto match = values.find(key);
    if (match == values.end()) {
        return defaultValue;
    }

    try {
        return stoi(match->second);
    } catch (const exception&) {
        return defaultValue;
    }
}

double Config::getDouble(const string& key, double defaultValue) const {
    const auto match = values.find(key);
    if (match == values.end()) {
        return defaultValue;
    }

    try {
        return stod(match->second);
    } catch (const exception&) {
        return defaultValue;
    }
}

int Config::getInitialServers() const {
    return getInt("initial_servers", 10);
}

int Config::getRuntime() const {
    return getInt("runtime_cycles", 1000);
}

int Config::getRestCycles() const {
    return getInt("rest_cycles", 5);
}

double Config::getArrivalProbability() const {
    return getDouble("arrival_probability", 0.2);
}

int Config::getMinProcessTime() const {
    return getInt("min_process_time", 1);
}

int Config::getMaxProcessTime() const {
    return getInt("max_process_time", 10);
}

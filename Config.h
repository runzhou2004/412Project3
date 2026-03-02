/**
 *  \file Config.h
 *  \brief Header file for the Config class, responsible for loading and parsing configuration settings from a specified file.
 *  The Config class provides functionality to load configuration settings from a file, parse key-value pairs, and retrieve configuration values as integers or doubles with default values. It serves as a central point for managing configuration settings in the system, allowing other components to access these settings without needing to worry about file parsing or error handling.
 *
 *  The class uses an unordered_map to store key-value pairs of configuration settings, enabling efficient retrieval of values based on their keys. The load method reads the configuration file line by line, ignoring comments and empty lines, and populates the internal map with the parsed settings. The getInt and getDouble methods allow retrieval of configuration values as integers or doubles, returning default values if the keys are not found or if conversion fails.
 *
 *  Overall, the Config class is designed to be flexible and easy to use, providing a simple interface for accessing configuration settings while abstracting away the complexities of file handling and parsing.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

using namespace std;

/**
 * @class Config
 * @brief The Config class is responsible for loading and parsing configuration settings from a specified file. It provides methods to retrieve configuration values as integers or doubles, with default values if the keys are not found or if the values cannot be converted to the desired type. The class uses an unordered_map to store key-value pairs of configuration settings, allowing for efficient retrieval of configuration values based on their keys.
 * The Config class is designed to be flexible and easy to use, allowing other components of the system to access configuration settings without needing to worry about the details of file parsing or error handling. It serves as a central point for managing configuration settings, making it easier to maintain and update the system's behavior based on different configurations.
 */
class Config {
    private:
        unordered_map<string, string> values;

        /**
         * @brief Loads the configuration settings from the specified file path. The method reads the file line by line, ignoring comments and empty lines, and parses key-value pairs to populate the internal unordered_map with configuration settings. If the file cannot be opened, it throws a runtime error.
         * @param filePath The path to the configuration file to be loaded.
         */
        void load(const string& filePath);

        /**
         * @brief Retrieves the value associated with the specified key as an integer. If the key is not found or if the value cannot be converted to an integer, it returns a default value.
         * @param key The key for which to retrieve the integer value.
         * @param defaultValue The default value to return if the key is not found or if conversion fails.
         * @return The integer value associated with the key, or the default value if not found or conversion fails.
         */
        int getInt(const string& key, int defaultValue) const;

        /**
         * @brief Retrieves the value associated with the specified key as a double. If the key is not found or if the value cannot be converted to a double, it returns a default value.
         * @param key The key for which to retrieve the double value.
         * @param defaultValue The default value to return if the key is not found or if conversion fails.
         * @return The double value associated with the key, or the default value if not found or conversion fails.
         */
        double getDouble(const string& key, double defaultValue) const;

    public:
        /**
         * @brief Constructs a Config object by loading configuration settings from the specified file path.
         * @param filePath The path to the configuration file to be loaded.
         */
        explicit Config(const string& filePath);

        /**
         * @brief Retrieves the initial number of servers to be used in the load balancer, as specified in the configuration file.
         * @return The initial number of servers.
         */
        int getInitialServers() const;

        /**
         * @brief Retrieves the total runtime in cycles for the load balancer, as specified in the configuration file.
         * @return The total runtime in cycles.
         */
        int getRuntime() const;

        /**
         * @brief Retrieves the number of rest cycles to be used as a cooldown period for scaling servers in the load balancer, as specified in the configuration file.
         * @return The number of rest cycles for cooldown.
         */
        int getRestCycles() const;

        /**
         * @brief Retrieves the probability of request arrival, as specified in the configuration file.
         * @return The probability of request arrival.
         */
        double getArrivalProbability() const;

        /**
         * @brief Retrieves the minimum processing time for requests, as specified in the configuration file.
         * @return The minimum processing time for requests.
         */
        int getMinProcessTime() const;

        /**
         * @brief Retrieves the maximum processing time for requests, as specified in the configuration file.
         * @return The maximum processing time for requests.
         */
        int getMaxProcessTime() const;
};

#endif

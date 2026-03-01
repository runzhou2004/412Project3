#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

using namespace std;

class Config {
    private:
        unordered_map<string, string> values;

        void load(const string& filePath);
        int getInt(const string& key, int defaultValue) const;
        double getDouble(const string& key, double defaultValue) const;

    public:
        explicit Config(const string& filePath);

        int getInitialServers() const;
        int getRuntime() const;
        int getRestCycles() const;
        double getArrivalProbability() const;
        int getMinProcessTime() const;
        int getMaxProcessTime() const;
};

#endif

//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <map>

#include "utills.h"
using namespace std;

class Properties {
public:
    std::string GetProperty(const std::string &key,
            const std::string &default_value = std::string()) const;

    const std::string &operator[](const std::string &key) const;

    const std::map <std::string, std::string> &properties() const;

    void SetProperty(const std::string &key, const std::string &value);

private:
    std::map <std::string, std::string> properties_;
};

inline std::string Properties::GetProperty(const std::string &key,
        const std::string &default_value) const {
    std::map<std::string, std::string>::const_iterator it = properties_.find(key);
    if (properties_.end() == it) {
        return default_value;
    } else return it->second;
}

inline const std::string &Properties::operator[](const std::string &key) const {
    return properties_.at(key);
}

inline const std::map <std::string, std::string> &Properties::properties() const {
    return properties_;
}

inline void Properties::SetProperty(const std::string &key,
        const std::string &value) {
    properties_[key] = value;
}

#endif //PROPERTIES_H

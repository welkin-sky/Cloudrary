#include "base.h"

void to_json(json& j, const Base& b) {
    for (const auto& item : b) {
        j.push_back(item);
    }
}

void from_json(const json& j, Base& b) {
    for (const auto& item : j) {
        Library temp;
        temp = item;
        b.add(temp);
    }
}

string Base::serialize(const Base& b) {
    json j = b;
    return j.dump();
}

Base Base::deserialize(const string& j) {
    auto tempJson = json::parse(j);
    return tempJson.get<Base>();
}
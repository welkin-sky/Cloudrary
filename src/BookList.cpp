#include "../include/base.h"

void to_json(json& j, const BookList& bl) { j = json::j_vec(bl.data()); }
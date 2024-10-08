// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "storage/aggregate_type.h"

#include <algorithm>

#include "common/logging.h"

namespace starrocks {

StorageAggregateType get_aggregation_type_by_string(const std::string& str) {
    std::string lower_str = str;
    std::transform(str.begin(), str.end(), lower_str.begin(), ::tolower);

    if (lower_str == "none") return STORAGE_AGGREGATE_NONE;
    if (lower_str == "sum") return STORAGE_AGGREGATE_SUM;
    if (lower_str == "min") return STORAGE_AGGREGATE_MIN;
    if (lower_str == "max") return STORAGE_AGGREGATE_MAX;
    if (lower_str == "replace") return STORAGE_AGGREGATE_REPLACE;
    if (lower_str == "replace_if_not_null") return STORAGE_AGGREGATE_REPLACE_IF_NOT_NULL;
    if (lower_str == "hll_union") return STORAGE_AGGREGATE_HLL_UNION;
    if (lower_str == "bitmap_union") return STORAGE_AGGREGATE_BITMAP_UNION;
    if (lower_str == "percentile_union") return STORAGE_AGGREGATE_PERCENTILE_UNION;
    if (lower_str == "agg_state_union") return STORAGE_AGGREGATE_AGG_STATE_UNION;
    LOG(WARNING) << "invalid aggregation type string. [aggregation='" << str << "']";
    return STORAGE_AGGREGATE_UNKNOWN;
}

std::string get_string_by_aggregation_type(StorageAggregateType type) {
    switch (type) {
    case STORAGE_AGGREGATE_NONE:
        return "none";
    case STORAGE_AGGREGATE_SUM:
        return "sum";
    case STORAGE_AGGREGATE_MIN:
        return "min";
    case STORAGE_AGGREGATE_MAX:
        return "max";
    case STORAGE_AGGREGATE_REPLACE:
        return "replace";
    case STORAGE_AGGREGATE_REPLACE_IF_NOT_NULL:
        return "replace_if_not_null";
    case STORAGE_AGGREGATE_HLL_UNION:
        return "hll_union";
    case STORAGE_AGGREGATE_BITMAP_UNION:
        return "bitmap_union";
    case STORAGE_AGGREGATE_PERCENTILE_UNION:
        return "percentile_union";
    case STORAGE_AGGREGATE_UNKNOWN:
        return "unknown";
    case STORAGE_AGGREGATE_AGG_STATE_UNION:
        return "agg_state_union";
    }
    return "";
}

} // namespace starrocks

namespace std {
ostream& operator<<(ostream& os, starrocks::StorageAggregateType method) {
    os << starrocks::get_string_by_aggregation_type(method);
    return os;
}
} // namespace std
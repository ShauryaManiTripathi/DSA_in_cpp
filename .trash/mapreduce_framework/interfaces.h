#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

namespace MapReduceFramework {

    // Standard Key-Value pair for MapReduce operations
    template<typename K, typename V>
    struct KeyValue {
        K key;
        V value;
        
        KeyValue() = default;
        KeyValue(const K& k, const V& v) : key(k), value(v) {}
        KeyValue(K&& k, V&& v) : key(std::move(k)), value(std::move(v)) {}
    };

    // Standard data types for flexibility
    using MapInput = std::string;  // Input to mapper (line, record, etc.)
    using MapKey = std::string;    // Key type from mapper
    using MapValue = std::string;  // Value type from mapper
    using ReduceKey = std::string; // Key type for reducer (usually same as MapKey)
    using ReduceValue = std::string; // Final output value type

    using MapOutput = std::vector<KeyValue<MapKey, MapValue>>;
    using ReduceInput = std::vector<MapValue>;
    using ReduceOutput = KeyValue<ReduceKey, ReduceValue>;

    // Abstract base class for Mappers
    class IMapper {
    public:
        virtual ~IMapper() = default;
        
        // Pure virtual function that each mapper must implement
        // Takes input data and returns key-value pairs
        virtual MapOutput map(const MapInput& input) = 0;
        
        // Optional: Get mapper description
        virtual std::string get_description() const { return "Generic Mapper"; }
    };

    // Abstract base class for Reducers  
    class IReducer {
    public:
        virtual ~IReducer() = default;
        
        // Pure virtual function that each reducer must implement
        // Takes a key and list of values, returns a single key-value pair
        virtual ReduceOutput reduce(const ReduceKey& key, const ReduceInput& values) = 0;
        
        // Optional: Get reducer description
        virtual std::string get_description() const { return "Generic Reducer"; }
    };

    // Configuration for MapReduce execution
    struct MapReduceConfig {
        int num_mappers = 4;
        int num_reducers = 2;
        bool verbose = true;
        std::string output_file = "";
        
        MapReduceConfig() = default;
        MapReduceConfig(int mappers, int reducers, bool verb = true) 
            : num_mappers(mappers), num_reducers(reducers), verbose(verb) {}
    };

    // Result handler interface for custom output processing
    class IResultHandler {
    public:
        virtual ~IResultHandler() = default;
        virtual void handle_results(const std::unordered_map<ReduceKey, ReduceValue>& results, 
                                  const MapReduceConfig& config) = 0;
    };

} // namespace MapReduceFramework

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <string>
#include <exception>

class DataProcessor {
private:
    std::atomic<bool> _is_running;
    std::thread _processing_thread;
    std::unordered_map<std::string, std::pair<std::chrono::system_clock::time_point, int>> _data_cache;
    std::mutex _cache_mutex;
    std::chrono::minutes _cache_ttl;

    void processing_loop() {
        while (_is_running.load()) {
            try {
                fetch_data();
                cleanup_cache();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } catch (const std::exception& e) {
                std::cerr << "Error in processing loop: " << e.what() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
    }

    void fetch_data() {
        try {
            auto data = get_external_data();
            
            if (data.empty()) {
                std::cout << "No data received" << std::endl;
                return;
            }
            
            auto processed_data = transform_data(data);
            store_data(processed_data);
            
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid data: " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Connection error: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error in data fetching: " << e.what() << std::endl;
        }
    }

    int get_external_data() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    }

    int transform_data(int data) {
        if (data < 0) {
            throw std::invalid_argument("Data cannot be negative");
        }
        return data * 2;
    }

    void store_data(int processed_data) {
        try {
            std::lock_guard<std::mutex> lock(_cache_mutex);
            auto now = std::chrono::system_clock::now();
            auto key = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()).count());
            
            _data_cache[key] = std::make_pair(now, processed_data);
            
        } catch (const std::exception& e) {
            std::cerr << "Error storing data: " << e.what() << std::endl;
        }
    }

    void cleanup_cache() {
        try {
            std::lock_guard<std::mutex> lock(_cache_mutex);
            auto now = std::chrono::system_clock::now();
            
            auto it = _data_cache.begin();
            while (it != _data_cache.end()) {
                if (now - it->second.first > _cache_ttl) {
                    it = _data_cache.erase(it);
                } else {
                    ++it;
                }
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error cleaning cache: " << e.what() << std::endl;
        }
    }

public:
    DataProcessor() : _is_running(false), _cache_ttl(std::chrono::minutes(10)) {}

    ~DataProcessor() {
        stop_processing();
    }

    void start_processing() {
        if (_is_running.exchange(true)) {
            std::cout << "Processing already running" << std::endl;
            return;
        }
        
        try {
            _processing_thread = std::thread(&DataProcessor::processing_loop, this);
            std::cout << "Data processing started" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error starting processing: " << e.what() << std::endl;
            _is_running = false;
        }
    }

    void stop_processing() {
        if (!_is_running.exchange(false)) {
            std::cout

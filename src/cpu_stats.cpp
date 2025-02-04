#include "../include/cpu_stats.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

CPUData read_cpu_data() {
    std::ifstream stat_file("/proc/stat");
    std::string line;
    std::getline(stat_file, line);
    std::istringstream ss(line);

    CPUData data;
    std::string cpu;
    ss >> cpu >> data.user >> data.nice >> data.system >> data.idle >> data.iowait >> data.irq >> data.softirq >> data.steal >> data.guest >> data.guest_nice;

    return data;
}

double calculate_cpu_use(CPUData& prev, CPUData& current) {
    ULL prev_idle = prev.idle + prev.iowait;
    ULL idle = current.idle + current.iowait;

    ULL prev_non_idle = prev.user + prev.nice + prev.system + prev.irq + prev.softirq + prev.steal;
    ULL non_idle = current.user + current.nice + current.system + current.irq + current.softirq + current.steal;

    ULL prev_total = prev_idle + prev_non_idle;
    ULL total = idle + non_idle;

    ULL total_diff = total - prev_total;
    ULL idle_diff = idle - prev_idle;

    double cpu_use = ((total_diff - idle_diff) / static_cast<double>(total_diff)) * 100.0;
    return cpu_use;
}
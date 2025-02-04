#pragma once 

typedef unsigned long long ULL;

struct CPUData {
    ULL user;
    ULL nice;
    ULL system;
    ULL idle;
    ULL iowait;
    ULL irq;
    ULL softirq;
    ULL steal;
    ULL guest;
    ULL guest_nice;
};

CPUData read_cpu_data(); 

double calculate_cpu_use(CPUData& prev, CPUData& current); 
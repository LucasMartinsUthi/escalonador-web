#include "definitions.h"
#include "process.h"

class Scheduler{
    private:
        vector<Process> processes;
        int total_duration;
        
    public:
        Scheduler(vector<Process> processes);

        vector<int> fcfs();
        vector<int> sjf();
        vector<int> rr(int quantum_size);
        void write_log();

        bool isFinished();

};
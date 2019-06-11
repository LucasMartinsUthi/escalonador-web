#include "definitions.h"

class Process{
    private:
        int label;
        int arrival;
        int duration;
        
        bool done = 0;
        
    public:
        int remaining;
        
        //Constructors
        Process();
        Process(int label, int arrival, int duration);
        
        //Getters
        int getLabel();
        int getArrival();
        int getDuration();
        int getRemaining();
        bool isDone();

        //Setters
        void setLabel(int label);
        void setArrival(int arrival);
        void setDuration(int duration);

        //Class functions
        void step();

        bool operator < (Process p);
};
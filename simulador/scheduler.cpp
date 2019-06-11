#include "scheduler.h"

Scheduler::Scheduler(vector<Process> processes){
    this->processes = processes;
    sort(this->processes.begin(), this->processes.end());
}

bool Scheduler::isFinished(){
    for(auto& p : processes){
        if(!p.isDone()){
            return false;
        }
    }
    return true;
}

vector<int> Scheduler::fcfs(){
    vector<int> timeline;
    
    for(auto& p : processes){
        while(!p.isDone()){
            p.step();
            timeline.push_back(p.getLabel());
        }
    }

    return timeline;
}

void printStack(deque<Process> s){
    while(!s.empty()){
        cout << s.front().getLabel() << " ";
        s.pop_front();
    }
    cout << endl;
}

vector<int> Scheduler::sjf(){
    deque<Process> s; //Process queue
    vector<int> timeline;
    int total_duration = 0;
    bool found_position;

    for(auto& p : processes)
        total_duration += p.getDuration();

    for(int current_clock = 0; current_clock < total_duration; current_clock++){
        vector<Process> in_clock;
        //Groups the process in the current clock
        for(auto& p:processes){
            if(p.getArrival() == current_clock && !p.isDone()){
                in_clock.push_back(p);
            }
        }
        //Orders by remaining duration
        sort(in_clock.begin(), in_clock.end(), [](const Process& a, const Process& b){
            return a.remaining < b.remaining;
        });

        //Insert into the processe queue accordingly
        for(auto& c : in_clock){
            //If the queue is empty or the process has less remaining time
            if(s.empty() || c.getRemaining() <= s.front().getRemaining() && c.getLabel() != s.front().getLabel()){
                //Puts in the front of the queue
                s.push_front(c);
            }else{
                //Finds an appropriate position
                found_position = 0;
                for(deque<Process>::iterator it = s.begin(); it < s.end(); it++){
                    if(c.getRemaining() <= it->getRemaining() && c.getLabel() != it->getLabel()){
                        it = s.insert(it, c);
                        it++;
                        found_position = 1;
                    }
                }
                if(!found_position){
                    s.push_back(c);
                }
            }
        }
        
        if(!s.empty()){
            s.front().step();
            timeline.push_back(s.front().getLabel());
            if(s.front().isDone()){
                s.pop_front();
            }
        }
        in_clock.clear();
    }
    return timeline;
}

vector<int> Scheduler::rr(int quantum_size){
    vector<int> timeline;
    while(!isFinished()){
        for(auto& p : processes){
            for(int i = 0; i < quantum_size; i++){
                if(!p.isDone()){
                    p.step();
                    timeline.push_back(p.getLabel());
                }
            }
        }
    }
    return timeline;
}
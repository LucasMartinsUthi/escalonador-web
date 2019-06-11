#include "process.h"

Process::Process(){}

Process::Process(int label, int arrival, int duration){
    this->label = label;
    this->arrival = arrival;
    this->duration = duration;
    this->remaining = duration;
}

bool Process::operator<(Process p){
    return this->getArrival() < p.getArrival();
}

int Process::getLabel(){
    return this->label;
}

int Process::getArrival(){
    return this->arrival;
}

int Process::getDuration(){
    return this->duration;
}

int Process::getRemaining(){
    return this->remaining;
}

bool Process::isDone(){
    return this->done;
}

void Process::setLabel(int label){
    this->label = label;
}

void Process::setArrival(int arrival){
    this->arrival = arrival;
}

void Process::setDuration(int duration){
    this->duration = duration;
}

void Process::step(){
    this->remaining--;
    
    if(remaining < 0){
        remaining = 0;
    }

    if(remaining == 0){
        done = 1;
    }
}
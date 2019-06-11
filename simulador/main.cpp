#include "scheduler.h"

vector<Process> parseFromFile(string filepath){
    vector<Process> processes;

    ifstream inFile;
    string line, temp;

    inFile.open(filepath, ios::in);
    int i = 0, pid, arrival, duration;
    
    while(inFile >> temp){
        if(i == 0){
            pid = stoi(temp);
        }
        if(i == 1){
            arrival = stoi(temp);
        }
        if(i == 2){
            duration = stoi(temp);
        }
        if(i >= 2){
            Process p(pid, arrival, duration);
            processes.push_back(p);
            i = 0;
        }else{
            i++;
        }        
    }    
    inFile.close();
    return processes;
}


int main(int argc, char* argv[]){
    
    if(argc < 4){
        cout << "Usage: simulator <input_file> <algorithm> <quantum_size>" << endl;
        exit(-1);
    }
    string algorithm(argv[2]);

    vector<int> timeline;
    vector<Process> processes = parseFromFile(argv[1]);
    Scheduler s(processes);

    cout << "[\"";
    
    if(algorithm == "FCFS"){
        timeline = s.fcfs();
        for(vector<int>::iterator it = timeline.begin(); it < timeline.end(); it++){
            cout << *it << "\",\"";
        }
    }
    else if(algorithm == "SJF"){
        timeline = s.sjf();
        for(vector<int>::iterator it = timeline.begin(); it < timeline.end(); it++){
            cout << *it << "\",\"";
        }
    } else if(algorithm == "RR"){
        timeline = s.rr(atoi(argv[3]));
        for(vector<int>::iterator it = timeline.begin(); it < timeline.end(); it++){
            cout << *it << "\",\"";
        }
    }

    cout << "\"]" << endl;
} 
// this is the only file you should modify and submit for grading

#include "scheduler.h"
#include "common.h"
#include "iostream"
// this is the function you should implement
//
// runs Round-Robin scheduling simulator
// input:
//   quantum = time slice
//   max_seq_len = maximum length of the reported executing sequence
//   processes[] = list of process with populated IDs, arrival_times, and bursts
// output:
//   seq[] - will contain the execution sequence but trimmed to max_seq_len size
//         - idle CPU will be denoted by -1
//         - other entries will be from processes[].id
//         - sequence will be compressed, i.e. no repeated consecutive numbers
//   processes[]
//         - adjust finish_time and start_time for each process
//         - do not adjust other fields
//
void simulate_rr(
    int64_t quantum, 
    int64_t max_seq_len,
    std::vector<Process> & processes,
    std::vector<int> & seq
) {
    seq.clear();


    int64_t curr_time =0;
    int64_t remaining_slice = quantum;
    int cpu = -1;
    std::vector<int> rq, jq;
    std::vector<int64_t> remaining_bursts;
    for(auto & process : processes){
        jq.push_back(process.id);
        remaining_bursts.push_back(process.burst);
    }
   
    while(1){
    
        cpu = -1;

        if(!rq.empty() && remaining_slice==0 ){
            if( remaining_bursts[rq[0]]!=0 ){
                remaining_slice = quantum;
                int current_process = rq[0];
                rq.erase(rq.begin());
                rq.push_back(current_process);
            }
        }
        
        if(!jq.empty()&&processes[jq[0]].arrival_time==curr_time){
            rq.push_back(jq[0]);
            jq.erase(jq.begin());
            continue;
        }
      
        if(!rq.empty() && remaining_bursts[rq[0]]==0){
            remaining_slice = quantum;
            processes[rq[0]].finish_time = curr_time;
            rq.erase(rq.begin());

        }
        
        if(!rq.empty() && remaining_slice <= quantum && remaining_slice>0){
            
            
            if(processes[rq[0]].start_time == -1) processes[rq[0]].start_time=curr_time;  
            remaining_slice--;
            cpu = rq[0];
            remaining_bursts[rq[0]]--;  
            
        } 
           
        if(rq.empty() && jq.empty()) break;
        if(!rq.empty() && !jq.empty()) 
     
        if(seq.back() !=cpu &&seq.push_back(cpu);
        curr_time++;

    } 
    return;
}

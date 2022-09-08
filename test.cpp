#include <bits/stdc++.h>
using namespace std;

double AVG_WT_RR;
double AVG_WT_SJF;
double AVG_WT_FCFS;
double AVG_WT_PRIORITY;

struct Process {
  string name;
  int AT, BT, ST, P, TQ, WT, REM;
};

int count_process() {
  int number;
  cout << "Enter the number of process(es): ";
  cin >> number;
  return number;
}

void take_user_input(vector<Process> &processes) {
  cout << "\nGive the input for all process in the following manner (name AT BT P TQ):\n";
  for (int i = 0; i < processes.size(); ++i)
    cin >> processes[i].name >> processes[i].AT >> processes[i].BT >> processes[i].P >> processes[i].TQ;
}

void debug_processes(vector<Process> &processes) {
  cout << "\nDebugging all process...";
  cout << "\nname" << '\t' << "AT" << '\t' << "BT" << '\t' << "ST" << '\t' << "P" << '\t' << "TQ" << '\t' << "WT" << '\n';
  for (auto &ele : processes)
    cout << ele.name << '\t' << ele.AT << '\t' << ele.BT << '\t' << ele.ST << '\t' << ele.P << '\t' << ele.TQ << '\t' << ele.WT << '\n';
}

double avg_wt_rr(vector<Process> processes) {
  int g = 0;
  double TOTAL_WT = 0.0;

  int sum_wt = 1;
  while (sum_wt) {
    sum_wt = 0;
    for (auto &process: processes) {
      if (process.BT < process.TQ && process.BT) {

        process.REM = process.BT;
        process.WT += (g - process.AT);
        g += process.REM;
        process.BT = 0;

      } else if (process.BT > 0) {

        process.REM = process.BT - process.TQ;
        process.BT = process.REM;
        process.WT += (g - process.AT);
        g += process.TQ;
        process.AT = g;

      }
      sum_wt += process.BT;
    }
  }

  for (auto &process : processes)
    TOTAL_WT += process.WT;

  double AVG_WT_RR = TOTAL_WT / processes.size();
  return AVG_WT_RR;
}

bool sjf_cmp(Process p1, Process p2) {
  return p1.BT < p2.BT;
}

double avg_wt_sjf(vector<Process> processes) {
  int g = 0;
  double TOTAL_WT = 0.0;

  sort(processes.begin(), processes.end(), sjf_cmp);
  for (auto &process : processes) {
    process.ST = g;
    g += process.BT;
    process.WT = process.ST - process.AT;
    TOTAL_WT += process.WT;
  }

  double AVG_WT_SJF = TOTAL_WT / processes.size();
  return AVG_WT_SJF;
}

double avg_wt_fcfs(vector<Process> processes) {
  int g = 0;
  double TOTAL_WT = 0.0;

  for (auto &process : processes) {
    process.ST = g;
    g += process.BT;
    process.WT = process.ST - process.AT;
    TOTAL_WT += process.WT;
  }

  double AVG_WT_FCFS = TOTAL_WT / processes.size();
  return AVG_WT_FCFS;
}

bool priority_cmp(Process p1, Process p2) {
  return p1.P > p2.P;
}

double avg_wt_priority(vector<Process> processes) {
  int g = 0;
  double TOTAL_WT = 0.0;

  sort(processes.begin(), processes.end(), priority_cmp);
  for (auto &process : processes) {
    process.ST = g;
    g += process.BT;
    process.WT = process.ST - process.AT;
    TOTAL_WT += process.WT;
  }

  double AVG_WT_PRIORITY = TOTAL_WT / processes.size();
  return AVG_WT_PRIORITY;
}

void show_output(vector<Process> &processes) {
  AVG_WT_RR = avg_wt_rr(processes);
  AVG_WT_SJF = avg_wt_sjf(processes);
  AVG_WT_FCFS = avg_wt_fcfs(processes);
  AVG_WT_PRIORITY = avg_wt_priority(processes);

  vector<pair<double, string>> output;

  output.push_back({AVG_WT_SJF, "Shortest Job First (SJF)"});
  output.push_back({AVG_WT_RR, "Round Robin Scheduling (RR)"});
  output.push_back({AVG_WT_FCFS, "First Come First Serve (FCFS)"});
  output.push_back({AVG_WT_PRIORITY, "Priority Based Scheduling"});

  cout << "\nAlgorithm" << "\t\t\t" << "Avg. WT" << '\n';
  cout << "------------------------------------------\n";
  for (auto &ele : output)
    cout << ele.second << "\t" << ele.first << '\n';
  
  sort(output.begin(), output.end());
  cout << "\n* The best algorithm is " << output[0].second << " having " << output[0].first << "s average waiting time.";
}

int main() {
  int t = 4;
  while (t --> 0) {
    vector<Process> processes(count_process());
    take_user_input(processes);
    show_output(processes);
  }
  return 0;
}

/*
4
P0 0 5 3 3
P1 1 3 2 3
P2 2 8 1 3
P3 3 6 2 3

4
P0 0 4  1 2
P1 1 2  4 2
P2 2 12 5 2
P3 3 7  2 2

4
P0 0 7  1 1
P1 1 2  2 1
P2 2 4  4 1
P3 3 10 3 1

4
P0 0 12 1 2
P1 1 7  7 2
P2 2 9  3 2
P3 3 19 5 2
*/

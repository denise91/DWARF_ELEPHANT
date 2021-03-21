#include "DwarfElephantApp.h"
#include "MooseInit.h"
#include "Moose.h"
#include "MooseApp.h"
#include "AppFactory.h"

#include <unistd.h>
#include <ios>

// Create a performance log
PerfLog Moose::perf_log("DwarfElephant");

void process_mem_usage(double& vm_usage, double& resident_set)
{
   //////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}

// Begin the main program.
int main(int argc, char *argv[])
{
  using std::cout;
  using std::endl;
  double vm, rss;

  std::ofstream outfile;

  //outfile.open("Memory_usage_trace_ignore_zero_entries.csv",std::ofstream::app);
  //outfile << "#Virtual Memory (kB), RSS (kB); mesh_File: " << argv[argc-1] << endl;
 
  process_mem_usage(vm, rss);
  cout << "Begin program VM: " << vm << "; RSS: " << rss << endl;
  //outfile << vm << ", " << rss << endl;
  //outfile.close();
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);

  // Register this application's MooseApp and any it depends on
  DwarfElephantApp::registerApps();

  // In case our are using a MOOSE version older than Jan 24, 2018
  // use the following line
  // MooseApp * app = AppFactory::createApp("DwarfElephantApp", argc, argv);

  // Create an instance of the application and store it in a smart pointer for easy cleanup
  std::shared_ptr<MooseApp> app = AppFactory::createAppShared("DwarfElephantApp", argc, argv);

  process_mem_usage(vm, rss);
  cout << "App run about to start VM: " << vm << "; RSS: " << rss << endl;

  //outfile.open("Memory_usage_trace_ignore_zero_entries.csv",std::ofstream::app);
  //outfile << vm << ", " << rss << endl;
  //outfile.close();

  // Execute the application
  app->run();

  process_mem_usage(vm, rss);
  cout << "App Run complete VM: " << vm << "; RSS: " << rss << endl;

  //outfile.open("Memory_usage_trace_ignore_zero_entries.csv",std::ofstream::app);
  //outfile << vm << ", " << rss << endl;
  //outfile.close();
  // In case our are using a MOOSE version older than Jan 24, 2018
  // use the following line
  // delete app;

  return 0;
}

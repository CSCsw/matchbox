#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sys/times.h>
#include <unistd.h>

namespace Matchbox {

typedef float Time;

class Timer {
public:
  Timer(): mOutputPrecision(6) {}

  void SetOutputPrecision(int outputPrecision) {
    mOutputPrecision = outputPrecision;
  }

  //void Start(void) { mBeginWall = times(&mBeginCpu); }

  //void Stop(void) { mEndWall = times(&mEndCpu); }
  
  void Start(void) { clock_gettime(CLOCK_MONOTONIC, &mTime); }
  void Stop(void) { clock_gettime(CLOCK_MONOTONIC, &end); }
 	 
 	long double GetTime(void){
 		long double diff = (end.tv_sec-mTime.tv_sec) + (end.tv_nsec - mTime.tv_nsec)/1000000000.0;
 		return diff;
 		//long double totalTime = (end.tv_sec+(end.tv_usec/1000000.0)) - (stime.tv_sec+(stime.tv_usec/1000000.0));
	 }
  /*Time GetWallTime(void) {
    return (Time)(mEndWall - mBeginWall) / sysconf(_SC_CLK_TCK);
  }

  Time GetCpuTime(void) {
    return (Time)(mEndCpu.tms_utime - mBeginCpu.tms_utime) /
           sysconf(_SC_CLK_TCK) +
           (Time)(mEndCpu.tms_stime - mBeginCpu.tms_stime) /
           sysconf(_SC_CLK_TCK);
  }

  Time GetUserCpuTime(void) {
    return (Time)(mEndCpu.tms_utime - mBeginCpu.tms_utime) /
           sysconf(_SC_CLK_TCK);
  }

  Time GetSystemCpuTime(void) {
    return (Time)(mEndCpu.tms_stime - mBeginCpu.tms_stime) /
           sysconf(_SC_CLK_TCK);

  }*/

  void Print(void);

private:
  //clock_t mBeginWall;
  //clock_t mEndWall;
  //struct tms mBeginCpu;
  //struct tms mEndCpu;
  //struct timeval stime;
  //struct timeval end;
  timespec mTime;
  timespec end;
  int mOutputPrecision;
}; // class Timer

} // namespace Matchbox

#endif // TIMER_H

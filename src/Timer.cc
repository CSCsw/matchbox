#include "Timer.h"

using namespace std;
using namespace Matchbox;

void Timer::Print(void) {
  //cout.setf(ios::left | ios::scientific | ios::showpoint);
  //cout.precision(mOutputPrecision);
  //cout << "time: "
       /*<<fixed << GetWallTime() << "s (wall), " <<fixed << GetCpuTime() << "s (cpu)"*/
        //<< GetTime()*1000.0 << " ms, "<< GetTime()<< " s."
       //<< endl;
	cout << "time: " << GetTime() << " s" << endl;
  //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
  
}

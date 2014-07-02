#include "MemoryAnalyzer.h"
#include "MemoryFree.h"


int MemoryAnalyzer::freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

int MemoryAnalyzer::freeRam_method2 () {
	return freeMemory();
}

/**
* The format will be:
* [MEMORY][WHEN][PRF_ALGORITHM][NUM_BIT_OUTPUT][VALUE_FREE_RAM]
* with:
* - MEMORY => is a static string (used to differentiate MemoryAnalyzer from TimingAnalyzer)
* - WHEN => START/END
* - PRF_ALGORITHM => HMAC_SHA1/HMAC_SHA256
* - NUM_BIT_OUTPUT => number of bits of the key generated by KDF
* - VALUE_FREE_RAM => current free ram mesured by "freeRam" function
*/
String MemoryAnalyzer::getCurrentFreeRam(String when, HMAC_type algorithm, size_t numBitOutputKDF) {

	String buf;
	buf += "[MEMORY]";
	buf += "[" + when + "]";

	switch(algorithm){
		case HMAC_SHA1:
    		buf += "[HMAC_SHA1]";
	    break;
	    case HMAC_SHA256:
	    	buf += "[HMAC_SHA256]";
	    break;
	}
	buf += "[" + String(numBitOutputKDF) + "]";
	buf += "[" + String(MemoryAnalyzer::freeRam_method2()) + "]";

	Serial.println(buf);

	return buf;

}

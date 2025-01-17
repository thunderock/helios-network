/**
 * @Author: Ashutosh Tiwari
 * @Date:   2023-08-28 12:17:13
 * @Last Modified by:   Ashutosh Tiwari
 * @Last Modified time: 2023-08-28 12:44:00
 */
//
//  CVCommons.h
//  CVNetwork
//
//  Created by Filipi Nascimento Silva on 11/11/12.
//  Copyright (c) 2012 Filipi Nascimento Silva. All rights reserved.
//

#ifndef CVNetwork_CVCommons_h
#define CVNetwork_CVCommons_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <emscripten.h>


#if __LP64__ || _WIN64 || NS_BUILD_32_LIKE_64 || CV_64BITS
#define CV_BUILD_64BITS 1
#endif


#if CV_USE_LIBDISPATCH
#include <dispatch/dispatch.h>
#define CV_ENABLE_PARALLELISM 1
#elif _OPENMP //CV_USE_LIBDISPATCH
#include <omp.h>
#define CV_USE_OPENMP 1
#define CV_ENABLE_PARALLELISM 1
#endif //_OPENMP

#define kCVDefaultParallelBlocks 1024

#if !defined(CV_INLINE)
#if defined(__EMSCRIPTEN__)
#define CV_INLINE static inline
#elif defined(__GNUC__)
#define CV_INLINE static __inline__ __attribute__((always_inline))
#elif defined(__MWERKS__) || defined(__cplusplus)
#define CV_INLINE static inline
#elif defined(_MSC_VER)
#define CV_INLINE static __inline
#elif defined(__WIN32__)
#define CV_INLINE static __inline__
#endif
#endif

#if !defined(CV_STATIC_INLINE)
#if defined(__GNUC__)
#define CV_STATIC_INLINE static __inline__
#elif defined(__MWERKS__) || defined(__cplusplus)
#define CV_STATIC_INLINE static inline
#elif defined(_MSC_VER)
#define CV_STATIC_INLINE static __inline
#elif defined(__WIN32__)
#define CV_STATIC_INLINE static __inline__
#endif
#endif

#ifdef __cplusplus
#define CV_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CV_EXTERN extern __attribute__((visibility ("default")))
#endif


#if defined(__GNUC__)
#define CVLikely(x)       __builtin_expect((x),1)
#define CVUnlikely(x)     __builtin_expect((x),0)
#define CVExpecting(x,y)  __builtin_expect((x),(y))
#else
#define CVLikely(x)       x
#define CVUnlikely(x)     x
#define CVExpecting(x,y)  x
#endif

#if !defined(CVMIN)
#define CVMIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(CVMAX)
#define CVMAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(CVABS)
#define CVABS(A)	((A) < 0 ? (-(A)) : (A))
#endif

#define __SHORT_FILE_ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define CVLog(...) do {fprintf(stderr,"#%s:%d[%s]: ", __SHORT_FILE_, __LINE__, __func__);fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");} while (0)

#if DEBUG
#define CVDebugLog(...) do {fprintf(stderr,"#%s:%d[%s]: ", __SHORT_FILE_, __LINE__, __func__);fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");} while (0)
#else
#define CVDebugLog(...)
#endif


#if CV_BENCHMARK_FUNCTIONS
#include <mach/mach_time.h>
CV_INLINE double CVTimeSubtract( uint64_t endTime, uint64_t startTime ){
    uint64_t difference = endTime - startTime;
    static double conversion = 0.0;
    
    if( conversion == 0.0 )
    {
        mach_timebase_info_data_t info;
        kern_return_t err = mach_timebase_info( &info );
        
		//Convert the timebase into seconds
        if( err == 0  )
			conversion = 1e-9 * (double) info.numer / (double) info.denom;
    }
    
    return conversion * (double) difference;
}

#define CV_BenchmarkPrepare(prefix) static uint64_t _CV_Benchmark_##prefix##_start; static double _CV_Benchmark_##prefix##_elapsed
#define CV_BenchmarkStart(prefix)   _CV_Benchmark_##prefix##_start = mach_absolute_time()
#define CV_BenchmarkStop(prefix)    _CV_Benchmark_##prefix##_elapsed = CVTimeSubtract(mach_absolute_time(),_CV_Benchmark_##prefix##_start)
#define CV_BenchmarkPrint(prefix)   CVLog("Function finished in %g s.",_CV_Benchmark_##prefix##_elapsed)
#define CV_BenchmarkTime(prefix)    _CV_Benchmark_##prefix##_elapsed

#else

#define CV_BenchmarkPrepare(prefix)
#define CV_BenchmarkStart(prefix)
#define CV_BenchmarkStop(prefix)
#define CV_BenchmarkPrint(prefix)
#define CV_BenchmarkTime(prefix)

#endif //CV_BENCHMARK_FUNCTIONS


/* Boolean Types */
typedef unsigned char CVBool;
#define CVBoolScan "hhu"

#define CVTrue 1
#define CVFalse 0

/* Capacity Grow*/
#define CVCapacityGrow(count) ((count)*2+1)

/* ATOMIC OPERATIONS */


#if __WIN32__
#include "Windows.h"
CV_INLINE CVBool CVAtomicCompareAndSwap32Barrier(int32_t oldValue, int32_t newValue, volatile int32_t *theValue) {
    int32_t actualOldValue = InterlockedCompareExchange((volatile LONG *)theValue, newValue, oldValue);
    return actualOldValue == oldValue ? CVTrue : CVFalse;
}
#if CV_BUILD_64BITS
CV_INLINE CVBool CVAtomicCompareAndSwap64Barrier(int64_t oldValue, int64_t newValue, volatile int64_t *theValue) {
	int64_t actualOldValue = InterlockedCompareExchange64((volatile LONGLONG *)theValue, newValue, oldValue);
    return actualOldValue == oldValue ? CVTrue : CVFalse;
}
#endif
CV_INLINE CVBool CVAtomicCompareAndSwapPtrBarrier(void* oldValue, void* newValue, void* volatile *theValue) {
	void *actualOldValue = InterlockedCompareExchangePointer((volatile PVOID*)theValue, newValue, (PVOID)oldValue);
	return actualOldValue == oldValue ? CVTrue : CVFalse;
}
CV_INLINE int32_t CVAtomicIncrement32(volatile int32_t *theValue) {
	return (int)InterlockedIncrement((volatile LONG*)theValue);
}

#if CV_BUILD_64BITS
CV_INLINE int64_t CVAtomicIncrement64(volatile int64_t *theValue) {
	return (long long)InterlockedIncrement64((volatile LONGLONG*)theValue);
}
#endif

CV_INLINE void CVMemoryBarrier(void) {
#if _MSC_VER
	MemoryBarrier();
#else
	__sync_synchronize();
#endif
}

#elif __APPLE__
#include <libkern/OSAtomic.h>
#include <stdatomic.h>

CV_INLINE CVBool CVAtomicCompareAndSwap32Barrier(int32_t __oldValue, int32_t __newValue, volatile int32_t *__theValue) {
	return OSAtomicCompareAndSwap32Barrier(__oldValue, __newValue, __theValue);
}
CV_INLINE CVBool CVAtomicCompareAndSwap64Barrier(int64_t __oldValue, int64_t __newValue, volatile int64_t *__theValue) {
	return OSAtomicCompareAndSwap64Barrier(__oldValue, __newValue, __theValue);
}
CV_INLINE CVBool CVAtomicCompareAndSwapPtrBarrier(void* __oldValue, void* __newValue, void* volatile *__theValue) {
	return OSAtomicCompareAndSwapPtrBarrier(__oldValue, __newValue, __theValue);
}
CV_INLINE int32_t CVAtomicIncrement32(volatile int32_t *theValue) {
	return OSAtomicIncrement32(theValue);
}
CV_INLINE int64_t CVAtomicIncrement64(volatile int64_t *theValue) {
	return OSAtomicIncrement64(theValue);
}
CV_INLINE void CVMemoryBarrier(void) {
	OSMemoryBarrier();
}
#else// DEPLOYMENT_TARGET_LINUX
	 // Simply leverage GCC's atomic built-ins (see http://gcc.gnu.org/onlinedocs/gcc-4.1.0/gcc/Atomic-Builtins.html)
CV_INLINE CVBool CVAtomicCompareAndSwap32Barrier(int32_t __oldValue, int32_t __newValue, volatile int32_t *__theValue) {
	return __sync_bool_compare_and_swap(__theValue, __oldValue, __newValue);
}
CV_INLINE CVBool CVAtomicCompareAndSwap64Barrier(int64_t __oldValue, int64_t __newValue, volatile int64_t *__theValue) {
	return __sync_bool_compare_and_swap(__theValue, __oldValue, __newValue);
}
CV_INLINE CVBool CVAtomicCompareAndSwapPtrBarrier(void* __oldValue, void* __newValue, void* volatile *__theValue) {
	return __sync_bool_compare_and_swap(__theValue, __oldValue, __newValue);
}
CV_INLINE int32_t CVAtomicIncrement32(volatile int32_t *theValue) {
	return __sync_fetch_and_add(theValue, 1);
}
CV_INLINE int64_t CVAtomicIncrement64(volatile int64_t *theValue) {
	return __sync_fetch_and_add(theValue, 1);
}
CV_INLINE void CVMemoryBarrier(void) {
	__sync_synchronize();
}
//#else
//#error "Don't know how to perform atomic operations."
#endif



/* Integer definitions */

#if CV_BUILD_64BITS
typedef uint64_t CVUInteger;
typedef int64_t CVInteger;
#define CVUIntegerScan PRIu64
#define CVIntegerScan PRId64
#define CVIntegerMAX INT64_MAX
#define CVUIntegerMAX UINT64_MAX

CV_INLINE CVBool CVAtomicCompareAndSwapIntegerBarrier(CVInteger __oldValue, CVInteger __newValue, volatile CVInteger* __theValue){
	return CVAtomicCompareAndSwap64Barrier(__oldValue, __newValue, __theValue);
}

CV_INLINE int64_t CVAtomicIncrementInteger(volatile CVInteger* theValue) {
	return CVAtomicIncrement64(theValue);
}

#else
typedef uint32_t CVUInteger;
typedef int32_t CVInteger;
#define CVUIntegerScan PRIu32
#define CVIntegerScan PRId32
#define CVIntegerMAX INT32_MAX
#define CVUIntegerMAX UINT32_MAX
CV_INLINE CVBool CVAtomicCompareAndSwapIntegerBarrier(CVInteger __oldValue, CVInteger __newValue, volatile CVInteger* __theValue){
	return CVAtomicCompareAndSwap32Barrier(__oldValue, __newValue, __theValue);
}

CV_INLINE int64_t CVAtomicIncrementInteger(volatile CVInteger* theValue) {
	return CVAtomicIncrement32(theValue);
}

#endif

typedef CVUInteger CVIndex;
#define CVIndexScan CVUIntegerScan
typedef CVIndex CVSize;
#define CVSizeScan CVUIntegerScan
typedef float CVFloat;
#define CVFloatScan "g"
typedef double CVDouble;
#define CVDoubleScan "g"

#define CVFloatMIN -FLT_MAX
#define CVFloatMAX FLT_MAX



#if __APPLE__
CV_INLINE void CVRandomSeedDev(){
	srandomdev();
	uint64_t okok = random();
	seed48((unsigned short*)&okok);
}
static int g_seed = 100;
CV_INLINE int CV_FastrandInt() {
	g_seed = (214013*g_seed+2531011);
	return (g_seed>>16)&0x7FFF;
}
CV_INLINE void CVRandomSeed(CVUInteger seed){srandom((unsigned int)seed);}
CV_INLINE CVUInteger CVRandom() {return random();}
CV_INLINE CVInteger CVRandomInRange(CVInteger start,CVInteger length){return (CVInteger)start+(CVInteger)(random()%(length));}
CV_INLINE CVFloat CVRandomFloat(){return (float)drand48();}

#elif defined(LINUX)
CV_INLINE void CVRandomSeedDev(){
	srandom(time(NULL));
	uint64_t okok = random();
	seed48((unsigned short*)&okok);
}
static int g_seed = 100;
CV_INLINE int CV_FastrandInt() {
	g_seed = (214013*g_seed+2531011);
	return (g_seed>>16)&0x7FFF;
}
CV_INLINE void CVRandomSeed(CVUInteger seed){srandom((unsigned int)seed);}
CV_INLINE CVUInteger CVRandom() {return random();}
CV_INLINE CVInteger CVRandomInRange(CVInteger start,CVInteger length){return (CVInteger)start+(CVInteger)(random()%(length));}
CV_INLINE CVFloat CVRandomFloat(){return (float)drand48();}
#else
#pragma message ("warning: Generic random")
CV_INLINE void CVRandomSeedDev(){srand(time(NULL));}
CV_INLINE void CVRandomSeed(CVUInteger seed){srand((unsigned int)seed);}
CV_INLINE CVUInteger CVRandom() {return rand();}
CV_INLINE CVInteger CVRandomInRange(CVInteger start,CVInteger length){
	uint32_t n = (uint32_t)length;
	uint32_t limit = RAND_MAX - RAND_MAX % n;
	uint32_t rnd;
	do {
		rnd = rand();
	} while (rnd >= limit);
	return start + (rnd % n);
}
CV_INLINE CVFloat CVRandomFloat(){return (float)rand()/(float)(RAND_MAX);}
#endif

typedef char CVChar;
typedef CVChar* CVString;

#define _kCVStringReadlineINITSIZE   112  /* power of 2 minus 16, helps malloc */
#define _kCVStringReadlineDELTASIZE (_kCVStringReadlineINITSIZE + 16)


CV_INLINE CVString CVNewStringReadingLine(FILE *f){
	int     cursize, ch, ix;
	char   *buffer, *temp;
	char* ln;
	
	ln = NULL; /* default */
	if (NULL == (buffer = (char *) malloc(_kCVStringReadlineINITSIZE))) return NULL;
	cursize = _kCVStringReadlineINITSIZE;
	
	ix = 0;
	while ((EOF != (ch = getc(f))) && ('\n' != ch)) {
		if (ix >= (cursize - 1)) { /* extend buffer */
			cursize += _kCVStringReadlineDELTASIZE;
			if (NULL == (temp = (char * )realloc(buffer, (size_t)cursize))) {
				/* ran out of memory, return partial line */
				buffer[ix] = '\0';
				ln = buffer;
				return NULL;
			}
			buffer = temp;
		}
		buffer[ix++] = ch;
	}
	if ((EOF == ch) && (0 == ix)) {
		free(buffer);
		return NULL;//Check
	}
	
	buffer[ix] = '\0';
	if (NULL == (temp = (char *)realloc(buffer, (size_t)ix + 1))) {
		ln = buffer;  /* without reducing it */
	}
	else ln = temp;
	return ln;
}


CV_INLINE CVSize CVStringScan(CVString* scannedString, const CVString scanString){
	CVSize scanStringLength = strlen(scanString);
	if(strncmp(*scannedString,scanString,scanStringLength)==0){
		(*scannedString)+= scanStringLength;
		return scanStringLength;
	}else{
		return 0;
	}
}

CV_INLINE CVSize CVStringScanCharacters(CVString* scannedString, CVChar scanCharacter){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	while (scannedStringTemp[0]==scanCharacter) {
		scannedStringTemp++;
		scannedCount++;
	}
	*scannedString = scannedStringTemp;
	return scannedCount;
}

CV_INLINE CVString CVNewStringScanningUpToCharacter(CVString* scannedString, CVChar stopCharacter){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	CVSize capacity = 1;
	CVString returnString = (CVString)calloc(1,sizeof(CVChar));
	while (scannedStringTemp[0]!=stopCharacter&&scannedStringTemp[0]) {
		if(capacity<scannedCount+2){
			capacity=CVCapacityGrow(scannedCount+2);
			returnString = (CVString)realloc(returnString,capacity);
		}
		returnString[scannedCount] = scannedStringTemp[0];
		scannedStringTemp++;
		scannedCount++;
	}
	returnString[scannedCount] = '\0';
	*scannedString = scannedStringTemp;
	return returnString;
}


CV_INLINE CVString CVNewStringFromString(const CVString theString){
	CVString newString = (char *) malloc(sizeof(char) * (strlen(theString)+1));
	strcpy(newString,theString);
	return newString;
}

#ifdef __EMSCRIPTEN__
// Emscripten does have this function, but it is not declared in stdio.h
extern int vasprintf(char **strp, const char *fmt, va_list ap);
#endif

static CVString CVNewStringFromFormat(const CVString format, ...){
	va_list arglist;
	va_start(arglist,format);
	CVString returnedString = NULL;
	vasprintf(&returnedString,format,arglist);
	va_end(arglist);
	return returnedString;
}

CV_INLINE CVString CVNewStringScanningUpToCharactersInList(CVString* scannedString, const CVString stopCharacters){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	CVSize capacity = 1;
	CVString returnString = (CVString)calloc(1,sizeof(CVChar));
	CVSize stopCharactersSize = strlen(stopCharacters);
	while (scannedStringTemp[0]) {
		CVIndex stopIndex=0;
		CVBool foundStopCharacter = CVFalse;
		for (stopIndex=0; stopIndex<stopCharactersSize; stopIndex++) {
			if(scannedStringTemp[0]==stopCharacters[stopIndex]){
				foundStopCharacter = CVTrue;
			};
		}
		
		if(foundStopCharacter){
			break;
		}
		
		if(capacity<scannedCount+2){
			capacity=CVCapacityGrow(scannedCount+2);
			returnString = (CVString)realloc(returnString,capacity);
		}
		returnString[scannedCount] = scannedStringTemp[0];
		scannedStringTemp++;
		scannedCount++;
	}
	returnString[scannedCount] = '\0';
	*scannedString = scannedStringTemp;
	return returnString;
}


CV_INLINE CVSize CVStringScanUpToCharactersInList(CVString* scannedString, const CVString stopCharacters){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	CVSize stopCharactersSize = strlen(stopCharacters);
	while (scannedStringTemp[0]) {
		CVIndex stopIndex=0;
		CVBool foundStopCharacter = CVFalse;
		for (stopIndex=0; stopIndex<stopCharactersSize; stopIndex++) {
			if(scannedStringTemp[0]==stopCharacters[stopIndex]){
				foundStopCharacter = CVTrue;
			};
		}
		
		if(foundStopCharacter){
			break;
		}
		
		scannedStringTemp++;
		scannedCount++;
	}
	*scannedString = scannedStringTemp;
	return scannedCount;
}

CV_INLINE CVString CVNewStringScanningUpToString(CVString* scannedString, const CVString stopString){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	CVSize capacity = 1;
	CVString returnString = (CVString)calloc(1,sizeof(CVChar));
	while (scannedStringTemp[0]) {
		CVString checkScannedString = scannedStringTemp;
		CVString checkStopString = stopString;
		while (checkScannedString[0]==checkStopString[0]&&checkScannedString[0]&&checkStopString[0]){
			checkScannedString++;
			checkStopString++;
		}
		if(checkStopString[0]){
			if(capacity<scannedCount+2){
				capacity=CVCapacityGrow(scannedCount+2);
				returnString = (CVString)realloc(returnString,capacity);
			}
			returnString[scannedCount] = scannedStringTemp[0];
			scannedStringTemp++;
			scannedCount++;
		}else{
			break;
		}
	}
	returnString[scannedCount] = '\0';
	*scannedString = scannedStringTemp;
	return returnString;
}


CV_INLINE CVSize CVStringScanUpToString(CVString* scannedString, const CVString stopString){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	while (scannedStringTemp[0]) {
		CVString checkScannedString = scannedStringTemp;
		CVString checkStopString = stopString;
		while (checkScannedString[0]==checkStopString[0]&&checkScannedString[0]&&checkStopString[0]){
			checkScannedString++;
			checkStopString++;
		}
		if(checkStopString[0]){
			scannedStringTemp++;
			scannedCount++;
		}else{
			break;
		}
	}
	*scannedString = scannedStringTemp;
	return scannedCount;
}


CV_INLINE CVSize CVStringScanIndex(CVString* scannedString, CVIndex* scannedIndex){
	CVString scannedStringTemp;
	CVSize scannedCount = 0;
	CVIndex scannedValue = strtol(*scannedString, &scannedStringTemp, 10);
	scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
	if(scannedCount){
		*scannedIndex = scannedValue;
		*scannedString = scannedStringTemp;
	}
	return scannedCount;
}


CV_INLINE CVInteger CVStringScanInteger(CVString* scannedString, CVInteger* scannedInteger){
	CVString scannedStringTemp;
	CVSize scannedCount = 0;
	CVInteger scannedValue = strtol(*scannedString, &scannedStringTemp, 10);
	scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
	if(scannedCount){
		*scannedInteger = scannedValue;
		*scannedString = scannedStringTemp;
	}
	return scannedCount;
}

CV_INLINE CVSize CVStringScanFloat(CVString* scannedString, float*  scannedFloat){
	CVString scannedStringTemp;
	CVSize scannedCount = 0;
	float scannedValue = strtof(*scannedString, &scannedStringTemp);
	scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
	if(scannedCount){
		*scannedFloat = scannedValue;
		*scannedString = scannedStringTemp;
	}
	return scannedCount;
}
CV_INLINE CVSize CVStringScanDouble(CVString* scannedString, double* scannedDouble){
	CVString scannedStringTemp;
	CVSize scannedCount = 0;
	double scannedValue = strtod(*scannedString, &scannedStringTemp);
	scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
	if(scannedCount){
		*scannedDouble = scannedValue;
		*scannedString = scannedStringTemp;
	}
	return scannedCount;
}


CV_INLINE CVSize CVStringScanStrictIndex(CVString* scannedString, CVIndex* scannedIndex){
	CVSize scannedCount = 0;
	if(!isspace(**scannedString)){
		CVString scannedStringTemp;
		CVIndex scannedValue = strtol(*scannedString, &scannedStringTemp, 10);
		scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
		if(scannedCount){
			*scannedIndex = scannedValue;
			*scannedString = scannedStringTemp;
		}
	}
	return scannedCount;
}


CV_INLINE CVInteger CVStringScanStrictInteger(CVString* scannedString, CVInteger* scannedInteger){
	CVSize scannedCount = 0;
	if(!isspace(**scannedString)){
		CVString scannedStringTemp;
		CVInteger scannedValue = strtol(*scannedString, &scannedStringTemp, 10);
		scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
		if(scannedCount){
			*scannedInteger = scannedValue;
			*scannedString = scannedStringTemp;
		}
	}
	return scannedCount;
}

CV_INLINE CVSize CVStringScanStrictFloat(CVString* scannedString, float* scannedFloat){
	CVSize scannedCount = 0;
	if(!isspace(**scannedString)){
		CVString scannedStringTemp;
		float scannedValue = strtof(*scannedString, &scannedStringTemp);
		scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
		if(scannedCount){
			*scannedFloat = scannedValue;
			*scannedString = scannedStringTemp;
		}
	}
	return scannedCount;
}

CV_INLINE CVSize CVStringScanStrictDouble(CVString* scannedString, double* scannedDouble){
	CVSize scannedCount = 0;
	if(!isspace(**scannedString)){
		CVString scannedStringTemp;
		double scannedValue = strtod(*scannedString, &scannedStringTemp);
		scannedCount = (CVSize)(scannedStringTemp-(*scannedString));
		if(scannedCount){
			*scannedDouble = scannedValue;
			*scannedString = scannedStringTemp;
		}
	}
	return scannedCount;
}


CV_INLINE CVSize CVStringScanCharactersList(CVString* scannedString, const CVString charactersList){
	CVString scannedStringTemp = *scannedString;
	CVSize scannedCount = 0;
	CVSize charListIndex = 0;
	CVSize charListCount = strlen(charactersList);
	CVSize notfoundChar = 0;
	while(charListIndex<charListCount&&notfoundChar<charListCount){
		CVChar scanCharacter = charactersList[charListIndex];
		charListIndex = (charListIndex+1)%charListCount;
		notfoundChar++;
		while (scannedStringTemp[0]==scanCharacter) {
			scannedStringTemp++;
			scannedCount++;
			notfoundChar=0;
		}
	}
	*scannedString = scannedStringTemp;
	return scannedCount;
}

CV_INLINE CVBool _CVStringIsInSet(CVChar readChar, CVString const charSet){
	if(readChar=='\0'){
		return CVFalse;
	}
	CVString curCharSet = charSet;
	CVBool charFound = CVFalse;
	while (*curCharSet&&!(charFound=((*(curCharSet++))==readChar))) {}
	return charFound;
}

CV_INLINE void CVStringTrim(CVString theString, CVString const trimCharacters){
	if(theString && theString[0]){
		CVString curString = theString;
		CVIndex stringIndex = strlen(curString);
		while(stringIndex&& *curString &&_CVStringIsInSet(curString[stringIndex - 1],trimCharacters)){
			curString[--stringIndex] = 0;
		}
		while(*curString && _CVStringIsInSet(*curString,trimCharacters)) ++curString, --stringIndex;
		memmove(theString, curString, stringIndex + 1);
	}
}

CV_INLINE void CVStringTrimSpaces(CVString theString) {
	if(theString && theString[0]){
		CVString curString = theString;
		CVIndex stringIndex = strlen(curString);
		while(isspace(curString[stringIndex - 1])) curString[--stringIndex] = 0;
		while(*curString && isspace(*curString)) ++curString, --stringIndex;
		memmove(theString, curString, stringIndex + 1);
	}
}

CV_INLINE void CVStringDestroy(CVString theString){
	free(theString);
}


CV_INLINE CVString CVNewStringByRemovingFileExtension(const CVString theString) {
	CVString newString, lastExtensionSeparator, lastPathSeparator;
#if __WIN32__
#pragma message ("warning: Windows may need to use other separators, check this. FIXME")
// #warning "Windows may need to use other separators, check this. FIXME"
	char extensionSeparator = '.';
	char pathSeparator = '\\';
#else
	char extensionSeparator = '.';
	char pathSeparator = '/';
#endif
	if (theString == NULL){
		return NULL;
	}
	
	if ((newString = (char *)calloc(sizeof(char),strlen(theString) + 1)) == NULL){
		return NULL;
	}
	
	strcpy(newString, theString);
	
	lastExtensionSeparator = strrchr(newString, extensionSeparator);
	lastPathSeparator = (pathSeparator == 0) ? NULL : strrchr(newString, pathSeparator);
	
	if(lastExtensionSeparator != NULL){
		if (lastPathSeparator != NULL) {
			if (lastPathSeparator < lastExtensionSeparator) {
				*lastExtensionSeparator = '\0';
			}
		}else{
			*lastExtensionSeparator = '\0';
		}
	}
	return newString;
}

CV_INLINE CVString CVNewStringFromPathExtension(const CVString theString) {
	CVString newString, lastExtensionSeparator, lastPathSeparator;
#if __WIN32__
#pragma message ("warning: Windows may need to use other separators, check this. FIXME")
// #warning "Windows may need to use other separators, check this. FIXME"
	char extensionSeparator = '.';
	char pathSeparator = '\\';
#else
	char extensionSeparator = '.';
	char pathSeparator = '/';
#endif
	if (theString == NULL){
		return NULL;
	}
	newString = NULL;
	lastExtensionSeparator = strrchr(theString, extensionSeparator);
	lastPathSeparator = (pathSeparator == 0) ? NULL : strrchr(theString, pathSeparator);
	CVSize stringLength = strlen(theString);
	if(lastExtensionSeparator != NULL){
		if (lastPathSeparator != NULL) {
			if (lastPathSeparator < lastExtensionSeparator) {
				CVSize extensionLength = ((theString+stringLength)-(lastExtensionSeparator+1));
				if ((newString = (char *)calloc(sizeof(char),extensionLength + 1)) == NULL){
					return NULL;
				}
				strcpy(newString, (lastExtensionSeparator+1));
			}
		}else{
			CVSize extensionLength = ((theString+stringLength)-(lastExtensionSeparator+1));
			if ((newString = (char *)calloc(sizeof(char),extensionLength + 1)) == NULL){
				return NULL;
			}
			strcpy(newString, (lastExtensionSeparator+1));
		}
	}
	if(newString==NULL){
		newString = CVNewStringFromString("");
	}
	return newString;
}



CV_INLINE int64_t ipow(int32_t base, uint8_t exp) {
    static const uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 255, // anything past 63 is a guaranteed overflow with base > 1
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
    };
	
    uint64_t result = 1;
	
    switch (highest_bit_set[exp]) {
		case 255: // we use 255 as an overflow marker and return 0 on overflow/underflow
			if (base == 1) {
				return 1;
			}
			
			if (base == -1) {
				return 1 - 2 * (exp & 1);
			}
			
			return 0;
		case 6:
			if (exp & 1) result *= base;
			exp >>= 1;
			base *= base;
		case 5:
			if (exp & 1) result *= base;
			exp >>= 1;
			base *= base;
		case 4:
			if (exp & 1) result *= base;
			exp >>= 1;
			base *= base;
		case 3:
			if (exp & 1) result *= base;
			exp >>= 1;
			base *= base;
		case 2:
			if (exp & 1) result *= base;
			exp >>= 1;
			base *= base;
		case 1:
			if (exp & 1) result *= base;
		default:
			return result;
    }
}

CV_INLINE CVUInteger ilog2(uint64_t value){
	
	const CVUInteger tab64[64] = {
		63,  0, 58,  1, 59, 47, 53,  2,
		60, 39, 48, 27, 54, 33, 42,  3,
		61, 51, 37, 40, 49, 18, 28, 20,
		55, 30, 34, 11, 43, 14, 22,  4,
		62, 57, 46, 52, 38, 26, 32, 41,
		50, 36, 17, 19, 29, 10, 13, 21,
		56, 45, 25, 31, 35, 16,  9, 12,
		44, 24, 15,  8, 23,  7,  6,  5};
	
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value |= value >> 32;
    return tab64[((uint64_t)((value - (value >> 1))*0x07EDD5E59A4E28C2)) >> 58];
}

CV_INLINE CVInteger ipow2(CVInteger n){
	return n>=0?(1<<n):0;
}



CV_INLINE uint64_t CVNextPowerOfTwo(uint64_t n){
	n = n - 1;
	n = n | (n >> 1);
	n = n | (n >> 2);
	n = n | (n >> 4);
	n = n | (n >> 8);
	n = n | (n >> 16);
	n = n | (n >> 32);
	n = n + 1;
	return n;
}


typedef struct _CVOperationControl{
	CVBool shouldAbort;
	CVInteger currentProgress;
	CVInteger maxProgress;
	CVInteger maxParallelBlocks;
	CVBool finished;
	void (*updateCallback)(struct _CVOperationControl*);
	void (*streamCallback)(struct _CVOperationControl*,CVIndex,const char* format, ...);
	FILE* defaultStreamFile;
	void* context;
} CVOperationControl;

CV_INLINE CVOperationControl* CVOperationControlCreate(){
	CVOperationControl* operationControl = (CVOperationControl*)malloc(sizeof(CVOperationControl));
	operationControl->shouldAbort=CVFalse;
	operationControl->context=CVFalse;
	operationControl->currentProgress=0;
	operationControl->maxProgress=-1;
	operationControl->maxParallelBlocks = kCVDefaultParallelBlocks;
	operationControl->context = NULL;
	operationControl->updateCallback = NULL;
	operationControl->streamCallback = NULL;
	operationControl->defaultStreamFile = NULL;
	//FIXME: Add callbacks and events support.
	return operationControl;
}

CV_INLINE void CVOperationControlDestroy(CVOperationControl* operationControl){
	free(operationControl);
}


#define __CVSTRINGIFY(x) #x
#define CVTOKENTOSTRING(x) __CVSTRINGIFY(x)


#if CV_USE_LIBDISPATCH
#include <dispatch/dispatch.h>
#define CV_ENABLE_PARALLELISM 1

#define CVParallelForStart(loopName, indexName, count) \
dispatch_semaphore_t __##loopName##Semaphore = dispatch_semaphore_create(1); \
dispatch_queue_t __##loopName##AsyncQueue = dispatch_queue_create("com.opencx.parallelfor." CVTOKENTOSTRING(__##loopName##AsyncQueue),NULL);\
dispatch_queue_t __##loopName##Queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);\
dispatch_apply(count, __##loopName##Queue, ^(size_t indexName) {

#define CVParallelForEnd(loopName) });\
dispatch_release(__##loopName##Semaphore);\
dispatch_release(__##loopName##AsyncQueue);


#define CVParallelLoopCriticalRegionStart(loopName) dispatch_semaphore_wait(__##loopName##Semaphore, DISPATCH_TIME_FOREVER);
#define CVParallelLoopCriticalRegionEnd(loopName) dispatch_semaphore_signal(__##loopName##Semaphore);

#define CVParallelLoopSyncCriticalRegionStart(loopName) dispatch_sync(__##loopName##Semaphore, ^{
#define CVParallelLoopSyncCriticalRegionEnd(loopName) });


#elif CV_USE_OPENMP
// #warning "OPENMP ENABLED"
#pragma message ("warning: OPENMP ENABLED")
#include <omp.h>
#define CV_USE_OPENMP 1
#define CV_ENABLE_PARALLELISM 1
#if __WIN32__
#define CVParallelForStart(loopName, indexName, count) \
CVInteger indexName; \
_Pragma("omp parallel for") \
for(indexName=0;indexName<count;indexName++)
#else
#define CVParallelForStart(loopName, indexName, count) \
CVIndex indexName; \
_Pragma("omp parallel for") \
for(indexName=0;indexName<count;indexName++)
#endif

#define CVParallelForEnd(loopName) 

#define CVParallelLoopCriticalRegionStart(loopName) _Pragma("omp critical") {
#define CVParallelLoopCriticalRegionEnd(loopName) }

#define CVParallelLoopSyncCriticalRegionStart(loopName) _Pragma("omp critical") {
#define CVParallelLoopSyncCriticalRegionEnd(loopName) }


#else

#define CV_ENABLE_PARALLELISM 0

#define CVParallelForStart(loopName, indexName, count) \
printf("NOT using OMP\n");\
CVIndex indexName;\
for(indexName=0;indexName<count;indexName++){

#define CVParallelForEnd(loopName) }

#define CVParallelLoopCriticalRegionStart(loopName)
#define CVParallelLoopCriticalRegionEnd(loopName)

#define CVParallelLoopSyncCriticalRegionStart(loopName)
#define CVParallelLoopSyncCriticalRegionEnd(loopName)


#endif //_OPENMP

typedef char* CVBitArray;

#define CVBitArrayMask(index) (1 << ((index) % CHAR_BIT))
#define CVBitArraySlot(index) ((index) / CHAR_BIT)
#define CVBitArraySet(bitArray, index) ((bitArray)[CVBitArraySlot(index)] |= CVBitArrayMask(index))
#define CVBitArrayClear(bitArray, index) ((bitArray)[CVBitArraySlot(index)] &= ~CVBitArrayMask(index))
#define CVBitArrayTest(bitArray, index) ((bitArray)[CVBitArraySlot(index)] & CVBitArrayMask(index))
#define CVBitArrayNSlots(size) ((size + CHAR_BIT - 1) / CHAR_BIT)

CV_INLINE CVBitArray CVNewBitArray(CVSize count){
	return (CVBitArray)calloc(CVBitArrayNSlots(count),1);
}

#define CVBitArrayStatic(variableName,count) char variableName[CVBitArrayNSlots(count)]

CV_INLINE CVBitArray CVReallocBitArray(CVBitArray bitArray,CVSize count){
	return (CVBitArray)realloc(bitArray,CVBitArrayNSlots(count));
}

CV_INLINE CVBitArray CVNewBitArrayClone(const CVBitArray bitArray,CVSize count){
	CVBitArray newBitArray = CVNewBitArray(count);
	memcpy(newBitArray, bitArray, CVBitArrayNSlots(count));
	return newBitArray;
}

CV_INLINE void CVNewBitArrayCopyTo(const CVBitArray fromBitArray,CVSize count, CVBitArray toBitArray){
	memcpy(toBitArray, fromBitArray, CVBitArrayNSlots(count));
}


CV_INLINE void CVGrowBitArray(CVSize newCount, CVSize* count, CVSize* capacity, CVBitArray* bitArray){
	if(*capacity<newCount){
		*capacity = CVCapacityGrow(newCount);
		*bitArray = (CVBitArray)realloc(*bitArray,CVBitArrayNSlots(*capacity));
	}
	if(count){
		*count = newCount;
	}
}


CV_INLINE void CVBitArrayClearAll(CVBitArray bitArray, CVSize count){
	memset(bitArray,0,CVBitArrayNSlots(count));
}

CV_INLINE void CVBitArrayDestroy(CVBitArray bitArray){
	free(bitArray);
}



#define CVGrowArray(newCount, elementSize, count, capacity, array) do{\
if((capacity)<(newCount)){\
(capacity) = CVCapacityGrow(newCount);\
array = realloc((array),(capacity)*(elementSize));\
}\
(count) = (newCount);\
} while (0)

#define CVGrowArrayAddElement(element, elementSize, count, capacity, array) do{\
if((capacity)<(count)+1){\
(capacity) = CVCapacityGrow((count)+1);\
(array) = realloc((array),(capacity)*(elementSize));\
}\
(count)++;\
(array)[count-1]=(element);\
} while (0)



#endif




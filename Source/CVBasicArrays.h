/**
 * @Author: Ashutosh Tiwari
 * @Date:   2023-08-28 12:17:13
 * @Last Modified by:   Ashutosh Tiwari
 * @Last Modified time: 2023-08-28 16:40:35
 */
//
//  CVBasicArrays.h
//  CVNetwork
//
//  Created by Filipi Nascimento Silva on 11/22/12.
//  Copyright (c) 2012 Filipi Nascimento Silva. All rights reserved.
//

#ifndef CVNetwork_CVBasicArrays_h
#define CVNetwork_CVBasicArrays_h

#include "CVCommons.h"

typedef struct{
	CVFloat* data;
	CVSize count;
	CVSize _capacity;
} CVFloatArray;

typedef CVFloatArray CVFloatStack;

typedef struct{
	CVDouble* data;
	CVSize count;
	CVSize _capacity;
} CVDoubleArray;

typedef CVDoubleArray CVDoubleStack;

typedef struct{
	CVInteger* data;
	CVSize count;
	CVSize _capacity;
} CVIntegerArray;

typedef CVIntegerArray CVIntegerStack;

typedef struct{
	CVInteger* data;
	CVSize count;
	CVSize _capacity;
} CVGLShortArray;

typedef struct{
	CVUInteger* data;
	CVSize count;
	CVSize _capacity;
} CVUIntegerArray;



typedef struct{
	void** data;
	CVSize count;
	CVSize _capacity;
} CVGenericArray;


typedef CVUIntegerArray CVUIntegerStack;
typedef CVGenericArray CVGenericStack;


CV_INLINE CVFloatArray* CVFloatArrayInitWithCapacity(CVSize capacity, CVFloatArray* theArray){
	theArray->count=0;
	theArray->_capacity=capacity;
	if (capacity==0) {
		theArray->data = NULL;
	}else{
		theArray->data = (float *)calloc(theArray->_capacity, sizeof(CVFloat));
	}
	return theArray;
}

CV_INLINE void CVFloatArrayDestroy(CVFloatArray* theArray){
	if(theArray->data!=NULL){
		free(theArray->data);
	}
}

CV_INLINE void CVFloatArrayReallocToCapacity(CVSize newCapacity, CVFloatArray* theArray){
	if(theArray->data!=NULL){
		theArray->data = (float *)realloc(theArray->data,newCapacity*sizeof(CVFloat));
	}else{
		theArray->data = (float *)calloc(newCapacity, sizeof(CVFloat));
	}
	theArray->_capacity=newCapacity;
	if(theArray->_capacity<theArray->count)
		theArray->count = theArray->_capacity;
}

CV_INLINE void CVFloatArrayAdd(CVFloat value, CVFloatArray* theArray){
	if(theArray->_capacity < theArray->count+1){
		CVFloatArrayReallocToCapacity(CVCapacityGrow(theArray->count+1), theArray);
	}
	theArray->data[theArray->count] = value;
	theArray->count++;
}

CV_INLINE void CVFloatArraySetCount(CVUInteger count, CVFloatArray* theArray){
	if(theArray->_capacity < count){
		CVFloatArrayReallocToCapacity(CVCapacityGrow(count), theArray);
	}else if(theArray->_capacity > count*3){
		CVFloatArrayReallocToCapacity(count, theArray);
	}
	theArray->count = count;
}

CV_INLINE CVFloatStack CVFloatStackMake(){
	CVFloatStack floatStack;
	CVFloatArrayInitWithCapacity(1, &floatStack);
	return floatStack;
}

CV_INLINE CVFloat CVFloatStackPop(CVFloatStack* floatStack){
	if (floatStack->count>0){
		floatStack->count--;
		return floatStack->data[floatStack->count];
	}else{
		return 0.0f;
	}
}

CV_INLINE void CVFloatStackPush(CVFloat value, CVFloatStack* floatStack){
	CVFloatArrayAdd(value, floatStack);
}

CV_INLINE CVFloat CVFloatStackTop(CVFloatStack* floatStack){
	if (floatStack->count>0){
		return floatStack->data[floatStack->count-1];
	}else{
		return 0.0f;
	}
}

CV_INLINE CVBool CVFloatStackIsEmpty(CVFloatStack* stack){
	if(stack->count>0){
		return CVFalse;
	}else{
		return CVTrue;
	}
}

CV_INLINE CVFloatArray CVFloatArrayCopy(CVFloatArray* theArray){
	CVFloatArray newArray;
	CVFloatArrayInitWithCapacity(theArray->count, &newArray);
	CVFloatArraySetCount(theArray->count, &newArray);
	memcpy(newArray.data, theArray->data, sizeof(CVFloat)*theArray->count);
	return newArray;
}


CV_INLINE CVDoubleArray* CVDoubleArrayInitWithCapacity(CVSize capacity, CVDoubleArray* theArray){
	theArray->count=0;
	theArray->_capacity=capacity;
	if (capacity==0) {
		theArray->data = NULL;
	}else{
		theArray->data = (double *)calloc(theArray->_capacity, sizeof(CVDouble));
	}
	return theArray;
}

CV_INLINE void CVDoubleArrayDestroy(CVDoubleArray* theArray){
	if(theArray->data!=NULL){
		free(theArray->data);
	}
}

CV_INLINE void CVDoubleArrayReallocToCapacity(CVSize newCapacity, CVDoubleArray* theArray){
	if(theArray->data!=NULL){
		theArray->data = (double *)realloc(theArray->data,newCapacity*sizeof(CVDouble));
	}else{
		theArray->data = (double *)calloc(newCapacity, sizeof(CVDouble));
	}
	theArray->_capacity=newCapacity;
	if(theArray->_capacity<theArray->count)
		theArray->count = theArray->_capacity;
}

CV_INLINE void CVDoubleArrayAdd(CVDouble value, CVDoubleArray* theArray){
	if(theArray->_capacity < theArray->count+1){
		CVDoubleArrayReallocToCapacity(CVCapacityGrow(theArray->count+1), theArray);
	}
	theArray->data[theArray->count] = value;
	theArray->count++;
}

CV_INLINE void CVDoubleArraySetCount(CVUInteger count, CVDoubleArray* theArray){
	if(theArray->_capacity < count){
		CVDoubleArrayReallocToCapacity(CVCapacityGrow(count), theArray);
	}else if(theArray->_capacity > count*3){
		CVDoubleArrayReallocToCapacity(count, theArray);
	}
	theArray->count = count;
}

CV_INLINE CVDoubleStack CVDoubleStackMake(){
	CVDoubleStack floatStack;
	CVDoubleArrayInitWithCapacity(1, &floatStack);
	return floatStack;
}

CV_INLINE CVDouble CVDoubleStackPop(CVDoubleStack* floatStack){
	if (floatStack->count>0){
		floatStack->count--;
		return floatStack->data[floatStack->count];
	}else{
		return 0.0;
	}
}

CV_INLINE void CVDoubleStackPush(CVDouble value, CVDoubleStack* floatStack){
	CVDoubleArrayAdd(value, floatStack);
}

CV_INLINE CVDouble CVDoubleStackTop(CVDoubleStack* floatStack){
	if (floatStack->count>0){
		return floatStack->data[floatStack->count-1];
	}else{
		return 0.0;
	}
}

CV_INLINE CVBool CVDoubleStackIsEmpty(CVDoubleStack* stack){
	if(stack->count>0){
		return CVFalse;
	}else{
		return CVTrue;
	}
}

CV_INLINE CVDoubleArray CVDoubleArrayCopy(CVDoubleArray* theArray){
	CVDoubleArray newArray;
	CVDoubleArrayInitWithCapacity(theArray->count, &newArray);
	CVDoubleArraySetCount(theArray->count, &newArray);
	memcpy(newArray.data, theArray->data, sizeof(CVDouble)*theArray->count);
	return newArray;
}



CV_INLINE CVIntegerArray* CVIntegerArrayInitWithCapacity(CVUInteger capacity, CVIntegerArray* theArray){
	theArray->count=0;
	theArray->_capacity=capacity;
	if (capacity==0) {
		theArray->data = NULL;
	}else{
		theArray->data = (int *)calloc(theArray->_capacity, sizeof(CVInteger));
	}
	return theArray;
}

CV_INLINE void CVIntegerArrayDestroy(CVIntegerArray* theArray){
	if(theArray->data!=NULL){
		free(theArray->data);
	}
}

CV_INLINE void CVIntegerArrayReallocToCapacity(CVUInteger newCapacity, CVIntegerArray* theArray){
	if(theArray->_capacity==newCapacity){
		return;
	}
	if(theArray->data!=NULL){
		theArray->data = (int *)realloc(theArray->data,newCapacity*sizeof(CVInteger));
	}else{
		theArray->data = (int *)calloc(newCapacity, sizeof(CVInteger));
	}
	theArray->_capacity=newCapacity;
	if(theArray->_capacity<theArray->count) theArray->count = theArray->_capacity;
}

CV_INLINE void CVIntegerArraySetCount(CVUInteger count, CVIntegerArray* theArray){
	if(theArray->_capacity < count){
		CVIntegerArrayReallocToCapacity(CVCapacityGrow(count), theArray);
	}else if(theArray->_capacity > count*3){
		CVIntegerArrayReallocToCapacity(count, theArray);
	}
	theArray->count = count;
}


CV_INLINE void CVIntegerArrayAdd(CVInteger value, CVIntegerArray* theArray){
	if(theArray->_capacity < theArray->count+1){
		CVIntegerArrayReallocToCapacity(CVCapacityGrow(theArray->count+1), theArray);
	}
	theArray->data[theArray->count] = value;
	theArray->count++;
}

CV_INLINE CVIntegerStack CVIntegerStackMake(){
	CVIntegerStack stack;
	CVIntegerArrayInitWithCapacity(1, &stack);
	return stack;
}

CV_INLINE CVInteger CVIntegerStackPop(CVIntegerStack* stack){
	if(stack->count>0){
		stack->count--;
		return stack->data[stack->count];
	}else{
		return 0;
	}
}

CV_INLINE void CVIntegerStackPush(CVInteger value, CVIntegerStack* stack){
	CVIntegerArrayAdd(value, stack);
}

CV_INLINE CVInteger CVIntegerStackTop(CVIntegerStack* stack){
	if(stack->count>0){
		return stack->data[stack->count-1];
	}else{
		return 0;
	}
}

CV_INLINE CVBool CVIntegerStackIsEmpty(CVIntegerStack* stack){
	if(stack->count>0){
		return CVFalse;
	}else{
		return CVTrue;
	}
}

CV_INLINE CVIntegerArray CVIntegerArrayCopy(CVIntegerArray* theArray){
	CVIntegerArray newArray;
	CVIntegerArrayInitWithCapacity(theArray->count, &newArray);
	CVIntegerArraySetCount(theArray->count, &newArray);
	memcpy(newArray.data, theArray->data, sizeof(CVInteger)*theArray->count);
	return newArray;
}



CV_INLINE CVUIntegerArray* CVUIntegerArrayInitWithCapacity(CVUInteger capacity, CVUIntegerArray* theArray){
	theArray->count=0;
	theArray->_capacity=capacity;
	if(capacity==0) {
		theArray->data = NULL;
	}else{
		theArray->data = (unsigned int *)(theArray->_capacity, sizeof(CVUInteger));
	}
	return theArray;
}

CV_INLINE void CVUIntegerArrayDestroy(CVUIntegerArray* theArray){
	if(theArray->data!=NULL){
		free(theArray->data);
	}
}

CV_INLINE void CVUIntegerArrayReallocToCapacity(CVUInteger newCapacity, CVUIntegerArray* theArray){
	if(theArray->data!=NULL){
		theArray->data = (unsigned int *)realloc(theArray->data,newCapacity*sizeof(CVUInteger));
	}else{
		theArray->data = (unsigned int *)calloc(newCapacity, sizeof(CVUInteger));
	}
	theArray->_capacity=newCapacity;
	if(theArray->_capacity<theArray->count) theArray->count = theArray->_capacity;
}

CV_INLINE void CVUIntegerArrayAdd(CVUInteger value, CVUIntegerArray* theArray){
	if(theArray->_capacity < theArray->count+1){
		CVUIntegerArrayReallocToCapacity(CVCapacityGrow(theArray->count+1), theArray);
	}
	theArray->data[theArray->count] = value;
	theArray->count++;
}


CV_INLINE void CVUIntegerArraySetCount(CVSize count, CVUIntegerArray* theArray){
	if(theArray->_capacity < count){
		CVUIntegerArrayReallocToCapacity(CVCapacityGrow(count), theArray);
	}else if(theArray->_capacity > count*3){
		CVUIntegerArrayReallocToCapacity(count, theArray);
	}
	theArray->count = count;
}

CV_INLINE CVUIntegerStack CVUIntegerStackMake(){
	CVUIntegerStack stack;
	CVUIntegerArrayInitWithCapacity(1, &stack);
	return stack;
}

CV_INLINE CVUInteger CVUIntegerStackPop(CVUIntegerStack* stack){
	if(stack->count>0){
		stack->count--;
		return stack->data[stack->count];
	}else{
		return 0;
	}
}

CV_INLINE void CVUIntegerStackPush(CVUInteger value, CVUIntegerStack* stack){
	CVUIntegerArrayAdd(value, stack);
}

CV_INLINE CVUInteger CVUIntegerStackTop(CVUIntegerStack* stack){
	if(stack->count>0){
		return stack->data[stack->count-1];
	}else{
		return 0;
	}
}

CV_INLINE CVBool CVUIntegerStackIsEmpty(CVUIntegerStack* stack){
	if(stack->count>0){
		return CVFalse;
	}else{
		return CVTrue;
	}
}

CV_INLINE CVUIntegerArray CVUIntegerArrayCopy(CVUIntegerArray* theArray){
	CVUIntegerArray newArray;
	CVUIntegerArrayInitWithCapacity(theArray->count, &newArray);
	CVUIntegerArraySetCount(theArray->count, &newArray);
	memcpy(newArray.data, theArray->data, sizeof(CVUInteger)*theArray->count);
	return newArray;
}


CV_INLINE CVGenericArray* CVGenericArrayInitWithCapacity(CVUInteger capacity, CVGenericArray* theArray){
	theArray->count=0;
	theArray->_capacity=capacity;
	if(capacity==0) {
		theArray->data = NULL;
	}else{
		*theArray->data = calloc(theArray->_capacity, sizeof(void*));
	}
	return theArray;
}

CV_INLINE void CVGenericArrayDestroy(CVGenericArray* theArray){
	if(theArray->data!=NULL){
		free(theArray->data);
	}
}



CV_INLINE void CVGenericArrayReallocToCapacity(CVUInteger newCapacity, CVGenericArray* theArray){
	if(theArray->data!=NULL){
		*theArray->data = realloc(theArray->data,newCapacity*sizeof(void*));
	}else{
		*theArray->data = calloc(newCapacity, sizeof(void*));
	}
	theArray->_capacity=newCapacity;
	if(theArray->_capacity<theArray->count) theArray->count = theArray->_capacity;
}

CV_INLINE void CVGenericArrayAdd(void* value, CVGenericArray* theArray){
	if(theArray->_capacity < theArray->count+1){
		CVGenericArrayReallocToCapacity(CVCapacityGrow(theArray->count+1), theArray);
	}
	theArray->data[theArray->count] = value;
	theArray->count++;
}

CV_INLINE void CVGenericArraySetCount(CVUInteger count, CVGenericArray* theArray){
	if(theArray->_capacity < count){
		CVGenericArrayReallocToCapacity(CVCapacityGrow(count), theArray);
	}else if(theArray->_capacity > count*3){
		CVGenericArrayReallocToCapacity(count, theArray);
	}
	theArray->count = count;
}

CV_INLINE CVGenericStack CVGenericStackMake(){
	CVGenericStack stack;
	CVGenericArrayInitWithCapacity(1, &stack);
	return stack;
}

CV_INLINE void* CVGenericStackPop(CVGenericStack* stack){
	if(stack->count>0){
		stack->count--;
		return stack->data[stack->count];
	}else{
		return 0;
	}
}

CV_INLINE void CVGenericStackPush(void* value, CVGenericStack* stack){
	CVGenericArrayAdd(value, stack);
}

CV_INLINE void* CVGenericStackTop(CVGenericStack* stack){
	if(stack->count>0){
		return stack->data[stack->count-1];
	}else{
		return 0;
	}
}

CV_INLINE CVBool CVGenericStackIsEmpty(CVGenericStack* stack){
	if(stack->count>0){
		return CVFalse;
	}else{
		return CVTrue;
	}
}


CV_INLINE CVGenericArray CVGenericArrayCopy(CVGenericArray* theArray){
	CVGenericArray newArray;
	CVGenericArrayInitWithCapacity(theArray->count, &newArray);
	CVGenericArraySetCount(theArray->count, &newArray);
	memcpy(newArray.data, theArray->data, sizeof(void*)*theArray->count);
	return newArray;
}





CV_INLINE CVBool CVQuickSortFloatArrayWithIndices(CVFloatArray floatArray, CVUIntegerArray indicesArray){
	CVUInteger MAX_LEVELS=floatArray.count;
	if(floatArray.count!=indicesArray.count){
		return CVFalse;
	}
	CVFloat  piv;
	CVInteger piv2, i=0, L, R ;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	
	beg[0]=0; end[0]=floatArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv=floatArray.data[L];
			piv2=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}
			
			while (L<R) {
				while (floatArray.data[R]>=piv && L<R)
					R--;
				
				if (L<R){
					indicesArray.data[L]=indicesArray.data[R];
					floatArray.data[L++]=floatArray.data[R];
				}
				while (floatArray.data[L]<=piv && L<R)
					L++;
				
				if (L<R){
					indicesArray.data[R]=indicesArray.data[L];
					floatArray.data[R--]=floatArray.data[L];
				}
			}
			floatArray.data[L]=piv;
			indicesArray.data[L]=piv2;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}



CV_INLINE CVBool CVQuickSortIndicesArrayWithFloat(CVIntegerArray indicesArray,CVFloatArray floatArray){
	CVInteger MAX_LEVELS=indicesArray.count;
	if(indicesArray.count!=floatArray.count){
		return CVFalse;
	}
	CVInteger  piv, i=0, L, R ;
	CVFloat piv2;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	
	beg[0]=0; end[0]=indicesArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv2=floatArray.data[L];
			piv=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}
			
			while (L<R) {
				while (indicesArray.data[R]>=piv && L<R)
					R--;
				
				if (L<R){
					indicesArray.data[L]=indicesArray.data[R];
					floatArray.data[L++]=floatArray.data[R];
				}
				while (indicesArray.data[L]<=piv && L<R)
					L++;
				
				if (L<R){
					indicesArray.data[R]=indicesArray.data[L];
					floatArray.data[R--]=floatArray.data[L];
				}
			}
			floatArray.data[L]=piv2;
			indicesArray.data[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}


CV_INLINE CVBool CVQuickSortDoubleArrayWithIndices(CVDoubleArray doubleArray, CVUIntegerArray indicesArray){
	CVUInteger MAX_LEVELS=doubleArray.count;
	if(doubleArray.count!=indicesArray.count){
		return CVFalse;
	}
	CVDouble  piv;
	CVInteger piv2, i=0, L, R ;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));

	beg[0]=0; end[0]=doubleArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv=doubleArray.data[L];
			piv2=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}

			while (L<R) {
				while (doubleArray.data[R]>=piv && L<R)
					R--;

				if (L<R){
					indicesArray.data[L]=indicesArray.data[R];
					doubleArray.data[L++]=doubleArray.data[R];
				}
				while (doubleArray.data[L]<=piv && L<R)
					L++;

				if (L<R){
					indicesArray.data[R]=indicesArray.data[L];
					doubleArray.data[R--]=doubleArray.data[L];
				}
			}
			doubleArray.data[L]=piv;
			indicesArray.data[L]=piv2;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}



CV_INLINE CVBool CVQuickSortIndicesArrayWithDouble(CVIntegerArray indicesArray,CVDoubleArray doubleArray){
	CVInteger MAX_LEVELS=indicesArray.count;
	if(indicesArray.count!=doubleArray.count){
		return CVFalse;
	}
	CVInteger  piv, i=0, L, R ;
	CVDouble piv2;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));

	beg[0]=0; end[0]=indicesArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv2=doubleArray.data[L];
			piv=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}

			while (L<R) {
				while (indicesArray.data[R]>=piv && L<R)
					R--;

				if (L<R){
					indicesArray.data[L]=indicesArray.data[R];
					doubleArray.data[L++]=doubleArray.data[R];
				}
				while (indicesArray.data[L]<=piv && L<R)
					L++;

				if (L<R){
					indicesArray.data[R]=indicesArray.data[L];
					doubleArray.data[R--]=doubleArray.data[L];
				}
			}
			doubleArray.data[L]=piv2;
			indicesArray.data[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}


CV_INLINE CVBool CVQuickSortIndicesArray(CVIntegerArray indicesArray){
	CVUInteger MAX_LEVELS=indicesArray.count;
	CVInteger  piv, i=0, L, R ;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	
	beg[0]=0; end[0]=indicesArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}
			
			while (L<R) {
				while (indicesArray.data[R]>=piv && L<R)
					R--;
				
				if (L<R){
					indicesArray.data[L++]=indicesArray.data[R];
				}
				while (indicesArray.data[L]<=piv && L<R)
					L++;
				
				if (L<R){
					indicesArray.data[R--]=indicesArray.data[L];
				}
			}
			indicesArray.data[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}


CV_INLINE CVBool CVQuickSortUIntegerArray(CVUIntegerArray indicesArray){
	CVUInteger MAX_LEVELS=indicesArray.count;
	CVUInteger  piv;
	CVInteger i=0, L, R ;
	CVInteger* beg=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	CVInteger* end=(CVInteger*) calloc(MAX_LEVELS, sizeof(CVInteger));
	
	beg[0]=0; end[0]=indicesArray.count;
	while (i>=0) {
		L=beg[i];
		R=end[i]-1;
		if (L<R) {
			piv=indicesArray.data[L];
			if (i==MAX_LEVELS-1){
				free(beg);
				return CVFalse;
			}
			
			while (L<R) {
				while (indicesArray.data[R]>=piv && L<R)
					R--;
				
				if (L<R){
					indicesArray.data[L++]=indicesArray.data[R];
				}
				while (indicesArray.data[L]<=piv && L<R)
					L++;
				
				if (L<R){
					indicesArray.data[R--]=indicesArray.data[L];
				}
			}
			indicesArray.data[L]=piv;
			beg[i+1]=L+1;
			end[i+1]=end[i];
			end[i++]=L;
		}
		else {
			i--;
		}
	}
	free(beg);
	free(end);
	return CVTrue;
}

enum {
	CVOrderedAscending = -1,
	CVOrderedSame,
	CVOrderedDescending
};
typedef CVInteger CVComparisonResult;

#if !defined(CV_ARRAY_COMPARE_FUNCTION)
#define CV_ARRAY_COMPARE_FUNCTION(leftValue, rightValue) (((leftValue)>(rightValue))?CVOrderedDescending:(((leftValue)<(rightValue))?CVOrderedAscending:CVOrderedSame))
#endif

CV_INLINE CVUInteger CVIntegerArrayPartition(CVIntegerArray* theArray, CVUInteger f, CVUInteger l, CVInteger pivot, CVComparisonResult comparisonResult){
	CVUInteger i = f-1, j = l+1;
	CVInteger* arrayData = theArray->data;
	while(CVTrue){
		do{
			j--;
		}while(CV_ARRAY_COMPARE_FUNCTION(pivot,arrayData[j])==comparisonResult);
		
		do{
			i++;
		}while(CV_ARRAY_COMPARE_FUNCTION(arrayData[i],pivot)==comparisonResult);
		
		if(i<j){
			CVInteger tmp = arrayData[i];
			arrayData[i] = arrayData[j];
			arrayData[j] = tmp;
		}else{
			return j;
		}
	}
}

CV_INLINE void CVIntegerArrayQuickSortImplementation(CVIntegerArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	while(f < l){
		CVUInteger m = CVIntegerArrayPartition(theArray, f, l, theArray->data[f],comparisonResult);
		CVIntegerArrayQuickSortImplementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVIntegerArrayInsertSortImplementation(CVIntegerArray* theArray, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVUInteger i,count = theArray->count;
	CVInteger* arrayData = theArray->data;
	for(i = 1; i < count; i++){
		CVInteger value = arrayData[i];
		CVUInteger j = i;
		while(j > 0 && CV_ARRAY_COMPARE_FUNCTION(value,arrayData[j-1])==comparisonResult){
			arrayData[j] = arrayData[j-1];
			j--;
		}
		theArray->data[j] = value;
	}
}

CV_INLINE void CVIntegerArrayInsertSortImplementation2(CVIntegerArray* theArray){
    //  Local Declaration
    CVInteger temp, current, walker;
	CVUInteger count = theArray->count;
	CVInteger* arrayData = theArray->data;
	
    //  Statement
    for(current = 1; current < count; current++)
    {
        temp = arrayData[current];
        walker = current - 1;
        while(walker >= 0 && temp > arrayData[walker])
        {
            arrayData[walker + 1] = arrayData[walker];
            walker--;
        }
        arrayData[walker + 1] = temp;
    }
	
    return;
}

CV_STATIC_INLINE void CVIntegerArrayQuickSort3Implementation(CVIntegerArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVInteger* arrayData = theArray->data;
	while(f + 16 < l){
		CVInteger v1 = arrayData[f], v2 = arrayData[l], v3 = arrayData[(f+l)/2];
        CVInteger median;
		if(CV_ARRAY_COMPARE_FUNCTION(v1,v2)==comparisonResult){
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v1)==comparisonResult){
				median = v1;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v2,v3)==comparisonResult){
					median=v2;
				}else{
					median=v3;
				}
			}
		}else{
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v2)==comparisonResult){
				median = v2;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v1,v3)==comparisonResult){
					median=v1;
				}else{
					median=v3;
				}
			}
		}
		CVInteger m = CVIntegerArrayPartition(theArray, f, l, median,comparisonResult);
		CVIntegerArrayQuickSort3Implementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVIntegerArrayQuickSort3(CVIntegerArray* theArray){
	if(theArray->count==0)
		return;
	CVIntegerArrayQuickSort3Implementation(theArray, 0, theArray->count-1,CVOrderedAscending);
	CVIntegerArrayInsertSortImplementation(theArray,CVOrderedAscending);
}











CV_INLINE CVUInteger CVFloatArrayPartition(CVFloatArray* theArray, CVUInteger f, CVUInteger l, CVFloat pivot, CVComparisonResult comparisonResult){
	CVUInteger i = f-1, j = l+1;
	CVFloat* arrayData = theArray->data;
	while(CVTrue){
		do{
			j--;
		}while(CV_ARRAY_COMPARE_FUNCTION(pivot,arrayData[j])==comparisonResult);
		
		do{
			i++;
		}while(CV_ARRAY_COMPARE_FUNCTION(arrayData[i],pivot)==comparisonResult);
		
		if(i<j){
			CVFloat tmp = arrayData[i];
			arrayData[i] = arrayData[j];
			arrayData[j] = tmp;
		}else{
			return j;
		}
	}
}

CV_INLINE void CVFloatArrayQuickSortImplementation(CVFloatArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	while(f < l){
		CVUInteger m = CVFloatArrayPartition(theArray, f, l, theArray->data[f],comparisonResult);
		CVFloatArrayQuickSortImplementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVFloatArrayInsertSortImplementation(CVFloatArray* theArray, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVUInteger i,count = theArray->count;
	CVFloat* arrayData = theArray->data;
	for(i = 1; i < count; i++){
		CVFloat value = arrayData[i];
		CVUInteger j = i;
		while(j > 0 && CV_ARRAY_COMPARE_FUNCTION(value,arrayData[j-1])==comparisonResult){
			arrayData[j] = arrayData[j-1];
			j--;
		}
		theArray->data[j] = value;
	}
}

CV_INLINE void CVFloatArrayInsertSortImplementation2(CVFloatArray* theArray){
	//  Local Declaration
	CVFloat temp;
	CVInteger current, walker;
	CVUInteger count = theArray->count;
	CVFloat* arrayData = theArray->data;
	
	//  Statement
	for(current = 1; current < count; current++)
	{
		temp = arrayData[current];
		walker = current - 1;
		while(walker >= 0 && temp > arrayData[walker])
		{
			arrayData[walker + 1] = arrayData[walker];
			walker--;
		}
		arrayData[walker + 1] = temp;
	}
	
	return;
}

CV_STATIC_INLINE void CVFloatArrayQuickSort3Implementation(CVFloatArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVFloat* arrayData = theArray->data;
	while(f + 16 < l){
		CVFloat v1 = arrayData[f], v2 = arrayData[l], v3 = arrayData[(f+l)/2];
		CVFloat median;
		if(CV_ARRAY_COMPARE_FUNCTION(v1,v2)==comparisonResult){
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v1)==comparisonResult){
				median = v1;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v2,v3)==comparisonResult){
					median=v2;
				}else{
					median=v3;
				}
			}
		}else{
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v2)==comparisonResult){
				median = v2;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v1,v3)==comparisonResult){
					median=v1;
				}else{
					median=v3;
				}
			}
		}
		CVFloat m = CVFloatArrayPartition(theArray, f, l, median,comparisonResult);
		CVFloatArrayQuickSort3Implementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVFloatArrayQuickSort3(CVFloatArray* theArray, CVComparisonResult order){
	if(theArray->count==0)
		return;
	CVFloatArrayQuickSort3Implementation(theArray, 0, theArray->count-1,order);
	CVFloatArrayInsertSortImplementation(theArray,order);
}











CV_INLINE CVUInteger CVDoubleArrayPartition(CVDoubleArray* theArray, CVUInteger f, CVUInteger l, CVDouble pivot, CVComparisonResult comparisonResult){
	CVUInteger i = f-1, j = l+1;
	CVDouble* arrayData = theArray->data;
	while(CVTrue){
		do{
			j--;
		}while(CV_ARRAY_COMPARE_FUNCTION(pivot,arrayData[j])==comparisonResult);

		do{
			i++;
		}while(CV_ARRAY_COMPARE_FUNCTION(arrayData[i],pivot)==comparisonResult);

		if(i<j){
			CVDouble tmp = arrayData[i];
			arrayData[i] = arrayData[j];
			arrayData[j] = tmp;
		}else{
			return j;
		}
	}
}

CV_INLINE void CVDoubleArrayQuickSortImplementation(CVDoubleArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	while(f < l){
		CVUInteger m = CVDoubleArrayPartition(theArray, f, l, theArray->data[f],comparisonResult);
		CVDoubleArrayQuickSortImplementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVDoubleArrayInsertSortImplementation(CVDoubleArray* theArray, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVUInteger i,count = theArray->count;
	CVDouble* arrayData = theArray->data;
	for(i = 1; i < count; i++){
		CVDouble value = arrayData[i];
		CVUInteger j = i;
		while(j > 0 && CV_ARRAY_COMPARE_FUNCTION(value,arrayData[j-1])==comparisonResult){
			arrayData[j] = arrayData[j-1];
			j--;
		}
		theArray->data[j] = value;
	}
}

CV_INLINE void CVDoubleArrayInsertSortImplementation2(CVDoubleArray* theArray){
	//  Local Declaration
	CVDouble temp;
	CVInteger current, walker;
	CVUInteger count = theArray->count;
	CVDouble* arrayData = theArray->data;

	//  Statement
	for(current = 1; current < count; current++)
	{
		temp = arrayData[current];
		walker = current - 1;
		while(walker >= 0 && temp > arrayData[walker])
		{
			arrayData[walker + 1] = arrayData[walker];
			walker--;
		}
		arrayData[walker + 1] = temp;
	}

	return;
}

CV_STATIC_INLINE void CVDoubleArrayQuickSort3Implementation(CVDoubleArray* theArray, CVUInteger f, CVUInteger l, CVComparisonResult comparisonResult){
	if(theArray->count==0)
		return;
	CVDouble* arrayData = theArray->data;
	while(f + 16 < l){
		CVDouble v1 = arrayData[f], v2 = arrayData[l], v3 = arrayData[(f+l)/2];
		CVDouble median;
		if(CV_ARRAY_COMPARE_FUNCTION(v1,v2)==comparisonResult){
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v1)==comparisonResult){
				median = v1;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v2,v3)==comparisonResult){
					median=v2;
				}else{
					median=v3;
				}
			}
		}else{
			if(CV_ARRAY_COMPARE_FUNCTION(v3,v2)==comparisonResult){
				median = v2;
			}else{
				if(CV_ARRAY_COMPARE_FUNCTION(v1,v3)==comparisonResult){
					median=v1;
				}else{
					median=v3;
				}
			}
		}
		CVDouble m = CVDoubleArrayPartition(theArray, f, l, median,comparisonResult);
		CVDoubleArrayQuickSort3Implementation(theArray, f, m,comparisonResult);
		f = m+1;
	}
}


CV_INLINE void CVDoubleArrayQuickSort3(CVDoubleArray* theArray, CVComparisonResult order){
	if(theArray->count==0)
		return;
	CVDoubleArrayQuickSort3Implementation(theArray, 0, theArray->count-1,order);
	CVDoubleArrayInsertSortImplementation(theArray,order);
}
















#endif

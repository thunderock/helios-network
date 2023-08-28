/**
 * @Author: Ashutosh Tiwari
 * @Date:   2023-08-28 12:17:13
 * @Last Modified by:   Ashutosh Tiwari
 * @Last Modified time: 2023-08-28 12:47:26
 */
//
//  CVNetwork.h
//  
//
//  Created by FIlipi Nascimento Silva on 26/09/12.
//
//

#ifndef CVNetwork_CVNetwork_h
#define CVNetwork_CVNetwork_h

#include "CVCommons.h"
#include "CVBasicArrays.h"

typedef enum{
	CVStringPropertyType = 0,
	CVNumberPropertyType = 1,
	CVVector2DPropertyType = 2,
	CVVector3DPropertyType = 3,
	CVUnknownPropertyType = 255,
} CVPropertyType;

typedef struct{
	CVSize* vertexNumOfEdges;
	CVSize* vertexCapacityOfEdges;
	CVIndex** vertexEdgesLists;
	CVIndex** vertexEdgesIndices;
	
	CVIndex* vertexNumOfInEdges;
	CVIndex* vertexCapacityOfInEdges;
	CVIndex** vertexInEdgesLists;
	CVIndex** vertexInEdgesIndices;
	
	CVIndex* edgeFromList;
	CVIndex* edgeToList;
	
	CVFloat* edgesWeights;
	CVFloat* verticesWeights;
	CVBool* verticesEnabled;
	
	CVSize vertexCapacity;
	CVSize edgesCapacity;
	
	CVSize edgesCount;
	CVSize verticesCount;
	
	CVBool editable;
	CVBool directed;
	CVBool edgeWeighted;
	CVBool vertexWeighted;
	
	CVString* vertexNames;
    
	CVString* propertiesNames;
	void** propertiesData;
	CVPropertyType* propertiesTypes;
	CVSize propertiesCount;
	
} CVNetwork;

typedef CVNetwork* CVNetworkRef;

typedef struct{
	CVIndex vertex;
	CVIndex level;
	CVFloat weight;
	CVIndex branchIndex;
} CVNetworkAgent;

typedef struct{
	CVNetworkAgent* data;
	CVSize count;
	CVSize _capacity;
	CVBitArray visitedNodes;
} CVAgentPath;


typedef struct{
	CVUInteger from;
	CVUInteger to;
} CVEdge;



CVBool EMSCRIPTEN_KEEPALIVE CVNetworkAddNewEdges(CVNetworkRef network, CVIndex* fromIndices, CVIndex* toIndices, CVFloat* weights, CVSize count);
void EMSCRIPTEN_KEEPALIVE CVNetworkDestroy(CVNetworkRef network);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromXNETFile(FILE* networkFile);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetwork(CVSize verticesCount, CVBool edgeWeighted, CVBool directed);
void EMSCRIPTEN_KEEPALIVE CVNetworkWriteToFile(CVNetworkRef theNetwork, FILE* networkFile);
void EMSCRIPTEN_KEEPALIVE CVNetworkWriteToGMLFile(CVNetworkRef theNetwork, FILE* networkFile);
void EMSCRIPTEN_KEEPALIVE CVNetworkWriteToEdgesFile(CVNetworkRef theNetwork, FILE* networkFile);
void EMSCRIPTEN_KEEPALIVE CVNetworkWriteToPajekFile(CVNetworkRef theNetwork, FILE* networkFile);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkWithNetwork(CVNetworkRef originalNetwork, CVBool edgeWeighted, CVBool directed);

// CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewRegularNetwork(CVSize* gridSize, CVSize dimension, CVFloat connectionRadius, CVBool toroidal);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewRegular2DNetwork(CVSize rows, CVSize columns, CVBool toroidal);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewRandomNetwork(CVSize verticesCount, CVFloat degree);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewFastRandomNetwork(CVSize verticesCount, CVFloat degree);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewWaxmanNetwork(CVSize verticesCount,CVFloat alpha, CVFloat beta, CVSize dimension);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewRandomGeographicNetwork(CVSize verticesCount, CVFloat maximumDistance, CVSize dimension);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewRandomProbabilisticGeographicNetwork(CVSize verticesCount,CVFloat connectionProbability, CVFloat maximumDistance, CVSize dimension);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkHomogeneusModel(CVSize degree, CVSize verticesCount);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRandomRemovingEdgeList(CVIndex* fromList,CVIndex* toList, CVSize edgesCount, CVSize verticesCount, CVBool directed, CVFloat rewireProbability);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRandomRemoving(const CVNetworkRef originalNetwork, CVFloat removingProbability);


CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRectangleRemovingEdgeList(CVIndex* fromList, CVIndex* toList, CVSize edgesCount, CVSize verticesCount, CVBool directed, CVFloat* positions, CVFloat minRectangleSize, CVFloat maxRectangleSize,CVSize rectangleCount,CVFloat removeProbability);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRectangleRemoving(const CVNetworkRef originalNetwork,CVFloat minRectangleSize, CVFloat maxRectangleSize,CVSize rectangleCount,CVFloat removeProbability);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRandomRewiring(const CVNetworkRef originalNetwork, CVFloat rewiringProbability);
CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromRandomRewiringEdgeList(CVIndex* fromList,CVIndex* toList, CVSize edgesCount, CVSize verticesCount, CVBool directed, CVFloat rewireProbability);
// CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewWattsStrogatzNetwork(CVSize approximateNumberOfVertices, CVSize dimension, CVFloat connectionRadius, CVBool toroidal, CVFloat rewiringProbability);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewBarabasiAlbertNetwork(CVSize initialSize, CVSize degreeGrowth, CVSize iterations);

CVNetworkRef* EMSCRIPTEN_KEEPALIVE CVNewBarabasiAlbertNetworkOverTime(CVSize initialSize, CVSize degreeGrowth, CVSize* iterationsArray, CVSize iterationsCount);

void EMSCRIPTEN_KEEPALIVE CVNetworkAppendProperty(CVNetworkRef theNetwork, CVString name, CVPropertyType type, void* data);

void* EMSCRIPTEN_KEEPALIVE CVNetworkPropertyWithName(const CVNetworkRef network, CVString name, CVPropertyType* outType);

void EMSCRIPTEN_KEEPALIVE CVNetworkGetDegree(const CVNetworkRef network, CVIntegerArray* degrees);

CVBool EMSCRIPTEN_KEEPALIVE CVNetworkCouldBeIsomorphic(const CVNetworkRef aNetwork,const CVNetworkRef bNetwork);

CVFloat EMSCRIPTEN_KEEPALIVE CVNetworkClusteringCoefficient(const CVNetworkRef aNetwork, CVIndex nodeIndex);

//private

CVNetworkRef CV_NewAllocationNetwork(CVSize verticesCount);


//Inline
CV_INLINE void CVNetworkGrowEdgesCount(CVNetworkRef network,CVSize growSize){
	network->edgesCount+=growSize;
	if(CVUnlikely(network->edgesCapacity < network->edgesCount)){
		network->edgesCapacity = 2 * network->edgesCount;
		network->edgeFromList = (unsigned int *)realloc(network->edgeFromList, sizeof(CVIndex)*network->edgesCapacity);
		network->edgeToList = (unsigned int *)realloc(network->edgeToList, sizeof(CVIndex)*network->edgesCapacity);
		if(network->edgeWeighted)
			network->edgesWeights = (float *)realloc(network->edgesWeights, sizeof(CVFloat)*network->edgesCapacity);
	}
}
CV_INLINE void CVNetworkGrowEdgesCapacity(CVNetworkRef network,CVSize capacityIncrease){
	CVSize newCapacity = network->edgesCount+capacityIncrease;
	if(CVUnlikely(network->edgesCapacity < newCapacity)){
		network->edgesCapacity = 2 * newCapacity;
		network->edgeFromList = (unsigned int *)realloc(network->edgeFromList, sizeof(CVIndex)*network->edgesCapacity);
		network->edgeToList = (unsigned int *)realloc(network->edgeToList, sizeof(CVIndex)*network->edgesCapacity);
		if(network->edgeWeighted)
			network->edgesWeights = (float *)realloc(network->edgesWeights, sizeof(CVFloat)*network->edgesCapacity);
	}
}
CV_INLINE void CVNetworkGrowVertexSetEdgeForVertex(CVNetworkRef network,CVIndex edgeIndex,CVIndex vertexIndex,CVIndex toVertexIndex){
	network->vertexNumOfEdges[vertexIndex]++;
	if(CVUnlikely(network->vertexCapacityOfEdges[vertexIndex] < network->vertexNumOfEdges[vertexIndex])){
		network->vertexCapacityOfEdges[vertexIndex]=CVCapacityGrow(network->vertexNumOfEdges[vertexIndex]);
		network->vertexEdgesLists[vertexIndex] = (CVIndex*) realloc(network->vertexEdgesLists[vertexIndex], sizeof(CVIndex)*network->vertexCapacityOfEdges[vertexIndex]);
		network->vertexEdgesIndices[vertexIndex] = (CVIndex*) realloc(network->vertexEdgesIndices[vertexIndex], sizeof(CVIndex)*network->vertexCapacityOfEdges[vertexIndex]);
	}
	network->vertexEdgesLists[vertexIndex][network->vertexNumOfEdges[vertexIndex]-1]=toVertexIndex;
	network->vertexEdgesIndices[vertexIndex][network->vertexNumOfEdges[vertexIndex]-1]=edgeIndex;
}

CV_INLINE void CVNetworkGrowVertexSetInEdgeForVertex(CVNetworkRef network,CVIndex edgeIndex,CVIndex vertexIndex,CVIndex toVertexIndex){
	network->vertexNumOfInEdges[vertexIndex]++;
	if(CVUnlikely(network->vertexCapacityOfInEdges[vertexIndex] < network->vertexNumOfInEdges[vertexIndex])){
		network->vertexCapacityOfInEdges[vertexIndex]=CVCapacityGrow(network->vertexNumOfInEdges[vertexIndex]);
		network->vertexInEdgesLists[vertexIndex] = (CVIndex*) realloc(network->vertexInEdgesLists[vertexIndex], sizeof(CVIndex)*network->vertexCapacityOfInEdges[vertexIndex]);
		network->vertexInEdgesIndices[vertexIndex] = (CVIndex*) realloc(network->vertexInEdgesIndices[vertexIndex], sizeof(CVIndex)*network->vertexCapacityOfInEdges[vertexIndex]);
	}
	network->vertexInEdgesLists[vertexIndex][network->vertexNumOfInEdges[vertexIndex]-1]=toVertexIndex;
	network->vertexInEdgesIndices[vertexIndex][network->vertexNumOfInEdges[vertexIndex]-1]=edgeIndex;
}



CV_INLINE CVSize CVNetworkCommonNeighborhood(const CVNetworkRef network,CVIndex vertex1,CVIndex vertex2){
	CVIndex v1n;
	CVSize commonNeighCount = 0;
	CVIndex* neigh1 = network->vertexEdgesLists[vertex1];
	CVIndex* neigh2 = network->vertexEdgesLists[vertex2];
	CVSize neigh1Count = network->vertexNumOfEdges[vertex1];
	CVSize neigh2Count = network->vertexNumOfEdges[vertex2];
	for (v1n=0; v1n<neigh1Count; v1n++) {
		CVIndex v2n;
		CVIndex neigh1Vertex = neigh1[v1n];
		for (v2n=0; v2n<neigh2Count; v2n++) {
			if(neigh1Vertex==neigh2[v2n]){
				commonNeighCount++;
			}
		}
	}
	return commonNeighCount;
}


CV_INLINE CVBool CVNetworkAreAdjacent(const CVNetworkRef network,CVIndex vertex1, CVIndex vertex2){
	CVIndex v1n;
	CVIndex* neigh1 = network->vertexEdgesLists[vertex1];
	CVSize neigh1Count = network->vertexNumOfEdges[vertex1];
	for (v1n=0; v1n<neigh1Count; v1n++) {
		CVIndex neigh1Vertex = neigh1[v1n];
		if(CVUnlikely(neigh1Vertex==vertex2)){
			return CVTrue;
		}
	}
	return CVFalse;
}

CVBool EMSCRIPTEN_KEEPALIVE CVNetworkAddNewEdge(CVNetworkRef network, CVIndex fromIndex, CVIndex toIndex, CVFloat weight);
CVBool EMSCRIPTEN_KEEPALIVE CVNetworkAddNewEdgeAndIntegrateWeight(CVNetworkRef network, CVIndex fromIndex, CVIndex toIndex, CVFloat weight);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkRemovingChains(const CVNetworkRef originalNetwork);

CVSize EMSCRIPTEN_KEEPALIVE CVNetworkNumberOfConnectedComponents(const CVNetworkRef theNetwork, CVGenericArray* connectedComponents);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromLargestComponent(const CVNetworkRef theNetwork);

CVSize EMSCRIPTEN_KEEPALIVE CVNetworkLargestComponentSize(const CVNetworkRef theNetwork, CVSize* connectedComponentsCount);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewSubNetworkFromNetwork(const CVNetworkRef theNetwork, const CVUIntegerArray verticesIndices);

CVNetworkRef EMSCRIPTEN_KEEPALIVE CVNewNetworkFromAdjacencyMatrix(const CVBitArray adjacencyMatrix,CVSize verticesCount, CVBool directed);
CVBitArray EMSCRIPTEN_KEEPALIVE CVNewAdjacencyMatrixFromNetwork(const CVNetworkRef theNetwork);




// Access to the network
CVSize EMSCRIPTEN_KEEPALIVE CVNetworkVerticesCount(const CVNetworkRef theNetwork);
CVSize EMSCRIPTEN_KEEPALIVE CVNetworkEdgesCount(const CVNetworkRef theNetwork);

CVSize EMSCRIPTEN_KEEPALIVE CVNetworkVertexDegree(const CVNetworkRef theNetwork, CVIndex vertexIndex);
CVSize EMSCRIPTEN_KEEPALIVE CVNetworkVertexInDegree(const CVNetworkRef theNetwork, CVIndex vertexIndex);

CVSize EMSCRIPTEN_KEEPALIVE CVNetworkVertexNumberOfEdges(const CVNetworkRef theNetwork, CVIndex vertexIndex);
CVSize EMSCRIPTEN_KEEPALIVE CVNetworkVertexNumberOfInEdges(const CVNetworkRef theNetwork, CVIndex vertexIndex);

CVIndex EMSCRIPTEN_KEEPALIVE CVNetworkVertexEdgeAtIndex(const CVNetworkRef theNetwork, CVIndex vertexIndex, CVIndex vertexEdgeIndex);
CVIndex EMSCRIPTEN_KEEPALIVE CVNetworkVertexInEdgeAtIndex(const CVNetworkRef theNetwork, CVIndex vertexIndex, CVIndex vertexedgeIndex);



#endif


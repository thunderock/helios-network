import HeliosNetwork from '../Compiled/test.mjs';
const heliosNet = await HeliosNetwork();
// console.log(wasm_module._malloc)
// console.log(wasm_module._randomNetwork(12));
window.heliosNet = heliosNet;
let N = 10000000;
let network = heliosNet._CVNewNetwork(N,0,0);
let i = 0;
// Async loop to add more edges 
const addEdge = () => {
	console.log("Testing network with k="+2.0*heliosNet._CVNetworkEdgesCount(network)/heliosNet._CVNetworkVerticesCount(network));
	// Also add this text to body
	document.body.innerHTML = `<p>Testing network with k=${2.0*heliosNet._CVNetworkEdgesCount(network)/heliosNet._CVNetworkVerticesCount(network)}</p>`;

	for (let j = 0; j < 100000; j++){
		heliosNet._CVNetworkAddNewEdge(network, Math.floor(Math.random() * N), Math.floor(Math.random() * N));
	}
	i++;
	if (i < 1000) {
		setTimeout(addEdge, 15);
	}
};

addEdge();
console.log(network);



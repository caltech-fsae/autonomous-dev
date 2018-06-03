// instantiate a loader
var loader = new THREE.PCDLoader();

// load a resource
loader.load(
	// resource URL
	'pointcloud.pcd',
	// called when the resource is loaded
	function (mesh) {
		scene.add(mesh);
	},
	// called when loading is in progresses
	function (xhr) {
		console.log( ( xhr.loaded / xhr.total * 100 ) + '% loaded' );
	},
	// called when loading has errors
	function (error) {
		console.log( 'An error happened' );
	}
);

console.log('The "EVENT_TYPE_ORIENTATION_CHANGED" event type:', $.streamingModule.EVENT_TYPE_ORIENTATION_CHANGED);
console.log('The "EVENT_TYPE_STREAM_STARTED" event type:', $.streamingModule.EVENT_TYPE_STREAM_STARTED);
console.log('The "EVENT_TYPE_STREAM_STOPPED" event type:', $.streamingModule.EVENT_TYPE_STREAM_STOPPED);
console.log('The "EVENT_TYPE_ERROR_CAMERA" event type:', $.streamingModule.EVENT_TYPE_ERROR_CAMERA);
console.log('The "EVENT_TYPE_ERROR_SERVER" event type:', $.streamingModule.EVENT_TYPE_ERROR_SERVER);
console.log('The "EVENT_TYPE_ERROR_NETWORK" event type:', $.streamingModule.EVENT_TYPE_ERROR_NETWORK);

console.log('torchIsOn:', $.streamingModule.torchIsOn);
console.log('isStarted:', $.streamingModule.isStarted);
console.log('activeCamera:', $.streamingModule.activeCamera);

$.streamingModule.setURL('http://www.netris.ru', false);
$.streamingModule.setURLAndStart('http://www.netris.ru', false);
$.streamingModule.start();
$.streamingModule.stop();
console.log('Cameras list:', $.streamingModule.getCameras());
$.streamingModule.useCamera({});
$.streamingModule.useTorch(true);

function streamingModule_orientationChangedHandler(event) {
	console.log('An "orientation_changed" event is fired');	
}

function streamingModule_streamStartedHandler(event) {
	console.log('An "stream_started" event is fired');	
}

function streamingModule_streamStoppedHandler(event) {
	console.log('An "stream_stopped" event is fired');	
}

function streamingModule_errorCameraHandler(event) {
	console.log('An "error_camera" event is fired');	
}

function streamingModule_errorServerHandler(event) {
	console.log('An "error_server" event is fired');	
}

function streamingModule_errorNetworkHandler(event) {
	console.log('An "error_network" event is fired');
}

function torchSwitcher_clickHandler(event) {
	if ($.streamingModule.torchIsOn) {
		$.torchSwitcher.title = L('torch_switcher_is_off', ' ');		
	} else {		
		$.torchSwitcher.title = L('torch_switcher_is_on', ' ');
	}
}

function startButton_clickHandler(event) {
	if ($.streamingModule.isStarted) {
		$.startButton.title = L('start_button_pause', ' ');		
	} else {		
		$.startButton.title = L('start_button_start', ' ');
	}
}

function cameraSwitcher_clickHandler(event) {
	if (!!$.streamingModule.activeCamera && $.streamingModule.activeCameraIsFront) {
		$.cameraSwitcher.title = L('camera_switcher_use_back', ' ');
	} else {		
		$.cameraSwitcher.title = L('camera_switcher_use_front', ' ');
	}
}

$.container.open();
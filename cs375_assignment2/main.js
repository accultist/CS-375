function init() {
    // code for WebGL2 context
    var canvas = document.getElementById("webgl-canvas");
    gl = canvas.getContext("webgl2");

    // clear colors (r,g,b,alpha)
    gl.clearColor(0.0,0.0,0.0,1.0);

    // create a JavaScript cone object
    // default is cone with 20 sides, but can be increased/decreased
    cone = new Cone(gl, 20);

    // call render function
    render();
}

//function render() {
this.render = function () {
    // clear the canvas
    gl.clear(gl.COLOR_BUFFER_BIT);

    // call render function for the cone to plot sides
    cone.render();
}

// call function when page is completely loaded
window.onload = init;

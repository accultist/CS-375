var time = 0.0;

function init() {
    var canvas = document.getElementById("webgl-canvas");
    gl = canvas.getContext("webgl2");
    gl.clearColor(135, 0.7, 0.5, 2);

    cube = new Cube(gl);

    p = perspective();
    cube.P = mat4();
    cube.MV = mat4();

    render();
}

function render(curr) {
    gl.clear(gl.COLOR_BUFFER_BIT);
    time += 3.0;                // speed of travel

    // slide across screen
    cube.MV = rotateZ(time);

    cube.MV = rotateY(time);
    cube.render();
    requestAnimationFrame(render);
}
window.onload = init;
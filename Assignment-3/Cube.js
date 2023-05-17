//---------------------------------------------------------------------------
//
//  --- Cube.js ---
//
//    A simple, encapsulated Cube object
//
//  All of the parameters of this function are optional, although, it's
//    possible that the WebGL context (i.e., the "gl" parameter) may not
//    be global, so passing that is a good idea.
//
//  Further, the vertex- and fragment-shader ids assume that the HTML "id" 
//    attributes for the vertex and fragment shaders are named
//
//      Vertex shader:   "Cube-vertex-shader"
//      Fragment shader: "Cube-fragment-shader"
//

function Cube( gl, vertexShaderId, fragmentShaderId ) {
    // Initialize the shader pipeline for this object using either shader ids
    //   declared in the application's HTML header, or use the default names.
    //
    const vertShdr = vertexShaderId || "Cube-vertex-shader";
    const fragShdr = fragmentShaderId || "Cube-fragment-shader";

    const shaderProgram = initShaders(gl, vertShdr, fragShdr);

    if (shaderProgram < 0) {
        alert("Error: Cone shader pipeline failed to compile.\n\n" +
            "\tvertex shader id:  \t" + vertShdr + "\n" +
            "\tfragment shader id:\t" + fragShdr + "\n");
        return;
    }

    // Set up our data:
    //   - positions contains our vertex positions
    //   - indices contains how to organize the vertices
    //       into primitives
    //
    let positions = [
        // Front face
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,

        // Back face
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,

        // Top face
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,

        // Bottom face
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, 0.5,

        // Right face
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5,

        // Left face
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
    ];

    let indices = [ 0, 1, 2, 0, 2, 3,           // front
                    4, 5, 6, 4, 6, 7,           // back
                    8, 9, 10, 8, 10, 11,        // top
                    12, 13, 14, 12, 14, 15,     // bottom
                    16, 17, 18, 16, 18, 19,     // right
                    20, 21, 22, 20, 22, 23,];   // left

    // Create our vertex buffer and initialize it with our positions data
    //

    let aPosition = new Attribute(gl, shaderProgram, positions,
        "aPosition", 3, gl.FLOAT);

    indices = new Indices(gl, indices);

    let MV = new Uniform(gl, shaderProgram, "MV");
    let P = new Uniform(gl, shaderProgram, "P");

    this.render = () => {
        // Enable our shader program
        gl.useProgram(shaderProgram);

        // Activate our vertex, enabling the vertex attribute we want data
        //   to be read from, and tell WebGL how to decode that data.
        //
        aPosition.enable();

        // Likewise enable our index buffer so we can use it for rendering
        //
        indices.enable();

        MV.update(this.MV);
        P.update(this.P);

        gl.drawElements(gl.TRIANGLES, indices.count, indices.type, 0);

        // Finally, reset our rendering state so that other objects we
        //   render don't try to use the Cone's data
        //
        aPosition.disable();
        indices.disable();
    };
};
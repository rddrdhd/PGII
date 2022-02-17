#version 460 core // kdyz nepujde, zkusit 450

// vertex attributes
layout ( location = 0 ) in vec4 in_position_ms;

// uniform variables
uniform mat4 P; // Model View Projection

void main( void ) // plati pro kazdy vertex te nasi posloupnousti.
{
	// Pohne se mi kamera, menim P
	gl_Position = P * in_position_ms; // model-space -> clip-space
}

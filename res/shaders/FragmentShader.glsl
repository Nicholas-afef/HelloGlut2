#version 330 core
out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 normal;
in vec3 fragPosition;

uniform vec3 objColor = vec3(1.0, .5, .31);
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 lightPosition = vec3(8.0, 8.0, 8.0);

uniform sampler2D u_Texture;

void main(){
    //calculate ambient light
    float ambientStrength = .2;
    vec3 ambient = ambientStrength * lightColor;

    //calculate diffusion light
    vec3 norm = normalize(normal);
    vec3 lightdir = normalize(lightPosition - fragPosition);
    float diffScalar = max(dot(norm,lightdir),0.0);
    vec3 diffuse = diffScalar * lightColor;

    vec3 result = (ambient + diffuse) * objColor;

    FragColor = texture(u_Texture, v_TexCoord) * vec4(result, 1.0);
};
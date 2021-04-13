#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D u_Texture;
    float shine;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_TexCoord;
in vec3 normal;
in vec3 fragPosition;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main(){
    // ambient light
    vec3 ambient = light.ambient * texture(material.u_Texture, v_TexCoord).rgb;

    //calculate diffusion light
    
    vec3 norm = normalize(normal);
    vec3 lightdir = normalize(light.position - fragPosition);
    float diffScalar = max(dot(normal,lightdir),0.0);
    vec3 diffuse = light.diffuse * diffScalar * texture(material.u_Texture, v_TexCoord).rgb;

    vec3 viewDir = normalize(viewPosition - fragPosition); //V
    vec3 reflectDir = reflect(lightdir, -normal); //Reflect about l norm
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine); //  (r dot v) pow shininess
    vec3 specular = light.specular * spec * texture(material.u_Texture, v_TexCoord).rgb; //k

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
};
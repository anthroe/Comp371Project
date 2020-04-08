#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 UV;

uniform sampler2D textureSampler; 

uniform vec3 lightDirection;
uniform vec3 viewPos;

uniform vec3 objectColor;

out vec4 FragColor;

void main()
{
    vec3 color = texture(textureSampler, UV).rgb;
    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.992f, 0.984f, 0.827f);

    // ambient
    vec3 ambient = 0.3 * color;

    // diffuse
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 8.0);
    vec3 specular = spec * lightColor; 

    vec3 lighting = (ambient + diffuse + specular)*color;

    FragColor = vec4(lighting, 1.0);
}
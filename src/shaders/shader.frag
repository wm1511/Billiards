#version 440
out vec4 FragColor;
in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;

struct Material
{
    vec3 diffuse;
    vec3 ao;
    float metallic;
    float roughness;

    sampler2D diffuseMap;
    sampler2D normalMap;
    sampler2D roughnessMap;
    sampler2D metallicMap;
    sampler2D aoMap;
    
    bool hasDiffuseMap;
    bool hasRoughnessMap;
    bool hasNormalMap;
    bool hasMetallicMap;
    bool hasAoMap;
};

struct Light
{
    vec3 position;
    vec3 color;
};

uniform samplerCube depthMap;
uniform int lightCount;
uniform Light lights[4];
uniform vec3 cameraPos;
uniform Material material;
uniform float far_plane;

const float PI = 3.14159265359;

vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos, vec3 lightPos)
{
    vec3 fragToLight = Position - lightPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(cameraPos - Position);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;

        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    return shadow;
}

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(material.normalMap, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(Position);
    vec3 Q2  = dFdy(Position);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
    vec3 diffuse = pow(material.diffuse, vec3(2.2));
    float ao = material.ao.r;
    float roughness = material.roughness;
    float metallic = material.metallic;
    vec3 N = normalize(Normal);

    if (material.hasDiffuseMap)
        diffuse = pow(texture(material.diffuseMap, TexCoords).rgb, vec3(2.2));

    if (material.hasRoughnessMap)
        roughness = texture(material.roughnessMap, TexCoords).r;
    
    if (material.hasAoMap)
        ao = texture(material.aoMap, TexCoords).r;

    if (material.hasMetallicMap)
        metallic = texture(material.metallicMap, TexCoords).r;

    if (material.hasNormalMap)
        N = getNormalFromMap();

    vec3 V = normalize(cameraPos - Position);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, diffuse, metallic);

    vec3 Lo = vec3(0.0);
    for(int i = 0; i < lightCount; ++i) 
    {
        vec3 L = normalize(lights[i].position - Position);
        vec3 H = normalize(V + L);
        float distance = length(lights[i].position - Position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lights[i].color * attenuation;

        float NDF = DistributionGGX(N, H, roughness);   
        float G = GeometrySmith(N, V, L, roughness);      
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
           
        vec3 numerator = NDF * G * F; 
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  

        float NdotL = max(dot(N, L), 0.0);        

        float shadow = ShadowCalculation(Position, lights[i].position);

        Lo += (1.0 - shadow) * (kD * diffuse / PI + specular) * radiance * NdotL;
    }   
    
    vec3 ambient = diffuse * vec3(0.03) * ao;
    
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}
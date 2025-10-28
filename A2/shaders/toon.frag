OF_GLSL_SHADER_HEADER

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform mat4 colorLUT;
uniform vec3 thresholds;
uniform vec3 objectColor;

out vec4 fragColor;

void main()
{
    vec3 N = normalize(Normal); // interpolation might give something that isn't unit length
    vec3 L = normalize(lightPos - FragPos);
    float diffuse = max(dot(N, L), 0.0);

    if (diffuse > thresholds.x) {
        fragColor = colorLUT[0];
    } else if (diffuse > thresholds.y) {
        fragColor = colorLUT[1];
    } else if (diffuse > thresholds.z) {
        fragColor = colorLUT[2];
    } else {
        fragColor = colorLUT[3];
    }
}
uniform sampler2D texture;
uniform float radius;
uniform vec2 resolution;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float sigma = radius;
    float twoSigmaSq = 2.0 * sigma * sigma;
    float weightSum = 0.0;

    for (int i = -10; i <= 10; ++i) {
        float x = float(i);
        float weight = exp(-x * x / twoSigmaSq);
        color += texture2D(texture, texCoord + vec2(x / resolution.x, 0.0)) * weight;
        weightSum += weight;
    }
    gl_FragColor = color / weightSum;
}

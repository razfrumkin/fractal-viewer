#version 120

float map(float value, float initial_minimum, float initial_maximum, float target_minimum, float target_maximum) {
    return target_minimum + (value - initial_minimum) * (target_maximum - target_minimum) / (initial_maximum - initial_minimum);
}

vec2 map(vec2 value, vec2 initial_minimum, vec2 initial_maximum, vec2 target_minimum, vec2 target_maximum) {
    return vec2(map(value.x, initial_minimum.x, initial_maximum.x, target_minimum.x, target_maximum.x),
                map(value.y, initial_minimum.y, initial_maximum.y, target_minimum.y, target_maximum.y));
}

vec3 hsv_to_rgb(vec3 color)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(color.xxx + K.xyz) * 6.0 - K.www);
    return color.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), color.y);
}

#define MANDELBROT 0
#define TRICORN 1
#define BURNING_SHIP 2
#define JULIA 3

uniform ivec2 resolution;

uniform vec2 bottom_left;
uniform vec2 top_right;

uniform int iterations;

uniform int current_set;

uniform vec2 julia_complex;
uniform vec2 phoenix_complex;

uniform int color_repeatings;

uniform bool draw_rainbow;
uniform float saturation;
uniform float brightness;

uniform vec4 first_color;
uniform vec4 second_color;

int mandelbrot(vec2 complex) {
    vec2 result = vec2(0.0, 0.0);
    
    for (int total_iterations = 1; total_iterations <= iterations; total_iterations += 1) {
        vec2 squared = vec2(result.x * result.x - result.y * result.y, 2.0 * result.x * result.y);
        result = squared + complex;
        
        float distance_squared = result.x * result.x + result.y * result.y;
        
        if (distance_squared > 4.0) {
            return total_iterations;
        }
    }
    
    return iterations;
}

int tricorn(vec2 complex) {
    vec2 result = vec2(0.0, 0.0);
    
    for (int total_iterations = 1; total_iterations <= iterations; total_iterations += 1) {
        vec2 squared = vec2(result.x * result.x - result.y * result.y, 2.0 * result.x * -result.y);
        result = squared + complex;
        
        float distance_squared = result.x * result.x + result.y * result.y;
        
        if (distance_squared > 4.0) {
            return total_iterations;
        }
    }
    
    return iterations;
}

int burning_ship(vec2 complex) {
    vec2 result = vec2(0.0, 0.0);
    
    for (int total_iterations = 1; total_iterations <= iterations; total_iterations += 1) {
        vec2 squared = vec2(result.x * result.x - result.y * result.y, abs(2.0 * result.x * result.y));
        result = squared + complex;
        
        float distance_squared = result.x * result.x + result.y * result.y;
        
        if (distance_squared > 4.0) {
            return total_iterations;
        }
    }
    
    return iterations;
}

int julia(vec2 complex, vec2 julia, vec2 phoenix) {
    vec2 result = complex;

    for (int total_iterations = 1; total_iterations <= iterations; total_iterations += 1) {
        vec2 squared = vec2(result.x * result.x - result.y * result.y, 2.0 * result.x * result.y);
        result = squared + phoenix * result + julia;
        
        float distance_squared = result.x * result.x + result.y * result.y;
        
        if (distance_squared > 4.0) {
            return total_iterations;
        }
    }
    
    return iterations;
}

int get_iterations(int set_type, vec2 complex) {
    if (set_type == MANDELBROT) return mandelbrot(complex);
    if (set_type == TRICORN) return tricorn(complex);
    if (set_type == BURNING_SHIP) return burning_ship(complex * vec2(1.0, -1.0));
    if (set_type == JULIA) return julia(complex, julia_complex, phoenix_complex);
    return -1;
}

void main() {    
    vec2 complex = map(gl_FragCoord.xy, vec2(0.0, 0.0), vec2(resolution.xy), bottom_left, top_right);
    int total_iterations = get_iterations(current_set, complex);

    if (total_iterations == iterations) {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    float value = map(float(total_iterations), 1.0, float(iterations), 0.0, float(color_repeatings));

    if (draw_rainbow) {
        vec3 hsv = vec3(value, saturation, brightness);
        gl_FragColor = vec4(hsv_to_rgb(hsv), 1.0);
        return;
    }

    gl_FragColor = mix(first_color, second_color, mod(value, 1.0));
}
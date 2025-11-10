#pragma once

#include "ofMain.h"

//ray class
class ray {
public:
	ray() { }

	ray(const glm::vec3 & origin, const glm::vec3 & direction) : orig(origin), dir(glm::normalize(direction)) {}

	glm::vec3 getOrigin() const { return orig; }
	glm::vec3 getDirection() const { return dir; }

	// Function to get a point along the ray at distance t
	glm::vec3 at(float t) const {
		return orig + t * dir;
	}

private:
	glm::vec3 orig;
	glm::vec3 dir;
};

// materials
struct Material {
	ofColor color; // Base diffuse color
	float ka = 0.1; // Ambient coefficient
	float kd = 0.8; // Diffuse coefficient
	float ks = 0.5; // Specular coefficient
	float shininess = 80.0;
};

//sphere
struct sphere {
	glm::vec3 center;
	float radius;
	Material material;
};

// lighting
struct Light {
	glm::vec3 position;
	ofColor color;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//background image
		ofImage background;
		int bgW = 1600;
		int bgH = 900;

		//intersection logic
		ofColor ray_intersection_bg(const ray& r);
		float ray_intersection_sphere(const ray & r, const sphere& s);

		//camera
		glm::vec3 camOrigin;
		float viewportHeight;
		float viewportWidth;
		float focalLength;

		//lighting
		ofColor ambientLight;
		vector<Light> lights;

		//spheres
		vector<sphere> spheres;

		//shading logic
		ofColor shade(const ray & r, const sphere & hitSphere, float closest_t);
};

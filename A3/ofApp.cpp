#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//bg setup
	background.allocate(bgW, bgH, OF_IMAGE_COLOR);

	//camera setup
	camOrigin = glm::vec3(0, 0, 0);
	focalLength = 3.0;
	viewportHeight = 2.0;
	viewportWidth = viewportHeight * (double(bgW) / bgH);

	//spheres
	spheres.push_back(sphere { glm::vec3(-1.5, 0, -5), 1.0f, Material { ofColor::red, 0.1f, 0.9f, 0.1f, 10.0f } });
	spheres.push_back(sphere { glm::vec3(1.5, 0, -5), 1.0f, Material { ofColor::green, 0.1f, 0.7f, 1.0f, 120.0f } });
	spheres.push_back(sphere { glm::vec3(0, -101, -5), 100.0f, Material { ofColor::blue, 0.1f, 0.8f, 0.1f, 10.0f } });
	spheres.push_back(sphere { glm::vec3(0, 0.5, -3), 0.5f, Material { ofColor(200, 200, 200), 0.1f, 0.5f, 1.0f, 100.0f } });

	//lights
	ambientLight = ofColor(50, 50, 50);
	lights.push_back(Light { glm::vec3(-5, 5, -2), ofColor(255, 255, 255) });
	lights.push_back(Light { glm::vec3(5, 5, -2), ofColor(150, 150, 255) });

	//RT loop
	for (int y = 0; y < bgH; y++) {
		for (int x = 0; x < bgW; x++) {
			//pixel to viewport
			auto u = (float)x / (float)bgW;
			auto v = (float)y / (float)bgH;

			//ray coordinates
			float ray_x = (u - 0.5f) * viewportWidth;
			float ray_y = (0.5f - v) * viewportHeight;
			float ray_z = -focalLength;

			//direction vector
			glm::vec3 direction = glm::vec3(ray_x, ray_y, ray_z);

			//create ray
			ray r(camOrigin, direction);
			ofColor pixelColor;

			//sphere intersection logic
			float closest_t = std::numeric_limits<float>::infinity();
			bool hitSphere = false;
			sphere hit;
			for (const auto & s : spheres) {
				float t = ray_intersection_sphere(r, s);
				if (t > 0.0f) {
					hitSphere = true;
					if (t < closest_t) hit = s;
					closest_t = std::min(closest_t, t);
				}
			}
			if (hitSphere) {
				pixelColor = shade(r, hit, closest_t);
			} else {
				pixelColor = ray_intersection_bg(r);
			}

			//set pixel color on image
			background.setColor(x, y, pixelColor);
		}
	}

	//update image
	background.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());
}


ofColor ofApp::ray_intersection_bg(const ray& r) {
	glm::vec3 direction = r.getDirection();
	//ratio of linear interpolation
	auto a = 0.5f * (direction.y + 1.0f);
	ofColor topColor(106, 134, 232); // Blue
	ofColor bottomColor(255, 255, 240); // Yellow
	return bottomColor.getLerped(topColor, a);
}

float ofApp::ray_intersection_sphere(const ray & r, const sphere & s) {
	auto a = glm::dot(r.getDirection(), r.getDirection());
	auto b = -2 * glm::dot(r.getDirection(), (s.center - r.getOrigin()));
	auto c = glm::dot((s.center - r.getOrigin()), (s.center - r.getOrigin())) - (s.radius * s.radius);
	auto discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0) {
		return -1.0f;
	} else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

ofColor ofApp::shade(const ray & r, const sphere & hitSphere, float closest_t) {
	const Material & mat = hitSphere.material;

	//various variables for light calculations
	glm::vec3 P = r.at(closest_t);
	glm::vec3 N = glm::normalize(r.at(closest_t) - hitSphere.center);
	glm::vec3 V = glm::normalize(camOrigin - P);

	//ambient
	ofColor ambient = mat.color * ambientLight * mat.ka;
	ofColor totalColor = ambient;

	//diffuse and specular
	for (const Light & light : lights) {
		glm::vec3 L = glm::normalize(light.position - P);

		//shadow ray
		ray shadowRay(P + N * 0.001f, L);
		bool inShadow = false;
		float distToLight = glm::distance(P, light.position);

		//check for shadows
		for (const sphere& s : spheres) {
			if (&s == &hitSphere) continue;

			float t_shadow = ray_intersection_sphere(shadowRay, s);

			if (t_shadow > 0.0f && t_shadow < distToLight) {
				inShadow = true;
				break;
			}
		}

		//if not in shadow add diffuse and specular
		if (!inShadow) {
			ofColor diffuse = max(0.0f, glm::dot(N, L)) * mat.color * mat.kd * light.color;

			glm::vec3 R = glm::reflect(-L, N);
			ofColor specular = pow(max(0.0f, glm::dot(V, R)), mat.shininess) * mat.ks * light.color;

			//calculating total color for the light
			totalColor += diffuse + specular;
		}
	}

	totalColor.clamp();
	return totalColor;
}

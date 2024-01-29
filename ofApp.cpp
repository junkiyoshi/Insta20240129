#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float span = 0.5;
	ofColor color;
	for (int i = 0; i < 5; i++) {

		ofMesh mesh;

		auto noise_seed = ofRandom(1000);
		for (float x = 30; x < 690; x += span) {

			for (float y = 30; y < 690; y += span) {

				float noise_value = ofNoise(noise_seed, x * 0.0005, y * 0.0005, glm::distance(glm::vec2(360, 360), glm::vec2(x, y)) * 0.003 - ofGetFrameNum() * 0.02);
				if ((noise_value > 0.55 && noise_value < 0.6)) {

					mesh.addVertex(glm::vec3(x, y, 0));
					mesh.addVertex(glm::vec3(x + span, y, 0));
					mesh.addVertex(glm::vec3(x + span, y + span, 0));
					mesh.addVertex(glm::vec3(x, y + span, 0));

					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 4); mesh.addIndex(mesh.getNumVertices() - 3);
					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);

					color.setHsb(ofMap(i, 0, 5, 0, 255), 230, 255);
					for (int i = 0; i < 4; i++) {

						mesh.addColor(color);
					}
				}
			}
		}

		mesh.draw();
	}

	/*
	int start = 200;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
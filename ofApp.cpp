#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("openFrameworks");

	ofNoFill();
	ofSetColor(39);
	ofSetLineWidth(2);

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	auto word = "PCD TOKYO 2020 !";
	auto base_location = glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word) * 0.5, this->font_size + 10);
	auto param = ofGetFrameNum();

	while (base_location.y < ofGetHeight()) {

		int sample_count = 180;
		vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);
		for (int word_index = 0; word_index < word_path.size(); word_index++) {

			vector<ofPolyline> outline = word_path[word_index].getOutline();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
				vector<glm::vec3> vertices = outline[outline_index].getVertices();

				ofBeginShape();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = base_location + vertices[vertices_index];

					if (param % (sample_count * 2) < sample_count) {

						if (vertices_index < param % sample_count) {

							ofVertex(location);
						}
					}
					else {

						if (vertices_index > param % sample_count) {

							ofVertex(location);
						}
					}

					if (vertices_index == param % sample_count) {

						ofDrawCircle(location, 3);
					}

				}
				ofEndShape();
			}

			param += sample_count / 3;
		}

		base_location += glm::vec2(0, this->font_size + 20);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
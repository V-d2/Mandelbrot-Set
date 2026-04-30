#include "ComplexPlane.h"





ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixelSize = { pixelWidth, pixelHeight }; // pixel size is the size of the window in pixels, it is used to map the pixels to the complex plane
	m_aspectRatio = (float)pixelHeight / (float)pixelWidth; // aspect ratio is the ratio of the height to the width of the window, it is used to maintain the correct aspect ratio of the complex plane when zooming in and out
	m_plane_center = { 0.0f, 0.0f }; // initial center of the complex plane
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio }; // initial size of the complex plane, it is used to determine the range of the complex plane that is currently being displayed
	m_zoom_Count = 0; // initial zoom count
	m_state = State::CALCULATING; // initial state of the complex plane, it is used to determine whether the complex plane is currently being calculated or displayed
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(m_pixelSize.x * m_pixelSize.y); // resize the vertex array to the number of pixels in the window, it is used to store the color of each pixel in the complex plane
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_vArray, states); // draw the vertex array to the screen, it is used to display the complex plane
}

void ComplexPlane::zoomIn() {
	m_zoom_Count++;
	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoom_Count); // calculate the new width of the complex plane based on the zoom count, it is used to determine the new size of the complex plane when zooming in
	float y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoom_Count) * m_aspectRatio; // calculate the new height of the complex plane based on the zoom count and aspect ratio, it is used to maintain the correct aspect ratio of the complex plane when zooming in
	m_plane_size = Vector2f(x,y); // set the new size of the complex plane
	m_state = State::CALCULATING; // set the state to calculating after zooming in, it is used to trigger the recalculation of the complex plane when zooming in
}

void ComplexPlane::zoomOut() {
		m_zoom_Count--;
		float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoom_Count); // calculate the new width of the complex plane based on the zoom count, it is used to determine the new size of the complex plane when zooming in
		float y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoom_Count) * m_aspectRatio; // calculate the new height of the complex plane based on the zoom count and aspect ratio, it is used to maintain the correct aspect ratio of the complex plane when zooming in
		m_plane_size = Vector2f(x, y); // set the new size of the complex plane
		m_state = State::CALCULATING; // set the state to calculating after zooming in, it is used to trigger the recalculation of the complex plane when zooming in
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
	m_plane_center = ComplexPlane::mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
	m_mouseLocation  = ComplexPlane::mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text){
	stringstream ss;
	ss << "Mandelbrot Set \n";
	ss << "Center:" << m_plane_center.x << ", " << m_plane_center.y << "\n";
	ss << "Cursor:" << m_mouseLocation.x << ", " << m_mouseLocation.y << "\n";
	ss << "Left-click to Zoom in\n";
	ss << "Right-click to Zoom out\n";
	text.setString(ss.str());
}

void ComplexPlane::updateRender() {
	if (m_state == State::CALCULATING) {
		for (int i = 0; i < m_pixelSize.y; i++) {
			for (int j = 0; j < m_pixelSize.x; j++) {
				m_vArray[j + i * m_pixelSize.x].position = { (float)j,(float)i };
				Vector2f coord = ComplexPlane::mapPixelToCoords(Vector2i(j, i));
				size_t it = countIterations(coord);
				Uint8 r, g, b;
				iterationsToRGB(it, r, g, b); // convert the number of iterations to a color, it is used to determine the color of the pixel based on the number of iterations it takes for the corresponding point in the complex plane to escape
			    m_vArray[j + i * m_pixelSize.x].color = { r, g, b };
			}
		}
		m_state = State::DISPLAYING; // set the state to displaying after calculating the colors of all pixels	
	}
}


size_t ComplexPlane::countIterations(Vector2f coord){
	size_t count = 0;

	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {

	return { 0.0f, 0.0f };
}
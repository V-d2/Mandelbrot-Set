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
	ss << "z: " << m_z;
	text.setString(ss.str()); // set the string of the text object to the stringstream, it is used to display the information about the complex plane on the screen

}

void ComplexPlane::updateRender() {
	//cout << "pixel size: " << m_pixelSize.x << "x" << m_pixelSize.y << " state" << (int)m_state << endl;
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


size_t ComplexPlane::countIterations(Vector2f coord) { // the coord is the coordinates of the pixel in the complex plane, it is used to determine the corresponding point in the complex plane for the pixel
	int i = 0;
	complex<float> c(coord.x, coord.y); // create a complex number from the coordinates of the pixel, it is used to represent the corresponding point in the complex plane
	complex<float> z(0, 0); 
	while (abs(z) < 2.0 && i < MAX_ITER) // the loop begins with z = 0, so at least one iteration.
	{
		z = z * z + c;
		i++; // the last iteraton makes the i == MAX_ITER
	}
	return i;
}

void ComplexPlane::iterationsToRGB(size_t iteration, Uint8& r, Uint8& g, Uint8& b) {
	if (iteration == MAX_ITER) {
		r = 0;
		g = 0;
		b = 0;
	}
	else {
		float percent = (float)iteration / MAX_ITER; // calculate the percentage of numbers iterations from 0 to MAX_ITER.  iteration begin with 1
		r = (9 * (1 - percent) * percent * percent * percent * 255);
		//r = 2 * -(pow(percent - 1, 2) - 1 / 2.0) * 255;
		
		g = (15 * (1 - percent) * (1 - percent) * percent * percent * 255);
		
		b = (9 * (1 - percent) * (1 - percent) * (1 - percent) * percent * 255);
		//b = 2 * -(pow(percent, 2) - 1 / 2.0) * 255;
		
	}
}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	float xPercent = (float)mousePixel.x / m_pixelSize.x; // calculate the percentage of the x coordinate of the mouse pixel relative to the width of the window, it is used to map the x coordinate of the mouse pixel to the corresponding x coordinate in the complex plane//
	float yPercent = (float)mousePixel.y / m_pixelSize.y; // calculate the percentage of the y coordinate of the mouse pixel relative to the height of the window, it is used to map the y coordinate of the mouse pixel to the corresponding y coordinate in the complex plane, it is subtracted from 1 because the y coordinate of the mouse pixel is measured from the top of the window, while the y coordinate of the complex plane is measured from the bottom of the window

	float x = m_plane_center.x - m_plane_size.x / 2 + xPercent * m_plane_size.x;
	float y = m_plane_center.y - m_plane_size.y / 2 + yPercent * m_plane_size.y;

	return Vector2f(x, y);
}
#pragma once
#include "Line2D.h"
#include "Point2D.h"
#include <GLFW/glfw3.h>

class Draw {
public:
	Draw();
	Draw(const Draw&) = delete;
	Draw(Draw&&) = delete;
	Draw& operator=(const Draw&) = delete;
	Draw& operator=(Draw&&) = delete;
	~Draw();
	void AddScaledPoint2D(const Point2D& point);
	void AddScaledLine2D(const Line2D& line);
	bool ShouldWindowClosePoll();

private:
	GLFWwindow& m_window;
};
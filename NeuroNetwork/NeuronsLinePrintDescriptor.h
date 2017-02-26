#pragma once

#include"TypeDefines.h"
#include <iostream>
struct NeuronsLinePrintDescriptor
{
	const neurons_line &_line;
	const size_t _width;
	const size_t _height;

	NeuronsLinePrintDescriptor(const neurons_line &line, size_t width, size_t height);

};

std::ostream & operator << (std::ostream & _o, const NeuronsLinePrintDescriptor &line);
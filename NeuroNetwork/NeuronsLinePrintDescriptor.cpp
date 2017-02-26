#include "NeuronsLinePrintDescriptor.h"



NeuronsLinePrintDescriptor::NeuronsLinePrintDescriptor(const neurons_line & line, size_t width, size_t height)
	: _line(line), _width(width), _height(height) 
{}


std::ostream & operator<<(std::ostream & _o, const NeuronsLinePrintDescriptor & _line)
{
	neurons_line::const_iterator it = begin(_line._line), it_end = end(_line._line);

	for (size_t i = 0; i < _line._height; ++i)
	{
		for (size_t j = 0; j < _line._width; ++j)
		{
			if (*it > 0)
				std::cout << " ";
			else
				std::cout << "0";
			++it;
		}
		std::cout << std::endl;
	}

	return _o;
}

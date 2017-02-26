#pragma once

#include <algorithm>
#include <numeric>
#include "TypeDefines.h"

struct NeuroNetSystem
{
	const link_koefs &_koefs;
	size_t _steps_processed;

	NeuroNetSystem(const link_koefs &koefs);

	bool Execute(neurons_line *line);

	neurons_line* operator () (neurons_line *line);
};

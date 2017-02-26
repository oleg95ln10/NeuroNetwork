#pragma once

#include <iostream>
#include <list>
#include <numeric>
#include <fstream>
#include "TypeDefines.h"


link_koefs LearnNeuroNet(const std::list<neurons_line> &src_images);

neurons_line read_neurons_state(const std::string &file_path, size_t len);
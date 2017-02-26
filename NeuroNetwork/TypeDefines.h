#pragma once

#include "NeuronState.h"
#include <vector>

typedef float koef_t; // Вес нейрона
typedef std::vector<neuron_state> neurons_line;// Состояние сети в момент t
typedef std::vector<std::vector<koef_t>> link_koefs;// Матрица весовых коэффициентов связей нейронов
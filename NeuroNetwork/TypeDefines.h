#pragma once

#include "NeuronState.h"
#include <vector>

typedef float koef_t; // ��� �������
typedef std::vector<neuron_state> neurons_line;// ��������� ���� � ������ t
typedef std::vector<std::vector<koef_t>> link_koefs;// ������� ������� ������������� ������ ��������
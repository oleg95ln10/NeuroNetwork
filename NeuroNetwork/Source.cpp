#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <fstream>

using std::begin;
using std::end;

using std::cout;
using std::endl;

using std::vector;
using std::list;

enum neuron_state { LOWER_STATE = -1, UPPER_STATE = 1 };
typedef float koef_t;
typedef vector<neuron_state> neurons_line;
typedef vector<vector<koef_t>> link_koefs;

struct neuro_net_system 
{
	const link_koefs &_koefs;
	size_t _steps_processed;

	neuro_net_system(const link_koefs &koefs) : _koefs(koefs) {}

	bool Execute(neurons_line *line) 
	{
		bool value_changed = false;

		neurons_line old_values(begin(*line), end(*line));
		link_koefs::const_iterator it_koefs = begin(_koefs);

		std::transform(
			begin(*line),
			end(*line),
			begin(*line),
			[&old_values, &it_koefs, &value_changed](neuron_state old_value) -> neuron_state {
			koef_t tmp_val = std::inner_product(
				begin(old_values),
				end(old_values),
				begin(*it_koefs++),
				koef_t(0)
			);
			neuron_state new_value = (tmp_val > 0 ? UPPER_STATE : LOWER_STATE);
			value_changed = (new_value != old_value) || value_changed;

			return new_value;
		});

		return value_changed;
	}

	neurons_line* operator () (neurons_line *line)
	{
		bool need_continue = true;
		_steps_processed = 0;

		while (need_continue) 
		{
			need_continue = Execute(line);
			++_steps_processed;
		}

		return line;
	}
};

link_koefs LearnNeuroNet(const list<neurons_line> &src_images)
{
	link_koefs result_koefs;
	size_t neurons_count = src_images.front().size();

	result_koefs.resize(neurons_count);
	for (size_t i = 0; i < neurons_count; ++i)
	{
		result_koefs[i].resize(neurons_count, 0);
	}

	for (size_t i = 0; i < neurons_count; ++i) {
		for (size_t j = 0; j < i; ++j) {
			koef_t val = 0;
			val = std::accumulate(begin(src_images), end(src_images), koef_t(0.0), [i, j](koef_t old_val, const neurons_line &image) -> koef_t {
				return old_val + (image[i] * image[j]);
			});
			result_koefs[i][j] = val;
			result_koefs[j][i] = val;
		}
	}

	return result_koefs;
}

struct neurons_line_print_descriptor 
{
	const neurons_line &_line;
	const size_t _width;
	const size_t _height;

	neurons_line_print_descriptor(const neurons_line &line, size_t width, size_t height) : _line(line), _width(width), _height(height) {}
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& operator << (std::basic_ostream<Ch, Tr>&stm, const neurons_line_print_descriptor &line)
{
	neurons_line::const_iterator it = begin(line._line), it_end = end(line._line);

	for (size_t i = 0; i < line._height; ++i)
	{
		for (size_t j = 0; j < line._width; ++j) 
		{
			if (*it > 0)
				cout << " ";
			else
				cout << "0";
			++it;
		}
		cout << endl;
	}

	return stm;
}

neurons_line read_neurons_state(const std::string &file_path, size_t len) 
{
	std::ifstream i_file(file_path);

	size_t i = 0;
	neurons_line result;
	result.reserve(len);

	while (i++ < len)
	{
		char val;
		i_file >> val;
		neuron_state state = (val == '0' ? LOWER_STATE : UPPER_STATE);
		result.push_back(state);
	}

	return result;
}

int main(int argc, char* argv[])
{
	list<neurons_line> src_images;
	std::string target_file_path;
	size_t width, height;


	width = 10;
	height = 10;
	target_file_path = "src.txt";
	
	
	src_images.push_back(read_neurons_state("t.txt", width * height));
	cout << "learning image: " << endl;
	cout << neurons_line_print_descriptor(src_images.back(), width, height) << endl;
	
	src_images.push_back(read_neurons_state("k.txt", width * height));
	cout << "learning image: " << endl;
	cout << neurons_line_print_descriptor(src_images.back(), width, height) << endl;



	link_koefs koefs = LearnNeuroNet(src_images);

	neuro_net_system net(koefs);

	neurons_line line;
	line = read_neurons_state(target_file_path, width * height);

	cout << "start: " << endl;
	cout << neurons_line_print_descriptor(line, width, height) << endl;
	cout << "---------------------------" << endl;

	net(&line);
	cout << neurons_line_print_descriptor(line, width, height) << endl;
	cout << "---------------------------" << endl;

	return 0;
}
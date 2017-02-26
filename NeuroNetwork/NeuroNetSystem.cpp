#include "NeuroNetSystem.h"



NeuroNetSystem::NeuroNetSystem(const link_koefs &koefs)
	: _koefs(koefs)
{}

bool NeuroNetSystem::Execute(neurons_line * line)
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

neurons_line * NeuroNetSystem::operator()(neurons_line * line)
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

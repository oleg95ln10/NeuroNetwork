#include "MyNeuroNetwork.h"

link_koefs LearnNeuroNet(const std::list<neurons_line> &src_images)
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
			val = std::accumulate(begin(src_images), end(src_images),
				koef_t(0.0), [i, j](koef_t old_val, const neurons_line &image) -> koef_t {
				return old_val + (image[i] * image[j]);
			});
			result_koefs[i][j] = val;
			result_koefs[j][i] = val;
		}
	}

	return result_koefs;
}
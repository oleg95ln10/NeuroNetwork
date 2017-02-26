#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "NeuronState.h"
#include "NeuroNetSystem.h"
#include "MyNeuroNetwork.h"
#include "NeuronsLinePrintDescriptor.h"


using std::cout;
using std::endl;
using std::list;

int main()
{
	list<neurons_line> src_images;
	std::string target_file_path;
	size_t width, height;

	width = 10;
	height = 10;
	target_file_path = "src.txt";	
	
	src_images.push_back(read_neurons_state("TrainingData/t.txt", width * height));
	cout << "learning image: " << endl;
	cout << NeuronsLinePrintDescriptor(src_images.back(), width, height) << endl;
	
	src_images.push_back(read_neurons_state("TrainingData/k.txt", width * height));
	cout << "learning image: " << endl;
	cout << NeuronsLinePrintDescriptor(src_images.back(), width, height) << endl;
	
	link_koefs koefs = LearnNeuroNet(src_images);

	NeuroNetSystem neuroNetSystem(koefs);

	neurons_line line = read_neurons_state(target_file_path, width * height);

	cout << "start: " << endl;
	cout << NeuronsLinePrintDescriptor(line, width, height) << endl;
	cout << "---------------------------" << endl;

	neuroNetSystem(&line);
	cout << NeuronsLinePrintDescriptor(line, width, height) << endl;
	cout << "---------------------------" << endl;

	return 0;
}
#pragma once

#include "Sunrise.h"

using namespace sunrise::dependency;

using TestOptions = emptyTuple;

class Math1 : public Stage<tuple<>, tuple<int*>, TestOptions> {

	using In =  tuple<>;
	using Out = tuple<int*>;

	Out run(In inputs, TestOptions options) override {
		return { new int(sqrt(3200000000000)) };
	}

};

class Math2 : public Stage<tuple<int*>, tuple<int*>, TestOptions> {

	using In =  tuple<int*>;
	using Out = tuple<int*>;

	Out run(In inputs, TestOptions options) override {

		auto input = std::get<0>(inputs);

		return { new int(pow(2,*input)) };
	}

};



void func() {

	//todo: should to be able to link an output to another input without creating a reasource to link between.so the reasource can be created by the dispatcehr or the stage which outputs the value

	auto dispatcher = new Dispatcher<tuple<int*>, tuple<>,TestOptions>();

	auto m1 = new Math1();
	auto m2 = new Math2();

	int* runningNumber = new int(0);
	int* outputNumber = new int(0);

	dispatcher->registerStageOutputs(m1, runningNumber);

	dispatcher->registerStageInputs(m2, runningNumber);
	dispatcher->registerStageOutputs(m2, outputNumber);

	dispatcher->run();

	// should be able to read output from

}


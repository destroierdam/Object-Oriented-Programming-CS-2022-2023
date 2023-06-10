#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <chrono>

namespace mine {
	using distance_t = float;
	using vel_t = float;
	using max_acc_t = float;
	using acc_t = float;
	using time_t = float;

	using data_res_t = std::pair<distance_t, max_acc_t>;
	using data_t = std::pair<vel_t, time_t>;

	data_res_t calcStats(std::vector<data_t> data) {
		distance_t distance = 0;
		max_acc_t max_acc = 0;

		for (std::size_t i = 1; i < data.size(); ++i) {
			vel_t dv = data[i].first - data[i - 1].first;
			time_t dt = data[i].second - data[i - 1].second;
			distance_t dS = (data[i - 1].first + data[i].first) * 0.5f * dt;
			distance += dS;
			acc_t acc = dv / dt;
			max_acc = std::max(max_acc, std::abs(acc));
		}
		return std::make_pair(distance, max_acc);
	}
}

namespace VCC {
	namespace BBB {
		using acc_t = double;
	}
}
#define logdebug(x) std::cerr << __FILE__ << ":" << __LINE__ << " " << x << "\n"
#define loginfo(x) std::cerr << __FILE__ << ":" << __LINE__ << " " << x << "\n"
#define logerr(x) std::cerr << __FILE__ << ":" << __LINE__ << " " << x << "\n"

int main() {
	loginfo("Program started");

	using namespace mine;
	std::vector<mine::data_t> data = {
		{10.f, 0.f},
		{11.f, 1.f},
		{15.f, 2.f},
		{50.f, 5.f}
	};
	VCC::BBB::acc_t asd;

	// std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
	auto nowTime = std::chrono::high_resolution_clock::now();
	
	try {
		throw std::runtime_error("WAT");
	}
	catch (std::exception& err) {
		logerr(err.what());
	}

	mine::data_res_t result = mine::calcStats(data);
	
	std::cout << "Distance:         " << std::setw(7) << result.first << std::endl;
	std::cout << "Max Acceleration: " << std::setw(7) << std::setprecision(6) << result.second << std::endl;
}
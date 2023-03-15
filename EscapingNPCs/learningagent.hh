#ifndef LEARNINGAGENT_HH
#define LEARNINGAGENT_HH

#include <vector>
#include <random>

const int NUM_EPISODES = 1000;
const int STATE_SIZE = 10;
const int ACTION_SIZE = 4;
const double ALPHA = 0.1;
const double GAMMA = 0.99;


class LearningAgent
{
public:
    LearningAgent();

    int get_action(int state);

    int get_best_action(int state);

    void update_q_value(int state, int action, int next_state, double reward);

    double get_max_q_value(int state);

    void set_epsilon(double epsilon);

private:
    std::vector<std::vector<double>> q_values_;
    std::default_random_engine generator_;
    std::uniform_real_distribution<> rand_dist_;
    double epsilon_ = 0.1;

};

#endif // LEARNINGAGENT_HH
